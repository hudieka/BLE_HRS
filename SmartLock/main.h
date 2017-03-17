/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/****************************************************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_
   
#include <stdint.h>
   
#include "board.h"
#include "fsl_lpuart.h"
#include "fsl_port.h"
#include "fsl_adc16.h" //ADC
   
#include "user_lpuart.h"
#include "user_adc16_interrupt.h" // User ADC head


/*****************************************************************************************************
* Declaration of module wide FUNCTIONs - NOT for use in other modules
*****************************************************************************************************/

#define LOAD_FUN_ADDR 0x2001

#define INSERT_NOP() asm(" nop");asm(" nop");asm(" nop");asm(" nop");asm(" nop");asm(" nop")

typedef struct _COMM_DATA
{
    uint8_t *send_buf;
    uint16_t send_len;
    uint8_t *recv_buf;
    uint16_t recv_len;
}BlueData;


typedef void    (*p_user_run_t)(BlueData * commdata);
typedef void    (*p_PIT_interrupt_t)(void);
typedef void    (*p_LPUART_interrupt_t)(void);
typedef void    (*p_TPM0_interrupt_t)(void);
typedef void    (*p_I2C0_interrupt_t)(void);
typedef void    (*p_I2C1_interrupt_t)(void);
typedef void    (*p_ADC_interrupt_t)(void);

struct STRU_PIF 
{
    p_user_run_t                p_user_run;
    p_PIT_interrupt_t           p_interrupt_pit;
    p_LPUART_interrupt_t        p_interrupt_lpuart;
    p_TPM0_interrupt_t          p_interrupt_tpm0;
    p_I2C0_interrupt_t          p_interrupt_i2c0;
    p_I2C1_interrupt_t          p_interrupt_i2c1;
    p_ADC_interrupt_t           p_interrupt_adc;
};

typedef void    (*p_pif_load_t)(struct STRU_PIF * p);

void    pif_load(struct STRU_PIF * p);


#endif



