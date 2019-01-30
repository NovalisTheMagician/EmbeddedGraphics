#ifndef LAYER_H_
#define LAYER_H_

#include "stm32f7.h"
#include "ltdc.h"

#include "pixelformat.h"
#include "tft.h"

void LAYER_SetWindow(LAYER_TypeDef *layer, uint32_t x, uint32_t y, uint32_t width, uint32_t height, PF_PixelFormat pf);
void LAYER_SetFramebuffer(LAYER_TypeDef *layer, void *framebuffer);
void LAYER_Enable(LAYER_TypeDef *layer);
void LAYER_Disable(LAYER_TypeDef *layer);
void LAYER_Reload(bool immediately);

#endif
