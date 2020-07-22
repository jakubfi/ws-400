#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <avr/io.h>
#include <util/delay.h>
#include "hd44780.h"
#include "mcp23017.h"
#include "i2cmaster.h"
#include "chars.h"
#include "pins.h"

#define SW_DIR	DDRC
#define SW_PORT	PORTC
#define SW_PIN	PINC
#define SW_SEL	(1 << PC3)
#define SW_OK	(1 << PC2)

MCP23017 dev[6];
uint8_t bus[96];

#define A 0
#define B 1
#define CONN(row, col) bus[row*48+col]

// -----------------------------------------------------------------------
void read_state()
{
	uint8_t pos = 0;

	for (uint8_t i=0 ; i<6 ; i++) {
		uint16_t io;
		io = mcp23017_read_register(dev+i, MCP23017_GPIOA);
		io |= mcp23017_read_register(dev+i, MCP23017_GPIOB) << 8;
		for (int8_t b=15 ; b>=0 ; b--) {
			uint8_t loc = 48*(pos&1) + (pos>>1);
			bus[loc] = (io >> b) & 1;
			pos++;
		}
	}
}

// -----------------------------------------------------------------------
void print_raw()
{
	char buf[11];
	buf[10] = '\0';
	for (uint8_t y=0 ; y<2 ; y++) {
		for (uint8_t x=0 ; x<10 ; x++) {
			buf[x] = '0' + CONN(y, x);
		}
		lcd_setpos(0, y);
		lcd_print(buf);
	}
}

// -----------------------------------------------------------------------
void print_state(const struct signal *s)
{
	char empty[] = "                ";
	lcd_setpos(0, 0);
	while (s->name) {
		if (((s->polarity == POS) && bus[s->loc]) || ((s->polarity == NEG) && !bus[s->loc])) {
			lcd_print(s->name);
			if (lcd_get_x() != 0) {
				lcd_print(" ");
			}
		}
		s++;
	}
	if (lcd_get_x() < 16) {
		lcd_puts(empty, 16-lcd_get_x());
	}
	if (lcd_get_y() == 0) {
		lcd_setpos(0, 1);
		lcd_puts(empty, 16);
	}
}

uint8_t CONN_COUNT = 10;

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
	uint8_t end_p = start_p*4 + 4;

	lcd_setpos(0, 0);
	for (uint8_t i=start_p ; i<end_p ; i++) {
		lcd_print(conns[i]);
	}

	uint8_t cpos = pos % 4;

	lcd_setpos(8*(cpos%2), cpos/2);
	lcd_write_data(CH_CURSOR);

}

// -----------------------------------------------------------------------
const struct signal * select()
{
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
	return NULL;
}

// -----------------------------------------------------------------------
// ---- MAIN -------------------------------------------------------------
// -----------------------------------------------------------------------
int main(void) {

	SW_DIR &= ~(SW_SEL|SW_OK);
	SW_PORT |= (SW_SEL|SW_OK);

	for (uint8_t i=0 ; i<6 ; i++) {
		mcp23017_init(dev+i, i);
		mcp23017_write_register(dev+i, MCP23017_IODIRA, 0xff);
		mcp23017_write_register(dev+i, MCP23017_IODIRB, 0xff);
		mcp23017_write_register(dev+i, MCP23017_IPOLA, 0);
		mcp23017_write_register(dev+i, MCP23017_IPOLB, 0);
		mcp23017_write_register(dev+i, MCP23017_GPPUA, 0);
		mcp23017_write_register(dev+i, MCP23017_GPPUB, 0);
	}

	lcd_init();
	lcd_cg_set(CH_CURSOR, cursor);
	lcd_cg_set(CH_HDOT, hdot);
	lcd_cg_set(CH_VDOT, vdot);
	lcd_clear();
	lcd_home();

	const struct signal *conn;
	conn = autodetect();
	if (!conn) {
	   	conn = select();
	}

	lcd_clear();

	while (1) {
		read_state();
//		print_raw();
		print_state(conn);
//		_delay_ms(200);
	}
}

// vim: tabstop=4 shiftwidth=4 autoindent
