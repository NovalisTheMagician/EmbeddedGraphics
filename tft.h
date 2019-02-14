#ifndef TFT_H_
#define TFT_H_

#define LCD_WIDTH	480
#define LCD_HEIGHT	272

#define HFP   32
#define HSYNC 41
#define HBP   13

#define VFP   2
#define VSYNC 10
#define VBP   2

void TFT_Init();
void TFT_WaitForVSYNC();

#endif