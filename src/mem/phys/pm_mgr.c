/**
 * \file pm_mgr.c
 * \date Saturday, January 28th 2023, 3:03:06 pm
 * \author Ahmed Ziabat Ziabat
 *
 *
 * BSD 3-Clause License
 *
 * \copyright Copyright (c) 2023, Ahmed Ziabat Ziabat aziabatz@alumnos.unex.es
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * \brief Fichero fuente para el manejador de memoria fisica
 */

#include <types.h>
#include <mem/phys/pm_mgr.h>
#include <printf.h>
#include <mem.h>
#include <mem/virt/paging.h>
#include <mem/virt/vm_mgr.h>
#include <mem/phys/pm_map.h>
#include <stdbool.h>
#include <debug.h>
#include <assert.h>


static pm_mgr_t pm_manager;
extern const uint32 end;

uint32 freed_blocks = 0;

#define SUPERBLOCK_OF(p)         (p/BLOCKS_PER_BYTE)
#define OFFSET_OF(p)        (p%BLOCKS_PER_BYTE)

static inline void free_block(uint32 block)
{
    // Prohibido liberar el bloque 0
    if(!block)
    {
        kinfo(WARNING, "Freeing physical page 0 is not possible");
        return;
    }
    
    uint32 idx = SUPERBLOCK_OF(block);
    // Mascara de 0 únicamente del bloque que queremos
    pm_manager.bitmap[idx] &= ~(1 << OFFSET_OF(block));
    pm_manager.free_blocks++;
    freed_blocks++;
}

static inline void use_block(uint32 block)
{
    uint32 idx = SUPERBLOCK_OF(block);
    pm_manager.bitmap[idx] |= 1 << OFFSET_OF(block);
    pm_manager.free_blocks--;
}

static inline bool status_block(uint32 block)
{
    uint32 idx = SUPERBLOCK_OF(block);
    uint8 superblock = pm_manager.bitmap[idx];
    return (superblock & (1 << OFFSET_OF(block)));
}

void pm_mgr_free(phys_t address)
{
    // Si la direccion no esta alineada, ERROR y ALINEAR?
    kprintf("%x", address);
    assert(PG_ALIGNED_4K(address));
    free_block(address/BLOCK_SIZE);
}



static uint32 first_fit(size_t pages)
{
    //No podemos reservar 0 paginas
    assert(pages);

    //No podemos reservar mas memoria de la disponible
    assert(pages <= pm_manager.free_blocks);

    size_t free_found = 0;
    size_t testing_bit = 0;

    size_t total_blocks = BLOCKS_PER_BYTE * pm_manager.bitmap_length;

    size_t total_libre = 0;

    for(size_t block = 0; block < total_blocks; block++)
    {
        if(status_block(block) == BLOCK_FREE)
        {
            if(free_found == 0)
            {
                testing_bit = block;
            }
            free_found++;
            total_libre++;
        }
        else
        {
            //No sirve, empezar a contar de nuevo
            if(free_found)
                kprintf("Max bloques contiguos %d\n", free_found);
            free_found = 0;
        }

        if(free_found == pages)
        {
            return testing_bit;
        }
    }
    kprintf("Max bloques libres %d\n", total_libre);
    return NULL;
}

phys_t pm_mgr_alloc(size_t pages)
{
    bool best_fit = (freed_blocks >= (pm_manager.bitmap_length/2)) ? true : false;

    // Recibimos el bloque valido si existe
    uint32 block = first_fit(pages);
    // Comprobar que se han satisfecho los bloques
    assert(block);

    //Ahora que tenemos suficiente espacio marcamos como usados los bloques
    for(size_t page = 0; page < pages; page++)
    {
        use_block(block+page);
    }

    return block*BLOCK_SIZE;
}

