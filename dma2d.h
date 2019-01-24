#ifndef DMA2D_H_
#define DMA2D_H_

#include "stm32f7.h"

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t ISR;
    volatile uint32_t IFCR;
    volatile uint32_t FGMAR;
    volatile uint32_t FGOR;
    volatile uint32_t BGMAR;
    volatile uint32_t BGOR;
    volatile uint32_t FGPFCCR;
    volatile uint32_t FGCOLR;
    volatile uint32_t BGPFCCR;
    volatile uint32_t BGCOLR;
    volatile uint32_t FGCMAR;
    volatile uint32_t BGCMAR;
    volatile uint32_t OPFCCR;
    volatile uint32_t OCOLR;
    volatile uint32_t OMAR;
    volatile uint32_t OOR;
    volatile uint32_t NLR;
    volatile uint32_t LWR;
    volatile uint32_t AMTCR;
} DMA2D_TypeDef;

#define DMA2D_BASE (AHB1PERIPH_BASE + 0xB000)
#define DMA2D ((DMA2D_TypeDef *) DMA2D_BASE)

#define DMA2D_FGCLUT_ADDRESS (DMA2D_BASE + 0x0400)
#define DMA2D_BGCLUT_ADDRESS (DMA2D_BASE + 0x0800)

#define DMA2D_FgClut ((uint32_t *) DMA2D_FGCLUT_ADDRESS)
#define DMA2D_BgClut ((uint32_t *) DMA2D_BGCLUT_ADDRESS)

#define DMA2D_CR_MODE_MEM2MEM       ((uint32_t)(0 << 16))
#define DMA2D_CR_MODE_MEM2MEMPFC    ((uint32_t)(1 << 16))
#define DMA2D_CR_MODE_MEM2MEMBLEND  ((uint32_t)(2 << 16))
#define DMA2D_CR_MODE_REG2MEM       ((uint32_t)(3 << 16))

#define DMA2D_CR_CEIE               ((uint32_t)(1 << 13))
#define DMA2D_CR_CTCIE              ((uint32_t)(1 << 12))
#define DMA2D_CR_CAEIE              ((uint32_t)(1 << 11))
#define DMA2D_CR_TWIE               ((uint32_t)(1 << 10))
#define DMA2D_CR_TCIE               ((uint32_t)(1 << 9))
#define DMA2D_CR_TEIE               ((uint32_t)(1 << 8))
#define DMA2D_CR_ABORT              ((uint32_t)(1 << 2))
#define DMA2D_CR_SUSP               ((uint32_t)(1 << 1))
#define DMA2D_CR_START              ((uint32_t)(1 << 0))

#define DMA2D_ISR_CEIF              ((uint32_t)(1 << 5))
#define DMA2D_ISR_CTCIF             ((uint32_t)(1 << 4))
#define DMA2D_ISR_CAEIF             ((uint32_t)(1 << 3))
#define DMA2D_ISR_TWIF              ((uint32_t)(1 << 2))
#define DMA2D_ISR_TCIF              ((uint32_t)(1 << 1))
#define DMA2D_ISR_TEIF              ((uint32_t)(1 << 0))

#define DMA2D_IFCR_CCEIF            ((uint32_t)(1 << 5))
#define DMA2D_IFCR_CCTCIF           ((uint32_t)(1 << 4))
#define DMA2D_IFCR_CAEIF            ((uint32_t)(1 << 3))
#define DMA2D_IFCR_CTWIF            ((uint32_t)(1 << 2))
#define DMA2D_IFCR_CTCIF            ((uint32_t)(1 << 1))
#define DMA2D_IFCR_CTEIF            ((uint32_t)(1 << 0))

#define DMA2D_XXPFCCR_ALPHA_SHIFT   ((uint32_t)(24))
#define DMA2D_XXPFCCR_AM_REPLACE    ((uint32_t)(1 << 16))
#define DMA2D_XXPFCCR_AM_MULTCONST  ((uint32_t)(2 << 16))
#define DMA2D_XXPFCCR_CLUTSIZE_SHIFT ((uint32_t)(8))
#define DMA2D_XXPFCCR_START         ((uint32_t)(1 << 5))

#define DMA2D_XXPFCCR_CCM_ARGB      ((uint32_t)(0 << 4))
#define DMA2D_XXPFCCR_CCM_RGB       ((uint32_t)(1 << 4))

typedef enum
{
    PFC_ARGB8888,
    PFC_RGB888,
    PFC_RGB565,
    PFC_ARGB1555,
    PFC_ARGB4444,
    PFC_L8,
    PFC_AL44,
    PFC_AL88,
    PFC_L4,
    PFC_A8,
    PFC_A4
} DMA2D_ColorFormat;

#endif
