#ifndef RNG_H_
#define RNG_H_

#include "stm32f7.h"

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t SR;
    volatile uint32_t DR;
} RNG_TypeDef;

#define RNG_BASE (AHB2PERIPH_BASE + 0x00060800)
#define RNG ((RNG_TypeDef *) RNG_BASE)

#define RNG_CR_CED      ((uint32_t)(1 << 5))
#define RNG_CR_IE       ((uint23_t)(1 << 3))
#define RNG_CR_RNGEN    ((uint32_t)(1 << 2))

#define RNG_SR_SEIS     ((uint32_t)(1 << 6))
#define RNG_SR_CEIS     ((uint32_t)(1 << 5))
#define RNG_SR_SECS     ((uint32_t)(1 << 2))
#define RNG_SR_CECS     ((uint32_t)(1 << 1))
#define RNG_SR_DRDY     ((uint32_t)(1 << 0))

void RNG_Init();
uint32_t RNG_GetRandom();

#endif
