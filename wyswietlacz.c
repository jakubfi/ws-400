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
	Indexes translate to pin positions as follows:

	 95 93 91 ...       ... 7 5 3 1
	.-------------\   \------------.
	|             /   /            |
    `-------------\   \------------'
	 94 92 90 ...       ... 6 4 2 0

	 This is due to how port expanders are connected to the debug connector
	 If "rotated" is set, whole thing gets rotated 180 deg.

*/

// -----------------------------------------------------------------------
uint8_t read_state(uint8_t rotated)
{
	uint8_t pos = 0;
	static uint16_t last_data[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	uint8_t data_changed = 0;

	// 6 ICs to read data from (6x16 bit)
	for (uint8_t i=0 ; i<6 ; i++) {
		uint16_t data;
		data = mcp23017_read_register(dev+i, MCP23017_GPIOA);
		data |= mcp23017_read_register(dev+i, MCP23017_GPIOB) << 8;
		if (data != last_data[i]) {
			data_changed = 1;
			last_data[i] = data;

			// fill bus data
			for (int8_t b=15 ; b>=0 ; b--) {
				uint8_t loc = 48*(pos&1) + (pos>>1);
				// if the device is rotated, fill bus table from the end
				if (rotated) loc = 95 - loc;
				bus[loc] = (data >> b) & 1;
				pos++;
			}
		} else {
			pos += 16;
		}
	}

	return data_changed;
}

// -----------------------------------------------------------------------
void print_raw(uint8_t pos)
{
	uint8_t xpos;

	int8_t count = (pos == 4) ? 8 : 10;
	int8_t start = 38 - 10*pos;
	if (start<0) start = 0;
	int8_t end = start + count;

	scr_clr();
	char s[12];
	sprintf(s, "%d-%d", 10*pos + count, 10*pos + 1);
	scr_print_at(11, 0, " pos");
	scr_print_at(11, 1, s);
	scr_put_at(10, 0, CH_VDOT);
	scr_put_at(10, 1, CH_VDOT);

	for (uint8_t y=0 ; y<2 ; y++) {
		xpos = (pos == 4) ? 2 : 0;
		for (uint8_t x=start ; x<end ; x++) {
			scr_put_at(xpos, y, '0' + CONN(y, x));
			xpos++;
		}
	}
}

// -----------------------------------------------------------------------
char * decimalize(const __flash struct signal *s, char *tmp, uint8_t polarity)
{
	int8_t *x = (int8_t*) s->reg;
	uint8_t shift = s->loc;
	uint16_t val = 0;
	while (*x != -1) {
		val <<= 1;
		if (bus[*x] == polarity) val |= 1;
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
		uint8_t sig_polarity = s->attr & SIG_POLARITY_MASK;
		uint8_t sig_type = s->attr & SIG_TYPE_MASK;

		str = NULL;
		if (sig_type == BIN) {
			if (bus[s->loc] == sig_polarity) str = (char *) s->name;
		} else if (sig_type == DEC) {
			str = decimalize(s, tmp, sig_polarity);
		}

		no_fit = smart_print(str);
		if (no_fit) {
			break;
		} else {
			s++;
		}
	}

	if (!s->name) s = NULL;

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
uint8_t key_pressed(uint8_t expected_key)
{
	uint8_t shift_reg = 0;
	int8_t repetitions = 0;

	do {
		shift_reg |= (SW_PIN & expected_key) ? 0 : 1;
		if ((repetitions == 0) && (shift_reg == 0)) {
			// no initial key press, nothing to do
			return 0;
		} else if (shift_reg == 0xff) {
			// got a key press
			return 1;
		} else {
			// press detected, start debouncing
			shift_reg <<= 1;
			repetitions++;
			_delay_ms(4);
		}
	} while (repetitions < 40);

	// no keypress after N repetitions
	return 0;
}

// -----------------------------------------------------------------------
void wait_no_key(void)
{
	while ((SW_PIN & (SW_SEL|SW_OK)) != (SW_SEL|SW_OK));
}

// -----------------------------------------------------------------------
const struct signal * select_connector()
{
	const uint8_t CONN_COUNT = 10;
	const struct signal *connections[] = { PX, PM, PP, PR, PA, FPAL, FPAR, FPML, FPMR, FPS };

	uint8_t pos = 0;

	menu_update(0);

	while (1) {
		if (key_pressed(SW_OK)) {
			wait_no_key();
			break;
		} else if (key_pressed(SW_SEL)) {
			pos++;
			if (pos >= CONN_COUNT) {
				pos = 0;
			}
			menu_update(pos);
			wait_no_key();
		}
	}

	return connections[pos];
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
int select_rotation(void)
{
	// If started with "OK" button pressed, assume display rotated 180 deg.
	if (!key_pressed(SW_OK)) return 0;

	scr_print_at(1, 0, ".-  DEVICE  <-.");
	scr_print_at(1, 1, "`>  ROTATED  -'");
	scr_blit();
	_delay_ms(500);
	wait_no_key();

	return 1;
}

// -----------------------------------------------------------------------
// ---- MAIN -------------------------------------------------------------
// -----------------------------------------------------------------------
int main(void)
{
	uint8_t rotated;
	uint8_t raw = 0;
	uint8_t raw_pos = 0;
	uint8_t key_was_pressed = 0;
	uint8_t data_changed;
	const struct signal *selected_connector;
	const __flash struct signal *start_signal;
	const __flash struct signal *next_signal = NULL;

	setup();
	scr_clr();

	rotated = select_rotation();
	selected_connector = select_connector();
	start_signal = selected_connector;

	while (1) {
		// read debug bus state
		data_changed = read_state(rotated);

		// Handle selecting next portion of signals (if they don't fit on the screen)
		if (key_pressed(SW_SEL)) {
			key_was_pressed = 1;
			if (raw) {
				if (raw_pos<4) raw_pos++;
				else raw_pos = 0;
			} else {
				if (next_signal) start_signal = next_signal;
				else start_signal = selected_connector;
			}
		}

		// Pressing "OK" switches between raw and normal display
		if (key_pressed(SW_OK)) {
			key_was_pressed = 1;
			raw = ~raw;
			start_signal = selected_connector;
		}

		// Update screen only if signal state changed or key was pressed.
		// Do it immediatly after a key press for nice interactivity
		// (don't wait for key depress).
		if (data_changed || key_was_pressed) {
			if (raw) {
				print_raw(raw_pos);
			} else {
				next_signal = print_state(start_signal);
			}
			scr_blit();
		}

		// Wait for key depress only if a key was pressed in current loop
		// so we don't wait if a key was pressed during screen update.
		// That's to avoid ghost presses.
		if (key_was_pressed) {
			key_was_pressed = 0;
			wait_no_key();
		}
	}
}

// vim: tabstop=4 shiftwidth=4 autoindent
