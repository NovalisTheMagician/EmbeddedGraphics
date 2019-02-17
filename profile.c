#include "profile.h"

#include "colors32.h"
#include "delay.h"

#include <string.h>
#include <stdio.h>

#define MAX_RUNS 100

static void DrawStatsFast(uint32_t clearTime, uint32_t verHorLineTime, 
                        uint32_t lineTime, uint32_t rectTime, 
                        uint32_t rectFillTime, uint32_t circleTime, 
                        uint32_t circleFillTime, uint32_t triangleTime, 
                        uint32_t triangleFillTime, uint32_t pixelTime,
                        uint32_t clearTimeAvg, uint32_t verHorLineTimeAvg, 
                        uint32_t lineTimeAvg, uint32_t rectTimeAvg, 
                        uint32_t rectFillTimeAvg, uint32_t circleTimeAvg, 
                        uint32_t circleFillTimeAvg, uint32_t triangleTimeAvg, 
                        uint32_t triangleFillTimeAvg, uint32_t pixelTimeAvg)
{
    REN_Clear(COL_BLACK);

    int yPos = 1;

    char buffer[100];
    sprintf(buffer, "CLEAR        %lu MS | AVG %lu MS", clearTime, clearTimeAvg);
    REN_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "PUTPIXEL     %lu MS | AVG %lu MS", pixelTime, pixelTimeAvg);
    REN_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "VERHORLINE   %lu MS | AVG %lu MS", verHorLineTime, verHorLineTimeAvg);
    REN_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "LINE         %lu MS | AVG %lu MS", lineTime, lineTimeAvg);
    REN_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "RECT         %lu MS | AVG %lu MS", rectTime, rectTimeAvg);
    REN_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "RECTFILL     %lu MS | AVG %lu MS", rectFillTime, rectFillTimeAvg);
    REN_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "CIRCLE       %lu MS | AVG %lu MS", circleTime, circleTimeAvg);
    REN_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "CIRCLEFILL   %lu MS | AVG %lu MS", circleFillTime, circleFillTimeAvg);
    REN_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "TRIANGLE     %lu MS | AVG %lu MS", triangleTime, triangleTimeAvg);
    REN_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "TRIANGLEFILL %lu MS | AVG %lu MS", triangleFillTime, triangleFillTimeAvg);
    REN_DrawString(buffer, 1, yPos, COL_YELLOW);

    REN_Flip(true);

    while(1);
}

static void DrawStatsSlow(uint32_t clearTime, uint32_t verHorLineTime, 
                        uint32_t lineTime, uint32_t rectTime, 
                        uint32_t rectFillTime, uint32_t circleTime, 
                        uint32_t circleFillTime, uint32_t triangleTime, 
                        uint32_t triangleFillTime, uint32_t pixelTime,
                        uint32_t clearTimeAvg, uint32_t verHorLineTimeAvg, 
                        uint32_t lineTimeAvg, uint32_t rectTimeAvg, 
                        uint32_t rectFillTimeAvg, uint32_t circleTimeAvg, 
                        uint32_t circleFillTimeAvg, uint32_t triangleTimeAvg, 
                        uint32_t triangleFillTimeAvg, uint32_t pixelTimeAvg)
{
    RENS_Clear(COL_BLACK);

    int yPos = 1;

    char buffer[100];
    sprintf(buffer, "CLEAR        %lu MS | AVG %lu MS", clearTime, clearTimeAvg);
    RENS_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "PUTPIXEL     %lu MS | AVG %lu MS", pixelTime, pixelTimeAvg);
    RENS_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "VERHORLINE   %lu MS | AVG %lu MS", verHorLineTime, verHorLineTimeAvg);
    RENS_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "LINE         %lu MS | AVG %lu MS", lineTime, lineTimeAvg);
    RENS_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "RECT         %lu MS | AVG %lu MS", rectTime, rectTimeAvg);
    RENS_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "RECTFILL     %lu MS | AVG %lu MS", rectFillTime, rectFillTimeAvg);
    RENS_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "CIRCLE       %lu MS | AVG %lu MS", circleTime, circleTimeAvg);
    REN_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "CIRCLEFILL   %lu MS | AVG %lu MS", circleFillTime, circleFillTimeAvg);
    RENS_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "TRIANGLE     %lu MS | AVG %lu MS", triangleTime, triangleTimeAvg);
    RENS_DrawString(buffer, 1, yPos, COL_YELLOW);

    yPos += 16;
    sprintf(buffer, "TRIANGLEFILL %lu MS | AVG %lu MS", triangleFillTime, triangleFillTimeAvg);
    RENS_DrawString(buffer, 1, yPos, COL_YELLOW);

    RENS_Flip(true);

    while(1);
}

