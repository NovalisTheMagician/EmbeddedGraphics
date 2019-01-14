#ifndef RCC_H_
#define RCC_H_

#include "stm32f7.h"

typedef struct
{
                                // offset   Description
    volatile uint32_t CR;       // 0x00     RCC clock control
    volatile uint32_t PLLCFGR;  // 0x04     RCC PLL configuration
    volatile uint32_t CFGR;     // 0x08     RCC clock configuration
    volatile uint32_t CIR;      // 0x0c     RCC clock interrupt
    volatile uint32_t AHB1RSTR; // 0x10     RCC AHB1 peripheral reset
    volatile uint32_t AHB2RSTR; // 0x14     RCC AHB2 peripheral reset
    volatile uint32_t AHB3RSTR; // 0x18     RCC AHB3 peripheral reset
    uint32_t RESERVED0;         // 0x1c     Reserved
    volatile uint32_t APB1RSTR; // 0x20     RCC APB1 peripheral reset
    volatile uint32_t APB2RSTR; // 0x24     RCC APB2 peripheral reset
    uint32_t RESERVED1[2];      // 0x28-0x2C    Reserved
    volatile uint32_t AHB1ENR;  // 0x30     RCC AHB1 peripheral clock
    volatile uint32_t AHB2ENR;  // 0x34     RCC AHB2 peripheral clock
    volatile uint32_t AHB3ENR;  // 0x38     RCC AHB3 peripheral clock
    uint32_t RESERVED2;         // 0x3c     Reserved
    volatile uint32_t APB1ENR;  // 0x40     RCC APB1 peripheral clock enable
    volatile uint32_t APB2ENR;  // 0x44     RCC APB2 peripheral clock enable
    uint32_t RESERVED3[2];      // 0x48-0x4c --Reserved--
    volatile uint32_t AHB1LPENR; // 0x50    RCC AHB1 p-clock enable in LP mode 
    volatile uint32_t AHB2LPENR; // 0x54    RCC AHB2 p-clock enable in LP mode
    volatile uint32_t AHB3LPENR; // 0x58    RCC AHB3 p-clock enable in LP mode
    uint32_t RESERVED4;         // 0x5c     --Reserved--
    volatile uint32_t APB1LPENR; // 0x60    RCC APB1 p-clock enable in LP mode
    volatile uint32_t APB2LPENR; // 0x64    RCC APB2 p-clock enable in LP mode
    uint32_t RESERVED5[2];      // 0x68-0x6c    Reserved
    volatile uint32_t BDCR;     // 0x70     RCC Backup domain control
    volatile uint32_t CSR;      // 0x74     RCC clock control & status
    uint32_t RESERVED6[2];      // 0x78-0x7c    Reserved
    volatile uint32_t SSCGR;    // 0x80     RCC spread spectrum clock generation
    volatile uint32_t PLLI2SCFGR; // 0x84   RCC PLLI2S configuration 
    volatile uint32_t PLLSAICFGR;
    volatile uint32_t DCKCFGR1;
    volatile uint32_t DCKCFGR2;
} RCC_TypeDef;

#define RCC_BASE    (AHB1PERIPH_BASE + 0x3800)
#define RCC         ((RCC_TypeDef *) RCC_BASE)

/***  RCC_AHB1ENR register  ***/
#define RCC_AHB1ENR_GPIOAEN ((uint32_t)0x00000001)
#define RCC_AHB1ENR_GPIOBEN ((uint32_t)0x00000002)
#define RCC_AHB1ENR_GPIOCEN ((uint32_t)0x00000004)
#define RCC_AHB1ENR_GPIODEN ((uint32_t)0x00000008)
#define RCC_AHB1ENR_GPIOEEN ((uint32_t)0x00000010)
#define RCC_AHB1ENR_GPIOFEN ((uint32_t)0x00000020)
#define RCC_AHB1ENR_GPIOGEN ((uint32_t)0x00000040)
#define RCC_AHB1ENR_GPIOHEN ((uint32_t)0x00000080)
#define RCC_AHB1ENR_GPIOIEN ((uint32_t)0x00000100)
#define RCC_AHB1ENR_GPIOJEN ((uint32_t)0x00000200)
#define RCC_AHB1ENR_GPIOKEN ((uint32_t)0x00000400)

#define RCC_AHB1ENR_DMA2DEN ((uint32_t)(1 << 23))

#define RCC_APB2ENR_SPI1EN  ((uint32_t)(1 << 12))
#define RCC_APB1ENR_SPI2EN  ((uint32_t)(1 << 14))
#define RCC_APB1ENR_SPI3EN  ((uint32_t)(1 << 15))
#define RCC_APB2ENR_SPI4EN  ((uint32_t)(1 << 13))
#define RCC_APB2ENR_SPI5EN  ((uint32_t)(1 << 20))
#define RCC_APB2ENR_SPI6EN  ((uint32_t)(1 << 21))

