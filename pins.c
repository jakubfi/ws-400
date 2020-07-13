#include <inttypes.h>
#include <stddef.h>
#include "pins.h"

#define P(u, b, p) { u, b<<3 | p }
#define D(n) (row_D+n-1)
#define C(n) (row_C+n-1)

const struct pinloc row_C[] = {
/*0*/ 	P(5,0,0), P(5,0,2),	P(5,0,4), P(5,0,6), P(5,1,0), P(5,1,2), P(5,1,4), P(5,1,6),
/*8*/ 	P(4,0,0), P(4,0,2), P(4,0,4), P(4,0,6), P(4,1,0), P(4,1,2), P(4,1,4), P(4,1,6),
/*16*/	P(3,0,0), P(3,0,2), P(3,0,4), P(3,0,6), P(3,1,0), P(3,1,2), P(3,1,4), P(3,1,6),
/*24*/	P(2,0,0), P(2,0,2), P(2,0,4), P(2,0,6), P(2,1,0), P(2,1,2), P(2,1,4), P(2,1,6),
/*32*/	P(1,0,0), P(1,0,2), P(1,0,4), P(1,0,6), P(1,1,0), P(1,1,2), P(1,1,4), P(1,1,6),
/*40*/	P(0,0,0), P(0,0,2), P(0,0,4), P(0,0,6), P(0,1,0), P(0,1,2), P(0,1,4), P(0,1,6),
/*48*/	P(5,0,0), P(5,0,2),	P(5,0,4), P(5,0,6), P(5,1,0), P(5,1,2), P(5,1,4), P(5,1,6),
/*56*/	P(4,0,0), P(4,0,2), P(4,0,4), P(4,0,6), P(4,1,0), P(4,1,2), P(4,1,4), P(4,1,6),
/*64*/	P(3,0,0), P(3,0,2), P(3,0,4), P(3,0,6), P(3,1,0), P(3,1,2), P(3,1,4), P(3,1,6),
/*72*/	P(2,0,0), P(2,0,2), P(2,0,4), P(2,0,6), P(2,1,0), P(2,1,2), P(2,1,4), P(2,1,6),
/*80*/	P(1,0,0), P(1,0,2), P(1,0,4), P(1,0,6), P(1,1,0), P(1,1,2), P(1,1,4), P(1,1,6),
/*88*/	P(0,0,0), P(0,0,2), P(0,0,4), P(0,0,6), P(0,1,0), P(0,1,2), P(0,1,4), P(0,1,6),
};

const struct pinloc row_D[] = {
/*0*/	P(5,0,1), P(5,0,3), P(5,0,5), P(5,0,7), P(5,1,1), P(5,1,3), P(5,1,5), P(5,1,7),
/*8*/	P(4,0,1), P(4,0,3), P(4,0,5), P(4,0,7), P(4,1,1), P(4,1,3), P(4,1,5), P(4,1,7),
/*16*/	P(3,0,1), P(3,0,3), P(3,0,5), P(3,0,7), P(3,1,1), P(3,1,3), P(3,1,5), P(3,1,7),
/*24*/	P(2,0,1), P(2,0,3), P(2,0,5), P(2,0,7), P(2,1,1), P(2,1,3), P(2,1,5), P(2,1,7),
/*32*/	P(1,0,1), P(1,0,3), P(1,0,5), P(1,0,7), P(1,1,1), P(1,1,3), P(1,1,5), P(1,1,7),
/*40*/	P(0,0,1), P(0,0,3), P(0,0,5), P(0,0,7), P(0,1,1), P(0,1,3), P(0,1,5), P(0,1,7),
/*48*/	P(5,0,1), P(5,0,3), P(5,0,5), P(5,0,7), P(5,1,1), P(5,1,3), P(5,1,5), P(5,1,7),
/*56*/	P(4,0,1), P(4,0,3), P(4,0,5), P(4,0,7), P(4,1,1), P(4,1,3), P(4,1,5), P(4,1,7),
/*64*/	P(3,0,1), P(3,0,3), P(3,0,5), P(3,0,7), P(3,1,1), P(3,1,3), P(3,1,5), P(3,1,7),
/*72*/	P(2,0,1), P(2,0,3), P(2,0,5), P(2,0,7), P(2,1,1), P(2,1,3), P(2,1,5), P(2,1,7),
/*80*/	P(1,0,1), P(1,0,3), P(1,0,5), P(1,0,7), P(1,1,1), P(1,1,3), P(1,1,5), P(1,1,7),
/*88*/	P(0,0,1), P(0,0,3), P(0,0,5), P(0,0,7), P(0,1,1), P(0,1,3), P(0,1,5), P(0,1,7),
};

