#include <mem/virt/vm_mgr.h>
#include <mem/heap/heap.h>
#include <assert.h>
#include <debug.h>
#include <printf.h>
#include <mem.h>

heap_t * init_kheap(pg_dir_t * dir, page_flags_t flags)
{
    heap_t * heap = NULL;
    assert(heap = (heap_t *)vm_map_page(dir, flags));
    //heap_block_t * head_block = (uintptr_t)heap + sizeof(heap_t);
    heap_block_t * head_block = (heap_block_t*)((uintptr_t)heap + sizeof(heap_t));
    heap->flags = flags;
    head_block->next = NULL;
    head_block->prev = NULL;
    head_block->used = false;
    head_block->mark = HEAP_BLOCK_MARK;
    head_block->base = (uintptr_t)head_block + sizeof(heap_block_t);
    head_block->length = ((uintptr_t)heap+0x1000) - head_block->base;



    heap->head = head_block;
    
    kinfo(INFO, "Heap allocated");
    kprintf("Heap address: %x\n"
            "Heap 1st block:\n"
            "\tbase: %x\n"
            "\tlength: %u\n",
            heap,
            heap->head->base,
            heap->head->length);

    return heap;
}

/* virt_t kmalloc(heap_t * heap,size_t size)
{
    assert(heap != NULL);

    heap_block_t * first_fit = NULL;
    
    virt_t address = NULL;

    for(heap_block_t * temp = heap->head;
        temp && !first_fit;
        temp = temp->next)
    {
        if(!temp->used)
        {
            if(temp->length >= size + sizeof(heap_block_t))
            {
                first_fit = temp;
            }
        }
    }

    if(first_fit)
    {
        heap_block_t * temp = first_fit + size + sizeof(heap_block_t);
        temp->used = false;
        temp->length = first_fit->length - size - sizeof(heap_block_t);
        temp->prev = first_fit;
        temp->next = first_fit->next;
        if(temp->next != NULL)
        {
            temp->next->prev = temp;
        }


        first_fit->length = size;
        first_fit->next = temp;
        first_fit->used = true;
        address = first_fit->base = (uintptr_t) first_fit + sizeof(heap_block_t);

    }



    return address;
}*/

static heap_block_t *split_block(heap_block_t *block, size_t size)
{
    assert(block != NULL && (block->length >= (size + sizeof(heap_block_t))));

    // Crear un nuevo bloque en la dirección de memoria correspondiente
    heap_block_t *new_block = (block->base + size);
    
    // Establecer los atributos del nuevo bloque
    new_block->mark = HEAP_BLOCK_MARK;
    new_block->used = false;
    new_block->length = block->length - size - sizeof(heap_block_t);
    new_block->prev = block;
    new_block->next = block->next;
    new_block->base = new_block + sizeof(heap_block_t);
    if (new_block->next != NULL) {
        new_block->next->prev = new_block;
    }

    return new_block;
}

void merge_blocks(heap_block_t* first_block, heap_block_t* second_block)
{
    
}

static inline heap_block_t * move_heap_block(heap_block_t * prev_block, size_t size, size_t remaining)
{
    heap_block_t * new_block = memcpy((uintptr_t)prev_block->base+size, prev_block->next, sizeof(heap_block_t));
    //new_block->base = (uintptr_t)new_block + sizeof(heap_block_t);
    new_block->base = (virt_t)((uintptr_t)new_block + sizeof(heap_block_t));
    new_block->length += remaining;
    new_block->mark = HEAP_BLOCK_MARK;
    new_block->prev = prev_block;
    new_block->used = false;

    return new_block;
}


virt_t kmalloc(heap_t * heap, size_t size)
{
    assert(heap != NULL);

    heap_block_t * first_fit = NULL;
    virt_t address = NULL;

    if (!size)
    {
        kinfo(WARNING, "Trying to allocate 0-sized block");
        return NULL;
    }
    

    for (heap_block_t * temp = heap->head; temp && !first_fit; temp = temp->next)
    {
        if (!temp->used && temp->length >= size)
        {
            first_fit = temp;
        }
    }

    if (first_fit)
    {
        
        if(first_fit->length == size)
        {
            //Solo marcar como usado y devolver la direccion
            first_fit->used = true;
        }
        else
        {
            size_t remaining_length = (first_fit->length - size);
            heap_block_t * new_block;

            if(remaining_length <= sizeof(heap_block_t))
            {
                //Es un bloque vacio o no hay espacio para bloque, hay que fusionar
                //Desplazar info del siguiente bloque hacia atras y añadir tamaño

                //Solo si el siguiente bloque esta libre
                if(!first_fit->next->used)
                {
                    //El siguiente bloque esta libre, se puede unir
                    new_block = move_heap_block(first_fit, size, remaining_length);
                }
            }
            else
            {
                //crear nuevo bloque
                new_block = split_block(first_fit, size);
            }

            first_fit->length = size;
            first_fit->next = new_block;
            first_fit->used = true;
            first_fit->base = (virt_t)((uintptr_t)first_fit + sizeof(heap_block_t));
        }

    }
    return first_fit->base;
}

bool kfree(heap_t * heap, virt_t address)
{
    assert(heap);

    heap_block_t * found = NULL;
    
    for(heap_block_t * temp = heap->head; temp && !found && temp->base <= address; temp = temp->next)
    {
        if(temp->base == address)
        {
            found = temp;
        }
    }

    if(!found)
    {
        kinfo(ERROR, "kfree cannot find chunk to be freed!");
        return false;
    }

    assert(found->mark == HEAP_BLOCK_MARK);
    kprintf("base: 0%x found+block: 0x%x|| found: 0%x size: %xh\n", found->base, found + sizeof(heap_block_t), found, sizeof(heap_block_t));
    virt_t base = found->base;
    virt_t block_base_offset = found;
    block_base_offset += sizeof(heap_block_t);
    assert(base == block_base_offset);

    heap_block_t * prev = found->prev;
    heap_block_t * next = found->next;


    // TODO Mejorar if-else

    //Ambos libres
    if((prev && !prev->used) && (next && !next->used))
    {
        prev->length = prev->length + found->length + next->length + (2 * sizeof(heap_block_t));
        next->prev = prev;
        prev->next = next;
    }
    else
    {
        //Solo el anterior esta libre
        if(prev && !prev->used)
        {
            prev->length += found->length + sizeof(heap_block_t);
            prev->next = found->next;
            found->next->prev = prev;
        }
        //Solo el siguiente esta libre
        else if(next && !next->used)
        {
            found->length += next->length + sizeof(heap_block_t);
            found->next = next->next;

            found->prev->next = found;
            found->next->prev = found;
        }
        //No hay bloques adyacentes libres
        else
        {
            found->used = false;
        }
    }

    found = NULL;
    
    return true;
}