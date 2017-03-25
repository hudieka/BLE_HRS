#include "main.h"

void pit_irq()
{
    INSERT_NOP();
}

void lpuart_irq()
{
    INSERT_NOP();
}

void tpm0_irq()
{
    INSERT_NOP();
}

void i2c0_irq()
{
    INSERT_NOP();
}

void i2c1_irq()
{
    INSERT_NOP();
}

void adc_irq()
{
    INSERT_NOP();
    DEMO_ADC16_IRQ_HANDLER_FUNC();
}

void lptmr0_irq()
{
    INSERT_NOP();
}
