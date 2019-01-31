#include "dma2d.h"
#include "rcc.h"

void DMA2D_Init()
{
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN;
}

void DMA2D_SetForeground(DMA2D_ImageDef *imageDef)
{
    DMA2D->FGPFCCR = imageDef->pixelFormat;
    DMA2D->FGCOLR = imageDef->color;
    DMA2D->FGMAR = (uint32_t)imageDef->memoryAddr;
    DMA2D->FGOR = imageDef->offset;
}

void DMA2D_SetBackground(DMA2D_ImageDef *imageDef)
{
    DMA2D->BGPFCCR = imageDef->pixelFormat;
    DMA2D->BGCOLR = imageDef->color;
    DMA2D->BGMAR = (uint32_t)imageDef->memoryAddr;
    DMA2D->BGOR = imageDef->offset;
}

void DMA2D_SetOutput(DMA2D_ImageDef *imageDef, uint16_t width, uint16_t height)
{
    DMA2D->OPFCCR = imageDef->pixelFormat;
    DMA2D->OCOLR = imageDef->color;
    DMA2D->OMAR = (uint32_t)imageDef->memoryAddr;
    DMA2D->OOR = imageDef->offset;
    DMA2D->NLR = (width << 16) | height;
}

void DMA2D_StartTransfer(DMA2D_TransferType transferType)
{
    DMA2D->CR = transferType | DMA2D_CR_START;
    while((DMA2D->CR & DMA2D_CR_START));
}
