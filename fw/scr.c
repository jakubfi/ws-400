#include <inttypes.h>
#include "hd44780.h"
#include "scr.h"

char screen[32];
uint8_t sx, sy;

// -----------------------------------------------------------------------
void scr_clr()
{
    for (uint8_t i=0 ; i<32 ; i++) screen[i] = ' ';
    sx = sy = 0;
}

// -----------------------------------------------------------------------
void scr_blit()
{
    uint8_t i;
    lcd_setpos(0, 0);
    for (i=0 ; i<16 ; i++) lcd_write_data(screen[i]);
    lcd_setpos(0, 1);
    for (i=16 ; i<32 ; i++) lcd_write_data(screen[i]);
}

// -----------------------------------------------------------------------
void scr_print(const char *str)
{
    while(*str) {
        scr_put_at(sx++, sy, *str++);
        if (sx >= LCD_COLS) {
            sy++;
            sx = 0;
        }
        if (sy >= LCD_LINES) {
            sy = 0;
        }
    }
}

