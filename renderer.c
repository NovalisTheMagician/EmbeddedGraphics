#include "renderer.h"

#include <math.h>
#include <stdlib.h>

#include "dma2d.h"
#include "pixelformat.h"
#include "tft.h"

#include "vector.h"

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

static void swap(int *v1, int *v2)
{
    int tmp = *v2;
    *v2 = *v1;
    *v1 = tmp;
}

void REN_DrawLine(int x0, int y0, int x1, int y1, color_t color)
{
    if (x0 > x1)
	{
		swap(&x0, &x1);
		swap(&y0, &y1);
	}

	float dx = (float)x1 - x0;
	float dy = (float)y1 - y0;

    float slope = dy / dx;

	if (dy > dx)
	{
		slope = 1.0f / slope;

		float x = (float)x0;
		for (int y = y0; y <= y1; ++y)
		{
			REN_PutPixel((int)roundf(x), y, color);
			x += slope;
		}
	}
	else
	{
		float y = (float)y0;
		for (int x = x0; x <= x1; ++x)
		{
			REN_PutPixel(x, (int)roundf(y), color);
			y += slope;
		}
	}
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

void REN_DrawCircle(int xc, int yc, int radius, color_t color)
{
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius * 2);

    while(x >= y)
    {
        REN_PutPixel(xc + x, yc + y, color);
        REN_PutPixel(xc + y, yc + x, color);
        REN_PutPixel(xc - y, yc + x, color);
        REN_PutPixel(xc - x, yc + y, color);
        REN_PutPixel(xc - x, yc - y, color);
        REN_PutPixel(xc - y, yc - x, color);
        REN_PutPixel(xc + y, yc - x, color);
        REN_PutPixel(xc + x, yc - y, color);

        if(err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }

        if(err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius * 2);
        }
    }
}

void REN_FillCircle(int xc, int yc, int radius, color_t color)
{
    for(int y = -radius; y <= radius; ++y)
    {
        for(int x = -radius; x <= radius; ++x)
        {
            if((x * x) + (y * y) <= (radius * radius))
                REN_PutPixel(xc + x, yc + y, color);
        }
    }
}

void REN_DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color)
{
    REN_DrawLine(x0, y0, x1, y1, color);
    REN_DrawLine(x1, y1, x2, y2, color);
    REN_DrawLine(x2, y2, x0, y0, color);
}

typedef struct
{
    vector_t v0;
    vector_t v1;
} edge_t;

static edge_t MakeEdge(vector_t v0, vector_t v1)
{
    edge_t edge;
    if(v0.y < v1.y)
    {
        edge.v0 = v0;
        edge.v1 = v1;
    }
    else
    {
        edge.v0 = v1;
        edge.v1 = v0;
    }
    
    return edge;
}

static void DrawEdgeSpan(edge_t e0, edge_t e1, color_t color)
{
    float e0dy = e0.v1.y - e0.v0.y;
    if(e0dy == 0.0f)
        return;

    float e1dy = e1.v1.y - e1.v0.y;
    if(e1dy == 0.0f)
        return;

    float e0dx = e0.v1.x - e0.v0.x;
    float e1dx = e1.v1.x - e1.v0.x;

    float factor0 = (e1.v0.y - e0.v0.y) / e0dy;
    float factorStep0 = 1.0f / e0dy;
    float factor1 = 0;
    float factorStep1 = 1.0f / e1dy;

    for(int y = e1.v0.y; y < e1.v1.y; ++y)
    {
        int x1 = (int)roundf(e0.v0.x + (e0dx * factor0));
        int x2 = (int)roundf(e1.v0.x + (e1dx * factor1));
        if(x2 < x1)
        {
            swap(&x1, &x2);
        }
        int length = x2 - x1;
        REN_HorizontalLine(x1, y, length, color);

        factor0 += factorStep0;
        factor1 += factorStep1;
    }
}

void REN_FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color)
{
    vector_t v0 = { x0, y0 };
    vector_t v1 = { x1, y1 };
    vector_t v2 = { x2, y2 };

    edge_t edges[3] = 
    {
        MakeEdge(v0, v1),
        MakeEdge(v1, v2),
        MakeEdge(v2, v0)
    };

    int maxLength = 0;
    int longEdge = 0;
    for(int i = 0; i < 3; ++i)
    {
        int length = edges[i].v1.y - edges[i].v0.y;
        if(length > maxLength)
        {
            maxLength = length;
            longEdge = i;
        }
    }

    int shortEdge1 = (longEdge + 1) % 3;
    int shortEdge2 = (longEdge + 2) % 3;

    DrawEdgeSpan(edges[longEdge], edges[shortEdge1], color);
    DrawEdgeSpan(edges[longEdge], edges[shortEdge2], color);
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

void REN_Flip(bool waitForVBlank)
{
    LAYER_SetFramebuffer(LAYER1, currentBuffer);
    if(waitForVBlank)
    {
        LAYER_Reload(false);
        TFT_WaitForVSYNC();
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
