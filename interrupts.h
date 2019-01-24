
void NIMHandler()           __attribute__ ((interrupt, weak, alias("FaultHandler")));
void HardFaultHandler()     __attribute__ ((interrupt, weak, alias("FaultHandler")));
void MemFaultHandler()      __attribute__ ((interrupt, weak, alias("FaultHandler")));
void BusFaultHandler()      __attribute__ ((interrupt, weak, alias("FaultHandler")));
void UsageFaultHandler()    __attribute__ ((interrupt, weak, alias("FaultHandler")));
void SVCallHandler()        __attribute__ ((interrupt, weak, alias("DefaultHandler")));
void DebugHandler()         __attribute__ ((interrupt, weak, alias("DefaultHandler")));
void PendSVHandler()        __attribute__ ((interrupt, weak, alias("DefaultHandler")));
void SystickHandler()       __attribute__ ((interrupt, weak, alias("DefaultHandler")));

void WindowWatchdogHandler() __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void PVDHandler()           __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void TampStampHandler()     __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void RTCWakeupHandler()     __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void FlashHandler()         __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void RCCHandler()           __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void EXTI0Handler()         __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void EXTI1Handler()         __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void EXTI2Handler()         __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void EXTI3Handler()         __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void EXTI4Handler()         __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void DMA1S0Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void DMA1S1Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void DMA1S2Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void DMA1S3Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void DMA1S4Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void DMA1S5Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void DMA1S6Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void ADCHandler()           __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void CAN1TXHandler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void CAN1RX0Handler()       __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void CAN1RX1Handler()       __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void CAN1SCEHandler()       __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void EXTI9_5Handler()       __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void TIM1BRK_TIM9Handler()  __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void TIM1UP_TIM10Handler()  __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void TIM1TRG_COM_TIM11Handler() __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void TIM1CCHandler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void TIM2Handler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void TIM3Handler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void TIM4Handler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void I2C1EVHandler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void I2C1ERHandler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void I2C2EVHandler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void I2C2ERHandler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void SPI1Handler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void SPI2Handler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void USART1Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void USART2Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void USART3Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void EXTI15_10Handler()      __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void RTCAlarmHandler()      __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void OTGFSWakeuphandler()   __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void TIM8BRK_TIM12Handler() __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void TIM8UP_TIM13Handler()  __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void TIM8TRG_COM_TIM14Handler() __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void TIM8CCHandler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void DMA1S7Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void FSMCHandler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void SDMMC1Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void TIM5Handler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void SPI3Handler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void UART4Handler()         __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void UART5Handler()         __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void TIM6_DACHandler()      __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void TIM7Handler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void DMA2S0Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void DMA2S1Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void DMA2S2Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void DMA2S3Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void DMA2S4Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void ETHHandler()           __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void ETHWakeupHandler()     __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void CAN2TXHandler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void CAN2RX0Handler()       __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void CAN2RX1Handler()       __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void CAN2SCEHandler()       __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void OTGFSHandler()         __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void DMA2S5Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void DMA2S6Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void DMA2S7Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void USART6Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void I2C3EVHandler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void I2C3ERHandler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void OTGHSEP1_OUTHandler()  __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void OTGHSEP1_INHandler()   __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void OTGHSWakeupHandler()   __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void OTGHSHandler()         __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void DCMIHandler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void CRYPHandler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void HASH_RNGHandler()      __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void FPUHandler()           __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void UART7Handler()         __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void UART8Handler()         __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void SPI4Handler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void SPI5Handler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void SPI6Handler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void SAI1Handler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void LCDHandler()           __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void LCDERRHandler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void DMA2DHandler()         __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void SAI2Handler()          __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void QUADSPIHandler()       __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void LPTIM1Handler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void HDMICECHander()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void I2C4EVHandler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));
void I2C4ERHandler()        __attribute__ ((interrupt, weak, alias("UnusedHandler")));

void SPDIFRXHandler()       __attribute__ ((interrupt, weak, alias("UnusedHandler")));

