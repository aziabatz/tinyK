/**
 * \file pm_mgr.h
 * \date Friday, January 27th 2023, 5:12:12 pm
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
 * \brief Fichero cabecera para el manejador de memoria fisica
 */


#ifndef TK_PHYS_MGR_H
#define TK_PHYS_MGR_H

#include <types.h>
#include <boot/multiboot.h>
#include <stddef.h>
#include "../virt/paging.h"

// \brief Tamaño mínimo de bloque en bytes(una pagina por defecto)
#define BLOCK_SIZE 4096

// \brief Número de bloques por cada byte del bitmap (cada bit direcciona toda una página de 4K)
#define BLOCKS_PER_BYTE 8

#define BLOCKS_ALL_USED 0xFF
#define BLOCKS_NONE_USED 0x00

#define BLOCK_FREE 0
#define BLOCK_USED 1

struct pm_mgr_info
{
    size_t bitmap_length;
    size_t free_blocks;
    uint8 * bitmap;
};

typedef struct pm_mgr_info pm_mgr_t;

void * pm_mgr_init(multiboot_memory_map_t * mb_map, size_t memory_size, pg_dir_t * dir);

void pm_mgr_get_status(size_t * total, size_t * free);

void pm_mgr_free(phys_t address);

//FIXME quitar address, solo vamos a reservar por num. de paginas
phys_t pm_mgr_alloc(phys_t address, size_t pages);


#endif