#ifndef STM32F7_H_
#define STM32F7_H_

#include <stdint.h>

#define PERIPH_BASE ((uint32_t)0x40000000)

/* Peripheral memory map */
#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE (PERIPH_BASE + 0x00010000)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE (PERIPH_BASE + 0x10000000)
#define AHB3PERIPH_BASE (PERIPH_BASE + 0x20000000)

#endif
