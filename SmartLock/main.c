/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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

#include "main.h"
#include "isr.h"

#include "user_adc16_interrupt.h"
#include "user_lpuart.h"

/* Start address of relocated interrutp vector table */
#define RELOCATED_VECTORS 0x1A000 

static void user_main(BlueData * commdata);

void JumpToUserApplication(unsigned long userSP, unsigned long userStartup)
{
  // set up stack pointer
  __asm("msr msp, r0");
  __asm("msr psp, r0");
  
  // Jump to PC (r1)
  __asm("mov pc, r1"); 
}

void dummy_call(void)
{
    int c;
    
    c = 1;
    
    if(c == 0)
    {
        pif_load(0);
    }
}

int main(void) 
{
  
  dummy_call();

  //SCB_VTOR = RELOCATED_VECTORS;
  SCB->VTOR = RELOCATED_VECTORS;
    // Jump to user application
  JumpToUserApplication(*((unsigned long*)RELOCATED_VECTORS), *((unsigned long*)(RELOCATED_VECTORS+4)));   
  
}


#pragma location = ".iec_section"

//这里添加外设初始化程序
void pif_load(struct STRU_PIF * p)
{
  INSERT_NOP();
  p->p_user_run           =  user_main;
  p->p_interrupt_pit      =  pit_irq;
  p->p_interrupt_lpuart   =  lpuart_irq;
  p->p_interrupt_tpm0     =  tpm0_irq;
  p->p_interrupt_i2c0     =  i2c0_irq;
  p->p_interrupt_i2c1     =  i2c1_irq;
  p->p_interrupt_adc      =  adc_irq;
  p->p_interrupt_lptmr0	  =  lptmr0_irq;
  
  user_adc16_init();
  user_lpuart_init();
  
  return;
}

//这里是主循环任务，buf为蓝牙接收到的数据，len为长度，如果长度为0表示没有新的数据
static void user_main(BlueData * commdata)
{
  INSERT_NOP();
  static int i = 0;
  int test_flag = 0;
  
  //Debug for test
  commdata->send_buf[0] = i;
  commdata->send_len = 1;
  i++;
  
  //TEST CODE START
  if(commdata->recv_len != 0)
  {
    test_flag = commdata->recv_buf[0];
    switch(test_flag)
    {
      //TEST ADC
      case 0:
      {
        user_call_adc16();
        break;
      }
    }
    
    commdata->recv_len = 0;
  }
  
  
  
  
  return;
}