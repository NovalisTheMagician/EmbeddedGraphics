#ifndef LTDC_H_
#define LTDC_H_

#include "stm32f7.h"

typedef struct
{
    uint32_t RESERVED0[2];
    volatile uint32_t SSCR;
    volatile uint32_t BPCR;
    volatile uint32_t AWCR;
    volatile uint32_t TWCR;
    volatile uint32_t GCR;
    uint32_t RESERVED1[2];
    volatile uint32_t SRCR;
    uint32_t RESERVED2[1];
    volatile uint32_t BCCR;
    uint32_t RESERVED3[1];
    volatile uint32_t IER;
    volatile uint32_t ISR;
    volatile uint32_t ICR;
    volatile uint32_t LIPCR;
    volatile uint32_t CPSR;
    volatile uint32_t CDSR;
} LTDC_t;

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t WHPCR;
    volatile uint32_t WVPCR;
    volatile uint32_t CKCR;
    volatile uint32_t PFCR;
    volatile uint32_t CACR;
    volatile uint32_t DCCR;
    volatile uint32_t BFCR;
    uint32_t RESERVED0[2];
    volatile uint32_t CFBAR;
    volatile uint32_t CFBLR;
    volatile uint32_t CFBLNR;
    uint32_t RESERVED1[4];
    volatile uint32_t CLUTWR;
} LAYER_t;

#define LTDC_BASE (APB2PERIPH_BASE + 0x6800)

#define LTDC ((LTDC_t *) LTDC_BASE)
#define LAYER1 ((LAYER_t *) (LTDC_BASE + 0x0084))
#define LAYER2 ((LAYER_t *) (LTDC_BASE + 0x0104))

#define LTDC_GCR_HSPOL_AH   ((uint32_t)(1 << 31))
#define LTDC_GCR_HSPOL_AL   ((uint32_t)(0 << 31))
#define LTDC_GCR_VSPOL_AH   ((uint32_t)(1 << 30))
#define LTDC_GCR_VSPOL_AL   ((uint32_t)(0 << 30))
#define LTDC_GCR_DEPOL_AH   ((uint32_t)(1 << 29))
#define LTDC_GCR_DEPOL_AL   ((uint32_t)(0 << 29))
#define LTDC_GCR_PCPOL_AH   ((uint32_t)(1 << 28))
#define LTDC_GCR_PCPOL_AL   ((uint32_t)(0 << 28))
#define LTDC_GCR_DEN        ((uint32_t)(1 << 16))
#define LTDC_GCR_LTDCEN     ((uint32_t)(1 << 0))

#define LTDC_SRCR_VBR       ((uint32_t)(1 << 1))
#define LTDC_SRCR_IMR       ((uint32_t)(1 << 0))

#define LTDC_LxCR_CLUTEN    ((uint32_t)(1 << 4))
#define LTDC_LxCR_COLKEN    ((uint32_t)(1 << 1))
#define LTDC_LxCR_LEN       ((uint32_t)(1 << 0))

#endif
