#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f7.h"

typedef struct
{
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint16_t BSRRL;
  volatile uint16_t BSRRH;
  volatile uint32_t LCKR;
  volatile uint32_t AFR[2];
} GPIO_TypeDef;

#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASE (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASE (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASE (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASE (AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASE (AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASE (AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASE (AHB1PERIPH_BASE + 0x1C00)
#define GPIOI_BASE (AHB1PERIPH_BASE + 0x2000)
#define GPIOJ_BASE (AHB1PERIPH_BASE + 0x2400)
#define GPIOK_BASE (AHB1PERIPH_BASE + 0x2800)

#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH ((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOI ((GPIO_TypeDef *) GPIOI_BASE)
#define GPIOJ ((GPIO_TypeDef *) GPIOJ_BASE)
#define GPIOK ((GPIO_TypeDef *) GPIOK_BASE)

typedef enum
{
  GPIO_MODE_IN = 0,
  GPIO_MODE_OUT,
  GPIO_MODE_AF,
  GPIO_MODE_ANALOG
} GPIO_Mode;

typedef enum
{
  GPIO_OTYPE_PUSHPULL = 0,
  GPIO_OTYPE_OPENDRAIN
} GPIO_OutputType;

typedef enum
{
  GPIO_PUD_NONE = 0,
  GPIO_PUD_PULLUP,
  GPIO_PUD_PULLDOWN
} GPIO_PullUpDown;

typedef enum
{
  GPIO_OSPEED_LOWSPEED = 0,
  GPIO_OSPEED_MEDIUMSPEED,
  GPIO_OSPEED_HIGHSPEED,
  GPIO_OSPEED_VERYHIGHSPEED
} GPIO_OSpeed;

void GPIO_Conf(GPIO_TypeDef *port, uint8_t pin, GPIO_Mode mode, GPIO_OutputType otype, GPIO_OSpeed ospeed, GPIO_PullUpDown pullup);

void GPIO_AFConf(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);

uint8_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin);
void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t val);

#endif
