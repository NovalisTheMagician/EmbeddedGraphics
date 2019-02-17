#include "stm32f7.h"
#include "rcc.h"
#include "gpio.h"
#include "sdram.h"

#define TMRD(x) ((x) << 0)
#define TXSR(x) ((x) << 4)
#define TRAS(x) ((x) << 8)
#define TRC(x)  ((x) << 12)
#define TWR(x)  ((x) << 16)
#define TRP(x)  ((x) << 20)
#define TRCD(x) ((x) << 24)

static void SetupGPIO();

void SDRAM_Init()
{
	SetupGPIO();
	
	RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;
	// Initialization step 1
	SDRAM->SDCR[0] = FMC_SDCR_SDCLK_2 | FMC_SDCR_NC_8 | FMC_SDCR_NR_12 | FMC_SDCR_MWID_16 | FMC_SDCR_NB_4 | FMC_SDCR_CAS_2 | FMC_SDCR_RBURST;
	// Initialization step 2
	SDRAM->SDTR[0] = TRC(7) | TRP(2) | TMRD(2) | TXSR(7) | TRAS(4) | TWR(2) | TRCD(2);
	// Initialization step 3	
	while(SDRAM->SDSR & FMC_SDSR_BUSY);
	SDRAM->SDCMR = FMC_SDCMR_MODE_CCE | FMC_SDCMR_CTB1 | (1 << 5);
	// Initialization step 4
	for(int i = 0; i  < 1000000; i++);
	// Initialization step 5
	while(SDRAM->SDSR & FMC_SDSR_BUSY);
	SDRAM->SDCMR = FMC_SDCMR_MODE_PALL | FMC_SDCMR_CTB1 | (1 << 5);
	// Initialization step 6
	while(SDRAM->SDSR & FMC_SDSR_BUSY);
	SDRAM->SDCMR = FMC_SDCMR_MODE_AUTOREFRESH | FMC_SDCMR_CTB1 | (8 << 5);
	// Initialization step 7
	while(SDRAM->SDSR & FMC_SDSR_BUSY);
	SDRAM->SDCMR = FMC_SDCMR_MODE_LOADMODE | FMC_SDCMR_CTB1 | (1 << 5) | (0x220 << 9);
	// Initialization step 8
	while(SDRAM->SDSR & FMC_SDSR_BUSY);
	SDRAM->SDRTR |= (0x0603 << 1);
	while(SDRAM->SDSR & FMC_SDSR_BUSY);

	// Clear the WriteProtect bit
	SDRAM->SDCR[0] &= ~FMC_SDCR_WP;
}

static void SetupGPIO()
{
	//address pins
	GPIO_AFConf(GPIOF, 0, 12);
	GPIO_AFConf(GPIOF, 1, 12);
	GPIO_AFConf(GPIOF, 2, 12);
	GPIO_AFConf(GPIOF, 3, 12);
	GPIO_AFConf(GPIOF, 4, 12);
	GPIO_AFConf(GPIOF, 5, 12);
	GPIO_AFConf(GPIOF, 12, 12);
	GPIO_AFConf(GPIOF, 13, 12);
	GPIO_AFConf(GPIOF, 14, 12);
	GPIO_AFConf(GPIOF, 15, 12);
	GPIO_AFConf(GPIOG, 0, 12);
	GPIO_AFConf(GPIOG, 1, 12);

	//data pins
	GPIO_AFConf(GPIOD, 14, 12);
	GPIO_AFConf(GPIOD, 15, 12);
	GPIO_AFConf(GPIOD, 0, 12);
	GPIO_AFConf(GPIOD, 1, 12);
	GPIO_AFConf(GPIOE, 7, 12);
	GPIO_AFConf(GPIOE, 8, 12);
	GPIO_AFConf(GPIOE, 9, 12);
	GPIO_AFConf(GPIOE, 10, 12);
	GPIO_AFConf(GPIOE, 11, 12);
	GPIO_AFConf(GPIOE, 12, 12);
	GPIO_AFConf(GPIOE, 13, 12);
	GPIO_AFConf(GPIOE, 14, 12);
	GPIO_AFConf(GPIOE, 15, 12);
	GPIO_AFConf(GPIOD, 8, 12);
	GPIO_AFConf(GPIOD, 9, 12);
	GPIO_AFConf(GPIOD, 10, 12);
	
	//control pins
	GPIO_AFConf(GPIOC, 3, 12);
	GPIO_AFConf(GPIOH, 3, 12);
	GPIO_AFConf(GPIOH, 5, 12);
	GPIO_AFConf(GPIOE, 0, 12);
	GPIO_AFConf(GPIOE, 1, 12);
	GPIO_AFConf(GPIOF, 11, 12);
	GPIO_AFConf(GPIOG, 4, 12);
	GPIO_AFConf(GPIOG, 5, 12);
	GPIO_AFConf(GPIOG, 8, 12);
	GPIO_AFConf(GPIOG, 15, 12);
}
