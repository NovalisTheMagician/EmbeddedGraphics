#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stm32f7.h"

typedef struct
{
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} SYSTICK_TypeDef;

#define SYSTICK_BASE ((uint32_t) 0xE000E010)
#define SYSTICK ((SYSTICK_TypeDef *) SYSTICK_BASE)

#define SYSTICK_CTRL_CLKSRC_AHB8    ((uint32_t)(0 << 2))
#define SYSTICK_CTRL_CLKSRC_AHB     ((uint32_t)(1 << 2))

#define SYSTICK_CTRL_TICKINT        ((uint32_t)(1 << 1))
#define SYSTICK_CTRL_EN             ((uint32_t)(1 << 0))

void SYSTICK_Init();

#endif
