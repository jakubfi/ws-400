#ifndef __SCR_H__
#define __SCR_H__

extern uint8_t sx, sy;
extern char screen[32];

void scr_clr();
void scr_blit();
#define scr_setpos(x, y) sx = x; sy = y
#define scr_put_at(x, y, c) screen[((y)<<4)+(x)] = c
void scr_print(const char *str);

#endif