#define RCC_AHB3ENR_FMCEN ((uint32_t)(1 << 0))

#define RCC_APB1ENR_PWREN ((uint32_t)(1 << 28))

#define RCC_APB2ENR_LTDCEN ((uint32_t)(1 << 26))

#define RCC_CR_PLLSAIRDY    ((uint32_t)(1 << 29))
#define RCC_CR_PLLSAION     ((uint32_t)(1 << 28))
#define RCC_CR_PLLI2SRDY    ((uint32_t)(1 << 27))
#define RCC_CR_PLLI2SON     ((uint32_t)(1 << 26))
#define RCC_CR_PLLRDY       ((uint32_t)(1 << 25))
#define RCC_CR_PLLON        ((uint32_t)(1 << 24))
#define RCC_CR_CSSON        ((uint32_t)(1 << 19))
#define RCC_CR_HSEBYP       ((uint32_t)(1 << 18))
#define RCC_CR_HSERDY       ((uint32_t)(1 << 17))
#define RCC_CR_HSEON        ((uint32_t)(1 << 16))
#define RCC_CR_HSIRDY       ((uint32_t)(1 << 1))
#define RCC_CR_HSION        ((uint32_t)(1 << 0))

#define RCC_PLLCFGR_PLLSRC_HSE ((uint32_t)(1 << 22))
#define RCC_PLLCFGR_PLLSRC_HSI ((uint32_t)(0 << 22))
#define PLL_Q(x) ((uint32_t)((x) << 24))
#define PLL_P(x) ((uint32_t)((x) << 16))
#define PLL_N(x) ((uint32_t)((x) << 6))
#define PLL_M(x) ((uint32_t)((x) << 0))

#define RCC_CFGR_PPRE2_DIV1     ((uint32_t)(0 << 13))
#define RCC_CFGR_PPRE2_DIV2     ((uint32_t)(4 << 13))
#define RCC_CFGR_PPRE2_DIV4     ((uint32_t)(5 << 13))
#define RCC_CFGR_PPRE2_DIV8     ((uint32_t)(6 << 13))
#define RCC_CFGR_PPRE2_DIV16    ((uint32_t)(7 << 13))

#define RCC_CFGR_PPRE1_DIV1     ((uint32_t)(0 << 10))
#define RCC_CFGR_PPRE1_DIV2     ((uint32_t)(4 << 10))
#define RCC_CFGR_PPRE1_DIV4     ((uint32_t)(5 << 10))
#define RCC_CFGR_PPRE1_DIV8     ((uint32_t)(6 << 10))
#define RCC_CFGR_PPRE1_DIV16    ((uint32_t)(7 << 10))

#define RCC_CFGR_HPRE_DIV1      ((uint32_t)(0 << 4))
#define RCC_CFGR_HPRE_DIV2      ((uint32_t)(8 << 4))
#define RCC_CFGR_HPRE_DIV4      ((uint32_t)(9 << 4))
#define RCC_CFGR_HPRE_DIV8      ((uint32_t)(10 << 4))
#define RCC_CFGR_HPRE_DIV16     ((uint32_t)(11 << 4))
#define RCC_CFGR_HPRE_DIV32     ((uint32_t)(12 << 4))
#define RCC_CFGR_HPRE_DIV64     ((uint32_t)(13 << 4))
#define RCC_CFGR_HPRE_DIV128    ((uint32_t)(14 << 4))
#define RCC_CFGR_HPRE_DIV256    ((uint32_t)(15 << 4))
#define RCC_CFGR_HPRE_DIV512    ((uint32_t)(16 << 4))

#define RCC_CFGR_SWS_HSI ((uint32_t)(0 << 2))
#define RCC_CFGR_SWS_HSE ((uint32_t)(1 << 2))
#define RCC_CFGR_SWS_PLL ((uint32_t)(2 << 2))

#define RCC_CFGR_SW_HSI ((uint32_t)(0))
#define RCC_CFGR_SW_HSE ((uint32_t)(1))
#define RCC_CFGR_SW_PLL ((uint32_t)(2))

#define AHB_PRESCALER RCC_CFGR_HPRE_DIV1
#define APB1_PRESCALER RCC_CFGR_PPRE1_DIV4
#define APB2_PRESCALER RCC_CFGR_PPRE2_DIV2

#define HSE_VALUE 25000000

#define PLL_M_Val 25
#define PLL_N_Val 400
#define PLL_P_Val 0
#define PLL_Q_Val 9

void RCC_InitClocks();

#endif
