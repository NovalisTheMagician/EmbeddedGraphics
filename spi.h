#ifndef SPI_H_
#define SPI_H_

#include "stm32f7.h"

typedef struct
{
    volatile uint16_t CR1;
    uint16_t RESERVED0;
    volatile uint16_t CR2;
    uint16_t RESERVED1;
    volatile uint16_t SR;
    uint16_t RESERVED2;
    volatile uint16_t DR;
    uint16_t RESERVED3;
    volatile uint16_t CRCPR;
    uint16_t RESERVED4;
    volatile uint16_t RXCRCR;
    uint16_t RESERVED5;
    volatile uint16_t TXCRCR;
    uint16_t RESERVED6;
    volatile uint16_t I2SCFGR;
    uint16_t RESERVED7;
    volatile uint16_t I2SPR;
    uint16_t RESERVED8;
} SPI_TypeDef;

#define SPI1_BASE (APB2PERIPH_BASE + 0x3000)
#define SPI2_BASE (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASE (APB1PERIPH_BASE + 0x3C00)
#define SPI4_BASE (APB2PERIPH_BASE + 0x3400)
#define SPI5_BASE (APB2PERIPH_BASE + 0x5000)
#define SPI6_BASE (APB2PERIPH_BASE + 0x5400)

#define SPI1 ((SPI_TypeDef *) SPI1_BASE)
#define SPI2 ((SPI_TypeDef *) SPI2_BASE)
#define SPI3 ((SPI_TypeDef *) SPI3_BASE)
#define SPI4 ((SPI_TypeDef *) SPI4_BASE)
#define SPI5 ((SPI_TypeDef *) SPI5_BASE)
#define SPI6 ((SPI_TypeDef *) SPI6_BASE)

#define SPI_CR1_BIDIMODE    ((uint16_t)(1 << 15))
#define SPI_CR1_BIDIOE      ((uint16_t)(1 << 14))
#define SPI_CR1_CRCEN       ((uint16_t)(1 << 13))
#define SPI_CR1_CRCNEXT     ((uint16_t)(1 << 12))

#define SPI_CR1_DFF_8       ((uint16_t)(0 << 11))
#define SPI_CR1_DFF_16      ((uint16_t)(1 << 11))

#define SPI_CR1_RXONLY      ((uint16_t)(1 << 10))
#define SPI_CR1_SSM         ((uint16_t)(1 << 9))
#define SPI_CR1_LSBFIRST    ((uint16_t)(1 << 7))
#define SPI_CR1_SPE         ((uint16_t)(1 << 6))

#define SPI_CR1_BR_CLK2     ((uint16_t)(0 << 3))
#define SPI_CR1_BR_CLK4     ((uint16_t)(1 << 3))
#define SPI_CR1_BR_CLK8     ((uint16_t)(2 << 3))
#define SPI_CR1_BR_CLK16    ((uint16_t)(3 << 3))
#define SPI_CR1_BR_CLK32    ((uint16_t)(4 << 3))
#define SPI_CR1_BR_CLK64    ((uint16_t)(5 << 3))
#define SPI_CR1_BR_CLK128   ((uint16_t)(6 << 3))
#define SPI_CR1_BR_CLK256   ((uint16_t)(7 << 3))

#define SPI_CR1_MSTR        ((uint16_t)(1 << 2))
#define SPI_CR1_CPOL        ((uint16_t)(1 << 1))
#define SPI_CR1_CPHA        ((uint16_t)(1 << 0))

#define SPI_CR2_TXEIE       ((uint16_t)(1 << 7))
#define SPI_CR2_RXNEIE      ((uint16_t)(1 << 6))
#define SPI_CR2_ERRIE       ((uint16_t)(1 << 5))

#define SPI_CR2_FRF_MOTO    ((uint16_t)(0 << 4))
#define SPI_CR2_FRF_TI      ((uint16_t)(1 << 4))

#define SPI_CR2_SSOE        ((uint16_t)(1 << 2))
#define SPI_CR2_TXDMAEN     ((uint16_t)(1 << 1))
#define SPI_CR2_RXDMAEN     ((uint16_t)(1 << 0))

#define SPI_SR_FRE          ((uint16_t)(1 << 8))
#define SPI_SR_BSY          ((uint16_t)(1 << 7))
#define SPI_SR_OVR          ((uint16_t)(1 << 6))
#define SPI_SR_MODF         ((uint16_t)(1 << 5))
#define SPI_SR_CRCERR       ((uint16_t)(1 << 4))
#define SPI_SR_UDR          ((uint16_t)(1 << 3))
#define SPI_SR_CHSIDE       ((uint16_t)(1 << 2))
#define SPI_SR_TXE          ((uint16_t)(1 << 1))
#define SPI_SR_RXNE         ((uint16_t)(1 << 0))

void SPI_Conf(SPI_TypeDef *spi);
uint16_t SPI_Transmit(SPI_TypeDef *spi, uint16_t val);

#endif
