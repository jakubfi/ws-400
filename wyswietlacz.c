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
uint8_t bus[12];

// -----------------------------------------------------------------------
void read_state()
{
	for (uint8_t i=0 ; i<6 ; i++) {
		bus[2*i+0] = mcp23017_read_register(dev+i, MCP23017_GPIOB);
		bus[2*i+1] = mcp23017_read_register(dev+i, MCP23017_GPIOA);
	}
}

// -----------------------------------------------------------------------
void print_raw()
{
}

// -----------------------------------------------------------------------
void print_state(const struct signal *s)
{
//	lcd_setpos(0, 0);
//	while (s->name) {
//		uint8_t ic = s->loc->ic_addr;
//		uint8_t bit = s->loc->bit;
//		if (((dev[ic].data >> bit) & 1)) {
//			lcd_print(s->name);
//			lcd_print(" ");
//		}
//		s++;
//	}
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

	for (uint8_t i=0 ; i<6 ; i++) {
		mcp23017_init(dev+i, i);
		mcp23017_write_register(dev+i, MCP23017_IODIRA, 0xff);
		mcp23017_write_register(dev+i, MCP23017_IODIRB, 0xff);
		mcp23017_write_register(dev+i, MCP23017_IPOLA, 0);
		mcp23017_write_register(dev+i, MCP23017_IPOLB, 0);
		mcp23017_write_register(dev+i, MCP23017_GPPUA, 0xff);
		mcp23017_write_register(dev+i, MCP23017_GPPUB, 0xff);
	}

	lcd_init();
	lcd_cg_set(0x0, d0000);
	lcd_cg_set(0x1, d0001);
	lcd_cg_set(0x2, d0010);
	lcd_cg_set(0x3, d0011);
	lcd_cg_set(0x4, d0100);
	lcd_cg_set(0x5, d0101);
	lcd_cg_set(0x6, d0110);
	lcd_cg_set(0x7, d0111);
	//lcd_cg_set(0x8, d1000);
	//lcd_cg_set(0x9, d1001);
	//lcd_cg_set(0xa, d1010);
	//lcd_cg_set(0xb, d1011);
	//lcd_cg_set(0xc, d1100);
	//lcd_cg_set(0xd, d1101);
	//lcd_cg_set(0xe, d1110);
	//lcd_cg_set(0xf, d1111);
	lcd_clear();
	lcd_home();

//	const struct signal *conn;
//	conn = autodetect();
//	if (!conn) {
//	   	conn = select();
//	}

	lcd_clear();

	lcd_setpos(0, 0);
	lcd_write_data(0x0);
	lcd_write_data(0x1);
	lcd_write_data(0x2);
	lcd_write_data(0x3);
	lcd_write_data(0x4);
	lcd_write_data(0x5);
	lcd_write_data(0x6);
	lcd_write_data(0x7);

	lcd_setpos(0, 1);
	lcd_write_data(0x8);
	lcd_write_data(0x9);
	lcd_write_data(0xa);
	lcd_write_data(0xb);
	lcd_write_data(0xc);
	lcd_write_data(0xd);
	lcd_write_data(0xe);
	lcd_write_data(0xf);
	while (1);
	while (1) {
		read_state();
		print_raw();
		_delay_ms(100);
	}
}

// vim: tabstop=4 shiftwidth=4 autoindent
