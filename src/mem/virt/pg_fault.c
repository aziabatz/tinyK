/**
 * \date Monday, October 17th 2022, 6:42:24 pm
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

#include <mem/virt/paging.h>
#include <mem/types.h>
#include <mem/virt/util.h>
#include <printf.h>
#include <system.h>
#include <dev/io/screen/text_color.h>

const char * pg_fault_description[8] = 
{
    "#PF: kernel-space: read: (non-present)",
    "#PF: kernel-space: read: (present)",
    "#PF: kernel-space: write: (read/write non-present)",
    "#PF: kernel-space: write: (read/write present)",

    "#PF: user-space: read: (user non-present)",
    "#PF: user-space: read: (user present)",
    "#PF: user-space: write: (user read/write non-present)",
    "#PF: user-space: write: (user read/write present)"
}; 





void page_fault(reg_frame_t * regs)
{
    virt_t cr2 = __pf_addr();

    set_bg(RED);

    kprintf("PAGE FAULT! CANNOT RECOVER!\n%s\n\n", pg_fault_description[(regs->err_code & 0b111)]);
    kprintf("Error Code: %x\n", regs->err_code);
    kprintf("Caused by vaddr[%%CR2]: %x\n\n", cr2);

    kpanic_reg_dump(regs);

    __stop();
}

void pg_set_handler()
{
    idt_set_handler(PG_PAGE_FAULT_CODE, &page_fault);
}