static inline load_region(phys_t base, size_t length, uint8 type)
{
    // bloque donde empieza la region
    phys_t start = base / BLOCK_SIZE;
    // numero de bloques del tamaño de la region
    size_t number_of_blocks = length / BLOCK_SIZE;

    for(int block = start; block < number_of_blocks; block++)
    {
        if(type == MULTIBOOT_MEMORY_AVAILABLE ||
            type == MULTIBOOT_MEMORY_ACPI_RECLAIMABLE)
        {
            free_block(block);
        }
    }
}

static inline virt_t map_to_dir(pg_dir_t * dir, phys_t paddr, virt_t vaddr, page_flags_t flags)
{
    uint16 pde = PG_PDE_IDX(vaddr);
    uint16 pte = PG_PTE_IDX(vaddr);

    pg_table_t * table = dir->tables[pde];
    if((!table && PG_PTE_PRESENT))
    {
        kinfo(ERROR, "Page Table not present. NOT IMPLEMENTED");
        kprintf("virt: 0x%x\n", vaddr);
        
        __stop();
    }

    //limpiar flags de la direccion
    table = ((uintptr_t)table) & ((uintptr_t)PG_PDE_FRAME);

    table->pages[pte] = paddr & PG_PTE_FRAME | (flags & PG_ENTRY_FLAGS);

    //acceder a la posicion en PD
    //si la tabla no esta presente
        //crear tabla
    //acceder a la posicion en PT
    //paginar direccion fisica
    //escribir flags 
    
    return vaddr & PG_PTE_FRAME;
}

void * pm_mgr_init(multiboot_memory_map_t *mb_map, size_t memory_size, pg_dir_t *dir)
{
    //&end;//esto es end

    // Total de memoria en bytes
    size_t mem_size_bytes = memory_size * 1024;
    size_t number_of_blocks = mem_size_bytes / BLOCK_SIZE;

    // bitmap_length es la longitud del vector en bytes
    pm_manager.bitmap_length = number_of_blocks / BLOCKS_PER_BYTE;

    // indicamos que toda la memoria esta en uso
    pm_manager.free_blocks = 0;
    // situamos el mapa de bits al final del kernel
    pm_manager.bitmap = &end;

    // calculamos el numero de paginas que va a necesitar el mapa de bits
    // Cada 4096 bytes del bitmap es una pagina, y reservamos una extra para paginas "parciales"
    size_t bitmap_paging_size = pm_manager.bitmap_length / PG_PAGE_SIZE;

    if(pm_manager.bitmap_length % PG_PAGE_SIZE)
        bitmap_paging_size+=1;

    //Inicializamos el gestor de memoria virtual
    vm_init(dir);

    for (size_t pg = 0; pg < bitmap_paging_size; pg++)
    {
        page_flags_t flags = PG_PTE_PRESENT | PG_PTE_READ_WRITE;
        //vm_map_page(dir, flags);
        map_to_dir(dir, pm_manager.bitmap+(0x1000*pg), pm_manager.bitmap+(0x1000*pg), flags);
    }


    for (size_t block = 0; block < pm_manager.bitmap_length; block++)
    {
        pm_manager.bitmap[block] = BLOCKS_ALL_USED;
    }

    int e = 0;
    multiboot_memory_map_t * map;
    while(map)
    {
        map = mboot_get_mmap_entry(e);

        if(map->addr_high || map->len_high)
            break;

        load_region(map->addr_low, map->len_low, map->type);

        e++;
    }

    pm_manager.bitmap[0] = BLOCKS_ALL_USED;


    pg_table_t * kernel_page_table = dir->tables[0];
    kernel_page_table = ((virt_t)kernel_page_table) & PG_PDE_FRAME;
    for(size_t entry = 0; entry < PG_MAX_PTE; entry++)
    {
        page_t page = kernel_page_table->pages[entry];
        page = ((phys_t)page) & PG_PTE_FRAME;
        if(page){
            use_block(entry);
        }
    }
}

void pm_mgr_get_status(size_t * total, size_t * free){
    *total = pm_manager.bitmap_length * BLOCKS_PER_BYTE;
    *free = pm_manager.free_blocks;
}
