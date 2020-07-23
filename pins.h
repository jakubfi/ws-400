#ifndef __PINS_H__
#define __PINS_H__

#include <inttypes.h>

#define Dr(n) (48-n)
#define Cr(n) (48-n+48)

#define Dl(n) (96-n)
#define Cl(n) (96-n+48)

enum disp_attrs {
	POS = 0,
	NEG,
	BIN, DEC, DECNEG, HEX
};

struct signal {
	const char *name;
	const int8_t loc;
	const int8_t *reg;
	const uint8_t polarity;
} signal;

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
