#ifndef REG_H
#define REG_H

#include <stdint.h>


#define PERIPH_BASE     0x40000000UL

/* APB1 – max 42 MHz */
#define APB1_BASE       (PERIPH_BASE + 0x00000000UL)
#define USART2_BASE     (APB1_BASE   + 0x00004400UL)   /* §30 */
#define I2C1_BASE       (APB1_BASE   + 0x00005400UL)   /* §27 */
#define CAN1_BASE       (APB1_BASE   + 0x00006400UL)   /* §32 */
#define PWR_BASE        (APB1_BASE   + 0x00007000UL)

/* APB2 – max 84 MHz */
#define APB2_BASE       (PERIPH_BASE + 0x00010000UL)
#define ADC1_BASE       (APB2_BASE   + 0x00002000UL)   /* §13 */
#define ADC_CMN_BASE    (APB2_BASE   + 0x00002300UL)

/* AHB1 */
#define AHB1_BASE       (PERIPH_BASE + 0x00020000UL)
#define GPIOA_BASE      (AHB1_BASE   + 0x00000000UL)
#define GPIOB_BASE      (AHB1_BASE   + 0x00000400UL)
#define GPIOC_BASE      (AHB1_BASE   + 0x00000800UL)
#define GPIOD_BASE      (AHB1_BASE   + 0x00000C00UL)
#define GPIOH_BASE      (AHB1_BASE   + 0x00001C00UL)
#define RCC_BASE        (AHB1_BASE   + 0x00003800UL)   /* §8  */
#define FLASH_R_BASE    (AHB1_BASE   + 0x00003C00UL)   /* §3  */

/* Cortex-M4 */
#define SYSTICK_BASE    0xE000E010UL
#define NVIC_ISER_BASE  0xE000E100UL

typedef struct {
    volatile uint32_t CR;           /* 0x00 */
    volatile uint32_t PLLCFGR;     /* 0x04 */
    volatile uint32_t CFGR;        /* 0x08 */
    volatile uint32_t CIR;         /* 0x0C */
    volatile uint32_t AHB1RSTR;    /* 0x10 */
    volatile uint32_t AHB2RSTR;    /* 0x14 */
    volatile uint32_t AHB3RSTR;    /* 0x18 */
    uint32_t          _r0;
    volatile uint32_t APB1RSTR;    /* 0x20 */
    volatile uint32_t APB2RSTR;    /* 0x24 */
    uint32_t          _r1[2];
    volatile uint32_t AHB1ENR;     /* 0x30 */
    volatile uint32_t AHB2ENR;     /* 0x34 */
    volatile uint32_t AHB3ENR;     /* 0x38 */
    uint32_t          _r2;
    volatile uint32_t APB1ENR;     /* 0x40 */
    volatile uint32_t APB2ENR;     /* 0x44 */
    uint32_t          _r3[2];
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    uint32_t          _r4;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    uint32_t          _r5[2];
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    uint32_t          _r6[2];
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
} RCC_t;

/* ---- Flash (RM0090 §3.4) ---- */
typedef struct {
    volatile uint32_t ACR;
    volatile uint32_t KEYR;
    volatile uint32_t OPTKEYR;
    volatile uint32_t SR;
    volatile uint32_t CR;
    volatile uint32_t OPTCR;
} FLASH_t;

/* ---- PWR ---- */
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CSR;
} PWR_t;

/* ---- GPIO (RM0090 §8.4) ---- */
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];   /* [0]=AFRL pin0-7, [1]=AFRH pin8-15 */
} GPIO_t;

/* ---- USART (RM0090 §30.6) ---- */
typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_t;

/* ---- I2C (RM0090 §27.6) ---- */
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
    volatile uint32_t FLTR;
} I2C_t;

