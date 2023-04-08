//
// Created by Ahmed Ziabat on 8/4/23.
//

#ifndef TINYK_ISR_H
#define TINYK_ISR_H

#ifndef TK_GUARD_ISR_HANDLER
    #error This function is only meant to be used by the ISR assembly routines
#else
/**
 * \brief Manejador último común a todos las interrupciones
 *
 * \param regs Marco de registros del procesador en el instante de la interrupción
 */
void isr_handler(reg_frame_t * regs);
#endif

#endif //TINYK_ISR_H
