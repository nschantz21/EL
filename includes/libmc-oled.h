#ifndef __LIBMC_OLED_H__
#define __LIBMC_OLED_H__

#include <stdint.h>

#define  ARRAY_SIZE(a)          (sizeof(a) / sizeof((a)[0]))
#ifdef PORTRAIT
	#define OLED_WIDTH              (80)
	#define OLED_HEIGHT             (160)
#else
	#define OLED_WIDTH              (160)
	#define OLED_HEIGHT             (80)
#endif

#define OLED_CHAR_WIDTH			(5)		// Does not include blank column on right
#define OLED_CHAR_HEIGHT		(8)		// Includes blank row at bottom
#define OLED_ROWS				(OLED_HEIGHT/OLED_CHAR_HEIGHT)
#define OLED_COLS				(OLED_WIDTH/(OLED_CHAR_WIDTH+1))

// Color definitions
#define ST7735_BLACK   0x0000
#define ST7735_BLUE    0x001F
#define ST7735_RED     0xF800
#define ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0
#define ST7735_WHITE   0xFFFF

uint32_t OLEDDrawString (uint16_t x, uint16_t y, char *pt, int16_t textColor);
void OLEDDrawChar (int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor);
void OLEDWriteNumber (int row, int col, int value, int len);
void OLEDFillRect (int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void OLEDClearScreen (void);
int OLEDInit (void);
void OLEDDeInit (void);
extern int x_limit, y_limit, row_limit, col_limit;

#endif
