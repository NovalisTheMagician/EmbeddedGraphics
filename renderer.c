#include "renderer.h"

#include "math.h"
#include "stdlib.h"

#include "tft.h"

extern unsigned long _sframebuf;

#define GLYPH_WIDTH 10
#define GLYPH_HEIGHT 16
#define NUM_CHARS 36
static uint32_t FONT[GLYPH_WIDTH * GLYPH_HEIGHT * NUM_CHARS] = {
#include "font.inc"
};

static color_t *frontBuffer;
static color_t *backBuffer;
static color_t *currentBuffer;

static viewport_t currentViewport;

void REN_Init(viewport_t viewport)
{
    currentViewport.x = viewport.x;
    currentViewport.y = viewport.y;
    currentViewport.width = viewport.width;
    currentViewport.height = viewport.height;

    size_t pixelSize = sizeof(color_t);

    LAYER1->WHPCR = ((HSYNC + HBP + currentViewport.width - 1) << 16) | (HSYNC + HBP + currentViewport.x);
    LAYER1->WVPCR = ((VSYNC + VBP + currentViewport.height - 1) << 16) | (VSYNC + VBP + currentViewport.y);
    LAYER1->CFBLR = ((currentViewport.width * pixelSize) << 16) | ((currentViewport.width * pixelSize) + 3);
    LAYER1->CFBLNR = (currentViewport.height);

	LAYER1->PFCR = LTDC_LxPFCR_PF_ARGB8888;

    frontBuffer = (color_t *)(&_sframebuf);
    backBuffer = frontBuffer + (currentViewport.width * currentViewport.height);

    currentBuffer = backBuffer;
    LAYER1->CFBAR = (uint32_t)frontBuffer;
    LTDC->SRCR = LTDC_SRCR_IMR;

    LAYER1->CR |= LTDC_LxCR_LEN;
}

void REN_Clear(color_t color)
{
   uint32_t width = currentViewport.width;
   uint32_t height = currentViewport.height;
   for(int i = 0; i < width * height; ++i)
   {
        currentBuffer[i] = color;
   }
}

void REN_PutPixel(int x, int y, color_t color)
{
    uint32_t width = currentViewport.width;
    uint32_t height = currentViewport.height;

    if((x < 0 || x >= width) || (y < 0 || y >= height))
        return;

    uint32_t offset = ((y * width) + x);
    currentBuffer[offset] = color;
}

void REN_VerticalLine(int x, int y, int length, color_t color)
{
    for(int cy = 0; cy < length; ++cy)
    {
        REN_PutPixel(x, cy + y, color);
    }
}

void REN_HorizontalLine(int x, int y, int length, color_t color)
{
    for(int cx = 0; cx < length; ++cx)
    {
        REN_PutPixel(cx + x, y, color);
    }
}

