#include <inttypes.h>
#include <stddef.h>
#include "pins.h"

// -----------------------------------------------------------------------
// ---- P-X (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const __flash struct signal PX[] = {
	{"P0",		D(52),	NULL,	BIN|POS},
	{"P1",		D(53),	NULL,	BIN|POS},
	{"P2",		D(50),	NULL,	BIN|POS},
	{"P3",		C(70),	NULL,	BIN|POS},
	{"P4",		D(51),	NULL,	BIN|POS},
	{"P5",		D(54),	NULL,	BIN|POS},
	{"I1",		D(57),	NULL,	BIN|POS},
	{"I2",		D(55),	NULL,	BIN|POS},
	{"I3",		C(50),	NULL,	BIN|POS},
	{"I4",		C(51),	NULL,	BIN|POS},
	{"I5",		C(52),	NULL,	BIN|POS},
	{"K1",		C(56),	NULL,	BIN|POS},
	{"K2",		C(87),	NULL,	BIN|POS},
	{"WW",		C(58),	NULL,	BIN|POS},
	{"WM",		D(56),	NULL,	BIN|POS},
	{"WP",		D(68),	NULL,	BIN|POS},
	{"WA",		D(69),	NULL,	BIN|POS},
	{"WZ",		C(71),	NULL,	BIN|POS},
	{"WX",		C(72),	NULL,	BIN|POS},
	{"WE",		C(73),	NULL,	BIN|POS},
	{"WR",		C(88),	NULL,	BIN|POS},
	{"W&",		D(87),	NULL,	BIN|POS},
	{"S1",		D(88),	NULL,	BIN|POS},
	{"ZGI",		C(69),	NULL,	BIN|NEG},
	{"ZW1",		D(91),	NULL,	BIN|NEG},
	{"DIN",		C(55),	NULL,	BIN|NEG},
