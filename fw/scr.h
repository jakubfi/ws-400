#ifndef __SCR_H__
#define __SCR_H__

extern uint8_t sx, sy;
extern char screen[32];

void scr_clr();
void scr_blit();
#define scr_setpos(x, y) sx = x; sy = y
#define scr_put_at(x, y, c) screen[((y)<<4)+(x)] = c
void scr_print(const char *str);
#define scr_print_at(x, y, str) scr_setpos(x, y); scr_print(str)

#endif
