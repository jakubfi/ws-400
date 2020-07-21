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

// -----------------------------------------------------------------------
void read_state()
{
#define SET(row, pin) dev[row[pin-1].ic_addr].data |= (1 << row[pin-1].bit)

	//SET(row_D, 88);
	//dev[0].data = 0xffff;
	//dev[1].data = 0xffff;
	//dev[2].data = 0xffff;
	//dev[3].data = 0xffff;
	//dev[4].data = 0xffff;
	//dev[5].data = 0xffff;
	dev[0].data = rand();
	dev[1].data = rand();
	dev[2].data = rand();
	dev[3].data = rand();
	dev[4].data = rand();
	dev[5].data = rand();
}

// -----------------------------------------------------------------------
void print_raw()
{
	char buf[] = "      ";

	for (uint8_t i=0 ; i<6 ; i++) {
		uint8_t p = 0;
		for (int8_t n=12 ; n>=0 ; n-=4) {
			buf[p++] = (dev[i].data >> n) & 0b1111;
		}
		lcd_setpos(5*(i%3), i/3);
		lcd_puts(buf, 5);
	}
}

// -----------------------------------------------------------------------
void print_state(const struct signal *s)
{
	lcd_setpos(0, 0);
	while (s->name) {
		uint8_t ic = s->loc->ic_addr;
		uint8_t bit = s->loc->bit;
		if (((dev[ic].data >> bit) & 1)) {
			lcd_print(s->name);
			lcd_print(" ");
		}
		s++;
	}
}

uint8_t CONN_COUNT = 10;

// -----------------------------------------------------------------------
void menu_select(uint8_t pos)
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
		"--------",
		"--------",
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
	lcd_write_data('}'+1);

}

// -----------------------------------------------------------------------
const struct signal * select()
{
	const struct signal *connections[] = { PX, PM, PP, PR, PA, FPAL, FPAR, FPML, FPMR, FPS };

	uint8_t pos = 0;
	uint8_t sel = 0;
	uint8_t psel = 0;
	uint8_t ok = 0;

	menu_select(0);

	while (1) {
		psel = sel;
		ok = SW_PIN & SW_OK;
		if (!ok) {
			break;
		}
		sel = SW_PIN & SW_SEL;
		if (!sel && psel) {
			pos++;
			if (pos > CONN_COUNT-1) {
				pos = 0;
			}
			menu_select(pos);
			_delay_ms(100);
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

	lcd_init();
	lcd_clear();
	lcd_home();
	lcd_cg_set(0, d0000);
	lcd_cg_set(1, d0001);
	lcd_cg_set(2, d0010);
	lcd_cg_set(3, d0011);
	lcd_cg_set(4, d0100);
	lcd_cg_set(5, d0101);
	lcd_cg_set(6, d0110);
	lcd_cg_set(7, d0111);
	lcd_cg_set(8, d1000);
	lcd_cg_set(9, d1001);
	lcd_cg_set(10, d1010);
	lcd_cg_set(11, d1011);
	lcd_cg_set(12, d1100);
	lcd_cg_set(13, d1101);
	lcd_cg_set(14, d1110);
	lcd_cg_set(15, d1111);

//	const struct signal *conn;
//	conn = autodetect();
//	if (!conn) {
//	   	conn = select();
//	}

	lcd_clear();

	while (1) {
		read_state();
		print_raw();
		_delay_ms(500);
	}
}

// vim: tabstop=4 shiftwidth=4 autoindent
