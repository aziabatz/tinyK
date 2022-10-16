/*
 * Created: Saturday, October 8th 2022, 2:00:18 pm
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

#ifndef TK_PORT_H
#define TK_PORT_H

#include <types.h>

/// @brief Tipo puerto E/S
typedef uint16 port_t;

/// @brief Función Puerto E/S salida de tamaño byte
/// @param port Puerto al que va dirigido el dato
/// @param value Valor del dato
extern void __out8(port_t port, uint8 value);

/// @brief Función Puerto E/S salida de tamaño 2 bytes
/// @param port Puerto al que va dirigido el dato
/// @param value Valor del dato
extern void __out16(port_t port, uint16 value);

/// @brief Función Puerto E/S salida de tamaño 4 bytes
/// @param port Puerto al que va dirigido el dato
/// @param value Valor del dato
extern void __out32(port_t port, uint32 value);

/// @brief Función Puerto E/S entrada de tamaño byte
/// @param port Puerto del que se lee el dato
/// @param value Puntero donde se almacena el dato leído
extern void __in8(port_t port, uint8 * value);

/// @brief Función Puerto E/S entrada de tamaño 2 bytes
/// @param port Puerto del que se lee el dato
/// @param value Puntero donde se almacena el dato leído
extern void __in16(port_t port, uint16 * value);

/// @brief Función Puerto E/S entrada de tamaño 4 bytes
/// @param port Puerto del que se lee el dato
/// @param value Puntero donde se almacena el dato leído
extern void __in32(port_t port, uint32 * value);

#endif