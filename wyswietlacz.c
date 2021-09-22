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

MCP23017 dev[6];

/*
 * There are two debugger connectors per each module. This device can be connected to any one of them.
 * Each connector is a 96-pin edge connector. Pins are numbered from the right, starting from 1.
 * Top row is "D" row, bottom is "C". Right connector has pins 1 to 48, left - 49 to 96.
 *
 * Port expanders on the device are connected as follows:
 *
 *       1B7 1B5 1B3       6A5 6A3 6A1
 *     .-------------\   \------------.
 *     | D48 D47 D46 /   / D2  D1  D0 |
 *     | C48 C47 C46 \   \ C2  C1  C0 |
 *     `-------------/   /------------'
 *       1B6 1B4 1B2       6A4 6A2 6A0
 *
 * Note: "1B7" = expander U1, port B, bit 7
 *
 * When connecting the device to the left port, pin numbers 49-96 are remapped to 1-48
*/

uint8_t rotated = 0;
uint16_t raw_data[6];

// -----------------------------------------------------------------------
void update_state(void)
{
#ifdef SIMULATED
	static const uint16_t sim_data[6] = {
		0b0000000000000000,
		0b0000000000000000,
		0b0000000100000000,
		0b0000000010000000,
		0b0000000000000000,
		0b0000000000000000,
	};
	#endif

	for (uint8_t i=0 ; i<6 ; i++) {
#ifdef SIMULATED
		raw_data[i] = sim_data[i];
#else
		raw_data[i]  = mcp23017_read_register(dev+i, MCP23017_GPIOB) << 8;
		raw_data[i] |= mcp23017_read_register(dev+i, MCP23017_GPIOA);
#endif
	}
}

// -----------------------------------------------------------------------
uint8_t read_signal(uint8_t row, uint8_t column)
{
	// Device connects to either right (pins 1-48) or left (pins 49-96) debug connector.
	// Translate row numbers to 1-48 for the left connector.
	if (column > 48) column = column - 48;

	// Pins are numbered right to left, 1 to 48. Bits are stored left to right.
	// Column numbers need to be swapped and reindexed: 1..48 -> 47..0
	column = 48 - column;

	// Translate row and column if the device is rotated.
	if (rotated) {
		column = 47 - column; // first column becomes last
		row = 1 - row; // top row becomes bottom
	}

	// Each word holds 8 columns of data
	const uint8_t word = column / 8;
	// 2 bits per column, 16 bits per word
	// upper row holds even bits (with no rotation)
	const uint8_t bit = 15 - (2 * (column % 8) + row);

	return (raw_data[word] >> bit) & 1;
}

// -----------------------------------------------------------------------
uint8_t read_signal_rowcol(uint8_t rowcol)
{
	const uint8_t row = rowcol >> 7;
	const uint8_t col = rowcol & 0b01111111;

	return read_signal(row, col);
}


// -----------------------------------------------------------------------
void print_raw(uint8_t pos)
{
	const int8_t columns = 8;
	const int8_t start = 1 + columns * pos;
	const int8_t end = start + columns;
	char s[12];

	scr_clr();

	sprintf(s, "%d-%d", end-1, start);
	scr_print_at(11, 0, " pos");
	scr_print_at(11, 1, s);
	scr_put_at(10, 0, CH_VDOT);
	scr_put_at(10, 1, CH_VDOT);

	uint8_t xpos = 8;
	for (uint8_t column=start ; column<end ; column++) {
		for (uint8_t row=ROW_D ; row<=ROW_C ; row++) {
			const uint8_t val = '0' + read_signal(row, column);
			scr_put_at(xpos, row, val);
		}
		xpos--;
		if (xpos == 4) xpos--; // additional space between nibbles
	}
}

// -----------------------------------------------------------------------
char * decimalize(const __flash struct signal *s, char *tmp, uint8_t polarity)
{
	int8_t *x = (int8_t*) s->d.reg;
	// Value may require shifting left if it is a part of larger register.
	// Shift is stored in the attributes.
	const uint8_t shift = (s->attr & SIG_SHIFT_MASK) >> SIG_SHIFT_POS;

	uint16_t val = 0;
	while (*x != 0) {
		val <<= 1;
		if (read_signal_rowcol(*x) == polarity) val |= 1;
		x++;
	}

	sprintf(tmp, "%s=%ld", s->name, ((uint32_t)val) << shift);

	return tmp;
}

// -----------------------------------------------------------------------
int smart_print(char *str)
{
	if (!str) return 0;

	const uint8_t len = strlen(str);
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
		const uint8_t sig_polarity = s->attr & SIG_POLARITY_MASK;
		const uint8_t sig_type = s->attr & SIG_TYPE_MASK;

		str = NULL;
		if (sig_type == BIN) {
			if (read_signal_rowcol(s->d.rowcol) == sig_polarity) str = (char *) s->name;
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

	const uint8_t start_p = 4*(pos / 4);
	const uint8_t end_p = start_p + 4;

	scr_clr();

	for (uint8_t i=start_p ; i<end_p ; i++) {
		scr_print(conns[i]);
	}

	const uint8_t cpos = pos % 4;
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
	uint8_t raw = 0;
	uint8_t raw_pos = 0;
	uint8_t key_was_pressed = 0;
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
		update_state();

		// Handle selecting next portion of signals (if they don't fit on the screen)
		if (key_pressed(SW_SEL)) {
			key_was_pressed = 1;
			if (raw) {
				raw_pos++;
				if (raw_pos>5) raw_pos = 0;
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

		// Update screen immediatly after a key press for nice interactivity
		// (don't wait for key depress).
		if (raw) {
			print_raw(raw_pos);
		} else {
			next_signal = print_state(start_signal);
		}
		scr_blit();

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
