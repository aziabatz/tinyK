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

pg_dir_t * create_page_directory()
{
    return NULL;
}

pg_table_t * create_page_table(pg_dir_t* dir, uint16 pd_index)
{
    return NULL;
}

virt_t map_addr(pg_dir_t * dir, phys_t paddr, virt_t vaddr, page_flags_t flags)
{
    uint16 pde = PG_PDE_IDX(vaddr);
    uint16 pte = PG_PTE_IDX(vaddr);

    pg_table_t * table = dir->tables[pde];
    if((!table && PG_PTE_PRESENT))
    {
        kinfo(ERROR, "Page Table not present. NOT IMPLEMENTED");
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

