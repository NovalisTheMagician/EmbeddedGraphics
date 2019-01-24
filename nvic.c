#include "nvic.h"

void NVIC_EnableIRQ(IRQn_Type irqn)
{
    NVIC->ISER[((uint32_t)irqn) >> 5] = (1 << (((uint32_t)irqn) & 0x1F));
}
