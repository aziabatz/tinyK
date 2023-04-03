/**
 * \file vm_mgr.h
 * \date Wednesday, February 1st 2023, 5:06:24 pm
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
 * \brief Fichero de cabecera para manejador de memoria virtual
 */

#include "../types.h"
#include "paging.h"
#include <stddef.h>

/**
 * @brief Create a paging directory
 * 
 * @return pg_dir_t* The paging directory allocated in phyiscal memory
 */
pg_dir_t * create_paging_directory();

/**
 * @brief Create a paging table
 * 
 * @param dir The paging directory
 * @param pd_index The entry index,
 * @param flags The paging table flags
 * @return pg_table_t* The paging table allocated in physical memory and set in the directory
 */
pg_table_t * create_paging_table(pg_dir_t* dir, uint16 pd_index, uint16 flags);

/**
 * @brief Create a page in a table
 * 
 * @param table 
 * @param pt_index 
 * @param flags 
 * @return page_t* 
 */
page_t * create_page(pg_table_t * table, uint16 pt_index, uint16 flags);

virt_t map_addr(pg_dir_t * dir, phys_t paddr, virt_t vaddr, page_flags_t flags);



