#include "renderer.h"

#include <math.h>
#include <stdlib.h>

#include "dma2d.h"
#include "pixelformat.h"
#include "nvic.h"

#include "layer.h"

extern unsigned long _sframebuf;

#define GLYPH_WIDTH 10
#define GLYPH_HEIGHT 16
#define NUM_CHARS 36
static const uint8_t FONT[GLYPH_WIDTH * GLYPH_HEIGHT * NUM_CHARS] = {
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

    LAYER_SetWindow(LAYER1, currentViewport.x, currentViewport.y, currentViewport.width, currentViewport.height, PF_ARGB8888);

    frontBuffer = (color_t *)(&_sframebuf);
    backBuffer = frontBuffer + (currentViewport.width * currentViewport.height);

    currentBuffer = backBuffer;

    LAYER_SetFramebuffer(LAYER1, frontBuffer);

    LAYER_Reload(true);

    LAYER_Enable(LAYER1);

    DMA2D_Init();

    NVIC_EnableIRQ(LCD_IRQn);
}

void REN_Clear(color_t color)
{
    uint16_t width = currentViewport.width;
    uint16_t height = currentViewport.height;

    DMA2D_image_t image = { 0 };
    image.color = color;
    image.pixelFormat = PF_ARGB8888;
    image.memoryAddr = currentBuffer;
    image.offset = 0;

    DMA2D_SetOutput(&image, width, height);
    DMA2D_StartTransfer(TT_REGTOMEM);
}

void REN_PutPixel(int x, int y, color_t color)
{
    uint16_t width = currentViewport.width;

    currentBuffer[x + y * width] = color;
}

void REN_VerticalLine(int x, int y, int length, color_t color)
{
    uint16_t width = currentViewport.width;
    uint16_t height = currentViewport.height;

    if(length <= 0 || x >= (int)width || y >= (int)height || x < 0)
        return;

    if(y < 0)
    {
        length += y;
        y = 0;
    }

    if((y + length) >= height)
    {
        length -= (y + length) - height;
    }

    DMA2D_image_t image = { 0 };
    image.color = color;
    image.pixelFormat = PF_ARGB8888;
    image.memoryAddr = &currentBuffer[x + y * width];
    image.offset = width - 1;

    DMA2D_SetOutput(&image, 1, length);
    DMA2D_StartTransfer(TT_REGTOMEM);
}

void REN_HorizontalLine(int x, int y, int length, color_t color)
{
    uint16_t width = currentViewport.width;
    uint16_t height = currentViewport.height;

    if(length <= 0 || x >= (int)width || y >= (int)height || y < 0)
        return;

    if(x < 0)
    {
        length += x;
        x = 0;
    }

    if((x + length) >= width)
    {
        length -= (x + length) - width;
    }

    DMA2D_image_t image = { 0 };
    image.color = color;
    image.pixelFormat = PF_ARGB8888;
    image.memoryAddr = &currentBuffer[x + y * width];
    image.offset = width;

    DMA2D_SetOutput(&image, length, 1);
    DMA2D_StartTransfer(TT_REGTOMEM);
}

void REN_DrawLine(int x0, int y0, int x1, int y1, color_t color)
{
    if(x0 < 0) x0 = 0;
    if(y0 < 0) y0 = 0;

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
    uint16_t screenWidth = currentViewport.width;
    uint16_t screenHeight = currentViewport.height;

    if((width <= 0) || (height <= 0) || (x >= (int)screenWidth) || (y >= (int)screenHeight))
        return;

    if(x < 0)
    {
        width += x;
        x = 0;
    }

    if(y < 0)
    {
        height += y;
        y = 0;
    }

    if((x + width) >= screenWidth)
    {
        width -= (x + width) - screenWidth;
    }

    if((y + height) >= screenHeight)
    {
        height -= (y + height) - screenHeight;
    }

    DMA2D_image_t image = { 0 };
    image.color = color;
    image.pixelFormat = PF_ARGB8888;
    image.memoryAddr = &currentBuffer[x + y * screenWidth];
    image.offset = screenWidth - width;

    DMA2D_SetOutput(&image, width, height);
    DMA2D_StartTransfer(TT_REGTOMEM);
}

void REN_DrawCircle(int x, int y, int radius, color_t color)
{
    int _x = radius - 1;
    int _y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius * 2);

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
            err += dx - (radius * 2);
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
    uint16_t width = currentViewport.width;
    uint16_t height = currentViewport.height;

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
    uint16_t width = currentViewport.width;

    DMA2D_image_t foreground = { 0 };
    foreground.color = color;
    foreground.pixelFormat = PF_A8;
    foreground.memoryAddr = &FONT[glyph];

    color_t *framebufferAdress = &currentBuffer[x + y * width];

    DMA2D_image_t background = { 0 };
    background.pixelFormat = PF_ARGB8888;
    background.memoryAddr = framebufferAdress;
    background.offset = width - GLYPH_WIDTH;

    DMA2D_image_t output = { 0 };
    output.pixelFormat = PF_ARGB8888;
    output.memoryAddr = framebufferAdress;
    output.offset = width - GLYPH_WIDTH;

    DMA2D_SetForeground(&foreground);
    DMA2D_SetBackground(&background);
    DMA2D_SetOutput(&output, GLYPH_WIDTH, GLYPH_HEIGHT);
    DMA2D_StartTransfer(TT_MEMTOMEMBLEND);
}

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
            int glyphOffset = (character - 'A') * GLYPH_SIZE;
            BlitGlyph(x + xOffset, y, glyphOffset, color);
        }
        else if(character >= '0' && character <= '9')
        {
            int glyphOffset = ((character - '0') + 26) * GLYPH_SIZE;
            BlitGlyph(x + xOffset, y, glyphOffset, color);
        }

        xOffset += GLYPH_WIDTH;
        ch++;
    }
}

static volatile int vblank = 0;

void REN_Flip(bool waitForVBlank)
{
    LAYER_SetFramebuffer(LAYER1, currentBuffer);
    if(waitForVBlank)
    {
        LAYER_Reload(false);
        while(!vblank);
        vblank = 0;
    }
    else
    {
        LAYER_Reload(true);
    }

    if(currentBuffer == frontBuffer)
        currentBuffer = backBuffer;
    else
        currentBuffer = frontBuffer;
}

void LCDHandler()
{
    vblank = 1;
    LTDC->ICR = (1 << 3);
}
