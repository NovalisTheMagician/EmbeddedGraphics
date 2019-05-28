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

#define DEMO_BTN_PIN 11

#define WIDTH 480
#define HEIGHT 272

void Test();
void FunInit();
void Fun(bool drawRects);
void ProfileFast(viewport_t viewport);
void ProfileSlow(viewport_t viewport);

void ProfileFast2(viewport_t viewport);
void ProfileSlow2(viewport_t viewport);

bool checkDemoBtn();

void DrawGradient();
void DrawGradient2();
void DrawGradient3();

void DrawRandLines();
void DrawRandCircles();
void DrawRandTriangles();

void buildTriVars();

const char* DEMO_NAMES[] = {
    "MOVING CHARACTERS (500)",
    "TEST SCENE",
    "MOVING BLOCKS (500)",
    "COLOR GRADIENT (RG)",
    "COLOR GRADIENT (GB)",
    "COLOR GRADIENT (RB)",
    "RANDOM LINES (100)",
    "RANDOM CIRCLES (50)",
    "RANDOM TRIANGLES (50)"
};

int demo = 0;
const int MAX_DEMO = 9;

const int MAX_DEMO_TIME = 5000;

int main()
{
    RNG_Init();

    GPIO_Conf(GPIOI, LED1, GPIO_MODE_OUT, GPIO_OTYPE_PUSHPULL, GPIO_OSPEED_VERYHIGHSPEED, GPIO_PUD_NONE);
    GPIO_Conf(GPIOI, DEMO_BTN_PIN, GPIO_MODE_IN, GPIO_OTYPE_PUSHPULL, GPIO_OSPEED_VERYHIGHSPEED, GPIO_PUD_NONE);

    viewport_t viewport = {
        0, 0, WIDTH, HEIGHT
    };

    //ProfileSlow(viewport);

    REN_Init(viewport);

    uint32_t clearColor = COL_BLACK;

    uint32_t current = millis();
    uint32_t last = current;

    uint32_t count = 0;
    int fps = 0;

    int fpsVal = 0;

    int demoTime = 0;
    int prevDemoTime = millis();

    buildTriVars();

    FunInit();

    while(1)
    {
        GPIO_WritePin(GPIOI, LED1, GPIO_ReadPin(GPIOI, DEMO_BTN_PIN));

        current = millis();
        uint32_t delta = current - last;
        last = current;

        demoTime += delta;

        if(demoTime >= MAX_DEMO_TIME)
        {
            demo = (demo + 1) % MAX_DEMO;
            demoTime -= MAX_DEMO_TIME;
        }

        count += delta;
        fps++;

        if(count >= 1000)
        {
            count = 0;
            fpsVal = fps;
            fps = 0;
        }

        REN_Clear(clearColor);
        
        if(demo == 0)
            Fun(false);
        else if(demo == 1)
            Test();
        else if(demo == 2)
            Fun(true);
        else if(demo == 3)
            DrawGradient();
        else if(demo == 4)
            DrawGradient2();
        else if(demo == 5)
            DrawGradient3();
        else if(demo == 6)
            DrawRandLines();
        else if(demo == 7)
            DrawRandCircles();
        else if(demo == 8)
            DrawRandTriangles();


        //delay(RNG_GetRandom() % 33);

        char buffer[8];
        sprintf(buffer, "FPS %d", fpsVal);
        REN_DrawString(buffer, 1, 1, COL_YELLOW);
        REN_DrawString(DEMO_NAMES[demo], 1, 24, COL_YELLOW);

        REN_Flip(true);
    }
}

static bool prevBtnDown = false;

bool checkDemoBtn()
{
    bool btn = GPIO_ReadPin(GPIOI, DEMO_BTN_PIN);
    if(btn && !prevBtnDown)
    {
        if(!prevBtnDown)
        {
            prevBtnDown = true;
            return true;
        }
        else 
            return false;
    }
    else if(!btn)
    {
        prevBtnDown = false;
    }
    return false;
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
    REN_DrawTriangle(200, 200, 300, 270, 150, 250, COL_MAGENTA);

    REN_FillCircle(WIDTH / 2, HEIGHT / 2, 40, COL_BLUE);
    REN_DrawCircle(WIDTH / 2, HEIGHT / 2, 40, COL_CYAN);
}

