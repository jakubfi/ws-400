#ifndef __PINS_H__
#define __PINS_H__

#include <inttypes.h>

#define POS 0
#define NEG 1

struct pinloc {
	const uint8_t ic_addr;
	const uint8_t bit;
} pinloc;

struct signal {
	const char *name;
	const struct pinloc *loc;
	const struct pinloc **reg;
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
