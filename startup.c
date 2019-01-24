#include "stm32f7.h"
#include "rcc.h"
#include "gpio.h"
#include "sdram.h"
#include "tft.h"
#include "systick.h"
#include "delay.h"

#include "interrupts.h"

#include <errno.h>

extern unsigned long _sflashdata;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;
extern unsigned long _estack;
extern unsigned long _ssdram;
extern unsigned long _esdram;

extern int main();

void Startup();

static void FaultHandler()
{
    while(1);
}

static void UnusedHandler()
{
    while(1);
}

static void DefaultHandler()
{
    while(1);
}

__attribute__ ((section(".vectors"), used))
void (* const _vectors[113])(void) = 
{
    (void *)&_estack,
    Startup,
    NIMHandler,
    HardFaultHandler,
    MemFaultHandler,
    BusFaultHandler,
    UsageFaultHandler,
    0,
    0,
    0,
    0,
    SVCallHandler,
    DebugHandler,
    0,
    PendSVHandler,
    SystickHandler,
    WindowWatchdogHandler,
    PVDHandler,
    TampStampHandler,
    RTCWakeupHandler,
    FlashHandler,
    RCCHandler,
    EXTI0Handler,
    EXTI1Handler,
    EXTI2Handler,
    EXTI3Handler,
    EXTI4Handler,
    DMA1S0Handler,
    DMA1S1Handler,
    DMA1S2Handler,
    DMA1S3Handler,
    DMA1S4Handler,
    DMA1S5Handler,
    DMA1S6Handler,
    ADCHandler,
    CAN1TXHandler,
    CAN1RX0Handler,
    CAN1RX1Handler,
    CAN1SCEHandler,
    EXTI9_5Handler,
    TIM1BRK_TIM9Handler,
    TIM1UP_TIM10Handler,
    TIM1TRG_COM_TIM11Handler,
    TIM1CCHandler,
    TIM2Handler,
    TIM3Handler,
    TIM4Handler,
    I2C1EVHandler,
    I2C1ERHandler,
    I2C2EVHandler,
    I2C2ERHandler,
    SPI1Handler,
    SPI2Handler,
    USART1Handler,
    USART2Handler,
    USART3Handler,
    EXTI5_10Handler,
    RTCAlarmHandler,
    OTGFSWakeuphandler,
    TIM8BRK_TIM12Handler,
    TIM8UP_TIM13Handler,
    TIM8TRG_COM_TIM14Handler,
    TIM8CCHandler,
    DMA1S7Handler,
    FSMCHandler,
    SDMMC1Handler,
    TIM5Handler,
    SPI3Handler,
    UART4Handler,
    UART5Handler,
    TIM6_DACHandler,
    TIM7Handler,
    DMA2S0Handler,
    DMA2S1Handler,
    DMA2S2Handler,
    DMA2S3Handler,
    DMA2S4Handler,
    ETHHandler,
    ETHWakeupHandler,
    CAN2TXHandler,
    CAN2RX0Handler,
    CAN2RX1Handler,
    CAN2SCEHandler,
    OTGFSHandler,
    DMA2S5Handler,
    DMA2S6Handler,
    DMA2S7Handler,
    USART6Handler,
    I2C3EVHandler,
    I2C3ERHandler,
    OTGHSEP1_OUTHandler,
    OTGHSEP1_INHandler,
    OTGHSWakeupHandler,
    OTGHSHandler,
    DCMIHandler,
    CRYPHandler,
    HASH_RNGHandler,
    FPUHandler,
    UART7Handler,
    UART8Handler,
    SPI4Handler,
    SPI5Handler,
    SPI6Handler,
    SAI1Handler,
    LCDHandler,
    LCDERRHandler,
    DMA2DHandler,
    SAI2Handler,
    QUADSPIHandler,
    LPTIM1Handler,
    HDMICECHander,
    I2C4EVHandler,
    I2C4ERHandler,
    SPDIFRXHandler
};

void EnableFPU()
{
    volatile uint32_t *CPACR = (uint32_t*)(0xE000ED88);
    *CPACR = (3 << 22) | (3 << 20);
}

void Startup()
{
    uint32_t *src = &_sflashdata;
    uint32_t *dest = &_sdata;

    while (dest < &_edata) *dest++ = *src++;
    dest = &_sbss;
    while (dest < &_ebss) *dest++ = 0;

    RCC_InitClocks();

    SYSTICK_Init();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | 
                    RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | 
                    RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN | 
                    RCC_AHB1ENR_GPIOGEN | RCC_AHB1ENR_GPIOHEN | 
                    RCC_AHB1ENR_GPIOIEN | RCC_AHB1ENR_GPIOJEN | 
                    RCC_AHB1ENR_GPIOKEN;

    SDRAM_Init();

    TFT_Init();

    EnableFPU();
    
    main();
}

char *__brkval = (char*)(&_ssdram);

void* _sbrk(int incr)
{
    char *prev = __brkval;
    if(incr != 0)
    {
        if(prev + incr >= (char*)&_esdram)
        {
            errno = ENOMEM;
            return (void*)-1;
        }
        __brkval = prev + incr;
    }
    return prev;
}

__attribute__((weak))
void _exit(int status)
{
    while(1);
}
