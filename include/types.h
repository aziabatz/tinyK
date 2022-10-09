/**
 * @author Ahmed Ziabat Ziabat <aziabatz@alumnos.unex.es>
 * @file Types definition
 * @date Created on 2022-10-05 9:37:13 am
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
#ifndef UNEXOS_TYPES_H
#define UNEXOS_TYPES_H

typedef signed char int8;
typedef unsigned char uint8;

typedef signed short int16;
typedef unsigned short uint16;

typedef signed int int32;
typedef unsigned int uint32;

typedef signed long long int int64;
typedef unsigned long long int uint64;

//typedef char* string;

//typedef unsigned int size_t;
typedef __SIZE_TYPE__ size_t;
typedef uint8 boolean;


/* typedef struct timestr{
  uint32 hour;
  uint32 mins;
  uint32 secs;
}ktime_t;

typedef uint32 posixtime_t; */





#define NULL ((void *)0)
#define true 1
#define false 0

//static int halt() { asm("jmp _stop"); }


/* #define BAD(s, f, l) ({print(s);NL;\
print(f);NL;\
print(l);NL;\
halt();\
})

#define ASSERT_NULL(x) ((x == NULL) ? BAD("NULLPTR", __FILE__, __LINE__) : NULL) */


//#define sizeof(x) ((char *)(&x + 1) - (char *)&x)

#endif
