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
