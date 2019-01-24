#include "scb.h"

void SCB_SystemReset()
{
    SCB->AIRCR = SCB_AIRCR_VECTKEY | (SCB->AIRCR & 0x700) | SCB_AIRCR_SYSRESETRQ;
    while(1);
}
