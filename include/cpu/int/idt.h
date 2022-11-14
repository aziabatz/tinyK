/**
 * \file idt.h
 * \date Tuesday, October 18th 2022, 5:05:18 pm
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

 * \brief Tabla de descriptores de interrupción
 */

#ifndef TK_IDT_H
#define TK_IDT_H

#include <cpu/desc/descriptor.h>
#include <cpu/regs.h>

/// \brief Número máximo de líneas de interrupción de la tabla de interrupciones
#define MAX_IDT_ENTRIES 256

/// \brief Bandera para interrupciones de tarea
#define IDT_GATE_TASK 0x5
/// \brief Bandera para interrupciones con selectores de 16 bits
#define IDT_GATE_INT16 0x6
/// \brief Bandera para interrupciones software con selectores de 16 bits
#define IDT_GATE_TRAP16 0x07
/// \brief Bandera para interrupciones con selectores de 16 bits
#define IDT_GATE_INT32 0x0E
/// \brief Bandera para interrupciones con selectores de 32 bits
#define IDT_GATE_TRAP32 0x0F

/// \brief Macro para asignar bits del anillo de privilegios de la interrupción
#define IDT_DPL(dpl) (dpl<<5)
/// \brief Bit que indica que la interrupción está presente en la tabla
#define IDT_P (1 << 7)

#ifndef KERNEL_CS
/// \brief Selector por defecto del segmento de código del núcleo.
#define KERNEL_CS 0x08
#endif

/**
 * \brief Descriptor de puerta de interrupción en la tabla
 * 
 */
struct idt_gate_desc
{
    /// \brief Parte baja(16 bits) de la dirección del manejador de interrupción
    uint16 offset_low;
    /// \brief Selector de segmento donde se ejecuta la interrupción
    uint16 seg_sel;
    /// \brief Bits reservados
    uint8 reserved;
    /// \brief Atributos de la puerta de interrupción
    uint8 flags;
    /// \brief Parte alta(16 bits) de la dirección del manejador de interrupción
    uint16 offset_high;
}__attribute__((packed));

/// \brief Tipo registro de descriptor de interrupción
typedef struct idt_gate_desc idt_gate_t;
/// \brief Tipo de tabla de desciptores como: Tabla de descriptores de interrupción
typedef descriptor_t idt_t;

/**
 * \brief Función para poner a punto la tabla de descriptores de interrupción y cargarla al registro correspondiente IDTR
 * 
 */
void idt_init();

/**
 * \brief Función que inserta una interrupción en la tabla
 * 
 * \param entry Número de entrada en la tabla de interrupciones
 * \param offset Dirección del manejador de interrupción
 * \param selector Selector del segmento de código donde se ejecuta la interrupción
 * \param flags Atributos de la interrupción en la tabla
 */
void idt_set_gate(uint32 entry, uint32 offset, uint16 selector, uint8 flags);

/**
 * \brief Asigna un nuevo manejador a una interrupción en la tabla
 * 
 * \param entry Número de entrada en la tabla de interrupciones
 * \param handler Dirección del nuevo manejador de interrupción
 */
void idt_set_handler(uint32 entry, uint32 handler);

/**
 * \brief Manejador último común a todos las interrupciones
 * 
 * \param regs Marco de registros del procesador en el instante de la interrupción
 */
void isr_handler(reg_frame_t * regs);

#endif