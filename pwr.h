#ifndef PWR_H_
#define PWR_H_

#include "stm32f7.h"

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CSR1;
    volatile uint32_t CR2;
    volatile uint32_t CSR2;
} PWR_t;

#define PWR_BASE (APB1PERIPH_BASE + 0x7000)
#define PWR ((PWR_t *) PWR_BASE)

#define PWR_CR_UDEN     ((uint32_t)(3 << 18))
#define PWR_CR_ODSWEN   ((uint32_t)(1 << 17))
#define PWR_CR_ODEN     ((uint32_t)(1 << 16))

#define PWR_CR_VOS_SCALE3 ((uint32_t)(1 << 14))
#define PWR_CR_VOS_SCALE2 ((uint32_t)(2 << 14))
#define PWR_CR_VOS_SCALE1 ((uint32_t)(3 << 14))

#define PWR_CR_ADCDC1   ((uint32_t)(1 << 13))
#define PWR_CR_MRUDS    ((uint32_t)(1 << 11))
#define PWR_CR_LPUDS    ((uint32_t)(1 << 10))
#define PWR_CR_FPDS     ((uint32_t)(1 << 9))
#define PWR_CR_DBP      ((uint32_t)(1 << 8))

#define PWR_CR_PLS_20V  ((uint32_t)(0 << 5))
#define PWR_CR_PLS_21V  ((uint32_t)(1 << 5))
#define PWR_CR_PLS_23V  ((uint32_t)(2 << 5))
#define PWR_CR_PLS_25V  ((uint32_t)(3 << 5))
#define PWR_CR_PLS_26V  ((uint32_t)(4 << 5))
#define PWR_CR_PLS_27V  ((uint32_t)(5 << 5))
#define PWR_CR_PLS_28V  ((uint32_t)(6 << 5))
#define PWR_CR_PLS_29V  ((uint32_t)(7 << 5))

#define PWR_CR_PVDE     ((uint32_t)(1 << 4))
#define PWR_CR_CSBF     ((uint32_t)(1 << 3))
#define PWR_CR_CWUF     ((uint32_t)(1 << 2))
#define PWR_CR_PDDS     ((uint32_t)(1 << 1))
#define PWR_CR_LPDS     ((uint32_t)(1 << 0))

#endif
