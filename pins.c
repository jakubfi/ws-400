#include <inttypes.h>
#include <stddef.h>
#include "pins.h"

// -----------------------------------------------------------------------
// ---- P-X (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const __flash struct signal PX[] = {
	{"P0",		Dl(52),	NULL,	BIN|POS},
	{"P1",		Dl(53),	NULL,	BIN|POS},
	{"P2",		Dl(50),	NULL,	BIN|POS},
	{"P3",		Cl(70),	NULL,	BIN|POS},
	{"P4",		Dl(51),	NULL,	BIN|POS},
	{"P5",		Dl(54),	NULL,	BIN|POS},
	{"I1",		Dl(57),	NULL,	BIN|POS},
	{"I2",		Dl(55),	NULL,	BIN|POS},
	{"I3",		Cl(50),	NULL,	BIN|POS},
	{"I4",		Cl(51),	NULL,	BIN|POS},
	{"I5",		Cl(52),	NULL,	BIN|POS},
	{"K1",		Cl(56),	NULL,	BIN|POS},
	{"K2",		Cl(87),	NULL,	BIN|POS},
	{"WW",		Cl(58),	NULL,	BIN|POS},
	{"WM",		Dl(56),	NULL,	BIN|POS},
	{"WP",		Dl(68),	NULL,	BIN|POS},
	{"WA",		Dl(69),	NULL,	BIN|POS},
	{"WZ",		Cl(71),	NULL,	BIN|POS},
	{"WX",		Cl(72),	NULL,	BIN|POS},
	{"WE",		Cl(73),	NULL,	BIN|POS},
	{"WR",		Cl(88),	NULL,	BIN|POS},
	{"W&",		Dl(87),	NULL,	BIN|POS},
	{"S1",		Dl(88),	NULL,	BIN|POS},
	{"ZGI",		Cl(69),	NULL,	BIN|NEG},
	{"ZW1",		Dl(91),	NULL,	BIN|NEG},
	{"DIN",		Cl(55),	NULL,	BIN|NEG},
//	{"DMCL",	Cl(53),	NULL,	BIN|NEG}, // not really, C53 is just a passthrough to A53
	{"DR",		Cl(74),	NULL,	BIN|NEG},
	{"DW",		Cl(75),	NULL,	BIN|NEG},
	{"DF",		Cl(76),	NULL,	BIN|NEG},
	{"REN",		Cl(91),	NULL,	BIN|NEG},
	{"ROK",		Cl(92),	NULL,	BIN|NEG},
	{"RPE",		Cl(93),	NULL,	BIN|NEG},
	{"OK*",		Cl(57),	NULL,	BIN|POS},
	{"H*N",		Cl(94),	NULL,	BIN|NEG},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- P-M (right) ------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t LG[] = { Dr(22), Dr(24), Dr(23), -1 };
