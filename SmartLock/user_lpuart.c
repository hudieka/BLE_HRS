#include "main.h"

#define BOARD_DEBUG_UART_BAUDRATE  9600

#define BOARD_CORECLOCK    20971520


uint8_t txbuff[] = "Hello\n";

void user_lpuart_init(void)
{
    
    lpuart_config_t config;
    
    /* Initialize LPUART0 pins below */
    /* Ungate the port clock */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Affects PORTC_PCR6 register */
    PORT_SetPinMux(PORTC, 6U, kPORT_MuxAlt4);
    /* Affects PORTC_PCR7 register */
    PORT_SetPinMux(PORTC, 7U, kPORT_MuxAlt4);
    
    CLOCK_SetLpuartClock(0x1U);
    
    LPUART_GetDefaultConfig(&config);
    config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
    config.enableTx = true;
    config.enableRx = true;

    LPUART_Init(LPUART0, &config, BOARD_CORECLOCK);
    
    LPUART_WriteBlocking(LPUART0, txbuff, sizeof(txbuff) - 1);


}