/* ---- ADC (RM0090 §13.13) ---- */
typedef struct {
    volatile uint32_t SR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMPR1;
    volatile uint32_t SMPR2;
    uint32_t          JOFR[4];
    volatile uint32_t HTR;
    volatile uint32_t LTR;
    volatile uint32_t SQR1;
    volatile uint32_t SQR2;
    volatile uint32_t SQR3;
    volatile uint32_t JSQR;
    uint32_t          JDR[4];
    volatile uint32_t DR;
} ADC_t;

typedef struct {
    volatile uint32_t CSR;
    volatile uint32_t CCR;
    volatile uint32_t CDR;
} ADC_CMN_t;

/* ---- CAN (RM0090 §32.9) ---- */
typedef struct {
    volatile uint32_t MCR;          /* 0x000 */
    volatile uint32_t MSR;          /* 0x004 */
    volatile uint32_t TSR;          /* 0x008 */
    volatile uint32_t RF0R;         /* 0x00C */
    volatile uint32_t RF1R;         /* 0x010 */
    volatile uint32_t IER;          /* 0x014 */
    volatile uint32_t ESR;          /* 0x018 */
    volatile uint32_t BTR;          /* 0x01C */
    uint32_t          _r[88];
    /* TX mailboxes 0-2 */
    volatile uint32_t TI0R;  volatile uint32_t TDT0R; volatile uint32_t TDL0R; volatile uint32_t TDH0R;
    volatile uint32_t TI1R;  volatile uint32_t TDT1R; volatile uint32_t TDL1R; volatile uint32_t TDH1R;
    volatile uint32_t TI2R;  volatile uint32_t TDT2R; volatile uint32_t TDL2R; volatile uint32_t TDH2R;
    /* RX FIFO 0 */
    volatile uint32_t RI0R;  volatile uint32_t RDT0R; volatile uint32_t RDL0R; volatile uint32_t RDH0R;
    /* RX FIFO 1 */
    volatile uint32_t RI1R;  volatile uint32_t RDT1R; volatile uint32_t RDL1R; volatile uint32_t RDH1R;
    uint32_t          _r2[12];
    /* Filter */
    volatile uint32_t FMR;
    volatile uint32_t FM1R;
    uint32_t          _r3;
    volatile uint32_t FS1R;
    uint32_t          _r4;
    volatile uint32_t FFA1R;
    uint32_t          _r5;
    volatile uint32_t FA1R;
    uint32_t          _r6[8];
    volatile uint32_t FR[28];
} CAN_t;

/* ---- SysTick (Cortex-M4 PPB) ---- */
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} SysTick_t;

/* ---- Peripheral pointers ---- */
#define RCC      ((RCC_t     *)RCC_BASE)
#define FLASH    ((FLASH_t   *)FLASH_R_BASE)
#define PWR      ((PWR_t     *)PWR_BASE)
#define GPIOA    ((GPIO_t    *)GPIOA_BASE)
#define GPIOB    ((GPIO_t    *)GPIOB_BASE)
#define GPIOC    ((GPIO_t    *)GPIOC_BASE)
#define GPIOD    ((GPIO_t    *)GPIOD_BASE)
#define USART2   ((USART_t   *)USART2_BASE)
#define I2C1     ((I2C_t     *)I2C1_BASE)
#define ADC1     ((ADC_t     *)ADC1_BASE)
#define ADC_CMN  ((ADC_CMN_t *)ADC_CMN_BASE)
#define CAN1     ((CAN_t     *)CAN1_BASE)
#define SYSTICK  ((SysTick_t *)SYSTICK_BASE)

/* RCC */
#define RCC_CR_HSEON            (1UL << 16)
#define RCC_CR_HSERDY           (1UL << 17)
#define RCC_CR_PLLON            (1UL << 24)
#define RCC_CR_PLLRDY           (1UL << 25)
/* PLLCFGR: PLLM=4[5:0], PLLN=168[14:6], PLLP=0→÷2[17:16],
            PLLSRC=HSE[22], PLLQ=4[27:24]                    */
