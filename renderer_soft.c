#include "renderer_soft.h"

#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "stdlib.h"

#include "tft.h"
#include "layer.h"

#include "pixelformat.h"

extern unsigned long _sframebuf;

#define GLYPH_WIDTH 10
#define GLYPH_HEIGHT 16
#define NUM_CHARS 36
static uint8_t FONT[GLYPH_WIDTH * GLYPH_HEIGHT * NUM_CHARS] = {
#include "font.inc"
};

static color_t *frontBuffer;
static color_t *backBuffer;
static color_t *currentBuffer;

static viewport_t currentViewport;

void RENS_Init(viewport_t viewport)
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
}

void RENS_Clear(color_t color)
{
    uint32_t width = currentViewport.width;
    uint32_t height = currentViewport.height;
    for(int i = 0; i < width * height; ++i)
    {
        currentBuffer[i] = color;
    }
}

void RENS_PutPixel(int x, int y, color_t color)
{
    uint32_t width = currentViewport.width;
    uint32_t height = currentViewport.height;

    if((x < 0 || x >= width) || (y < 0 || y >= height))
        return;

    uint32_t offset = ((y * width) + x);
    currentBuffer[offset] = color;
}

void RENS_VerticalLine(int x, int y, int length, color_t color)
{
    for(int cy = 0; cy < length; ++cy)
    {
        RENS_PutPixel(x, cy + y, color);
    }
}

void RENS_HorizontalLine(int x, int y, int length, color_t color)
{
    for(int cx = 0; cx < length; ++cx)
    {
        RENS_PutPixel(cx + x, y, color);
    }
}

void RENS_DrawLine(int x0, int y0, int x1, int y1, color_t color)
{
    if(x0 < 0) x0 = 0;
    if(y0 < 0) y0 = 0;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    if(dx == 0)
    {
        if(y0 < y1)
            RENS_VerticalLine(x0, y0, y1 - y0, color);
        else
            RENS_VerticalLine(x0, y1, y0 - y1, color);
        return;
    }

    if(dy == 0)
    {
        if(x0 < x1)
            RENS_HorizontalLine(x0, y0, x1 - x0, color);
        else
            RENS_HorizontalLine(x1, y0, x0 - x1, color);
        return;
    }

    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;

    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    do
    {
        RENS_PutPixel(x0, y0, color);
        
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

static void swap(int *v1, int *v2)
{
    int tmp = *v2;
    *v2 = *v1;
    *v1 = tmp;
}

void RENS_DrawLineNaive(int x0, int y0, int x1, int y1, color_t color)
{
    if (x0 > x1)
	{
		swap(&x0, &x1);
		swap(&y0, &y1);
	}

	float dx = (float)x1 - x0;
	float dy = (float)y1 - y0;

	if (dy > dx)
	{
		float slope = dx / dy;

		float x = (float)x0;
		for (int y = y0; y <= y1; ++y)
		{
			RENS_PutPixel((int)roundf(x), y, color);
			x += slope;
		}
	}
	else
	{
		float slope = dy / dx;

		float y = (float)y0;
		for (int x = x0; x <= x1; ++x)
		{
			RENS_PutPixel(x, (int)roundf(y), color);
			y += slope;
		}
	}
}

void RENS_DrawRect(int x, int y, int width, int height, color_t color)
{
    RENS_HorizontalLine(x, y, width, color);
    RENS_HorizontalLine(x, y + (height - 1), width, color);
    RENS_VerticalLine(x, y, height, color);
    RENS_VerticalLine(x + (width - 1), y, height, color);
}

void RENS_FillRect(int x, int y, int width, int height, color_t color)
{
    for(int cy = 0; cy < height; ++cy)
    {
        RENS_HorizontalLine(x, cy + y, width, color);
    }
}

void RENS_DrawCircle(int xc, int yc, int radius, color_t color)
{
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius * 2);

    while(x >= y)
    {
        RENS_PutPixel(xc + x, yc + y, color);
        RENS_PutPixel(xc + y, yc + x, color);
        RENS_PutPixel(xc - y, yc + x, color);
        RENS_PutPixel(xc - x, yc + y, color);
        RENS_PutPixel(xc - x, yc - y, color);
        RENS_PutPixel(xc - y, yc - x, color);
        RENS_PutPixel(xc + y, yc - x, color);
        RENS_PutPixel(xc + x, yc - y, color);

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

static float DegToRad(float deg)
{
	return deg * (180.0f / (float)M_PI);
}

void RENS_DrawCircleNaive(int xc, int yc, int radius, color_t color)
{
    for (int i = 0; i < 360; ++i)
	{
		float x = xc + cosf(DegToRad((float)i)) * radius;
		float y = yc + sinf(DegToRad((float)i)) * radius;

		RENS_PutPixel((int)roundf(x), (int)roundf(y), color);
	}
}

void RENS_FillCircle(int xc, int yc, int radius, color_t color)
{
    for(int y = -radius; y <= radius; ++y)
    {
        for(int x = -radius; x <= radius; ++x)
        {
            if((x * x) + (y * y) <= (radius * radius))
                RENS_PutPixel(xc + x, yc + y, color);
        }
    }
}

void RENS_DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color)
{
    RENS_DrawLine(x0, y0, x1, y1, color);
    RENS_DrawLine(x1, y1, x2, y2, color);
    RENS_DrawLine(x2, y2, x0, y0, color);
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

void RENS_FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color)
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
                RENS_PutPixel(px, py, color);
        }
    }
}

static void BlitGlyph(int x, int y, int glyph, color_t color)
{
    for(int _y = 0; _y < GLYPH_HEIGHT; ++_y)
    {
        for(int _x = 0; _x < GLYPH_WIDTH; ++_x)
        {
            int index =  glyph + _x + _y * GLYPH_WIDTH;
            uint8_t fontColor = FONT[index];
            if(fontColor != 0x00)
                RENS_PutPixel(x + _x, y + _y, color);
        }
    }
}

void RENS_DrawString(const char *string, int x, int y, color_t color)
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

void RENS_Flip(bool waitForVBlank)
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
