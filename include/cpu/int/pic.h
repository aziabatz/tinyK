/**
 * \file pic.h
 * \date Wednesday, October 12th 2022, 6:00:22 pm
 * \author Ahmed Ziabat Ziabat
 * 
 * 
 * BSD 3-Clause License
 * 
 * \copyright Copyright (c) 2022, Ahmed Ziabat Ziabat <aziabatz@alumnos.unex.es>
 * All rights reserved.
 * * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * * 
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * * 
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
 * \brief Fichero de cabecera para el manejo del controlador PIC 8259
 */

#ifndef TK_PIC_H
#define TK_PIC_H

#include <stdbool.h>
#include <dev/io/port.h>

/// \brief Puerto del controlador maestro
#define PIC_MASTER          0x20
/// \brief Puerto E/S para comando del controlador maestro
#define PIC_MASTER_COMMAND  PIC_MASTER
/// \brief Puerto E/S para datos del controlador maestro
#define PIC_MASTER_DATA     PIC_MASTER+1

/// \brief Puerto del controlador esclavo
#define PIC_SLAVE           0xA0
/// \brief Puerto E/S para comando del controlador esclavo
#define PIC_SLAVE_COMMAND   PIC_SLAVE
/// \brief Puerto E/S para datos del controlador esclavo
#define PIC_SLAVE_DATA      PIC_SLAVE+1

/// \brief Palabra de comando de inicialización del controlador
#define PIC_ICW4            0x01
/// \brief Ĉomando de inicialización
#define PIC_INIT            0x10

/// \brief Número de líneas de interrupción del controlador maestro
#define PIC_MASTER_LINES    8
/// \brief Número de líneas de interrupción del controlador esclavo
#define PIC_SLAVE_LINES     8
/// \brief Número máximo de líneas de ambos controladores en cascada
#define PIC_MAX_LINES       PIC_MASTER_LINES + PIC_SLAVE_LINES

/// \brief Desplazamiento dentro de la tabla de interrupciones para interrupciones provienientes del PIC
#define PIC_OFFSET          PIC_MASTER

/**
 * \brief Activa o desactiva el controlador aplicando la máscara correspondiente
 * 
 * \param enable Nuevo estado activado/desactivado del controlador
 */
void pic_set(bool enable);

/**
 * \brief Devuelve el estado de activación del controlador
 * 
 * \return true Si el controlador PIC está activo
 * \return false En caso contrario
 */
bool pic_is_enabled();

/**
 * \brief Reasigna las interrupciones provenientes del PIC con respecto a `#PIC_OFFSET`
 * 
 */
void pic_remap();

/**
 * \brief Reasigna las interrupciones provenientes del PIC con respecto a un desplazamiento dado
 * 
 * \param master Nuevo desplazamiento de las interrupciones del maestro
 * \param slave Desplazamiento de las interrupciones del esclavo
 */
void pic_remap_offset(uint8 master, uint8 slave);

/**
 * \brief Comunica a los controladores el reconocimiento de una solicitud de interrupción recibida
 * 
 * \param ack_slave Indica si se debe enviar el reconocimiento de interrupción a ambos controladores
 */
void pic_ack(bool ack_slave);

#endif