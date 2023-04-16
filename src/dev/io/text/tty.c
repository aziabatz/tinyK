/*
 * Created: Thursday, October 13th 2022, 6:10:43 pm
 * Author: Ahmed Ziabat Ziabat
 * 
 * 
 * BSD 3-Clause License
 * 
 * Copyright (c) 2022, Ahmed Ziabat Ziabat <aziabatz@alumnos.unex.es>
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
 */

#include <printf.h>
#include <dev/io/screen/vga.h>
#include <str.h>

static driver_t * tty_dev = NULL;

#define STR_NULL "(null)"

void set_tty_dev(driver_t * device)
{
    tty_dev = device;
}

size_t kprint(char * str)
{
    if(!tty_dev)
    {
        return 0;
    }

    size_t len = strlen(str);
    
    driver_data_t ddata = {
        .data = str,
        .info = tty_dev->info,
        .size = len
    };

    tty_dev->write(&ddata);

    return len;
}

void putc(char c);

void kprint_hex(uint32 hex)
{
    char * c_hex = "0123456789ABCDEF";
    char hex_str[9];
    hex_str[8] = '\0';

    for(size_t i = 0, j = 7; i < 8; i++, j--)
    {
        hex_str[j] = c_hex[(hex >> (4*i) & 0x0F)];
    }

    //kprint("0x");
    kprint(hex_str);
}

static inline void reverse(char * str)
{
    size_t i = 0;
    size_t j = strlen(str)-1;
    char c;
    for(i,j; i<j; i++, j--)
    {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

void kprint_dec(int32 num)
{
    char str[16];

    uint8 sign = 0;

    if(num < 0)
    {
        sign = 1;
        num = -num;//descartamos temporalmente el signo
    }

    int i = 0;
    //para convertir a base 10 hacemos sucesivas divisiones entre 10
    do
    {
        str[i++] = num % 10 + '0';//tomamos el resto y lo convertimos a char
        //asignamos a i e incrementamos i      
    }
    while ((num/=10)>0);//descartamos el resto
    
    //asignamos signo si corresponde y terminamos la cadena
    if(sign)
    {
        str[i++] = '-';
    }
    str[i] = '\0';

    //invertimos la cadena resultante 
    reverse(str);

    kprint(str);
}

void kprint_u(uint32 num)
{
    char str[16];

    int i = 0;
    //para convertir a base 10 hacemos sucesivas divisiones entre 10
    do
    {
        str[i++] = num % 10 + '0';//tomamos el resto y lo convertimos a char
        //asignamos a i e incrementamos i      
    }
    while ((num/=10)>0);//descartamos el resto
    
    str[i] = '\0';

    //invertimos la cadena resultante 
    reverse(str);

    kprint(str);
}

size_t kprintf(char * fmt, ...)
{
    if(!tty_dev)
    {
        return NULL;
    }

    va_list args;
    va_start(args, fmt);

    //char buffer[20];
    char c;


    while((c=*fmt++) != NULL)
    {

            /*TODO vga must offer a way to put a char
            without sending a driver data struct, as it is
            very slow
            */

        if(c != '%')
        {
            putc(c);
        }
        else
        {
            char * p = NULL;
            c = *fmt++;
            
            switch(c)
            {
                case 's':
                case 'S':
                    p = va_arg(args, char *);
                    if(p == NULL)
                    {
                        p = STR_NULL;
                    }
                    kprint(p);
                    break;
                case 'x':
                case 'X':
                    kprint_hex(va_arg(args, uint32));
                    break;
                case 'i':
                case 'I':
                case 'd':
                case 'D':
                    //TODO int
                    kprint_dec(va_arg(args, int));
                    break;
                case 'u':
                case 'U':
                    //TODO unsigned
                    uint32 u =va_arg(args, uint32);
                    kprint_u(u);
                    break;
                case 'c':
                    putc(va_arg(args, int));
                    break;
                case '%':
                    putc('%');
                    break;
                default:
                    //hemos recibido % y otro char
                    //imprimimos los dos
                    putc('%');
                    putc(c);
            }
        }
    }

    va_end(args);
}