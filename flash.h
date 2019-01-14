#ifndef FLASH_H_
#define FLASH_H_

#include "stm32f7.h"

typedef struct
{
    volatile uint32_t ACR;
    volatile uint32_t KEYR;
    volatile uint32_t OPTKEYR;
    volatile uint32_t SR;
    volatile uint32_t CR;
    volatile uint32_t OPTCR;
    volatile uint32_t OPTCR1;
} FLASH_TypeDef;

#define FLASH_BASE (AHB1PERIPH_BASE + 0x3C00)
#define FLASH ((FLASH_TypeDef *) FLASH_BASE)

#endif
