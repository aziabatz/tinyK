/**
 * @author Ahmed Ziabat Ziabat <aziabatz@alumnos.unex.es>
 * @file Description
 * @date Created on 2022-10-05 1:57:23 pm
 * @copyright Copyright 2022 Ahmed Ziabat
 Redistribution and use in source and binary forms, with or without modification, are permitted
 provided that the following conditions are met:
  1. Redistributions of source code must retain the above copyright notice, this list of conditions
 and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions
 and the following disclaimer in the documentation and/or other materials provided with the
 distribution.
  3. Neither the name of the copyright holder nor the names of its contributors may be used to
 endorse or promote products derived from this software without specific prior written
 permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS &quot;AS IS&quot; AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 OF SUCH DAMAGE.
 */
#ifndef TK_VGA_H
#define TK_VGA_H

#include <dev/driver.h>

driver_t * get_vga_driver();
driver_t * install_vga();

int32 vga_read(driver_data_t * data);
int32 vga_write(driver_data_t * data);


struct vga_spec {
    size_t width;
    size_t height;
    size_t depth;
    char * fb_start;
};

typedef struct vga_spec vga_spec_t;

#define FRAMEBUFFER (char *) 0xB8000
#define FB_CHAR (color,ch) (uint16)(((color << 8) & 0xFF00) | ch)
#define VGA_INDEX_PORT 0x3D4
#define VGA_CHAR_PORT 0x3D5

#endif
