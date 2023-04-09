/**
 * \date Sunday, October 23rd 2022, 6:30:50 pm
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

#include <mem/phys/pm_map.h>
#include <stddef.h>
#include <printf.h>

#define MEM_TABLE_SEPARATOR "-----------------------------------------------------------------"
#define MEM_TABLE_HEADER    "|BASE              |LENGTH            |\tSIZE\t|TYPE"
#define MEM_TABLE_ROW       "|0x%x%x|0x%x%x|\t%d\t|(%d)%s\n"

static multiboot_info_t * mboot_info = NULL;
static size_t mboot_mmap_len = 0;
static uint32 mboot_mmap_addr = 0;

static const char * phys_ram_str[6] = {
    "RAM?!",
    MBOOT_AVAILABLE_STR,
    MBOOT_RESERVED_STR,
    MBOOT_ACPI_RECLAIMABLE_STR,
    MBOOT_NVS_STR,
    MBOOT_BADRAM_STR
};

void mboot_mmap_load(multiboot_info_t * mboot)
{
    mboot_info = mboot;
    mboot_mmap_len = mboot->mmap_length;
    mboot_mmap_addr = mboot->mmap_addr;

    kprintf("Multiboot mmap size is: %d/%d = %d entries\n", mboot_mmap_len, sizeof(multiboot_memory_map_t),mboot_mmap_len/sizeof(multiboot_memory_map_t));
}

void mboot_show_mmap()
{
    //kprintf("--------------------------------------------------------------------------------\n");
  //  kprintf("|BASE------|LENGTH----|TYPE----|\n");
    //kprintf("|---------------|------------|-------------------------------------------------|\n");

    kprintf("%s\n", MEM_TABLE_HEADER);
    kprintf("%s\n", MEM_TABLE_SEPARATOR);

    multiboot_memory_map_t * mmap;//= mboot_info->mmap_addr;

    for(size_t entry = 0; entry < mboot_mmap_len; entry += sizeof(multiboot_memory_map_t))
    {
        mmap = mboot_mmap_addr + entry;
        kprintf(MEM_TABLE_ROW, mmap->addr_high, mmap->addr_low, mmap->len_high, mmap->len_low, mmap->size, mmap->type, phys_ram_str[mmap->type]);
        //kprintf("%s\n", MEM_TABLE_SEPARATOR);
    }
}

//FIXME QUE OCURRE CON DIRECCIONES +4GB?
multiboot_memory_map_t * mboot_get_mmap_entry(uint32 entry)
{
    multiboot_memory_map_t * map = mboot_mmap_addr + (entry * sizeof(multiboot_memory_map_t));
    if(map>(mboot_mmap_addr + mboot_mmap_len))
        map = NULL;

    return map;
}

