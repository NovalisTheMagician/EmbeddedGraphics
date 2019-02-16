#include "delay.h"

static volatile uint32_t systickMillisCount = 0;

void SystickHandler()
{
    ++systickMillisCount;
}

uint32_t millis()
{
    return systickMillisCount;
}

void delay(uint32_t ms)
{
    uint32_t start = millis();
    while((millis() - start) < ms);
}
