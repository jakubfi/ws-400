#ifndef __PINS_H__
#define __PINS_H__

#include <inttypes.h>

// macros for setting signal position on the debug bus
#define Dr(n) (48-n)	// upper row, right connector
#define Cr(n) (48-n+48)	// lower row, right connector
#define Dl(n) (96-n)	// upper row, left connector
#define Cl(n) (96-n+48)	// lower row, left connector

enum signal_types {
	POS = 0,
	NEG,
	BIN, DEC, DECNEG, HEX
};

struct signal {
	const char *name;			// name of the signal
	const int8_t loc;			// location on the debug bus
	const int8_t *reg;			// pointer to a register signal table, if this is a n-bit register
	const uint8_t type;			// signal type: POSitive, NEGative, DECimal, DECimalNEGative
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
