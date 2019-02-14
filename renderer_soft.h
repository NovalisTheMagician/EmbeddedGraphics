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

void RENS_Init(viewport_t viewport);
void RENS_Clear(color_t color);

void RENS_PutPixel(int x, int y, color_t color);
void RENS_VerticalLine(int x, int y, int length, color_t color);
void RENS_HorizontalLine(int x, int y, int length, color_t color);

void RENS_DrawLine(int x0, int y0, int x1, int y1, color_t color);

void RENS_DrawRect(int x, int y, int width, int height, color_t color);
void RENS_FillRect(int x, int y, int width, int height, color_t color);

void RENS_DrawCircle(int x, int y, int radius, color_t color);
void RENS_FillCircle(int x, int y, int radius, color_t color);

void RENS_DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);
void RENS_FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);

void RENS_DrawString(const char *string, int x, int y, color_t color);

void RENS_Flip(bool waitForVBlank);

#endif
