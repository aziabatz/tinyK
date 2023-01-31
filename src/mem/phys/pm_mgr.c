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

static pm_mgr_t pm_manager;
extern const uint32 end;

void * pm_mgr_init(multiboot_memory_map_t * mb_map, size_t memory_size)
{
    //&end;//esto es end

    size_t mem_size_bytes = memory_size * 1024;
    size_t number_of_blocks = mem_size_bytes / BLOCK_SIZE;
    
    pm_manager.bitmap_length = number_of_blocks / BLOCKS_PER_BYTE;
    //indicamos que toda la memoria esta en uso
    pm_manager.free_blocks = 0;
    //situamos el mapa de bits al final del kernel
    pm_manager.bitmap = &end;

    memset(pm_manager.bitmap, BLOCKS_ALL_USED, pm_manager.bitmap_length);
    
    
}

void * getAvailableMemory(multiboot_memory_map_t * mb_mmap)
{

}