/**
 * @author Ahmed Ziabat Ziabat <aziabatz@alumnos.unex.es>
 * @file Common utils functions (system-wide)
 * @date Created on 2022-10-05 9:33:50 am
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

#ifndef UNEXOS_UTIL_H
#define UNEXOS_UTIL_H

#define LOW_8(address) (uint8)((address) & 0xFF)
#define LOW_16(address) (uint16)((address) & 0xFFFF)

#define HIGH_8(address) (uint8)(LOW_8(address >> 8))
#define HIGH_16(address) (uint16)(((address) >> 16) & 0xFFFF)

#endif