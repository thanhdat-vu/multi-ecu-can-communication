#include "I2c.h"
#include "Reg.h"
#include "OsIf.h"


void I2c_Init(void)
{
    RCC->APB1ENR  |= RCC_APB1ENR_I2C1EN;
    (void)RCC->APB1ENR;

    RCC->APB1RSTR |=  RCC_APB1RSTR_I2C1RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_I2C1RST;

    I2C1->CR1 &= ~I2C_CR1_PE;
    I2C1->CR1 |=  I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    I2C1->CR2   = 42U;    /* FREQ = 42 MHz */
    I2C1->CCR   = 210U;   /* Standard mode, CCR = 210 */
    I2C1->TRISE = 43U;
    I2C1->OAR1  = (1UL << 14);
    I2C1->CR1  |= I2C_CR1_PE;
    I2C1->CR1  |= I2C_CR1_ACK;
}


static uint8_t I2C1_WaitSet(volatile uint32_t *reg, uint32_t mask)
{
    uint32_t cnt = I2C_TIMEOUT;
    while (((*reg) & mask) == 0U) { if (--cnt == 0U) return 0U; }
    return 1U;
}



static uint8_t I2C1_WaitClear(volatile uint32_t *reg, uint32_t mask)
{
    uint32_t cnt = I2C_TIMEOUT;
    while (((*reg) & mask) != 0U) { if (--cnt == 0U) return 0U; }
    return 1U;
}


uint8_t I2c_MasterTransmit(uint8_t addr7, const uint8_t *data, uint8_t len)
{
    uint8_t i;

    if ((data == (void *)0) || (len == 0U)) { return 0U; }

    if (!I2C1_WaitClear(&I2C1->SR2, I2C_SR2_BUSY)) { return 0U; }

    I2C1->CR1 |= I2C_CR1_START;
    if (!I2C1_WaitSet(&I2C1->SR1, I2C_SR1_SB)) { return 0U; }

    /* SLA+W – gửi địa chỉ 7-bit << 1 | 0 (write) */
    I2C1->DR = (uint8_t)((addr7 << 1U) & 0xFEU);
    {
        uint32_t cnt = I2C_TIMEOUT;
        for (;;)
        {
            uint32_t sr1 = I2C1->SR1;
            if (sr1 & I2C_SR1_ADDR) { break; }   /* ADDR set: OK */
            if (sr1 & I2C_SR1_AF)                 /* NACK */
            {
                I2C1->SR1 &= ~I2C_SR1_AF;
                I2C1->CR1 |= I2C_CR1_STOP;
                return 0U;
            }
            if (--cnt == 0U) { I2C1->CR1 |= I2C_CR1_STOP; return 0U; }
        }
    }

    { volatile uint32_t tmp = I2C1->SR1; tmp = I2C1->SR2; (void)tmp; }

    for (i = 0U; i < len; i++)
    {
        if (!I2C1_WaitSet(&I2C1->SR1, I2C_SR1_TXE)) { return 0U; }
        I2C1->DR = data[i];
    }

    if (!I2C1_WaitSet(&I2C1->SR1, I2C_SR1_BTF)) { return 0U; }
    I2C1->CR1 |= I2C_CR1_STOP;

    return 1U;
}
