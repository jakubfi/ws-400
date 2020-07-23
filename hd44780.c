#include <inttypes.h>
#include <string.h>
#include <util/delay.h>
#include "hd44780.h"

static uint8_t px = 0;
static uint8_t py = 0;

// -----------------------------------------------------------------------
static uint8_t lcd_read()
{
	static uint8_t tmp;

	LCD_DATA_DIR = 0x00;
	LCD_RW_PORT |= LCD_RW;
	LCD_E_PORT |= LCD_E;
	asm("nop");
	asm("nop");
	tmp = LCD_DATA_PIN;
	LCD_E_PORT &= ~LCD_E;
	return tmp;
}

// -----------------------------------------------------------------------
static void lcd_write(uint8_t data)
{
	LCD_DATA_DIR = 0xFF;
	LCD_RW_PORT &= ~LCD_RW;
	LCD_E_PORT |= LCD_E;
	LCD_DATA_PORT = data;
	asm("nop");
	LCD_E_PORT &= ~LCD_E;
}

// -----------------------------------------------------------------------
uint8_t lcd_read_addr()
{
	LCD_RS_PORT &= ~LCD_RS;
	return lcd_read();
}

// -----------------------------------------------------------------------
inline static uint8_t lcd_busy()
{
	return lcd_read_addr() & 0x80;
}

// -----------------------------------------------------------------------
uint8_t lcd_read_data()
{
	LCD_RS_PORT |= LCD_RS;
	return lcd_read();
}

// -----------------------------------------------------------------------
void lcd_write_cmd(uint8_t cmd)
{
	LCD_RS_PORT &= ~LCD_RS;
	lcd_write(cmd);
	while (lcd_busy());
}

// -----------------------------------------------------------------------
void lcd_write_data(uint8_t data)
{
	LCD_RS_PORT |= LCD_RS;
	lcd_write(data);
	while (lcd_busy());
}

// -----------------------------------------------------------------------
void lcd_puts(const char *str, int8_t len)
{
	do {
		lcd_write_data(*str);
		str++;
		len--;
	} while (len>0);
}

// -----------------------------------------------------------------------
void lcd_print(const char *str)
{
	while(*str) {
		lcd_write_data(*str);
		str++;
		px++;
		if (px >= LCD_COLS) {
			py++;
			px = 0;
			lcd_setpos(px, py);
		}
	}
}

// -----------------------------------------------------------------------
uint8_t lcd_get_x()
{
	return px;
}

// -----------------------------------------------------------------------
uint8_t lcd_get_y()
{
	return py;
}

// -----------------------------------------------------------------------
void lcd_setpos(uint8_t x, uint8_t y)
{
	px = x;
	py = y;
	lcd_write_cmd(HD44780_DDRAM_ADDR | (x + (0x40 * y)));
}

// -----------------------------------------------------------------------
void lcd_clear()
{
	px = 0;
	py = 0;
	lcd_write_cmd(HD44780_CLEAR);
	_delay_ms(1.6);
}

// -----------------------------------------------------------------------
void lcd_home()
{
	lcd_write_cmd(HD44780_HOME);
	_delay_ms(1.6);
}

// -----------------------------------------------------------------------
void lcd_cg_set(const uint8_t ch, const __flash uint8_t *chdata)
{
	lcd_write_cmd(HD44780_CGRAM_ADDR | (ch<<3));
	for (unsigned int i = 0 ; i<8 ; i++) {
		lcd_write_data(*(chdata++));
	}
}

// -----------------------------------------------------------------------
void lcd_init()
{
	LCD_DATA_DIR = 0xFF;
	LCD_E_DIR |= LCD_E;
	LCD_RS_DIR |= LCD_RS;
	LCD_RW_DIR |= LCD_RW;

	LCD_RS_PORT &= ~LCD_RS;
	LCD_E_PORT &= ~LCD_E;
	LCD_RW_PORT &= ~LCD_RW;

	_delay_ms(15);

	lcd_write_cmd(HD44780_FUNCTION | HD44780_FONT5x7 | HD44780_TWO_LINES | HD44780_8_BIT);
	lcd_write_cmd(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_RIGHT | HD44780_EM_SHIFT );
	lcd_write_cmd(HD44780_DISPLAY | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_BLINK_OFF);
}

// vim: tabstop=4 shiftwidth=4 autoindent
