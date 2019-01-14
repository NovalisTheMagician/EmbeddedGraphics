#ifndef SDRAM_H_
#define SDRAM_H_

#include "stm32f7.h"
#include "gpio.h"

typedef struct
{
  volatile uint32_t SDCR[2];
  volatile uint32_t SDTR[2];
  volatile uint32_t SDCMR;
  volatile uint32_t SDRTR;
  volatile uint32_t SDSR;
} SDRAM_TypeDef;

#define FMC_BASE ((uint32_t)0xA0000000)
#define SDRAM_BASE (FMC_BASE + 0x0140)

#define SDRAM ((SDRAM_TypeDef *) SDRAM_BASE)

#define FMC_SDCR_RPIPE_1  ((uint32_t)0x2000)
#define FMC_SDCR_RPIPE_2  ((uint32_t)0x4000)

#define FMC_SDCR_RBURST   ((uint32_t)0x1000)

#define FMC_SDCR_SDCLK_2        ((uint32_t)0x0800)
#define FMC_SDCR_SDCLK_3        ((uint32_t)0x0C00)

#define FMC_SDCR_WP   ((uint32_t)0x0200)

#define FMC_SDCR_CAS_1  ((uint32_t)0x0080)
#define FMC_SDCR_CAS_2  ((uint32_t)0x0100)
#define FMC_SDCR_CAS_3  ((uint32_t)0x0180)

#define FMC_SDCR_NB_2   ((uint32_t)0x0000)
#define FMC_SDCR_NB_4   ((uint32_t)0x0040)

#define FMC_SDCR_MWID_8   ((uint32_t)0x0000)
#define FMC_SDCR_MWID_16  ((uint32_t)0x0010)
#define FMC_SDCR_MWID_32  ((uint32_t)0x0020)

#define FMC_SDCR_NR_11  ((uint32_t)0x0000)
#define FMC_SDCR_NR_12  ((uint32_t)0x0004)
#define FMC_SDCR_NR_13  ((uint32_t)0x0008)

#define FMC_SDCR_NC_8   ((uint32_t)0x0000)
#define FMC_SDCR_NC_9   ((uint32_t)0x0001)
#define FMC_SDCR_NC_10  ((uint32_t)0x0002)
#define FMC_SDCR_NC_11  ((uint32_t)0x0003)

#define FMC_SDSR_BUSY   ((uint32_t)0x0020)

#define FMC_SDCMR_CTB1  ((uint32_t)0x0010)
#define FMC_SDCMR_CTB2  ((uint32_t)0x0008)

#define FMC_SDCMR_MODE_NORMAL       ((uint32_t)0x0000)
#define FMC_SDCMR_MODE_CCE          ((uint32_t)0x0001)
#define FMC_SDCMR_MODE_PALL         ((uint32_t)0x0002)
#define FMC_SDCMR_MODE_AUTOREFRESH  ((uint32_t)0x0003)
#define FMC_SDCMR_MODE_LOADMODE     ((uint32_t)0x0004)
#define FMC_SDCMR_MODE_SELFREFRESH  ((uint32_t)0x0005)
#define FMC_SDCMR_MODE_POWERDOWN    ((uint32_t)0x0006)

// SDRAM base address for Bank 1
#define SDRAM_BASE_ADDR 0xC0000000
// SDRAM size is 8MB
#define SDRAM_SIZE 0x00800000

void SDRAM_Init();

#endif
