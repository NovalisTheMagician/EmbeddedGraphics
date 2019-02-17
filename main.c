#include "stm32f7.h"
#include "gpio.h"
#include "sdram.h"
#include "tft.h"
#include "systick.h"
#include "delay.h"
#include "colors32.h"
#include <math.h>
#include "renderer.h"
#include "renderer_soft.h"
#include <stdio.h>
#include "rng.h"
#include <string.h>

#include "profile.h"

#define LED1 1

#define WIDTH 480
#define HEIGHT 272

void Test();
void FunInit();
void Fun();
void ProfileFast(viewport_t viewport);
void ProfileSlow(viewport_t viewport);

void ProfileFast2(viewport_t viewport);
void ProfileSlow2(viewport_t viewport);

int main()
{
    RNG_Init();

    GPIO_Conf(GPIOI, LED1, GPIO_MODE_OUT, GPIO_OTYPE_PUSHPULL, GPIO_OSPEED_VERYHIGHSPEED, GPIO_PUD_NONE);

    viewport_t viewport = {
        0, 0, WIDTH, HEIGHT
    };

    ProfileFast(viewport);

    REN_Init(viewport);

    uint32_t clearColor = COL_BLACK;

    uint32_t current = millis();
    uint32_t last = current;

    uint32_t count = 0;
    int fps = 0;

    int fpsVal = 0;

    FunInit();

    while(1)
    {
        current = millis();
        uint32_t delta = current - last;
        last = current;

        count += delta;
        fps++;

        if(count >= 1000)
        {
            count = 0;
            fpsVal = fps;
            fps = 0;
        }

        REN_Clear(clearColor);
        
        //Fun();
        Test();
        //Profile();

        //delay(RNG_GetRandom() % 33);

        char buffer[8];
        sprintf(buffer, "FPS %d", fpsVal);
        REN_DrawString(buffer, 1, 1, COL_YELLOW);

        REN_Flip(true);
    }
}

static int x = 0, y = 80;
static int dx = 1, dy = 2;

void Test()
{
    //update state
    x += dx;
    y += dy;

    if(((x + 16) >= WIDTH) || (x < 0))
        dx = -dx;
    if(((y + 16) >= HEIGHT) || (y < 0))
        dy = -dy;

    //draw state
    
    REN_DrawRect(0, 0, WIDTH, HEIGHT, COL_MAGENTA);

    REN_FillRect(x, y, 16, 16, COL_WHITE);

    REN_FillRect(0, 200, 20, 70, COL_GREEN);
    REN_DrawRect(0, 200, 20, 70, COL_YELLOW);

    REN_DrawLine(100, 100, 200, 100, COL_RED);
    REN_DrawLine(100, 100, 100, 200, COL_RED);
    REN_DrawLine(100, 100, 0, 100, COL_RED);
    REN_DrawLine(100, 100, 100, 0, COL_RED);

    REN_DrawLine(100, 100, 200, 200, COL_GREEN);
    REN_DrawLine(100, 100, 0, 0, COL_GREEN);

    REN_DrawLine(100, 100, 200, 150, COL_BLUE);
    REN_DrawLine(100, 100, 150, 200, COL_BLUE);

    REN_FillTriangle(200, 200, 300, 270, 150, 250, COL_RED);
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
}

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    uint32_t color;
    char letter[2];
} block_t;

#define NUM_BLOCKS 10

static block_t blocks[NUM_BLOCKS];

void FunInit()
{
    char letters[36][2] = {
        "A", "B", "C", "D", "E", "F",
        "G", "H", "I", "J", "K", "L",
        "M", "N", "O", "P", "Q", "R",
        "T", "U", "V", "W", "X", "Y",
        "Z", "0", "1", "2", "3", "4",
        "5", "6", "7", "8", "9"
    };

    for(int i = 0; i < NUM_BLOCKS; ++i)
    {
        int negative = (RNG_GetRandom() % 2) == 0 ? 1 : -1;
        int letter = RNG_GetRandom() % 36;

        blocks[i].x = RNG_GetRandom() % (WIDTH - 16);
        blocks[i].y = RNG_GetRandom() % (HEIGHT - 16);
        blocks[i].dx = ((RNG_GetRandom() % 5) + 1) * negative;
        blocks[i].dy = ((RNG_GetRandom() % 5) + 1) * negative;
        blocks[i].color = RNG_GetRandom() | (0xFF << 24);
        memcpy(blocks[i].letter, letters[letter], 2);
    }
}

void Fun()
{
    for(int i = 0; i < NUM_BLOCKS; ++i)
    {
        int x = blocks[i].x;
        int y = blocks[i].y;

        int dx = blocks[i].dx;
        int dy = blocks[i].dy;

        x += dx;
        y += dy;

        if(((x + 16) >= WIDTH) || (x < 0))
            dx = -dx;
        if(((y + 16) >= HEIGHT) || (y < 0))
            dy = -dy;

        blocks[i].x = x;
        blocks[i].y = y;
        blocks[i].dx = dx;
        blocks[i].dy = dy;

        REN_FillRect(x, y, 16, 16, blocks[i].color);
        //REN_DrawString(blocks[i].letter, x, y, blocks[i].color);
    }
}

/*
void led_on(uint32_t led)
{
    GPIO_WritePin(GPIOI, led, 1);
}
*/
