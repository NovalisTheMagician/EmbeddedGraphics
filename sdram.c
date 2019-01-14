#include "stm32f7.h"
#include "rcc.h"
#include "gpio.h"
#include "sdram.h"

#define TMRD(x) (x << 0)
#define TXSR(x) (x << 4)
#define TRAS(x) (x << 8)
#define TRC(x)  (x << 12)
#define TWR(x)  (x << 16)
#define TRP(x)  (x << 20)
#define TRCD(x) (x << 24)

static  GPIO_TypeDef * const GPIOInitTable[] = {
		// address ports
		GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOG, GPIOG,
		// data ports
		GPIOD, GPIOD, GPIOD, GPIOD, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE,
		GPIOD, GPIOD, GPIOD,
		// control ports
		GPIOC, GPIOH, GPIOH, GPIOE, GPIOE, GPIOF, GPIOG, GPIOG, GPIOG, GPIOG,
		0
};

static uint8_t const PINInitTable[] = {
		// address pins
		0, 1, 2, 3, 4, 5, 12, 13, 14, 15, 0, 1,
		// data pins
		14, 15, 0, 1, 7, 8, 9, 10, 11, 12, 13, 14, 15,
		8, 9, 10,
		// control pins
		3, 3, 5, 0, 1, 11, 4, 5, 8, 15,
		0
};

void InitGPIO()
{

}

void SDRAM_Init()
{
	volatile uint32_t ptr = 0;
	volatile uint32_t i = 0;

	while(GPIOInitTable[i] != 0) 
	{
		GPIO_AFConf(GPIOInitTable[i], PINInitTable[i], 12);
		i++;
	}
	
	RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;
	// Initialization step 1
	SDRAM->SDCR[0] = FMC_SDCR_SDCLK_2 | FMC_SDCR_NC_8 | FMC_SDCR_NR_12 | FMC_SDCR_MWID_16 | FMC_SDCR_NB_4 | FMC_SDCR_CAS_2 | FMC_SDCR_RBURST;
	// Initialization step 2
	SDRAM->SDTR[0] = TRC(7) | TRP(2) | TMRD(2) | TXSR(7) | TRAS(4) | TWR(2) | TRCD(2);
	// Initialization step 3	
	while(SDRAM->SDSR & FMC_SDSR_BUSY);
	SDRAM->SDCMR = FMC_SDCMR_MODE_CCE | FMC_SDCMR_CTB1 | (1 << 5);
	// Initialization step 4
	for(i = 0; i  < 1000000; i++);
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

	uint32_t temp = SDRAM->SDCR[0];
	SDRAM->SDCR[0] = (temp & ~FMC_SDCR_WP);

	// Clear SDRAM
	for(ptr = SDRAM_BASE_ADDR; ptr < (SDRAM_BASE_ADDR + SDRAM_SIZE); ptr += 4)
			*((uint32_t *)ptr) = 0xFF000000;
}
