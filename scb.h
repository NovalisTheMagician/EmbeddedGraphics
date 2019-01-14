#ifndef SCB_H_
#define SCB_H_

#include "stm32f7.h"

typedef struct
{
    volatile uint32_t CPUID;
    volatile uint32_t ICSR;
    volatile uint32_t VTOR;
    volatile uint32_t AIRCR;
    volatile uint32_t SCR;
    volatile uint32_t CCR;
    volatile uint32_t SHPR1;
    volatile uint32_t SHPR2;
    volatile uint32_t SHPR3;
    volatile uint32_t SHCSR;
    volatile uint32_t CFSR;
    volatile uint32_t HFSR;
    uint32_t RESERVED1;
    volatile uint32_t MMFAR;
    volatile uint32_t BFAR;
    uint32_t RESERVED2;
} SCB_Typedef;

#define SCB_BASE ((uint32_t) 0xE000ED00)
#define SCB ((SCB_Typedef *) SCB_BASE)

#endif
