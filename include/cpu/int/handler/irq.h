//
// Created by Ahmed Ziabat on 8/4/23.
//

#ifndef TINYK_IRQ_H
#define TINYK_IRQ_H

#ifndef TK_GUARD_IRQ_HANDLER
    #error This function is only meant to be used by the IRQ assembly routines
#else
/**
 * \brief Manejador de interrupción hardware común. Obtiene el número de interrupción y envía los registros recibidos al manejador específico correspondiente
 * \param regs Marco de registros de la CPU en el instante de la interrupción
 */
void irq_handler(reg_frame_t * regs);
#endif

#endif //TINYK_IRQ_H
