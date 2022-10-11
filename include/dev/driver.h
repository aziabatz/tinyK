/**
 * @author Ahmed Ziabat Ziabat <aziabatz@alumnos.unex.es>
 * @file Driver related header file
 * @date Created on 2022-10-05 9:36:02 am
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
#ifndef UNEXOS_DRIVER_H
#define UNEXOS_DRIVER_H

#include <types.h>
#include <stddef.h>

struct driver_info
{
    uint32 did;
    char * alias;
};

typedef struct driver_info driver_info_t;

struct driver_data
{
    driver_info_t * info;
    void * data;
    size_t size;
};

typedef struct driver_data driver_data_t;

typedef int32 (*driver_read_t)(driver_data_t*);
typedef int32 (*driver_write_t)(driver_data_t*);

//typedef uint8 (*driver_install_t)(driver_info_t*);

//TODO open & close operations
struct driver{
    driver_info_t * info;
    driver_read_t read;
    driver_write_t write;
//    driver_install_t install;
};

typedef struct driver driver_t;


#endif