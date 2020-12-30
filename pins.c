#include <inttypes.h>
#include <stddef.h>
#include "pins.h"

const __flash struct signal PX[] = {
	{"P0",	Dl(52), NULL, POS},
	{"P1",	Dl(53), NULL, POS},
	{"P2",	Dl(50), NULL, POS},
	{"P3",	Cl(70), NULL, POS},
	{"P4",	Dl(51), NULL, POS},
	{"P5",	Dl(54), NULL, POS},
	{"I1",	Dl(57), NULL, POS},
	{"I2",	Dl(55), NULL, POS},
	{"I3",	Cl(50), NULL, POS},
	{"I4",	Cl(51), NULL, POS},
	{"I5",	Cl(52), NULL, POS},
	{"K1",	Cl(56), NULL, POS},
	{"K2",	Cl(87), NULL, POS},
	{"WW",	Cl(58), NULL, POS},
	{"WM",	Dl(56), NULL, POS},
	{"WP",	Dl(68), NULL, POS},
	{"WA",	Dl(69), NULL, POS},
	{"WZ",	Cl(71), NULL, POS},
	{"WX",	Cl(72), NULL, POS},
	{"WE",	Cl(73), NULL, POS},
	{"WR",	Cl(88), NULL, POS},
	{"W&",	Dl(87), NULL, POS},

	{"S1",	Dl(88), NULL, POS},

	{"ZGI",	Cl(69), NULL, NEG},
	{"ZW1",	Dl(91), NULL, NEG},

	{"DIN",	Cl(55), NULL, NEG},
//	{"DMCL",Cl(53), NULL, NEG}, // przepuszczone przez pakiet do plateru?
	{"DR",	Cl(74), NULL, NEG},
	{"DW",	Cl(75), NULL, NEG},
	{"DF",	Cl(76), NULL, NEG},

	{"REN",	Cl(91), NULL, NEG},
	{"ROK",	Cl(92), NULL, NEG},
	{"RPE",	Cl(93), NULL, NEG},

	{"OK*",	Cl(57), NULL, POS},
	{"H*N",	Cl(94), NULL, NEG},
	{NULL}
};

const int8_t LG[] = { Dr(22), Dr(24), Dr(23), -1 };
const int8_t LK[] = { Cr(27), Cr(21), Cr(24), Cr(25), -1 };
const __flash struct signal PM[] = {
	{"LG",		0, LG, DEC},
	{"LK",		0, LK, DEC},

	{"CYCLE",	Cr(39), NULL, POS},
	{"WAIT",	Cr(40), NULL, POS},
	{"START",	Cr(41), NULL, POS},
	{"PRZERW",	Cr(42), NULL, POS},
	{"LOAD",	Cr(43), NULL, POS},
	{"STORE",	Cr(44), NULL, POS},
	{"FETCH",	Cr(45), NULL, POS},
	{"BIN",		Cr(46), NULL, POS},
	{"PR",		Dr(44), NULL, POS},
	{"WB",		Dr(45), NULL, POS},
	{"WP",		Dr(46), NULL, POS},
	{"WM",		Dr(47), NULL, POS},
	{"PB",		Dr(48), NULL, POS},
	{"WLS",		Dr(21), NULL, POS},

	{NULL}
};

const int8_t NPA[] = { Dr(8), Dr(9), Dr(7), Dr(10), -1 };
const int8_t NPB[] = { Dr(25), Dr(26), Dr(28), Dr(27), -1 };
const int8_t RS[] = { Cr(5), Cr(9), Cr(6), Cr(8), Cr(7), Cr(2), Cr(4), Cr(3), Dr(8), Cr(10), -1 };
const __flash struct signal PP[] = {
	{ "NPA", 0, NPA, DEC },
	{ "NPB", 0, NPB, DEC },
	{ "RS", 0, RS, DEC },
	{NULL}
};

const int8_t DNB[] = { Dr(40), Dr(41), Dr(42), Dr(43), -1 };
const int8_t R[] = { Cr(47), Cr(46), Cr(48), -1 };
const int8_t KI[] = { Dr(45), Dr(44), -1 };
const __flash struct signal PR[] = {
	{ "DNB", 0, DNB, DEC },
	{ "BLR", Cr(41), NULL, NEG },
	{ "W>R", Cr(43), NULL, NEG },
	{ "R", 0, R, DECNEG },
	{ "KI", 0, KI, DEC },
	{ "DQB", Dr(46), NULL, NEG },
	{ "DPN", Dr(48), NULL, NEG },
	{NULL}
};

const __flash struct signal PA[] = {
	{ "W>AC", Cl(50), NULL, POS },
	{ "W>IC", Cl(51), NULL, POS },
	{ "W>DT", Dl(52), NULL, NEG },
	{ "W>AR", Cl(53), NULL, POS },
	{ "AR>AD", Dl(55), NULL, NEG },

	{ "ICP1", Cl(52), NULL, POS },
	{ "SAB", Cl(54), NULL, NEG },
	{ "SCB", Cl(55), NULL, NEG },
	{ "BWB", Cl(56), NULL, NEG },
	{ "SD", Cl(57), NULL, NEG },
	{ "$-1", Dl(51), NULL, POS },
	{ "CARRY", Dl(53), NULL, NEG },
	{ "AS2", Dl(54), NULL, POS },
	{NULL}
};

