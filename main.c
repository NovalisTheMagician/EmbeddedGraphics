#include "stm32f7.h"
#include "gpio.h"
#include "sdram.h"
#include "tft.h"
#include "systick.h"
#include "delay.h"

#include "colors16.h"

#include <math.h>

#include "renderer.h"

#define LED1 1

#define WIDTH 480
#define HEIGHT 272

void led_on(uint32_t led);
void led_off(uint32_t led);

void blink(int amount, uint32_t led);
void blink_fast(int amount, uint32_t led);

int main()
{
    GPIO_Conf(GPIOI, LED1, GPIO_MODE_OUT, GPIO_OTYPE_PUSHPULL, GPIO_OSPEED_VERYHIGHSPEED, GPIO_PUD_NONE);

    viewport_t viewport = {
        0, 0, WIDTH, HEIGHT
    };

    REN_Init(viewport);

    uint32_t clearColor = COL_BLACK;

    int x = 0, y = 80;
    int dx = 1, dy = 1;

    while(1)
    {
        //update state
        x += dx;
        y += dy;

        if(((x + 16) >= WIDTH) || (x < 0))
            dx = -dx;
        if(((y + 16) >= HEIGHT) || (y < 0))
            dy = -dy;

        //draw state
        REN_Clear(clearColor);
        REN_DrawRect(0, 0, WIDTH, HEIGHT, COL_MAGENTA);

        REN_FillRect(x, y, 16, 16, COL_WHITE);

        //REN_FillRect(100, 100, 32, 32, COL_GREEN);

        REN_FillRect(0, 200, 20, 70, COL_GREEN);
        REN_DrawRect(0, 200, 20, 70, COL_YELLOW);

        //REN_DrawLine(100, 100, 200, 100, COL_RED);
        //REN_DrawLine(100, 100, 100, 200, COL_RED);
        //REN_DrawLine(100, 100, 0, 100, COL_RED);
        //REN_DrawLine(100, 100, 100, 0, COL_RED);

        //REN_DrawLine(100, 100, 200, 200, COL_GREEN);
        //REN_DrawLine(100, 100, 0, 0, COL_GREEN);

        //REN_DrawLine(100, 100, 200, 150, COL_BLUE);
        //REN_DrawLine(100, 100, 150, 200, COL_BLUE);

        //REN_FillTriangle(200, 200, 300, 270, 150, 250, COL_RED);
        //REN_DrawTriangle(200, 200, 300, 270, 150, 250, COL_MAGENTA);

        //REN_FillCircle(WIDTH / 2, HEIGHT / 2, 40, COL_BLUE);
        //REN_DrawCircle(WIDTH / 2, HEIGHT / 2, 40, COL_CYAN);

        /*
        for(int ny = 0; ny < HEIGHT; ++ny)
        {
            for(int nx = 0; nx < WIDTH; ++nx)
            {
                int r = 255 * nx / WIDTH;
                int g = 255 * ny / HEIGHT;

                REN_PutPixel(nx, ny, (255 << 24) | (r << 16) | (g << 8));
            }
        }
        */
        
        //REN_DrawString("HELLO WORLD", 0, 0, COL_WHITE);
        //REN_DrawString("HELLO WORLD", 0, 16, COL_RED);
        //REN_DrawString("HELLO WORLD", 0, 32, COL_GREEN);
        //REN_DrawString("HELLO WORLD", 0, 48, COL_BLUE);
        //REN_DrawString("HELLO WORLD", 0, 64, COL_CYAN);
        //REN_DrawString("HELLO WORLD", 0, 80, COL_MAGENTA);
        //REN_DrawString("HELLO WORLD", 0, 96, COL_YELLOW);

        REN_Flip();
    }
}

int n = 1000;
void blink(int amount, uint32_t led)
{
    for(int i = 0; i < amount; ++i)
    {
        led_on(led);
        delay(n);
        led_off(led);
        delay(n);
    }
}

void led_on(uint32_t led)
{
    GPIO_WritePin(GPIOI, led, 1);
}

void led_off(uint32_t led)
{
    GPIO_WritePin(GPIOI, led, 0);
}
