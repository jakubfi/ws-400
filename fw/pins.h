#ifndef __PINS_H__
#define __PINS_H__

#include <inttypes.h>

#define ROW_D 0
#define ROW_C 1

// Macros for setting signal position on the debug bus
#define D(column) (column | (ROW_D << 7))
#define C(column) (column | (ROW_C << 7))

#define SIG_POLARITY_MASK	0b00000001
#define SIG_TYPE_MASK		0b00000110
#define SIG_SHIFT_MASK		0b11110000
#define SIG_SHIFT_POS		4

enum signal_attrs {
	NEG = 0 << 0,
	POS = 1 << 0,
	BIN = 0 << 1,
	DEC = 1 << 1,
	HEX = 2 << 1,
};

struct signal {
	const char *name;			// name of the signal
	union d {
		const int8_t rowcol;	// signal location on the debug bus or shift for registers
		const int8_t *reg;		// pointer to a register signal table, if this is a n-bit register
	} d;
	const uint8_t attr;			// signal attributes
};

extern const __flash struct signal PX[];
extern const __flash struct signal PM[];
extern const __flash struct signal PP[];
extern const __flash struct signal PR[];
extern const __flash struct signal PA[];
extern const __flash struct signal FPAR[];
extern const __flash struct signal FPAL[];
extern const __flash struct signal FPMR[];
extern const __flash struct signal FPML[];
extern const __flash struct signal FPS[];

#endif

// vim: tabstop=4 shiftwidth=4 autoindent
