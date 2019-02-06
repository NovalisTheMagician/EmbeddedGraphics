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
    volatile uint8_t SHPR[12];
    volatile uint32_t CFSR;
    volatile uint32_t HFSR;
    volatile uint32_t DFSR;
    volatile uint32_t MMFAR;
    volatile uint32_t BFAR;
    volatile uint32_t AFSR;
    volatile uint32_t PFR[2];
    volatile uint32_t DFR;
    volatile uint32_t ADR;
    volatile uint32_t MMFR[4];
    volatile uint32_t ISAR[5];
} SCB_t;

#define SCB_BASE ((uint32_t) 0xE000ED00)
#define SCB ((SCB_t *) SCB_BASE)

#define SCB_AIRCR_VECTKEY       ((uint32_t)(0x5FA << 16))
#define SCB_AIRCR_SYSRESETRQ    ((uint32_t)(1 << 2))

void SCB_SystemReset();

#endif