//	{"DMCL",	C(53),	NULL,	BIN|NEG}, // not really, C53 is just a passthrough to A53
	{"DR",		C(74),	NULL,	BIN|NEG},
	{"DW",		C(75),	NULL,	BIN|NEG},
	{"DF",		C(76),	NULL,	BIN|NEG},
	{"REN",		C(91),	NULL,	BIN|NEG},
	{"ROK",		C(92),	NULL,	BIN|NEG},
	{"RPE",		C(93),	NULL,	BIN|NEG},
	{"OK*",		C(57),	NULL,	BIN|POS},
	{"H*N",		C(94),	NULL,	BIN|NEG},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- P-M (right) ------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t LG[] = {
	D(22), D(24), D(23), -1
};
const int8_t LK[] = {
	C(27), C(21), C(24), C(25), -1
};
const __flash struct signal PM[] = {
	{"LG",		0,		LG,		DEC|POS},
	{"LK",		0,		LK,		DEC|POS},
	{"CYCLE",	C(39),	NULL,	BIN|POS},
	{"WAIT",	C(40),	NULL,	BIN|POS},
	{"START",	C(41),	NULL,	BIN|POS},
	{"PRZERW",	C(42),	NULL,	BIN|POS},
	{"LOAD",	C(43),	NULL,	BIN|POS},
	{"STORE",	C(44),	NULL,	BIN|POS},
	{"FETCH",	C(45),	NULL,	BIN|POS},
	{"BIN",		C(46),	NULL,	BIN|POS},
	{"PR",		D(44),	NULL,	BIN|POS},
	{"WB",		D(45),	NULL,	BIN|POS},
	{"WP",		D(46),	NULL,	BIN|POS},
	{"WM",		D(47),	NULL,	BIN|POS},
	{"PB",		D(48),	NULL,	BIN|POS},
	{"WLS",		D(21),	NULL,	BIN|POS},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- P-P (right) ------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t NPA[] = {
	D(8), D(9), D(7), D(10), -1
};
const int8_t NPB[] = {
	D(25), D(26), D(28), D(27), -1
};
const int8_t RS[] = {
	C(5), C(9), C(6), C(8), C(7), C(2), C(4), C(3), D(8), C(10), -1
};
const __flash struct signal PP[] = {
	{"NPA",		0,		NPA,	DEC|POS},
	{"NPB",		0,		NPB,	DEC|POS},
	{"RS",		0,		RS,		DEC|POS},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- P-R (right) ------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t DNB[] = {
	D(40), D(41), D(42), D(43), -1
};
const int8_t R[] = {
	C(47), C(46), C(48), -1
};
const int8_t KI[] = {
	D(45), D(44), -1
};
const __flash struct signal PR[] = {
	{"DNB",		0,		DNB,	DEC|NEG},
	{"BLR",		C(41),	NULL,	BIN|NEG},
	{"W>R",		C(43),	NULL,	BIN|NEG},
	{"R",		0,		R,		DEC|NEG},
	{"KI",		0,		KI,		DEC|NEG},
	{"DQB",		D(46),	NULL,	BIN|NEG},
	{"DPN",		D(48),	NULL,	BIN|NEG},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- P-A (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t MW[] = {
	C(71), C(70), C(72), -1
};
const int8_t A[] = {
	C(88), C(89), -1
};
const int8_t SH[] = {
	C(57), C(55), D(69), C(54), -1
};
const int8_t SL[] = {
	C(57), C(94), D(69), C(91), -1
};
const __flash struct signal PA[] = {
	{"W>AC",	C(50),	NULL,	BIN|POS},
	{"W>IC",	C(51),	NULL,	BIN|POS},
	{"W>DT",	D(52),	NULL,	BIN|NEG},
	{"W>AR",	C(53),	NULL,	BIN|POS},
	{"AR>AD",	D(55),	NULL,	BIN|NEG},
	{"IC>AD",	D(50),	NULL,	BIN|NEG},
	{"ARP1",	C(68),	NULL,	BIN|POS},	// AR + 1
	{"ARM4",	C(74),	NULL,	BIN|NEG},	// AR - 4
	{"ICP1",	C(52),	NULL,	BIN|POS},	// IC + 1

	{"MW",		0,		MW,		DEC|NEG},	// W bus input select
	{"BWA",		C(73),	NULL,	BIN|NEG},	// W bus low byte select
	{"BWB",		C(56),	NULL,	BIN|NEG},	// W bus high byte select

	{"$-1",		D(51),	NULL,	BIN|POS},	// ALU something
	{"CARRY",	D(53),	NULL,	BIN|NEG},	// ALU cary out
	{"SARYT",	C(69),	NULL,	BIN|POS},	// ALU M
	{"P16",		C(58),	NULL,	BIN|NEG},	// ALU carry into 8-11

	{"SxH",		0,		SH,		DEC|NEG},	// ALU high S input
	{"SxL",		0,		SL,		DEC|NEG},	// ALU low S input

	{"A",		0,		A,		DEC|NEG},	// A bus input select
	{"BAA",		C(92),	NULL,	BIN|NEG},	// A bus select 10-15
	{"BAB",		C(90),	NULL,	BIN|NEG},	// A bus select 8-9
	{"BAC",		C(93),	NULL,	BIN|NEG},	// A bus select 0-7

	{"AS2",		D(54),	NULL,	BIN|POS},	// AT select S1

	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPS (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t LP[] = {
	C(89), C(90), -1
};
const __flash struct signal FPS[] = {
	{"F1",		C(73),	NULL,	BIN|POS},
	{"F2",		C(74),	NULL,	BIN|POS},
	{"F3",		C(72),	NULL,	BIN|POS},
	{"F4",		C(75),	NULL,	BIN|POS},
	{"F5",		C(94),	NULL,	BIN|POS},
	{"F6",		C(76),	NULL,	BIN|POS},
	{"F7",		C(93),	NULL,	BIN|POS},
	{"F8",		C(92),	NULL,	BIN|POS},
	{"F10",		C(88),	NULL,	BIN|POS},
	{"F11",		C(69),	NULL,	BIN|POS},
	{"F12",		C(70),	NULL,	BIN|POS},
	{"F13",		C(91),	NULL,	BIN|POS},
	{"S1",		C(71),	NULL,	BIN|POS},
	{"LP",		0,		LP,		DEC|POS},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPM (right) ------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t FD[] = {
	C(21), C(22), C(23), C(24), C(39), C(40), C(41), C(42), -1
};
const int8_t FIC1[] = {
	C(44), C(45), C(47), C(46), -1
};
const __flash struct signal FPMR[] = {
	{"D",		0,		FD,		DEC|POS},
	{"FIC1",	0,		FIC1,	DEC|POS},
	{"SGN",		D(21),	NULL,	BIN|POS},
	{"WT",		C(25),	NULL,	BIN|POS},
	{"WDT",		C(26),	NULL,	BIN|POS},
	{"D-1",		C(27),	NULL,	BIN|POS},
	{"D-2",		C(28),	NULL,	BIN|POS},
	{"CK",		C(29),	NULL,	BIN|POS},
	{"PM",		C(43),	NULL,	BIN|POS},
	{"WC",		C(48),	NULL,	BIN|POS},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPM (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t FIC2[] = {
	C(51), C(50), -1
};
const __flash struct signal FPML[] = {
	{"G",		C(49),	NULL,	BIN|POS},
	{"FIC2",	4,		FIC2,	DEC|POS},
	{"DI",		C(52),	NULL,	BIN|POS},
	{"IDI",		C(53),	NULL,	BIN|POS},
	{"M-1",		C(54),	NULL,	BIN|POS},
	{"D&",		C(55),	NULL,	BIN|POS},
	{"END",		C(56),	NULL,	BIN|POS},
	{"WS",		C(57),	NULL,	BIN|POS},
	{"CI",		C(58),	NULL,	BIN|POS},
	{"FWZ",		D(57),	NULL,	BIN|POS},
	{"T-1",		D(58),	NULL,	BIN|POS},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPA (right) ------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t T1[] = {
	D(7), D(6), C(2), D(4), C(4), D(7), C(8), C(9), C(21), C(10), C(22), C(20), C(23), C(25), C(26), C(24), C(27), C(41), C(29), C(39), C(42), C(44), C(28), C(40), C(47), C(48), -1
};
const __flash struct signal FPAR[] = {
	{"T1",		14,		T1,		DEC|POS},
	{"TAB",		C(1),	NULL,	BIN|NEG},
	{"TAA",		D(1),	NULL,	BIN|NEG},
	{"CLKTA",	D(2),	NULL,	BIN|NEG},
	{"M0",		C(3),	NULL,	BIN|POS},
	{"FP0",		D(3),	NULL,	BIN|POS},
	{"CLKM",	C(5),	NULL,	BIN|NEG},
	{"FAB",		D(5),	NULL,	BIN|POS},
	{"FC0",		D(6),	NULL,	BIN|NEG},
	{"C1",		D(8),	NULL,	BIN|POS},
	{"MA",		D(9),	NULL,	BIN|NEG},
	{"M15",		D(10),	NULL,	BIN|POS},
	{"M14",		D(20),	NULL,	BIN|POS},
	{"P*16",	D(21),	NULL,	BIN|NEG},
	{"CP",		D(22),	NULL,	BIN|POS},
	{"FRB",		D(23),	NULL,	BIN|POS},
	{"FRA1",	D(24),	NULL,	BIN|POS},
	{"M*32",	C(33),	NULL,	BIN|POS},
	{"P*32",	D(37),	NULL,	BIN|NEG},
	{"FAA",		C(43),	NULL,	BIN|NEG},
	{"CLKTB",	C(45),	NULL,	BIN|NEG},
	{"TRB",		C(46),	NULL,	BIN|NEG},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPA (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t T2[] = {
	C(49), C(50), C(58), C(53), C(52), C(54), C(68), C(69), C(70), C(72), C(89), C(88), C(86), C(71), -1
};
const __flash struct signal FPAL[] = {
	{"T2",		0,		T2,		DEC|POS},
	{"0>M",		C(55),	NULL,	BIN|NEG},
	{"F9KA",	C(56),	NULL,	BIN|POS},
	{"LKB",		C(57),	NULL,	BIN|POS},
	{"T>C",		C(73),	NULL,	BIN|POS},
	{"MB",		C(74),	NULL,	BIN|NEG},
	{"M*40",	C(75),	NULL,	BIN|POS},
	{"M39",		C(76),	NULL,	BIN|POS},
	{"M38",		C(87),	NULL,	BIN|POS},
	{"CLKTC",	C(90),	NULL,	BIN|POS},
	{"P*40",	C(92),	NULL,	BIN|NEG},
	{NULL}
};

// vim: tabstop=4 shiftwidth=4 autoindent