const int8_t FD[] = { Cr(21), Cr(22), Cr(23), Cr(24), Cr(39), Cr(40), Cr(41), Cr(42), -1 };
const int8_t FIC1[] = { Cr(44), Cr(45), Cr(47), Cr(46), -1 };
const __flash struct signal FPMR[] = {
	{ "D", 0, FD, DEC },
	{ "FIC1", 0, FIC1, DEC },
	{ "SGN", Dr(21), NULL, POS },
	{ "WT", Cr(25), NULL, POS },
	{ "WDT", Cr(26), NULL, POS },
	{ "D-1", Cr(27), NULL, POS },
	{ "D-2", Cr(28), NULL, POS },
	{ "CK", Cr(29), NULL, POS },
	{ "PM", Cr(43), NULL, POS },
	{ "WC", Cr(48), NULL, POS },
	{NULL}
};

const int8_t FIC2[] = { Cl(51), Cl(50), -1 };
const __flash struct signal FPML[] = {
	{ "G", Cl(49), NULL, POS },
	{ "FIC2", 4, FIC2, DEC },
	{ "DI", Cl(52), NULL, POS },
	{ "IDI", Cl(53), NULL, POS },
	{ "M-1", Cl(54), NULL, POS },
	{ "D&", Cl(55), NULL, POS },
	{ "END", Cl(56), NULL, POS },
	{ "WS", Cl(57), NULL, POS },
	{ "CI", Cl(58), NULL, POS },
	{ "FWZ", Dl(57), NULL, POS },
	{ "T-1", Dl(58), NULL, POS },
	{NULL}
};

const int8_t T1[] = { Dr(7), Dr(6), Cr(2), Dr(4), Cr(4), Dr(7), Cr(8), Cr(9), Cr(21), Cr(10), Cr(22), Cr(20), Cr(23), Cr(25), Cr(26), Cr(24), Cr(27), Cr(41), Cr(29), Cr(39), Cr(42), Cr(44), Cr(28), Cr(40), Cr(47), Cr(48), -1 };
const __flash struct signal FPAR[] = {
	{ "T1", 14, T1, DEC },
	{ "TAB", Cr(1), NULL, NEG },
	{ "TAA", Dr(1), NULL, NEG },
	{ "CLKTA", Dr(2), NULL, NEG },
	{ "M0", Cr(3), NULL, POS },
	{ "FP0", Dr(3), NULL, POS },
	{ "CLKM", Cr(5), NULL, NEG },
	{ "FAB", Dr(5), NULL, POS },
	{ "FC0", Dr(6), NULL, NEG },
	{ "C1", Dr(8), NULL, POS },
	{ "MA", Dr(9), NULL, NEG },
	{ "M15", Dr(10), NULL, POS },
	{ "M14", Dr(20), NULL, POS },
	{ "P*16", Dr(21), NULL, NEG },
	{ "CP", Dr(22), NULL, POS },
	{ "FRB", Dr(23), NULL, POS },
	{ "FRA1", Dr(24), NULL, POS },
	{ "M*32", Cr(33), NULL, POS },
	{ "P*32", Dr(37), NULL, NEG },
	{ "FAA", Cr(43), NULL, NEG },
	{ "CLKTB", Cr(45), NULL, NEG },
	{ "TRB", Cr(46), NULL, NEG },
	{NULL}
};

const int8_t T2[] = { Cl(49), Cl(50), Cl(58), Cl(53), Cl(52), Cl(54), Cl(68), Cl(69), Cl(70), Cl(72), Cl(89), Cl(88), Cl(86), Cl(71), -1 };
const __flash struct signal FPAL[] = {
	{ "T2", 0, T2, DEC },
	{ "0>M", Cl(55), NULL, NEG },
	{ "F9KA", Cl(56), NULL, POS },
	{ "LKB", Cl(57), NULL, POS },
	{ "T>C", Cl(73), NULL, POS },
	{ "MB", Cl(74), NULL, NEG },
	{ "M*40", Cl(75), NULL, POS },
	{ "M39", Cl(76), NULL, POS },
	{ "M38", Cl(87), NULL, POS },
	{ "CLKTC", Cl(90), NULL, POS },
	{ "P*40", Cl(92), NULL, NEG },
	{NULL}
};

const int8_t LP[] = { Cl(89), Cl(90), -1 };
const __flash struct signal FPS[] = {
	{ "F1", Cl(73), NULL, POS },
	{ "F2", Cl(74), NULL, POS },
	{ "F3", Cl(72), NULL, POS },
	{ "F4", Cl(75), NULL, POS },
	{ "F5", Cl(94), NULL, POS },
	{ "F6", Cl(76), NULL, POS },
	{ "F7", Cl(93), NULL, POS },
	{ "F8", Cl(92), NULL, POS },
	{ "F10", Cl(88), NULL, POS },
	{ "F11", Cl(69), NULL, POS },
	{ "F12", Cl(70), NULL, POS },
	{ "F13", Cl(91), NULL, POS },

	{ "S1", Cl(71), NULL, POS },
	{ "LP", 0, LP, DEC },
	{NULL}
};

// vim: tabstop=4 shiftwidth=4 autoindent
