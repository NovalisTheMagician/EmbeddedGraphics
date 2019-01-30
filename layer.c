#include "layer.h"

#include <stdlib.h>

void LAYER_SetWindow(LAYER_TypeDef *layer, uint32_t x, uint32_t y, uint32_t width, uint32_t height, PF_PixelFormat pf)
{
    size_t pixelSize;
    switch(pf)
    {
        case PF_ARGB8888:    pixelSize = sizeof(uint32_t); break;
        case PF_RGB565:      pixelSize = sizeof(uint16_t); break;
        case PF_L8:          pixelSize = sizeof(uint8_t); break;
        default:        pixelSize = sizeof(uint32_t); break;
    }

    layer->WHPCR = ((HSYNC + HBP + width - 1) << 16) | (HSYNC + HBP + x);
    layer->WVPCR = ((VSYNC + VBP + height - 1) << 16) | (VSYNC + VBP + y);
    layer->CFBLR = ((width * pixelSize) << 16) | ((width * pixelSize) + 3);
    layer->CFBLNR = height;

    layer->PFCR = PF_ARGB8888;
}

void LAYER_SetFramebuffer(LAYER_TypeDef *layer, void *framebuffer)
{
    layer->CFBAR = (uint32_t)framebuffer;
}

void LAYER_Reload(bool immediately)
{
    if(immediately)
        LTDC->SRCR = LTDC_SRCR_IMR;
    else
        LTDC->SRCR = LTDC_SRCR_VBR;
}

void LAYER_Enable(LAYER_TypeDef *layer)
{
    layer->CR |= LTDC_LxCR_LEN;
}

void LAYER_Disable(LAYER_TypeDef *layer)
{
    layer->CR &= ~LTDC_LxCR_LEN;
}
