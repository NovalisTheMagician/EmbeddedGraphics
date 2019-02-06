#include "spi.h"
#include "rcc.h"
#include "gpio.h"

void SPI_Conf(SPI_t *spi)
{
    if(spi == SPI5)
    {
        RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;

        GPIO_AFConf(GPIOF, 7, 5);
        GPIO_AFConf(GPIOF, 8, 5);
        GPIO_AFConf(GPIOF, 9, 5);

        SPI5->CR1 = SPI_CR1_BR_CLK16 | SPI_CR1_MSTR | (1 << 8) | SPI_CR1_SSM;

        SPI5->CR1 |= SPI_CR1_SPE;
    }
}

uint16_t SPI_Transmit(SPI_t *spi, uint16_t val)
{
    spi->DR = val;
    while((spi->SR & (SPI_SR_TXE | SPI_SR_RXNE)) == 0);
    return spi->DR;
}
