#ifndef RENDERER_H_
#define RENDERER_H_

#include "stm32f7.h"
#include "ltdc.h"

typedef uint32_t color_t;

typedef struct 
{
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
} viewport_t;

void REN_Init(viewport_t viewport);
void REN_Clear(color_t color);
void REN_Clear2(color_t color);

void REN_PutPixel(int x, int y, color_t color);
void REN_VerticalLine(int x, int y, int length, color_t color);
void REN_HorizontalLine(int x, int y, int length, color_t color);

void REN_DrawLine(int x0, int y0, int x1, int y1, color_t color);

void REN_DrawRect(int x, int y, int width, int height, color_t color);
void REN_FillRect(int x, int y, int width, int height, color_t color);

void REN_DrawCircle(int x, int y, int radius, color_t color);
void REN_FillCircle(int x, int y, int radius, color_t color);

void REN_DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);
void REN_FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);

void REN_DrawString(const char *string, int x, int y, color_t color);

void REN_Flip(bool waitForVBlank);

#endif
