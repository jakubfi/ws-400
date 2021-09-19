#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "hd44780.h"
#include "mcp23017.h"
#include "i2cmaster.h"
#include "chars.h"
#include "pins.h"
#include "scr.h"

#define SW_DIR	DDRC
#define SW_PORT	PORTC
#define SW_PIN	PINC
#define SW_SEL	(1 << PC3)
#define SW_OK	(1 << PC2)

#define CONN(row, col) bus[row*48+col]

MCP23017 dev[6];
uint8_t bus[96];

/*
	Bus represents one 96-pin debug edge connector, either left or right.
	Positions are numbered as follows:

	 95 93 91 ...       ... 7 5 3 1
	.-------------\   \------------.
	|             /   /            |
    `-------------\   \------------'
	 94 92 90 ...       ... 6 4 2 0

	 if "rotated" is set, whole thing gets rotated 180 deg.

*/

// -----------------------------------------------------------------------
uint8_t read_state(uint8_t rotated)
{
	uint8_t pos = 0;
	static uint16_t last_data[6];
	uint8_t data_change = 0;

	// 6 ICs to read data from (6x16 bit)
	for (uint8_t i=0 ; i<6 ; i++) {
		uint16_t data;
		data = mcp23017_read_register(dev+i, MCP23017_GPIOA);
		data |= mcp23017_read_register(dev+i, MCP23017_GPIOB) << 8;
		if (!data_change && (data != last_data[i])) data_change = 1;
		last_data[i] = data;

		// fill bus data
		for (int8_t b=15 ; b>=0 ; b--) {
			uint8_t loc = 48*(pos&1) + (pos>>1);
			// if the device is rotated, fill bus table from the end
			if (rotated) loc = 95 - loc;
			bus[loc] = (data >> b) & 1;
			pos++;
		}
	}

	return data_change;
}

// -----------------------------------------------------------------------
void print_raw(uint8_t pos)
{
	uint8_t xpos;

	int8_t count = pos==4 ? 8 : 10;
	int8_t start = 38-10*pos;
	if (start<0) start = 0;
	int8_t end = start + count;

	scr_clr();
	char s[12];
	sprintf(s, "%d-%d", pos*10+count, pos*10+1);
	scr_print_at(11, 0, " pos");
	scr_print_at(11, 1, s);
	scr_put_at(10, 0, CH_VDOT);
	scr_put_at(10, 1, CH_VDOT);

	for (uint8_t y=0 ; y<2 ; y++) {
		xpos = pos==4 ? 2 : 0;
		for (uint8_t x=start ; x<end ; x++) {
			scr_put_at(xpos, y, '0' + CONN(y, x));
			xpos++;
		}
	}

	scr_blit();
}

// -----------------------------------------------------------------------
char * decimalize(const __flash struct signal *s, char *tmp, uint8_t neg)
{
	int8_t *x = (int8_t*) s->reg;
	uint8_t shift = s->loc;
	uint16_t val = 0;
	while (*x != -1) {
		val <<= 1;
		if (neg) {
			if (!bus[*x]) val |= 1;
		} else {
			if (bus[*x]) val |= 1;
		}
		x++;
	}
	sprintf(tmp, "%s=%ld", s->name, ((uint32_t)val) << shift);
	return tmp;
}

// -----------------------------------------------------------------------
int smart_print(char *str)
{
	if (!str) return 0;

	uint8_t len = strlen(str);
	if (sx+len > LCD_COLS-sy) { // -sy to make space for CH_CONT at line 1
		if (sy >= 1) {
			scr_put_at(15, 1, CH_CONT);
			return 1;
		} else {
			scr_setpos(0, 1);
		}
	}

	scr_print(str);
	if ((sx > 0) && (sx < LCD_COLS)) {
		scr_print(" ");
	}
	return 0;
}

// -----------------------------------------------------------------------
const struct signal * print_state(const __flash struct signal *s)
{
	char *str;
	char tmp[10];
	uint8_t no_fit = 0;

	scr_clr();

	while (s->name) {
		str = NULL;
		switch (s->type) {
			case POS:
				if (bus[s->loc]) str = (char *) s->name;
				break;
			case NEG:
				if (!bus[s->loc]) str = (char *) s->name;
				break;
			case DEC:
				str = decimalize(s, tmp, 0);
				break;
			case DECNEG:
				str = decimalize(s, tmp, 1);
				break;
		}
		no_fit = smart_print(str);
		if (no_fit) {
			break;
		} else {
			s++;
		}
	}

	if (!s->name) s = NULL;

	scr_blit();

	return s;
}

