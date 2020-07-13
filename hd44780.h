#ifndef __HD44780_H_
#define __HD44780_H_

#include <avr/io.h>

// --- port setup --------------------------------------------------------

#define LCD_RS_DIR	DDRK
#define LCD_RS_PORT	PORTK
#define LCD_RS		(1 << PK2)

#define LCD_RW_DIR	DDRK
#define LCD_RW_PORT	PORTK
#define LCD_RW		(1 << PK1)

#define LCD_E_DIR	DDRK
#define LCD_E_PORT	PORTK
#define LCD_E		(1 << PK0)

#define LCD_DATA_DIR	DDRF
#define LCD_DATA_PORT	PORTF
#define LCD_DATA_PIN	PINF

// --- HD44780 commands --------------------------------------------------

#define HD44780_CLEAR			0x01
#define HD44780_HOME			0x02
#define HD44780_ENTRY_MODE		0x04
#define HD44780_DISPLAY			0x08
#define HD44780_SHIFT			0x10
#define HD44780_FUNCTION		0x20
#define HD44780_CGRAM_ADDR		0x40
#define HD44780_DDRAM_ADDR		0x80

#define HD44780_EM_SHIFT_RIGHT	0 << 0
#define HD44780_EM_SHIFT_LEFT	1 << 0
#define HD44780_EM_NOSHIFT		0 << 1
#define HD44780_EM_SHIFT		1 << 1

#define HD44780_BLINK_OFF		0 << 0
#define HD44780_BLINK_ON		1 << 0
#define HD44780_CURSOR_OFF		0 << 1
#define HD44780_CURSOR_ON		1 << 1
#define HD44780_DISPLAY_OFF		0 << 2
#define HD44780_DISPLAY_ON		1 << 2

#define HD44780_SHIFT_LEFT		0 << 2
#define HD44780_SHIFT_RIGHT		1 << 2
#define HD44780_SHIFT_CURSOR	0 << 3
#define HD44780_SHIFT_DISPLAY	1 << 3

#define HD44780_FONT5x7			0 << 2
#define HD44780_FONT5x10		1 << 2
#define HD44780_ONE_LINE		0 << 3
#define HD44780_TWO_LINES		1 << 3
#define HD44780_4_BIT			0 << 4
#define HD44780_8_BIT			1 << 4

void lcd_write_cmd(const uint8_t cmd);
void lcd_write_data(const uint8_t data);
unsigned char lcd_read_data(void);
void lcd_puts(const char *, int8_t len);
uint8_t lcd_print(const char *);
void lcd_setpos(const uint8_t x, const uint8_t y);
void lcd_clear(void);
void lcd_home(void);
void lcd_cg_set(const uint8_t ch, const uint8_t *chdata);
void lcd_init(void);

#endif

// vim: tabstop=4 shiftwidth=4 autoindent
