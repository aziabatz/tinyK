#include <mem/virt/vm_mgr.h>
#include <mem/heap/heap.h>
#include <assert.h>
#include <debug.h>
#include <printf.h>

static heap_t * heap = NULL;

heap_t * init_kheap(pg_dir_t * dir, page_flags_t flags)
{
    if(heap == NULL)
    {
        assert(heap = (heap_t *)vm_map_page(dir, flags));
        heap_block_t * head_block;
        heap->flags = flags;
        head_block->next = NULL;
        head_block->prev = NULL;
        head_block->used = false;
        head_block->mark = HEAP_BLOCK_MARK;
        head_block->base = (uintptr_t)heap + sizeof(heap_t) + sizeof(heap_block_t);
        head_block->length = ((uintptr_t)heap+0x1000) - head_block->base;

        heap->head = head_block;
        
        kinfo(INFO, "Heap allocated");
        kprintf("Heap address: %x\n"
                "Heap 1st block:\n"
                "\tbase: %x\n"
                "\tlength: %u\n",
                heap, heap->head->base,
                heap->head->length);
    }
}