#define D(n) (row_D+n-1)
#define C(n) (row_C+n-1)

const struct signal PX[] = {
	{"P0",	D(52), NULL, POS},
	{"P1",	D(53), NULL, POS},
	{"P2",	D(50), NULL, POS},
	{"P3",	C(70), NULL, POS},
	{"P4",	D(51), NULL, POS},
	{"P5",	D(54), NULL, POS},

	{"I1",	D(57), NULL, POS},
	{"I2",	D(55), NULL, POS},
	{"I3",	C(50), NULL, POS},
	{"I4",	C(51), NULL, POS},
	{"I5",	C(52), NULL, POS},

	{"K1",	C(56), NULL, POS},
	{"K2",	C(87), NULL, POS},

	{"WW",	C(58), NULL, POS},
	{"WM",	D(56), NULL, POS},
	{"WP",	D(68), NULL, POS},
	{"WA",	D(69), NULL, POS},
	{"WZ",	C(71), NULL, POS},
	{"WX",	C(72), NULL, POS},
	{"WE",	C(73), NULL, POS},
	{"WR",	C(88), NULL, POS},
	{"W&",	D(87), NULL, POS},

	{"S1",	D(88), NULL, POS},
	{"OK*",	C(57), NULL, POS},
	{"ZW1",	D(91), NULL, NEG},
	{"ZGI",	C(69), NULL, NEG},
	{"H*N",	C(94), NULL, NEG},

	{"DIN",	C(55), NULL, NEG},
	{"DMCL",C(52), NULL, NEG},
	{"DR",	C(74), NULL, NEG},
	{"DW",	C(75), NULL, NEG},
	{"DF",	C(76), NULL, NEG},
	{"REN",	C(91), NULL, NEG},
	{"ROK",	C(92), NULL, NEG},
	{"RPE",	C(93), NULL, NEG},
	{NULL}
};

const struct pinloc *LG[] = { D(23), D(24), D(22), NULL };
const struct pinloc *LK[] = { C(27), C(21), C(24), C(25), NULL };
const struct signal PM[] = {
	{"LG",		NULL, LG, POS},
	{"LK",		NULL, LK, POS},

	{"WLS",		D(21), NULL, POS},
	{"CYCLE",	C(39), NULL, POS},
	{"WAIT",	C(40), NULL, POS},
	{"START",	C(41), NULL, POS},
	{"PRZERW",	C(42), NULL, POS},
	{"LOAD",	C(43), NULL, POS},
	{"STORE",	C(44), NULL, POS},
	{"FETCH",	C(45), NULL, POS},
	{"BIN",		C(46), NULL, POS},
	{"PR",		D(44), NULL, POS},
	{"WB",		D(45), NULL, POS},
	{"WP",		D(46), NULL, POS},
	{"WM",		D(47), NULL, POS},
	{"PB",		D(48), NULL, POS},
	{NULL}
};

const struct pinloc *NPA[] = { D(8), D(9), D(7), D(10), NULL };
const struct pinloc *NPB[] = { D(25), D(26), D(28), D(27), NULL };
const struct pinloc *RS[] = { C(5), C(9), C(6), C(8), C(7), C(2), C(4), C(3), D(8), C(10), NULL };
const struct signal PP[] = {
	{ "NPA", NULL, NPA, POS },
	{ "NPB", NULL, NPB, POS },
	{ "RS", NULL, RS, POS },
	{NULL}
};

const struct pinloc *DNB[] = { D(40), D(41), D(42), D(43), NULL };
const struct pinloc *R[] = { C(47), C(46), C(48), NULL };
const struct pinloc *KI[] = { D(45), D(44), NULL };
const struct signal PR[] = {
	{ "DNB", NULL, DNB, POS },
	{ "BLR", C(41), NULL, NEG },
	{ "W>R", C(43), NULL, NEG },
	{ "R", NULL, R, POS },
	{ "KI", NULL, KI, POS },
	{ "DQB", D(46), NULL, NEG },
	{ "DPN", D(48), NULL, NEG },
	{NULL}
};

const struct signal PA[] = {
	{ "W>AC", C(50), NULL, POS },
	{ "W>IC", C(51), NULL, POS },
	{ "W>DT", D(52), NULL, NEG },
	{ "W>AR", C(53), NULL, POS },
	{ "AR>AD", D(55), NULL, NEG },

	{ "ICP1", C(52), NULL, POS },
	{ "SAB", C(54), NULL, NEG },
	{ "SCB", C(55), NULL, NEG },
	{ "BWB", C(56), NULL, NEG },
	{ "SD", C(57), NULL, NEG },
	{ "$-1", D(51), NULL, POS },
	{ "CARRY", D(53), NULL, NEG },
	{ "AS2", D(54), NULL, POS },
	{NULL}
};