#define RCC_PLLCFGR_VAL         ((4UL)|(168UL<<6)|(0UL<<16)|(1UL<<22)|(4UL<<24))
#define RCC_CFGR_SW_PLL         (0x2UL << 0)
#define RCC_CFGR_SWS_PLL        (0x2UL << 2)
#define RCC_CFGR_HPRE_DIV1      (0x0UL << 4)
#define RCC_CFGR_PPRE1_DIV4     (0x5UL << 10)
#define RCC_CFGR_PPRE2_DIV2     (0x4UL << 13)
#define RCC_APB1ENR_PWREN       (1UL << 28)
#define RCC_APB1ENR_USART2EN    (1UL << 17)
#define RCC_APB1ENR_I2C1EN      (1UL << 21)
#define RCC_APB1ENR_CAN1EN      (1UL << 25)
#define RCC_APB1RSTR_I2C1RST    (1UL << 21)
#define RCC_APB2ENR_ADC1EN      (1UL << 8)
#define RCC_AHB1ENR_GPIOAEN     (1UL << 0)
#define RCC_AHB1ENR_GPIOBEN     (1UL << 1)
#define RCC_AHB1ENR_GPIOCEN     (1UL << 2)
#define RCC_AHB1ENR_GPIODEN     (1UL << 3)
#define RCC_AHB1ENR_GPIOHEN     (1UL << 7)

/* Flash */
#define FLASH_ACR_LATENCY_5WS   (5UL << 0)
#define FLASH_ACR_PRFTEN        (1UL << 8)
#define FLASH_ACR_ICEN          (1UL << 9)
#define FLASH_ACR_DCEN          (1UL << 10)

/* PWR */
#define PWR_CR_VOS              (1UL << 14)

/* GPIO MODER: 00=in 01=out 10=AF 11=analog */
#define GPIO_AF    2UL
#define GPIO_IN    0UL
#define GPIO_AN    3UL
/* PUPDR: 00=none 01=PU */
#define GPIO_PU    1UL
/* AF numbers (RM0090 tbl 9) */
#define AF4_I2C1   4UL
#define AF7_USART  7UL
#define AF9_CAN    9UL

/* USART */
#define USART_SR_TXE    (1UL << 7)
#define USART_SR_TC     (1UL << 6)
#define USART_CR1_UE    (1UL << 13)
#define USART_CR1_TE    (1UL << 3)
#define USART_CR1_RE    (1UL << 2)

/* I2C */
#define I2C_CR1_PE      (1UL << 0)
#define I2C_CR1_START   (1UL << 8)
#define I2C_CR1_STOP    (1UL << 9)
#define I2C_CR1_ACK     (1UL << 10)
#define I2C_CR1_SWRST   (1UL << 15)
#define I2C_SR1_SB      (1UL << 0)
#define I2C_SR1_ADDR    (1UL << 1)
#define I2C_SR1_BTF     (1UL << 2)
#define I2C_SR1_TXE     (1UL << 7)
#define I2C_SR1_AF      (1UL << 10)
#define I2C_SR2_BUSY    (1UL << 1)

/* ADC */
#define ADC_SR_EOC          (1UL << 1)
#define ADC_CR2_ADON        (1UL << 0)
#define ADC_CR2_CONT        (1UL << 1)
#define ADC_CR2_EOCS        (1UL << 10)
#define ADC_CR2_SWSTART     (1UL << 30)
#define ADC_CCR_ADCPRE_DIV4 (0x1UL << 16)

/* CAN */
#define CAN_MCR_INRQ    (1UL << 0)
#define CAN_MCR_SLEEP   (1UL << 1)
#define CAN_MCR_NART    (1UL << 4)   /* 0 = auto retransmit (ENABLE) */
#define CAN_MCR_ABOM    (1UL << 6)
#define CAN_MSR_INAK    (1UL << 0)
#define CAN_MSR_SLAK    (1UL << 1)
#define CAN_TSR_TME0    (1UL << 26)
#define CAN_TSR_TME1    (1UL << 27)
#define CAN_TSR_TME2    (1UL << 28)
#define CAN_TIR_TXRQ    (1UL << 0)
#define CAN_RF1R_FMP1   (0x3UL)
#define CAN_RF1R_RFOM1  (1UL << 5)
#define CAN_IER_FMPIE1  (1UL << 4)
#define CAN_FMR_FINIT   (1UL << 0)
#define CAN_RI1R_STID_S 21U
#define CAN_RI1R_IDE    (1UL << 2)