void REN_DrawLine(int x0, int y0, int x1, int y1, color_t color)
{
    
    if((x0 - x1) == 0)
    {
        if(y0 < y1)
            REN_VerticalLine(x0, y0, y1 - y0, color);
        else
            REN_VerticalLine(x0, y1, y0 - y1, color);
        return;
    }

    if((y0 - y1) == 0)
    {
        if(x0 < x1)
            REN_HorizontalLine(x0, y0, x1 - x0, color);
        else
            REN_HorizontalLine(x1, y0, x0 - x1, color);
        return;
    }

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;

    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    do
    {
        REN_PutPixel(x0, y0, color);
        
        e2 = err;
        if(e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }
        if(e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
    while(x0 != x1 && y0 != y1);
}

void REN_DrawRect(int x, int y, int width, int height, color_t color)
{
    REN_HorizontalLine(x, y, width, color);
    REN_HorizontalLine(x, y + (height - 1), width, color);
    REN_VerticalLine(x, y, height, color);
    REN_VerticalLine(x + (width - 1), y, height, color);
}

void REN_FillRect(int x, int y, int width, int height, color_t color)
{
    for(int cy = 0; cy < height; ++cy)
    {
        REN_HorizontalLine(x, cy + y, width, color);
    }
}

void REN_DrawCircle(int x, int y, int radius, color_t color)
{
    int _x = radius - 1;
    int _y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while(_x >= _y)
    {
        REN_PutPixel(x + _x, y + _y, color);
        REN_PutPixel(x + _y, y + _x, color);
        REN_PutPixel(x - _y, y + _x, color);
        REN_PutPixel(x - _x, y + _y, color);
        REN_PutPixel(x - _x, y - _y, color);
        REN_PutPixel(x - _y, y - _x, color);
        REN_PutPixel(x + _y, y - _x, color);
        REN_PutPixel(x + _x, y - _y, color);

        if(err <= 0)
        {
            _y++;
            err += dy;
            dy += 2;
        }

        if(err > 0)
        {
            _x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void REN_FillCircle(int x, int y, int radius, color_t color)
{
    for(int _y = -radius; _y <= radius; ++_y)
    {
        for(int _x = -radius; _x <= radius; ++_x)
        {
            if((_x * _x) + (_y * _y) <= (radius * radius))
                REN_PutPixel(x + _x, y + _y, color);
        }
    }
}

void REN_DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color)
{
    REN_DrawLine(x0, y0, x1, y1, color);
    REN_DrawLine(x1, y1, x2, y2, color);
    REN_DrawLine(x2, y2, x0, y0, color);
}

static int min(int a, int b)
{
    return a < b ? a : b;
}

static int max(int a, int b)
{
    return a > b ? a : b;
}

static int halfspace(int ax, int ay, int bx, int by, int cx, int cy)
{
    return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
}

void REN_FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color)
{
    uint32_t width = currentViewport.width;
    uint32_t height = currentViewport.height;

    int minX = min(x0, min(x1, x2));
    int minY = min(y0, min(y1, y2));
    int maxX = max(x0, max(x1, x2));
    int maxY = max(y0, max(y1, y2));

    minX = max(minX, 0);
    minY = max(minY, 0);
    maxX = min(maxX, width - 1);
    maxY = min(maxY, height - 1);

    for(int py = minY; py < maxY; ++py)
    {
        for(int px = minX; px < maxX; ++px)
        {
            int w0 = halfspace(x1, y1, x2, y2, px, py);
            int w1 = halfspace(x2, y2, x0, y0, px, py);
            int w2 = halfspace(x0, y0, x1, y1, px, py);

            if(w0 >= 0 && w1 >= 0 && w2 >= 0)
                REN_PutPixel(px, py, color);
        }
    }
}

static void BlitGlyph(int x, int y, int glyph, color_t color)
{
    for(int gy = 0; gy < GLYPH_HEIGHT; ++gy)
    {
        for(int gx = 0; gx < GLYPH_WIDTH; ++gx)
        {
            int index =  glyph + gx + gy * GLYPH_WIDTH;
            uint32_t fontColor = FONT[index];
            if(fontColor == 0xFF000000)
                REN_PutPixel(x + gx, y + gy, color);
        }
    }
}

#include "gpio.h"

void REN_DrawString(const char *string, int x, int y, color_t color)
{
    int GLYPH_SIZE = GLYPH_WIDTH * GLYPH_HEIGHT;

    int xOffset = 0;

    const char *ch = string;
    while(*ch != '\0')
    {
        char character = *ch;
        if(character >= 'A' && character <= 'Z')
        {
            int glyphIndex = (character - 'A') * GLYPH_SIZE;
            BlitGlyph(x + xOffset, y, glyphIndex, color);
        }
        else if(character >= '0' && character <= '9')
        {
            int glyphIndex = ((character - '0') + 26) * GLYPH_SIZE;
            BlitGlyph(x + xOffset, y, glyphIndex, color);
        }

        xOffset += GLYPH_WIDTH;
        ch++;
    }
}

void REN_Flip()
{
    LAYER1->CFBAR = (uint32_t)currentBuffer;
    LTDC->SRCR = LTDC_SRCR_IMR;

    if(currentBuffer == frontBuffer)
        currentBuffer = backBuffer;
    else
        currentBuffer = frontBuffer;
}
