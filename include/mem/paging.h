/**
 * \date Monday, October 17th 2022, 5:42:46 pm
 * \author Ahmed Ziabat Ziabat
 * 
 * 
 * BSD 3-Clause License
 * 
 * \copyright Copyright (c) 2022, Ahmed Ziabat Ziabat <aziabatz@alumnos.unex.es>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
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

 * \brief
 */

#ifndef TK_PAGING_H
#define TK_PAGING_H

#include <types.h>
#include <cpu/int/idt.h>

typedef uint32 phys_t;
typedef uint32 virt_t;

#define PG_MAX_PTE                  1024
#define PG_MAX_PDE                  1024
#define PG_PAGE_SIZE                4096 // 4KiB pages

#define PG_MAX_VMEM                 PG_MAX_PDE * PG_MAX_PTE * PG_PAGE_SIZE //4GiB addressed through paging

#define PG_PAGE_FAULT_CODE          0x0E

#define PG_ENTRY_FLAGS              0xFFF

#define PVIRT_DIR_SHIFT             0x16
#define PVIRT_TAB_SHIFT             0x0C

#define PG_PTE_PRESENT              (1 << 0)
#define PG_PTE_READ_WRITE           (1 << 1)
#define PG_PTE_USER_KERNEL          (1 << 2)
#define PG_PTE_WRITE_THROUGH        (1 << 3)
#define PG_PTE_CACHE_DISABLE        (1 << 4)
#define PG_PTE_ACCESSED             (1 << 5)
#define PG_PTE_DIRTY                (1 << 6)
#define PG_PTE_PAT                  (1 << 7)
#define PG_PTE_GLOBAL               (1 << 8)
#define PG_PTE_AVAILABLE            (0b111 << 9)
#define PG_PTE_FRAME                ~(PG_ENTRY_FLAGS)

#define PG_PDE_PRESENT              PG_PTE_PRESENT
#define PG_PDE_READ_WRITE           PG_PTE_READ_WRITE
#define PG_PDE_USER_KERNEL          PG_PTE_USER_KERNEL
#define PG_PDE_WRITE_THROUGH        PG_PTE_WRITE_THROUGH
#define PG_PDE_CACHE_DISABLE        PG_PTE_CACHE_DISABLE
#define PG_PDE_ACCESSED             PG_PTE_ACCESSED
#define PG_PDE_AVAILABLE            (0b111101 << 6)
#define PG_PDE_SIZE                 (0 << 7) // For now only 4KB pages
#define PG_PDE_FRAME                PG_PTE_FRAME

#define PG_ALIGNED_4K(address)      (0 == (address & PAGING_ENTRY_FLAGS))

#define PG_FAULT_MESSAGE            "US RW  P - Cause?\n" \
                                    "%d  %d  %d   %s\n"

void pg_set_handler(void);

#endif