#define CAN_TSR_RQCP0   (1UL << 0)
#define CAN_TSR_TXOK0   (1UL << 1)
#define CAN_TSR_ALST0   (1UL << 2)
#define CAN_TSR_TERR0   (1UL << 3)
#define CAN_TSR_ABRQ0   (1UL << 7)

#define CAN_TSR_RQCP1   (1UL << 8)
#define CAN_TSR_TXOK1   (1UL << 9)
#define CAN_TSR_ALST1   (1UL << 10)
#define CAN_TSR_TERR1   (1UL << 11)
#define CAN_TSR_ABRQ1   (1UL << 15)

#define CAN_TSR_RQCP2   (1UL << 16)
#define CAN_TSR_TXOK2   (1UL << 17)
#define CAN_TSR_ALST2   (1UL << 18)
#define CAN_TSR_TERR2   (1UL << 19)
#define CAN_TSR_ABRQ2   (1UL << 23)

#define RCC_APB1RSTR_CAN1RST    (1UL << 25)

/* CAN1 RX1 IRQ number = 21 (RM0090 §10.2 tbl 49) */
#define CAN1_RX1_IRQn   21U

/* SysTick */
#define SYSTICK_ENABLE  (1UL << 0)
#define SYSTICK_TICKINT (1UL << 1)
#define SYSTICK_CLKSRC  (1UL << 2)

/* Timeout counters (poll loops) */
#define I2C_TIMEOUT     200000UL
#define ADC_TIMEOUT     100000UL
#define CAN_TIMEOUT     100000UL
#define UART_TIMEOUT    100000UL

/* NVIC enable helper */

#define CAN_ID_MAIN_TO_ABS      0x121UL  /* Main command -> ABS */
#define CAN_ID_ABS_TO_MAIN      0x122UL  /* ABS feedback -> Main */
#define CAN_ID_MAIN_CAN_DIAG    0x211UL  /* Main CAN diagnostic */

#define UART_PRINT_TIMEOUT_MS   100U
#define ADC_POLL_TIMEOUT_MS     10U
#define TASK_PERIOD_MS          100U
#define COMIF_CAN_DIAG_PERIOD_MS 100U

#define LCD_ROW_LEN             16U
#define LCD_BUF_LEN             17U
#define LCD_BLANK_LINE          "                "
#define LCD_DANGER_LINE         "AIRBAG: DANGER "
#define LCD_SAFE_LINE           "AIRBAG: SAFE   "
#define LCD_BRAKE_LINE          "   Car Braked   "

#define BUTTON_PRESSED          1U
#define BUTTON_RELEASED         0U
#define MOVAVG_OLD_WEIGHT       3U
#define MOVAVG_DIVISOR          4U
#define DISPLAY_ZERO_THRESHOLD  2U

/* LCD I2C address – SLAVE_ADDRESS_LCD = 0x4E (8-bit) → 7-bit = 0x27 */
#define LCD_I2C_7BIT            0x27U

/* PCF8574 → HD44780 bit layout (giống i2c-lcd.c):
 *  P7 P6 P5 P4 | P3  P2  P1  P0
 *  D7 D6 D5 D4 | BL  EN  RW  RS
 *  BL  = 0x08   luôn bật
 *  EN  = 0x04
 *  RW  = 0x02   luôn 0 (write)
 *  RS  = 0x01   0=cmd, 1=data
 */
#define LCD_BL  0x08U
#define LCD_EN  0x04U
#define LCD_RS  0x01U

void nvic_enable(uint32_t irq);

#endif