const int8_t LK[] = { Cr(27), Cr(21), Cr(24), Cr(25), -1 };
const __flash struct signal PM[] = {
	{"LG",		0,		LG,		DEC|POS},
	{"LK",		0,		LK,		DEC|POS},
	{"CYCLE",	Cr(39),	NULL,	BIN|POS},
	{"WAIT",	Cr(40),	NULL,	BIN|POS},
	{"START",	Cr(41),	NULL,	BIN|POS},
	{"PRZERW",	Cr(42),	NULL,	BIN|POS},
	{"LOAD",	Cr(43),	NULL,	BIN|POS},
	{"STORE",	Cr(44),	NULL,	BIN|POS},
	{"FETCH",	Cr(45),	NULL,	BIN|POS},
	{"BIN",		Cr(46),	NULL,	BIN|POS},
	{"PR",		Dr(44),	NULL,	BIN|POS},
	{"WB",		Dr(45),	NULL,	BIN|POS},
	{"WP",		Dr(46),	NULL,	BIN|POS},
	{"WM",		Dr(47),	NULL,	BIN|POS},
	{"PB",		Dr(48),	NULL,	BIN|POS},
	{"WLS",		Dr(21),	NULL,	BIN|POS},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- P-P (right) ------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t NPA[] = {
	Dr(8), Dr(9), Dr(7), Dr(10), -1
};
const int8_t NPB[] = {
	Dr(25), Dr(26), Dr(28), Dr(27), -1
};
const int8_t RS[] = {
	Cr(5), Cr(9), Cr(6), Cr(8), Cr(7), Cr(2), Cr(4), Cr(3), Dr(8), Cr(10), -1
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
	Dr(40), Dr(41), Dr(42), Dr(43), -1
};
const int8_t R[] = {
	Cr(47), Cr(46), Cr(48), -1
};
const int8_t KI[] = {
	Dr(45), Dr(44), -1
};
const __flash struct signal PR[] = {
	{"DNB",		0,		DNB,	DEC|NEG},
	{"BLR",		Cr(41),	NULL,	BIN|NEG},
	{"W>R",		Cr(43),	NULL,	BIN|NEG},
	{"R",		0,		R,		DEC|NEG},
	{"KI",		0,		KI,		DEC|NEG},
	{"DQB",		Dr(46),	NULL,	BIN|NEG},
	{"DPN",		Dr(48),	NULL,	BIN|NEG},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- P-A (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t MW[] = {
	Cl(71), Cl(70), Cl(72), -1
};
const int8_t A[] = {
	Cl(88), Cl(89), -1
};
const int8_t SH[] = {
	Cl(57), Cl(55), Dl(69), Cl(54), -1
};
const int8_t SL[] = {
	Cl(57), Cl(94), Dl(69), Cl(91), -1
};
const __flash struct signal PA[] = {
	{"W>AC",	Cl(50),	NULL,	BIN|POS},
	{"W>IC",	Cl(51),	NULL,	BIN|POS},
	{"W>DT",	Dl(52),	NULL,	BIN|NEG},
	{"W>AR",	Cl(53),	NULL,	BIN|POS},
	{"AR>AD",	Dl(55),	NULL,	BIN|NEG},
	{"IC>AD",	Dl(50),	NULL,	BIN|NEG},
	{"ARP1",	Cl(68),	NULL,	BIN|POS},	// AR + 1
	{"ARM4",	Cl(74),	NULL,	BIN|NEG},	// AR - 4
	{"ICP1",	Cl(52),	NULL,	BIN|POS},	// IC + 1

	{"MW",		0,		MW,		DEC|NEG},	// W bus input select
	{"BWA",		Cl(73),	NULL,	BIN|NEG},	// W bus low byte select
	{"BWB",		Cl(56),	NULL,	BIN|NEG},	// W bus high byte select

	{"$-1",		Dl(51),	NULL,	BIN|POS},	// ALU something
	{"CARRY",	Dl(53),	NULL,	BIN|NEG},	// ALU cary out
	{"SARYT",	Cl(69),	NULL,	BIN|POS},	// ALU M
	{"P16",		Cl(58),	NULL,	BIN|NEG},	// ALU carry into 8-11

	{"SxH",		0,		SH,		DEC|NEG},	// ALU high S input
	{"SxL",		0,		SL,		DEC|NEG},	// ALU low S input

	{"A",		0,		A,		DEC|NEG},	// A bus input select
	{"BAA",		Cl(92),	NULL,	BIN|NEG},	// A bus select 10-15
	{"BAB",		Cl(90),	NULL,	BIN|NEG},	// A bus select 8-9
	{"BAC",		Cl(93),	NULL,	BIN|NEG},	// A bus select 0-7

	{"AS2",		Dl(54),	NULL,	BIN|POS},	// AT select S1

	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPS (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t LP[] = {
	Cl(89), Cl(90), -1
};
const __flash struct signal FPS[] = {
	{"F1",		Cl(73),	NULL,	BIN|POS},
	{"F2",		Cl(74),	NULL,	BIN|POS},
	{"F3",		Cl(72),	NULL,	BIN|POS},
	{"F4",		Cl(75),	NULL,	BIN|POS},
	{"F5",		Cl(94),	NULL,	BIN|POS},
	{"F6",		Cl(76),	NULL,	BIN|POS},
	{"F7",		Cl(93),	NULL,	BIN|POS},
	{"F8",		Cl(92),	NULL,	BIN|POS},
	{"F10",		Cl(88),	NULL,	BIN|POS},
	{"F11",		Cl(69),	NULL,	BIN|POS},
	{"F12",		Cl(70),	NULL,	BIN|POS},
	{"F13",		Cl(91),	NULL,	BIN|POS},
	{"S1",		Cl(71),	NULL,	BIN|POS},
	{"LP",		0,		LP,		DEC|POS},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPM (right) ------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t FD[] = {
	Cr(21), Cr(22), Cr(23), Cr(24), Cr(39), Cr(40), Cr(41), Cr(42), -1
};
const int8_t FIC1[] = {
	Cr(44), Cr(45), Cr(47), Cr(46), -1
};
const __flash struct signal FPMR[] = {
	{"D",		0,		FD,		DEC|POS},
	{"FIC1",	0,		FIC1,	DEC|POS},
	{"SGN",		Dr(21),	NULL,	BIN|POS},
	{"WT",		Cr(25),	NULL,	BIN|POS},
	{"WDT",		Cr(26),	NULL,	BIN|POS},
	{"D-1",		Cr(27),	NULL,	BIN|POS},
	{"D-2",		Cr(28),	NULL,	BIN|POS},
	{"CK",		Cr(29),	NULL,	BIN|POS},
	{"PM",		Cr(43),	NULL,	BIN|POS},
	{"WC",		Cr(48),	NULL,	BIN|POS},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPM (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t FIC2[] = {
	Cl(51), Cl(50), -1
};
const __flash struct signal FPML[] = {
	{"G",		Cl(49),	NULL,	BIN|POS},
	{"FIC2",	0,		FIC2,	DEC|POS},
	{"DI",		Cl(52),	NULL,	BIN|POS},
	{"IDI",		Cl(53),	NULL,	BIN|POS},
	{"M-1",		Cl(54),	NULL,	BIN|POS},
	{"D&",		Cl(55),	NULL,	BIN|POS},
	{"END",		Cl(56),	NULL,	BIN|POS},
	{"WS",		Cl(57),	NULL,	BIN|POS},
	{"CI",		Cl(58),	NULL,	BIN|POS},
	{"FWZ",		Dl(57),	NULL,	BIN|POS},
	{"T-1",		Dl(58),	NULL,	BIN|POS},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPA (right) ------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t T1[] = {
	Dr(7), Dr(6), Cr(2), Dr(4), Cr(4), Dr(7), Cr(8), Cr(9), Cr(21), Cr(10), Cr(22), Cr(20), Cr(23), Cr(25), Cr(26), Cr(24), Cr(27), Cr(41), Cr(29), Cr(39), Cr(42), Cr(44), Cr(28), Cr(40), Cr(47), Cr(48), -1
};
const __flash struct signal FPAR[] = {
	{"T1",		14,		T1,		DEC|POS},
	{"TAB",		Cr(1),	NULL,	BIN|NEG},
	{"TAA",		Dr(1),	NULL,	BIN|NEG},
	{"CLKTA",	Dr(2),	NULL,	BIN|NEG},
	{"M0",		Cr(3),	NULL,	BIN|POS},
	{"FP0",		Dr(3),	NULL,	BIN|POS},
	{"CLKM",	Cr(5),	NULL,	BIN|NEG},
	{"FAB",		Dr(5),	NULL,	BIN|POS},
	{"FC0",		Dr(6),	NULL,	BIN|NEG},
	{"C1",		Dr(8),	NULL,	BIN|POS},
	{"MA",		Dr(9),	NULL,	BIN|NEG},
	{"M15",		Dr(10),	NULL,	BIN|POS},
	{"M14",		Dr(20),	NULL,	BIN|POS},
	{"P*16",	Dr(21),	NULL,	BIN|NEG},
	{"CP",		Dr(22),	NULL,	BIN|POS},
	{"FRB",		Dr(23),	NULL,	BIN|POS},
	{"FRA1",	Dr(24),	NULL,	BIN|POS},
	{"M*32",	Cr(33),	NULL,	BIN|POS},
	{"P*32",	Dr(37),	NULL,	BIN|NEG},
	{"FAA",		Cr(43),	NULL,	BIN|NEG},
	{"CLKTB",	Cr(45),	NULL,	BIN|NEG},
	{"TRB",		Cr(46),	NULL,	BIN|NEG},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPA (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t T2[] = {
	Cl(49), Cl(50), Cl(58), Cl(53), Cl(52), Cl(54), Cl(68), Cl(69), Cl(70), Cl(72), Cl(89), Cl(88), Cl(86), Cl(71), -1
};
const __flash struct signal FPAL[] = {
	{"T2",		0,		T2,		DEC|POS},
	{"0>M",		Cl(55),	NULL,	BIN|NEG},
	{"F9KA",	Cl(56),	NULL,	BIN|POS},
	{"LKB",		Cl(57),	NULL,	BIN|POS},
	{"T>C",		Cl(73),	NULL,	BIN|POS},
	{"MB",		Cl(74),	NULL,	BIN|NEG},
	{"M*40",	Cl(75),	NULL,	BIN|POS},
	{"M39",		Cl(76),	NULL,	BIN|POS},
	{"M38",		Cl(87),	NULL,	BIN|POS},
	{"CLKTC",	Cl(90),	NULL,	BIN|POS},
	{"P*40",	Cl(92),	NULL,	BIN|NEG},
	{NULL}
};

// vim: tabstop=4 shiftwidth=4 autoindent
