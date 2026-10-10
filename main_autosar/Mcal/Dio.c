#include "Dio.h"
#include "Reg.h"


void Dio_Init(void)
{
    /* Bật clock tất cả port */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN
                 |  RCC_AHB1ENR_GPIOCEN  | RCC_AHB1ENR_GPIODEN
                 |  RCC_AHB1ENR_GPIOHEN;
    (void)RCC->AHB1ENR;  

    /* ===== GPIOA ===== */
    /* PA2 AF7 (USART TX): MODER=10, OTYPER=0(PP), OSPEEDR=11(HS), PUPDR=00 */
    /* PA3 AF7 (USART RX): MODER=10, PUPDR=01(PU)                            */
    GPIOA->MODER   &= ~((0x3UL<<(2*2)) | (0x3UL<<(3*2)));
    GPIOA->MODER   |=  (GPIO_AF<<(2*2)) | (GPIO_AF<<(3*2));
    GPIOA->OTYPER  &= ~(1UL << 2);
    GPIOA->OSPEEDR |=  (0x3UL << (2*2));
    GPIOA->PUPDR   &= ~((0x3UL<<(2*2)) | (0x3UL<<(3*2)));
    GPIOA->PUPDR   |=  (GPIO_PU << (3*2));
    /* AFRL (pin 0-7): PA2=AF7, PA3=AF7 */
    GPIOA->AFR[0]  &= ~((0xFUL<<(2*4)) | (0xFUL<<(3*4)));
    GPIOA->AFR[0]  |=  (AF7_USART<<(2*4)) | (AF7_USART<<(3*4));

    /* PA4 ADC1_IN4: Analog, no pull */
    GPIOA->MODER   &= ~(0x3UL << (4*2));
    GPIOA->MODER   |=  (GPIO_AN << (4*2));
    GPIOA->PUPDR   &= ~(0x3UL << (4*2));

    /* ===== GPIOB ===== */
    /* PB6 I2C1_SCL, PB7 I2C1_SDA: AF4, open-drain, HS, pull-up */
    GPIOB->MODER   &= ~((0x3UL<<(6*2)) | (0x3UL<<(7*2)));
    GPIOB->MODER   |=  (GPIO_AF<<(6*2)) | (GPIO_AF<<(7*2));
    GPIOB->OTYPER  |=  (1UL<<6) | (1UL<<7);      /* open-drain */
    GPIOB->OSPEEDR |=  (0x3UL<<(6*2)) | (0x3UL<<(7*2));
    GPIOB->PUPDR   &= ~((0x3UL<<(6*2)) | (0x3UL<<(7*2)));
    GPIOB->PUPDR   |=  (GPIO_PU<<(6*2)) | (GPIO_PU<<(7*2));
    /* AFRL: PB6=AF4, PB7=AF4 */
    GPIOB->AFR[0]  &= ~((0xFUL<<(6*4)) | (0xFUL<<(7*4)));
    GPIOB->AFR[0]  |=  (AF4_I2C1<<(6*4)) | (AF4_I2C1<<(7*4));

    /* ===== GPIOC ===== */
    /* PC10 SW1 (brake), PC12 SW2 (dir): Input, pull-up – thay HAL_GPIO_Init */
    GPIOC->MODER   &= ~((0x3UL<<(10*2)) | (0x3UL<<(12*2)));
    /* MODER = 00 (input) – đã clear */
    GPIOC->PUPDR   &= ~((0x3UL<<(10*2)) | (0x3UL<<(12*2)));
    GPIOC->PUPDR   |=  (GPIO_PU<<(10*2)) | (GPIO_PU<<(12*2));

    /* ===== GPIOD: CAN1 PD0 RX, PD1 TX - match HAL MSP exactly ===== */
    GPIOD->MODER &= ~((0x3UL << (0U * 2U)) | (0x3UL << (1U * 2U)));
    GPIOD->MODER |=  ((0x2UL << (0U * 2U)) | (0x2UL << (1U * 2U)));   // AF mode

    GPIOD->OTYPER &= ~((1UL << 0U) | (1UL << 1U));                    // push-pull both

    GPIOD->OSPEEDR &= ~((0x3UL << (0U * 2U)) | (0x3UL << (1U * 2U)));
    GPIOD->OSPEEDR |=  ((0x3UL << (0U * 2U)) | (0x3UL << (1U * 2U))); // very high

    GPIOD->PUPDR &= ~((0x3UL << (0U * 2U)) | (0x3UL << (1U * 2U)));   // NOPULL

    GPIOD->AFR[0] &= ~((0xFUL << (0U * 4U)) | (0xFUL << (1U * 4U)));
    GPIOD->AFR[0] |=  ((0x9UL << (0U * 4U)) | (0x9UL << (1U * 4U)));  // AF9 CAN1
}

uint8 Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    switch (ChannelId) {
    case DIO_CHANNEL_BRAKE_SW:
        return (uint8)(((GPIOC->IDR & (1UL << 10U)) == 0U) ? 1U : 0U);
    case DIO_CHANNEL_DIRECTION_SW:
        return (uint8)(((GPIOC->IDR & (1UL << 12U)) == 0U) ? 1U : 0U);
    default:
        return 0U;
    }
}
