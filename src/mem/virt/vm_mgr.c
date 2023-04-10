/**
 * \file vm_mgr.c
 * \date Wednesday, February 1st 2023, 11:12:00 pm
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
 * \brief Fichero fuente para manejador de memoria virtual
 */



#include <mem/virt/vm_mgr.h>
#include <system.h>
#include <debug.h>
#include <stddef.h>
#include <mem/phys/pm_mgr.h>
#include <mem.h>
#include <assert.h>

#ifndef TK_GUARD_VM_MGR_ONLY
    #define TK_GUARD_VM_MGR_ONLY
    #include <mem/virt/mgr/directory.h>
    #include <mem/virt/mgr/table.h>
    #include <mem/virt/mgr/page.h>
#endif

static pg_dir_t * kernel_directory = NULL;

extern pg_dir_t * __get_current_dir();

static inline pg_table_t * vm_new_table(pg_dir_t * dir, page_flags_t flags)
{
    pg_table_t * table = (pg_table_t*) vm_alloc_page(dir, flags);
    memset(table, 0, sizeof(pg_table_t));
    return table;
}

static inline pg_dir_t * vm_new_dir(pg_dir_t * src_dir, page_flags_t flags)
{
    pg_dir_t * dir = (pg_dir_t *) vm_alloc_page(src_dir, flags);
    memset(dir, 0, sizeof(pg_dir_t));
    return dir;
}

/**
 * @brief Devuelve la referencia a una pagina de la tabla.
 * SIN LIMPIAR BANDERAS
 * 
 * @param table 
 * @param index 
 * @return page_t* 
 */
static inline page_t * get_page(pg_table_t * table, uint16 index)
{
    page_t * page = NULL;
    if(table && PG_ALIGNED_4K(table))
    {
        page = &(table->pages[index]);
    }
    return page;
}

/**
 * @brief Devuelve la referencia a una tabla del directorio.
 * SIN LIMPIAR BANDERAS
 * 
 * @param dir 
 * @param index 
 * @return pg_table_t* 
 */
static inline pg_table_t * get_table(pg_dir_t * dir, uint16 index)
{
    pg_table_t * table = NULL;
    if(dir && PG_ALIGNED_4K(dir))
    {
        table = dir->tables[index];
    }
    return table;    
}

/**
 * @brief Devuelve la pagina fisica de una dir. virtual
 * 
 * @param vaddr 
 * @param directory 
 * @return page_t 
 */
static inline page_t vm_get_phys_page(virt_t vaddr, pg_dir_t * dir)
{
    page_t phys_page = (page_t) NULL;
    if(dir && PG_ALIGNED_4K(dir))
    {
        pg_table_t * table = get_table(dir, PG_PDE_IDX(vaddr));
        if(table)
        {
            page_t * page = get_page(PG_PDE_GET_FRAME(table), PG_PTE_IDX(vaddr));
            if(page)
            {
                phys_page = PG_PTE_GET_FRAME(page);
            }
        }
    }
    return phys_page;
}

/** 
 * @brief Reserva una pagina y devuelve su dir fisica
 * 
 * @param flags 
 * @return page_t 
 */
static page_t vm_create_page(uint16 flags)
{
    page_t page = pm_mgr_alloc(1);
    assert(page);
    page |= (flags & PG_ENTRY_FLAGS);
    page |= PG_PTE_PRESENT;

    return page;
}

/**
 * @brief Asigna una página a su entrada en la tabla
 * 
 * @param table 
 * @param index 
 * @param flags 
 * @return virt_t 
 */
virt_t vm_alloc_page(pg_dir_t * dir, uint16 flags)
{
    page_t new_page = vm_create_page(flags);

    uint16 pde = PG_PDE_IDX(new_page);
    uint16 pte = PG_PTE_IDX(new_page);

    pg_table_t * table = get_table(dir, pde);

    if( !((uintptr_t)table & PG_PDE_PRESENT) ||
        (pde != PG_MAX_PDE) && (pte == PG_MAX_PTE - 1) )
    {
        // Estamos en la ultima entrada
        // La ultima entrada sera la tabla siguiente(mapeada)
        // Creamos la tabla

        // Aqui tenemos la tabla
        dir->tables[pde] = (uintptr_t)new_page | flags | PG_PDE_PRESENT;
        table = PG_PDE_GET_FRAME(dir->tables[pde]);
        new_page = vm_create_page(flags);
    }

    //Aqui ya tenemos la pagina
    page_t * page = get_page(PG_PDE_GET_FRAME(table), pte);
    if(page && *page)
    {
        pm_mgr_free(PG_PTE_GET_FRAME(*page));
        kinfo(WARNING, "Page is already present and in use. Returning NULL");
        return NULL;
    }
    //dir->tables[pde]->pages[pte] = new_page; 

    *page = new_page;
    
    return PG_PTE_GET_FRAME(new_page);
}

/**
 * @brief Libera una pagina de memoria fisica y la desasigna en la tabla
 * 
 * @param table 
 * @param index 
 */
void vm_free_page(pg_table_t * table, uint16 index)
{ 
    if((uintptr_t)table & PG_PDE_PRESENT)
    {
        page_t * page = get_page(PG_PDE_GET_FRAME(table), index);
        if((uintptr_t)page & PG_PTE_PRESENT)
        {
            pm_mgr_free(PG_PTE_GET_FRAME(*page));
            *page = (page_t) NULL;
        }
    }
}

//-----------------------------------------------------------------------

virt_t vm_map_page(pg_dir_t * dir, uint16 flags)
{
    virt_t vaddr = vm_alloc_page(dir, flags);
    return vaddr;
}

void vm_unmap(pg_dir_t * dir, virt_t vaddr)
{
    pg_table_t * table = get_table(dir, PG_PDE_IDX(vaddr));
    vm_free_page(table, PG_PTE_IDX(vaddr));
}

pg_dir_t * vm_clone_dir(pg_dir_t * dir)
{
    
    // Creamos un nuevo directorio de páginas
    pg_dir_t * new_dir = vm_new_dir(dir, (PG_PDE_READ_WRITE | PG_PDE_PRESENT));

    for(uint16 pde = 0; pde < PG_MAX_PDE; pde++)
    {
        pg_table_t * table = dir->tables[pde];
        //Comprobamos que no es nulo y que está presente
        if((uintptr_t)table & PG_PDE_PRESENT)
        {
            new_dir->tables[pde] = table;
        }
    }
}

void vm_init(pg_dir_t * kernel_dir)
{
    if(kernel_directory == NULL)
    {
        assert(PG_ALIGNED_4K(kernel_dir));
        kernel_directory = kernel_dir;
    }
}