const struct pinloc *FD[] = { C(21), C(22), C(23), C(24), C(39), C(40), C(41), C(42), NULL };
const struct pinloc *FIC1[] = { C(44), C(45), C(46), C(47), NULL };
const struct signal FPAR[] = {
	{ "D", NULL, FD, POS },
	{ "FIC1", NULL, FIC1, POS },
	{ "SGN", D(21), NULL, POS },
	{ "WT", C(25), NULL, POS },
	{ "WDT", C(26), NULL, POS },
	{ "D-1", C(27), NULL, POS },
	{ "D-2", C(28), NULL, POS },
	{ "CK", C(29), NULL, POS },
	{ "PM", C(43), NULL, POS },
	{ "WC", C(48), NULL, POS },
	{NULL}
};

const struct pinloc *FIC2[] = { C(51), C(50), NULL };
const struct signal FPAL[] = {
	{ "G", C(49), NULL, POS },
	{ "FIC2", NULL, FIC2, POS },
	{ "DI", C(52), NULL, POS },
	{ "IDI", C(53), NULL, POS },
	{ "M-1", C(54), NULL, POS },
	{ "D&", C(55), NULL, POS },
	{ "END", C(56), NULL, POS },
	{ "WS", C(57), NULL, POS },
	{ "CI", C(58), NULL, POS },
	{ "FWZ", D(57), NULL, POS },
	{ "T-1", D(58), NULL, POS },
	{NULL}
};

const struct pinloc *T1[] = { D(7), D(6), C(2), D(4), C(4), D(7), C(8), C(9), C(21), C(10), C(22), C(20), C(23), C(25), C(26), C(24), C(27), C(41), C(29), C(39), C(42), C(44), C(28), C(40), C(47), C(48), NULL };
const struct signal FPMR[] = {
	{ "T1", NULL, T1, POS},
	{ "TAB", C(1), NULL, NEG },
	{ "TAA", D(1), NULL, NEG },
	{ "CLKTA", D(2), NULL, NEG },
	{ "M0", C(3), NULL, POS },
	{ "FP0", D(3), NULL, POS },
	{ "CLKM", C(5), NULL, NEG },
	{ "FAB", D(5), NULL, POS },
	{ "FC0", D(6), NULL, NEG },
	{ "C1", D(8), NULL, POS },
	{ "MA", D(9), NULL, NEG },
	{ "M15", D(10), NULL, POS },
	{ "M14", D(20), NULL, POS },
	{ "P*16", D(21), NULL, NEG },
	{ "CP", D(22), NULL, POS },
	{ "FRB", D(23), NULL, POS },
	{ "FRA1", D(24), NULL, POS },
	{ "M*32", C(33), NULL, POS },
	{ "P*32", D(37), NULL, NEG },
	{ "FAA", C(43), NULL, NEG },
	{ "CLKTB", C(45), NULL, NEG },
	{ "TRB", C(46), NULL, NEG },
	{NULL}
};

const struct pinloc *T2[] = { C(49), C(50), C(58), C(53), C(52), C(54), C(68), C(69), C(70), C(72), C(89), C(88), C(86), C(71), NULL };
const struct signal FPML[] = {
	{ "T2", NULL, T2, POS},
	{ "0>M", C(55), NULL, NEG },
	{ "F9KA", C(56), NULL, POS },
	{ "LKB", C(57), NULL, POS },
	{ "T>C", C(73), NULL, POS },
	{ "MB", C(74), NULL, NEG },
	{ "M*40", C(75), NULL, POS },
	{ "M39", C(76), NULL, POS },
	{ "M38", C(87), NULL, POS },
	{ "CLKTC", C(90), NULL, POS },
	{ "P*40", C(92), NULL, NEG },
	{NULL}
};

const struct signal FPS[] = {
	{ "F1", C(73), NULL, POS },
	{ "F2", C(74), NULL, POS },
	{ "F3", C(72), NULL, POS },
	{ "F4", C(75), NULL, POS },
	{ "F5", C(94), NULL, POS },
	{ "F6", C(76), NULL, POS },
	{ "F7", C(93), NULL, POS },
	{ "F8", C(92), NULL, POS },
	{ "F10", C(88), NULL, POS },
	{ "F11", C(69), NULL, POS },
	{ "F12", C(70), NULL, POS },
	{ "F13", C(91), NULL, POS },

	{ "S1", C(71), NULL, POS },
	{ "LPB", C(89), NULL, POS },
	{ "LPA", C(90), NULL, POS },
	{NULL}
};

// vim: tabstop=4 shiftwidth=4 autoindent
