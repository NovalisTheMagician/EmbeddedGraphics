#include "rng.h"
#include "rcc.h"

void RNG_Init()
{
    RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;
    RNG->CR |= RNG_CR_RNGEN;
}

uint32_t RNG_GetRandom()
{
    while(RNG->SR != RNG_SR_DRDY);
    return RNG->DR;
}