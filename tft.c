#include "tft.h"
#include "ltdc.h"
#include "gpio.h"
#include "rcc.h"
#include "sdram.h"

#include "delay.h"

#define DISP_PORT GPIOI
#define DISP_PIN 12

#define BACKLIGHT_PORT GPIOK
#define BACKLIGHT_PIN 3

static void SetupGPIO();

void TFT_Init()
{
    SetupGPIO();

	GPIO_WritePin(DISP_PORT, DISP_PIN, 1);
	GPIO_WritePin(BACKLIGHT_PORT, BACKLIGHT_PIN, 1);

    RCC->PLLSAICFGR = (384 << 6) | (5 << 28);

    RCC->DCKCFGR1 |= (2 << 16);

    RCC->CR |= RCC_CR_PLLSAION;
    while((RCC->CR & RCC_CR_PLLSAIRDY) == 0);
    RCC->APB2ENR |= RCC_APB2ENR_LTDCEN;

    LTDC->SSCR = ((HSYNC - 1) << 16) | (VSYNC - 1);
    LTDC->BPCR = ((HSYNC + HBP - 1) << 16) | (VSYNC + VBP - 1);
    LTDC->AWCR = ((HSYNC + HBP + LCD_WIDTH - 1) << 16) | (VSYNC + VBP + LCD_HEIGHT - 1);
    LTDC->TWCR = ((HSYNC + HBP + LCD_WIDTH + HFP - 1) << 16) | (VSYNC + VBP + LCD_HEIGHT + VFP - 1);
	LTDC->BCCR = (255 << 16) | 255;

	LTDC->IER = (1 << 3);

    LTDC->GCR |= LTDC_GCR_LTDCEN;
}

static void SetupGPIO()
{
	//red
	GPIO_AFConf(GPIOI, 15, 14);
	GPIO_AFConf(GPIOJ, 0, 14);
	GPIO_AFConf(GPIOJ, 1, 14);
	GPIO_AFConf(GPIOJ, 2, 14);
	GPIO_AFConf(GPIOJ, 3, 14);
	GPIO_AFConf(GPIOJ, 4, 14);
	GPIO_AFConf(GPIOJ, 5, 14);
	GPIO_AFConf(GPIOJ, 6, 14);

	//green
	GPIO_AFConf(GPIOJ, 7, 14);
	GPIO_AFConf(GPIOJ, 8, 14);
	GPIO_AFConf(GPIOJ, 9, 14);
	GPIO_AFConf(GPIOJ, 10, 14);
	GPIO_AFConf(GPIOJ, 11, 14);
	GPIO_AFConf(GPIOK, 0, 14);
	GPIO_AFConf(GPIOK, 1, 14);
	GPIO_AFConf(GPIOK, 2, 14);

	//blue
	GPIO_AFConf(GPIOE, 4, 14);
	GPIO_AFConf(GPIOJ, 13, 14);
	GPIO_AFConf(GPIOJ, 14, 14);
	GPIO_AFConf(GPIOJ, 15, 14);
	GPIO_AFConf(GPIOG, 12, 9);
	GPIO_AFConf(GPIOK, 4, 14);
	GPIO_AFConf(GPIOK, 5, 14);
	GPIO_AFConf(GPIOK, 6, 14);

	//hsync
	GPIO_AFConf(GPIOI, 10, 14);
	//vsync
	GPIO_AFConf(GPIOI, 9, 14);
	//de
	GPIO_AFConf(GPIOK, 7, 14);
	//clk
	GPIO_AFConf(GPIOI, 14, 14);

	GPIO_AFConf(GPIOI, 8, 14);
	GPIO_AFConf(GPIOI, 13, 14);

	//disp enable
	GPIO_Conf(DISP_PORT, DISP_PIN, GPIO_MODE_OUT, GPIO_OTYPE_PUSHPULL, GPIO_OSPEED_VERYHIGHSPEED, GPIO_PUD_NONE);
	//backlight enable
	GPIO_Conf(BACKLIGHT_PORT, BACKLIGHT_PIN, GPIO_MODE_OUT, GPIO_OTYPE_PUSHPULL, GPIO_OSPEED_VERYHIGHSPEED, GPIO_PUD_NONE);
}
