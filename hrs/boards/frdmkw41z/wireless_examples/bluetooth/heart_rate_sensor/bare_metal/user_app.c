/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include <string.h>
#include "Panic.h"
#include "user_app.h"

#define USER_GETMAX   22


struct STRU_PIF pif;
p_pif_load_t load;

BlueData g_BDbuf;

static uint8_t g_u8BLE_recv[USER_GETMAX];
static uint8_t g_u8BLE_send[USER_GETMAX];


uint8_t user_getfrombule (uint8_t *UserData, uint8_t len)
{
  if(len > USER_GETMAX)
  {
    memcpy(g_u8BLE_recv, UserData, USER_GETMAX);
    g_BDbuf.recv_len = USER_GETMAX;
  }
  else
  {
    memcpy(g_u8BLE_recv, UserData, len);
    g_BDbuf.recv_len = len;
  }
  
  return 0;
}

void user_com_memory_init()
{
  g_BDbuf.recv_buf = g_u8BLE_recv;
  g_BDbuf.send_buf = g_u8BLE_send;
  g_BDbuf.recv_len = 0;
  g_BDbuf.send_len = 0;
}

void user_init(void)
{
  struct STRU_PIF *p;
  load = (p_pif_load_t)LOAD_FUN_ADDR;
  p = &pif;
  (*load)(p);
}

void user_run(void)
{
  pif.p_user_run(&g_BDbuf);
  g_BDbuf.recv_len = 0;
  
}

void user_isr(uint8_t flag)
{
  switch(flag)
  {
    case 0:
    {
      pif.p_interrupt_pit();
      break;
    }
    
    case 1:
    {
      pif.p_interrupt_lpuart();
      break;
    }
    
    case 2:
    {
      pif.p_interrupt_tpm0();
      break;
    }
    
    case 3:
    {
      pif.p_interrupt_i2c0();
      break;
    }
    
    case 4:
    {
      pif.p_interrupt_i2c1();
      break;
    }
    
    case 5:
    {
      pif.p_interrupt_adc();
      break;
    }
	case 6:
	{
	  pif.p_interrupt_lptmr0();
	}
  }
}


uint8_t UserAppCheck()
{
  uint8_t ret = 0;
  if( *(unsigned int *)(LOAD_FUN_ADDR - 1) != 0xFFFFFFFF  )
  {
    ret = 1;
  }
  
  return ret;
}