// -----------------------------------------------------------------------
void menu_update(uint8_t pos)
{
	static uint8_t last_pos = 99;
	if (last_pos == pos) return;
	last_pos = pos;

	static const char *conns[] = {
		" P-X (l)",
		" P-M (r)",
		" P-P (r)",
		" P-R (r)",
		" P-A (l)",
		" FPA (l)",
		" FPA (r)",
		" FPM (l)",
		" FPM (r)",
		" FPS (l)",
		"\x02\x02\x02\x02\x02\x02\x02\x02",
		"\x02\x02\x02\x02\x02\x02\x02\x02",
		NULL
	};

	uint8_t start_p = 4*(pos / 4);
	uint8_t end_p = start_p + 4;

	scr_clr();

	for (uint8_t i=start_p ; i<end_p ; i++) {
		scr_print(conns[i]);
	}

	uint8_t cpos = pos % 4;
	scr_put_at(8*(cpos%2), cpos/2, CH_CURSOR);

	scr_blit();
}

// -----------------------------------------------------------------------
const struct signal * select()
{
	const uint8_t CONN_COUNT = 10;
	const struct signal *connections[] = { PX, PM, PP, PR, PA, FPAL, FPAR, FPML, FPMR, FPS };

	uint8_t pos = 0;
	uint8_t sel = 0;
	uint8_t psel = 0;
	uint8_t ok = 0;

	menu_update(0);

	while (1) {
		psel = sel;
		ok = SW_PIN & SW_OK;
		if (!ok) {
			_delay_ms(150);
			break;
		}
		sel = SW_PIN & SW_SEL;
		if (!sel && psel) {
			pos++;
			if (pos > CONN_COUNT-1) {
				pos = 0;
			}
			menu_update(pos);
			_delay_ms(150);
		}
	}

	return connections[pos];
}

// -----------------------------------------------------------------------
const struct signal * autodetect()
{
	// not implemented
	return NULL;
}

// -----------------------------------------------------------------------
void setup()
{
	// setup switches
	SW_DIR &= ~(SW_SEL|SW_OK);
	SW_PORT |= (SW_SEL|SW_OK);

	// setup MCP23017
	for (uint8_t i=0 ; i<6 ; i++) {
		mcp23017_init(dev+i, i);
		mcp23017_write_register(dev+i, MCP23017_IODIRA, 0xff);
		mcp23017_write_register(dev+i, MCP23017_IODIRB, 0xff);
		mcp23017_write_register(dev+i, MCP23017_IPOLA, 0);
		mcp23017_write_register(dev+i, MCP23017_IPOLB, 0);
		mcp23017_write_register(dev+i, MCP23017_GPPUA, 0);
		mcp23017_write_register(dev+i, MCP23017_GPPUB, 0);
	}

	// setup LCD
	lcd_init();
	lcd_cg_set(CH_CURSOR, cursor);
	lcd_cg_set(CH_HDOT, hdot);
	lcd_cg_set(CH_VDOT, vdot);
	lcd_cg_set(CH_CONT, cont);
	lcd_clear();
	lcd_home();
}

// -----------------------------------------------------------------------
// ---- MAIN -------------------------------------------------------------
// -----------------------------------------------------------------------
int main(void)
{
	setup();

	scr_clr();

	// If started with "OK" button pressed, assume display rotated 180 deg.
	uint8_t rotated = 0;
	if (!(SW_PIN & SW_OK)) {
		rotated = 1;
		scr_print_at(0, 0, " .-  DEVICE  <-.");
		scr_print_at(0, 1, " `>  ROTATED  -'");
		scr_blit();
		_delay_ms(500);
	}
	// wait for keys depress
	while ((SW_PIN & (SW_SEL|SW_OK)) != (SW_SEL|SW_OK));

	const struct signal *conn;
	conn = autodetect();
	if (!conn) {
	   	conn = select();
	}

	uint8_t raw = 0;
	uint8_t raw_pos = 0;
	const __flash struct signal *start_signal = conn;
	const __flash struct signal *next_signal = NULL;
	uint8_t sel=1, psel;
	uint8_t ok=1, pok;

	// wait for keys depress
	while ((SW_PIN & (SW_SEL|SW_OK)) != (SW_SEL|SW_OK));

	while (1) {
		// read debug bus state
		read_state(rotated);

		// handle selecting next portion of signals (if they don't fit on the screen)
		psel = sel;
		sel = SW_PIN & SW_SEL;
		if (!sel && psel) {
			if (raw) {
				if (raw_pos<4) {
					raw_pos++;
				} else {
					raw_pos = 0;
				}
			} else {
				if (next_signal) start_signal = next_signal;
				else start_signal = conn;
			}
			_delay_ms(150);
		}

		// pressing "OK" switches between raw and normal display
		pok = ok;
		ok = SW_PIN & SW_OK;
		if (!ok && pok) {
			raw = ~raw;
			start_signal = conn;
			_delay_ms(150);
		}

		// print signals
		if (raw) {
			print_raw(raw_pos);
		} else {
			next_signal = print_state(start_signal);
		}
	}
}

// vim: tabstop=4 shiftwidth=4 autoindent
