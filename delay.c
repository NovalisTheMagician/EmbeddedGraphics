#include "delay.h"

volatile uint32_t systick_millis_count = 0;

void SystickHandler()
{
    ++systick_millis_count;
}

uint32_t millis()
{
    volatile uint32_t ret = systick_millis_count;
    return ret;
}

void delay(uint32_t ms)
{
    uint32_t start = millis();
    while((millis() - start) < ms);
}
