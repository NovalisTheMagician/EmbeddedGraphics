#include "gpio.h"

static void GPIO_SetAFHigh(GPIO_TypeDef *port, uint8_t pin, uint8_t af)
{
    uint32_t shift = pin * 4;
    uint32_t mask = (15 << shift);
    port->AFR[1] = (port->AFR[1] & ~mask) | (af << shift);
}

static void GPIO_SetAFLow(GPIO_TypeDef *port, uint8_t pin, uint8_t af)
{
    uint32_t shift = pin * 4;
    uint32_t mask = (15 << shift);
    port->AFR[0] = (port->AFR[0] & ~mask) | (af << shift);
}

void GPIO_Conf(GPIO_TypeDef *port, uint8_t pin, GPIO_Mode mode, GPIO_OutputType otype, GPIO_OSpeed ospeed, GPIO_PullUpDown pullup)
{
    //check if the pin is in range [0, 15]
    if(pin > 15) return;

    uint32_t shift1 = pin;
    uint32_t shift2 = pin * 2;

    uint32_t mask1 = (1 << shift1);
    uint32_t mask2 = (3 << shift2);

    port->MODER = (port->MODER & ~mask2) | (mode << shift2);
    port->OTYPER = (port->OTYPER & ~mask1) | (otype << shift1);
    port->OSPEEDR = (port->OSPEEDR & ~mask2) | (ospeed << shift2);
    port->PUPDR = (port->PUPDR & ~mask2) | (pullup << shift2);
}

void GPIO_AFConf(GPIO_TypeDef *port, uint8_t pin, uint8_t mode)
{
    if(pin > 15) return;

    uint32_t shift1 = pin;
    uint32_t shift2 = pin * 2;

    uint32_t mask1 = (1 << shift1);
    uint32_t mask2 = (3 << shift2);

    if(pin < 8)
    {
        GPIO_SetAFLow(port, pin, mode);
    }
    else
    {
        GPIO_SetAFHigh(port, pin % 8, mode);
    }

    port->MODER = (port->MODER & ~mask2) | (GPIO_MODE_AF << shift2);
    port->OTYPER = (port->OTYPER & ~mask1) | (GPIO_OTYPE_PUSHPULL << shift1);
    port->OSPEEDR = (port->OSPEEDR & ~mask2) | (GPIO_OSPEED_VERYHIGHSPEED << shift2);
    port->PUPDR = (port->PUPDR & ~mask2) | (GPIO_PUD_NONE << shift2);
}

uint8_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin)
{
    uint32_t mask = (1 << pin);
    return port->IDR & mask;
}

void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t val)
{
    uint16_t mask = (1 << pin);
    if(val)
    {
        port->BSRRL = mask;
    }
    else
    {
        port->BSRRH = mask;
    }
}
