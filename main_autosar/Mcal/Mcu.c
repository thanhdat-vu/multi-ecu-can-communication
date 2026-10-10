#include "Mcu.h"
#include "Reg.h"


void nvic_enable(uint32_t irq)
{
    ((volatile uint32_t *)NVIC_ISER_BASE)[irq >> 5U] = (1UL << (irq & 0x1FU));
}


void Mcu_InitClock(void)
{
    /* Bật PWR + voltage scale 1 (RM0090 §5.3.3) */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR      |= PWR_CR_VOS;

    /* Flash: 5WS + prefetch + I-cache + D-cache */
    FLASH->ACR = FLASH_ACR_LATENCY_5WS | FLASH_ACR_PRFTEN
               | FLASH_ACR_ICEN | FLASH_ACR_DCEN;
    /* Chờ latency được chấp nhận trước khi tăng clock */
    while ((FLASH->ACR & 0x7UL) != FLASH_ACR_LATENCY_5WS) { __asm volatile ("nop"); }

    /* Bật HSE, chờ ổn định */
    RCC->CR |= RCC_CR_HSEON;
    while ((RCC->CR & RCC_CR_HSERDY) == 0U) { __asm volatile ("nop"); }

    /* Cấu hình PLL */
    RCC->PLLCFGR = RCC_PLLCFGR_VAL;

    /* Bus dividers (set trước bật PLL) */
    RCC->CFGR = RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2;

    /* Bật PLL, chờ lock */
    RCC->CR |= RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) == 0U) { __asm volatile ("nop"); }

    /* Chuyển SYSCLK → PLL */
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & (0x3UL << 2)) != RCC_CFGR_SWS_PLL) { __asm volatile ("nop"); }
}


void Mcu_InitSysTick(void)
{
    SYSTICK->LOAD = 168000UL - 1UL;   /* 168 000 ticks = 1 ms */
    SYSTICK->VAL  = 0UL;
    SYSTICK->CTRL = SYSTICK_CLKSRC | SYSTICK_TICKINT | SYSTICK_ENABLE;
}
