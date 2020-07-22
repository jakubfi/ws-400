#ifndef __PINS_H__
#define __PINS_H__

#include <inttypes.h>

enum disp_attrs {
	POS = 0,
	NEG,
	BIN, DEC, HEX
};

struct signal {
	const char *name;
	const int8_t loc;
	const int8_t *reg;
	const uint8_t polarity;
} signal;

extern const struct signal PX[];
extern const struct signal PM[];
extern const struct signal PP[];
extern const struct signal PR[];
extern const struct signal PA[];
extern const struct signal FPAR[];
extern const struct signal FPAL[];
extern const struct signal FPMR[];
extern const struct signal FPML[];
extern const struct signal FPS[];

#endif

// vim: tabstop=4 shiftwidth=4 autoindent