void ProfileFast(viewport_t viewport)
{
    uint32_t start, end, buf;
    uint32_t clearTime, verHorLineTime, lineTime, rectTime, rectFillTime,
                circleTime, circleFillTime, triangleTime, triangleFillTime,
                pixelTime;
    
    uint32_t clearTimeAvg, verHorLineTimeAvg, lineTimeAvg, rectTimeAvg, rectFillTimeAvg,
                circleTimeAvg, circleFillTimeAvg, triangleTimeAvg, triangleFillTimeAvg,
                pixelTimeAvg;

    REN_Init(viewport);

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        REN_Clear(COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    clearTimeAvg = buf / MAX_RUNS;
    clearTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        REN_PutPixel(100, 100, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    pixelTimeAvg = buf / MAX_RUNS;
    pixelTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        REN_VerticalLine(0, 0, 100, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    verHorLineTimeAvg = buf / MAX_RUNS;
    verHorLineTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        REN_DrawRect(0, 0, 100, 100, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    rectTimeAvg = buf / MAX_RUNS;
    rectTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        REN_FillRect(0, 0, 100, 100, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    rectFillTimeAvg = buf / MAX_RUNS;
    rectFillTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        REN_DrawLine(0, 0, 100, 100, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    lineTimeAvg = buf / MAX_RUNS;
    lineTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        REN_DrawCircle(200, 150, 50, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    circleTimeAvg = buf / MAX_RUNS;
    circleTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        REN_FillCircle(200, 150, 50, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    circleFillTimeAvg = buf / MAX_RUNS;
    circleFillTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        REN_DrawTriangle(200, 200, 300, 270, 150, 250, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    triangleTimeAvg = buf / MAX_RUNS;
    triangleTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        REN_FillTriangle(200, 200, 300, 270, 150, 250, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    triangleFillTimeAvg = buf / MAX_RUNS;
    triangleFillTime = buf;

    DrawStatsFast(clearTime, verHorLineTime, lineTime, 
                    rectTime, rectFillTime, circleTime,
                    circleFillTime, triangleTime, triangleFillTime, 
                    pixelTime, clearTimeAvg, verHorLineTimeAvg, lineTimeAvg, 
                    rectTimeAvg, rectFillTimeAvg, circleTimeAvg,
                    circleFillTimeAvg, triangleTimeAvg, triangleFillTimeAvg, 
                    pixelTimeAvg);
}

void ProfileSlow(viewport_t viewport)
{
    uint32_t start, end, buf;
    uint32_t clearTime, verHorLineTime, lineTime, rectTime, rectFillTime,
                circleTime, circleFillTime, triangleTime, triangleFillTime,
                pixelTime;
    
    uint32_t clearTimeAvg, verHorLineTimeAvg, lineTimeAvg, rectTimeAvg, rectFillTimeAvg,
                circleTimeAvg, circleFillTimeAvg, triangleTimeAvg, triangleFillTimeAvg,
                pixelTimeAvg;

    RENS_Init(viewport);

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        RENS_Clear(COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    clearTimeAvg = buf / MAX_RUNS;
    clearTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        RENS_PutPixel(100, 100, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    pixelTimeAvg = buf / MAX_RUNS;
    pixelTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        RENS_VerticalLine(0, 0, 100, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    verHorLineTimeAvg = buf / MAX_RUNS;
    verHorLineTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        REN_DrawRect(0, 0, 100, 100, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    rectTimeAvg = buf / MAX_RUNS;
    rectTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        RENS_FillRect(0, 0, 100, 100, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    rectFillTimeAvg = buf / MAX_RUNS;
    rectFillTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        RENS_DrawLine(0, 0, 100, 100, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    lineTimeAvg = buf / MAX_RUNS;
    lineTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        RENS_DrawCircle(200, 150, 50, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    circleTimeAvg = buf / MAX_RUNS;
    circleTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        RENS_FillCircle(200, 150, 50, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    circleFillTimeAvg = buf / MAX_RUNS;
    circleFillTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        RENS_DrawTriangle(200, 200, 300, 270, 150, 250, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    triangleTimeAvg = buf / MAX_RUNS;
    triangleTime = buf;

    buf = 0;
    for(int i = 0; i < MAX_RUNS; i++)
    {
        start = millis();
        RENS_FillTriangle(200, 200, 300, 270, 150, 250, COL_MAGENTA);
        end = millis();
        buf += end - start;
    }
    triangleFillTimeAvg = buf / MAX_RUNS;
    triangleFillTime = buf;

    DrawStatsSlow(clearTime, verHorLineTime, lineTime, 
                    rectTime, rectFillTime, circleTime,
                    circleFillTime, triangleTime, triangleFillTime, 
                    pixelTime, clearTimeAvg, verHorLineTimeAvg, lineTimeAvg, 
                    rectTimeAvg, rectFillTimeAvg, circleTimeAvg,
                    circleFillTimeAvg, triangleTimeAvg, triangleFillTimeAvg, 
                    pixelTimeAvg);
}