void DrawGradient()
{
    for(int ny = 0; ny < HEIGHT; ++ny)
    {
        for(int nx = 0; nx < WIDTH; ++nx)
        {
            int r = 255 * nx / WIDTH;
            int g = 255 * ny / HEIGHT;

            REN_PutPixel(nx, ny, (255 << 24) | (r << 16) | (g << 8));
        }
    }
}

void DrawGradient2()
{
    for(int ny = 0; ny < HEIGHT; ++ny)
    {
        for(int nx = 0; nx < WIDTH; ++nx)
        {
            int g = 255 * nx / WIDTH;
            int b = 255 * ny / HEIGHT;

            REN_PutPixel(nx, ny, (255 << 24) | (g << 8) | (b << 0));
        }
    }
}

void DrawGradient3()
{
    for(int ny = 0; ny < HEIGHT; ++ny)
    {
        for(int nx = 0; nx < WIDTH; ++nx)
        {
            int r = 255 * nx / WIDTH;
            int b = 255 * ny / HEIGHT;

            REN_PutPixel(nx, ny, (255 << 24) | (r << 16) | (b << 0));
        }
    }
}

void DrawRandLines()
{
    for(int i = 0; i < 100; ++i)
    {
        int x0 = RNG_GetRandom() % WIDTH;
        int y0 = RNG_GetRandom() % HEIGHT;
        int x1 = RNG_GetRandom() % WIDTH;
        int y1 = RNG_GetRandom() % HEIGHT;
        uint32_t color = RNG_GetRandom() | (0xFF << 24);
        REN_DrawLine(x0, y0, x1, y1, color);
    }
}

void DrawRandCircles()
{
    for(int i = 0; i < 50; ++i)
    {
        int radius = RNG_GetRandom() % 30;

        int x0 = radius + (RNG_GetRandom() % (WIDTH - radius));
        int y0 = radius + (RNG_GetRandom() % (HEIGHT - radius));
        
        uint32_t color = RNG_GetRandom() | (0xFF << 24);
        REN_FillCircle(x0, y0, radius, color);
    }
}

int _x0;
int _y0;
int _x1;
int _y1;
int _x2;
int _y2;

void buildTriVars()
{
    _x0 = RNG_GetRandom() % WIDTH;
    _y0 = RNG_GetRandom() % HEIGHT;
    _x1 = RNG_GetRandom() % WIDTH;
    _y1 = RNG_GetRandom() % HEIGHT;
    _x2 = RNG_GetRandom() % WIDTH;
    _y2 = RNG_GetRandom() % HEIGHT;
}

void DrawRandTriangles()
{
    for(int i = 0; i < 50; ++i)
    {
        int x0 = RNG_GetRandom() % WIDTH;
        int y0 = RNG_GetRandom() % HEIGHT;
        int x1 = RNG_GetRandom() % WIDTH;
        int y1 = RNG_GetRandom() % HEIGHT;
        int x2 = RNG_GetRandom() % WIDTH;
        int y2 = RNG_GetRandom() % HEIGHT;
        uint32_t color = RNG_GetRandom() | (0xFF << 24);
        REN_FillTriangle(x0, y0, x1, y1, x2, y2, color);
        //REN_FillTriangle(_x0, _y0, _x1, _y1, _x2, _y2, color);
    }
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

#define NUM_BLOCKS 500

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

void Fun(bool drawRects)
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

        if(drawRects)
            REN_FillRect(x, y, 16, 16, blocks[i].color);
        else
            REN_DrawString(blocks[i].letter, x, y, blocks[i].color);
    }
}


void led_on(uint32_t led)
{
    GPIO_WritePin(GPIOI, led, 1);
}

