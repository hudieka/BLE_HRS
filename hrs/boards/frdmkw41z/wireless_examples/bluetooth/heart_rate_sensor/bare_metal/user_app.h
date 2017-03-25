#ifndef _USER_APP_H_
#define _USER_APP_H_


/*****************************************************************************************************
* Declaration of module wide FUNCTIONs - NOT for use in other modules
*****************************************************************************************************/

#define LOAD_FUN_ADDR 0x2001

#define USER_APP_READY     0x55
#define USER_APP_NONE      0

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
typedef void    (*p_LPTMR0_interrupt_t)(void);


struct STRU_PIF
{
    p_user_run_t     p_user_run;
    p_PIT_interrupt_t           p_interrupt_pit;
    p_LPUART_interrupt_t        p_interrupt_lpuart;
    p_TPM0_interrupt_t          p_interrupt_tpm0;
    p_I2C0_interrupt_t          p_interrupt_i2c0;
    p_I2C1_interrupt_t          p_interrupt_i2c1;
    p_ADC_interrupt_t           p_interrupt_adc;
	p_ADC_interrupt_t           p_interrupt_lptmr0;
};

typedef void    (*p_pif_load_t)(struct STRU_PIF * p);

void    pif_load(struct STRU_PIF * p);

uint8_t user_getfrombule (uint8_t *UserData, uint8_t len);

void user_init(void);
void user_run(void);
void user_isr(uint8_t flag);

void user_com_memory_init();
uint8_t UserAppCheck();










#endif