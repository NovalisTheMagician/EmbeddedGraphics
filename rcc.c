#include "rcc.h"
#include "pwr.h"
#include "flash.h"

void RCC_InitClocks()
{
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    PWR->CR1 |= PWR_CR_VOS_SCALE1;

    RCC->CR |= RCC_CR_HSEON;    // HSE ON
    while((RCC->CR & RCC_CR_HSERDY) == 0);

    RCC->PLLCFGR = PLL_M(PLL_M_Val) | PLL_Q(PLL_Q_Val) | PLL_N(PLL_N_Val) | PLL_P(PLL_P_Val) | RCC_PLLCFGR_PLLSRC_HSE;

    RCC->CFGR |= AHB_PRESCALER | APB1_PRESCALER | APB2_PRESCALER | RCC_CFGR_SW_PLL;

    FLASH->ACR |= 5;

    // enable prefetch and art accelerator
    FLASH->ACR |= (1 << 9) | (1 << 8);

    // Now, switch ON the PLL
    RCC->CR |= RCC_CR_PLLON;    // PLL ON
    while((RCC->CR & 0x02000000) == 0);

    // wait till PLL is really used as SYSCLK
    while((RCC->CFGR & RCC_CFGR_SWS_PLL) == 0);
}
