#include "Adc.h"
#include "Reg.h"
#include "OsIf.h"
#include "Det.h"

static uint32 Adc_LastValue = 0U;

void Adc_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    (void)RCC->APB2ENR;

    ADC_CMN->CCR &= ~(0x3UL << 16);
    ADC_CMN->CCR |=  (0x1UL << 16);

    ADC1->CR2 = 0U;
    ADC1->CR1 = 0U;
    ADC1->SMPR2 &= ~(0x7UL << 12U);
    ADC1->SQR1 &= ~(0xFUL << 20U);
    ADC1->SQR3 &= ~0x1FUL;
    ADC1->SQR3 |= 4U;
    ADC1->CR2 = ADC_CR2_CONT | ADC_CR2_EOCS;
    ADC1->CR2 |= ADC_CR2_ADON;

    OsIf_DelayMs(1U);
}

uint32 Adc_Read(void)
{
    uint32 cnt = 1000000UL;
    uint32 val;

    ADC1->CR2 |= ADC_CR2_ADON;
    OsIf_DelayMs(1U);

    ADC1->SR = 0U;
    (void)ADC1->DR;

    ADC1->CR2 |= ADC_CR2_SWSTART;

    while ((ADC1->SR & ADC_SR_EOC) == 0U) {
        if (--cnt == 0U) {
            Det_Printf("ADC TIMEOUT | SR=0x%08lX CR2=0x%08lX DR=0x%08lX\r\n",
                       ADC1->SR, ADC1->CR2, ADC1->DR);
            return Adc_LastValue;
        }
    }

    val = ADC1->DR & 0x0FFFUL;
    ADC1->CR2 &= ~ADC_CR2_ADON;
    Adc_LastValue = val;
    return val;
}
