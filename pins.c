#include <inttypes.h>
#include <stddef.h>
#include "pins.h"

// -----------------------------------------------------------------------
// ---- P-X (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const __flash struct signal PX[] = {
	{"P0",		{D(52)},	BIN|POS},
	{"P1",		{D(53)},	BIN|POS},
	{"P2",		{D(50)},	BIN|POS},
	{"P3",		{C(70)},	BIN|POS},
	{"P4",		{D(51)},	BIN|POS},
	{"P5",		{D(54)},	BIN|POS},
	{"I1",		{D(57)},	BIN|POS},
	{"I2",		{D(55)},	BIN|POS},
	{"I3",		{C(50)},	BIN|POS},
	{"I4",		{C(51)},	BIN|POS},
	{"I5",		{C(52)},	BIN|POS},
	{"K1",		{C(56)},	BIN|POS},
	{"K2",		{C(87)},	BIN|POS},
	{"WW",		{C(58)},	BIN|POS},
	{"WM",		{D(56)},	BIN|POS},
	{"WP",		{D(68)},	BIN|POS},
	{"WA",		{D(69)},	BIN|POS},
	{"WZ",		{C(71)},	BIN|POS},
	{"WX",		{C(72)},	BIN|POS},
	{"WE",		{C(73)},	BIN|POS},
	{"WR",		{C(88)},	BIN|POS},
	{"W&",		{D(87)},	BIN|POS},
	{"S1",		{D(88)},	BIN|POS},
	{"ZGI",		{C(69)},	BIN|NEG},
	{"ZW1",		{D(91)},	BIN|NEG},
	{"DIN",		{C(55)},	BIN|NEG},
//	{"DMCL",	{C(53)},	BIN|NEG}, // not really, C53 is just a passthrough to A53
	{"DR",		{C(74)},	BIN|NEG},
	{"DW",		{C(75)},	BIN|NEG},
	{"DF",		{C(76)},	BIN|NEG},
	{"REN",		{C(91)},	BIN|NEG},
	{"ROK",		{C(92)},	BIN|NEG},
	{"RPE",		{C(93)},	BIN|NEG},
	{"OK*",		{C(57)},	BIN|POS},
	{"H*N",		{C(94)},	BIN|NEG},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- P-M (right) ------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t LG[] = {
	D(22), D(24), D(23), 0
};
const int8_t LK[] = {
	C(27), C(21), C(24), C(25), 0
};
const __flash struct signal PM[] = {
	{"LG",		.d.reg=LG,	DEC|POS},
	{"LK",		.d.reg=LK,	DEC|POS},
	{"CYCLE",	{C(39)},	BIN|POS},
	{"WAIT",	{C(40)},	BIN|POS},
	{"START",	{C(41)},	BIN|POS},
	{"PRZERW",	{C(42)},	BIN|POS},
	{"LOAD",	{C(43)},	BIN|POS},
	{"STORE",	{C(44)},	BIN|POS},
	{"FETCH",	{C(45)},	BIN|POS},
	{"BIN",		{C(46)},	BIN|POS},
	{"PR",		{D(44)},	BIN|POS},
	{"WB",		{D(45)},	BIN|POS},
	{"WP",		{D(46)},	BIN|POS},
	{"WM",		{D(47)},	BIN|POS},
	{"PB",		{D(48)},	BIN|POS},
	{"WLS",		{D(21)},	BIN|POS},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- P-P (right) ------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t NPA[] = {
	D(8), D(9), D(7), D(10), 0
};
const int8_t NPB[] = {
	D(25), D(26), D(28), D(27), 0
};
const int8_t RS[] = {
	C(5), C(9), C(6), C(8), C(7), C(2), C(4), C(3), D(8), C(10), 0
};
const __flash struct signal PP[] = {
	{"NPA",		.d.reg=NPA,	DEC|POS},
	{"NPB",		.d.reg=NPB,	DEC|POS},
	{"RS",		.d.reg=RS,	DEC|POS},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- P-R (right) ------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t DNB[] = {
	D(40), D(41), D(42), D(43), 0
};
const int8_t R[] = {
	C(47), C(46), C(48), 0
};
const int8_t KI[] = {
	D(45), D(44), 0
};
const __flash struct signal PR[] = {
	{"DNB",		.d.reg=DNB,	DEC|NEG},
	{"BLR",		{C(41)},	BIN|NEG},
	{"W>R",		{C(43)},	BIN|NEG},
	{"R",		.d.reg=R,	DEC|NEG},
	{"KI",		.d.reg=KI,	DEC|NEG},
	{"DQB",		{D(46)},	BIN|NEG},
	{"DPN",		{D(48)},	BIN|NEG},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- P-A (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t MW[] = {
	C(71), C(70), C(72), 0
};
const int8_t A[] = {
	C(88), C(89), 0
};
const int8_t SH[] = {
	C(57), C(55), D(69), C(54), 0
};
const int8_t SL[] = {
	C(57), C(94), D(69), C(91), 0
};
const __flash struct signal PA[] = {
	{"W>AC",	{C(50)},	BIN|POS},
	{"W>IC",	{C(51)},	BIN|POS},
	{"W>DT",	{D(52)},	BIN|NEG},
	{"W>AR",	{C(53)},	BIN|POS},
	{"AR>AD",	{D(55)},	BIN|NEG},
	{"IC>AD",	{D(50)},	BIN|NEG},
	{"ARP1",	{C(68)},	BIN|POS},	// AR + 1
	{"ARM4",	{C(74)},	BIN|NEG},	// AR - 4
	{"ICP1",	{C(52)},	BIN|POS},	// IC + 1

	{"MW",		.d.reg=MW,	DEC|NEG},	// W bus input select
	{"BWA",		{C(73)},	BIN|NEG},	// W bus low byte select
	{"BWB",		{C(56)},	BIN|NEG},	// W bus high byte select

	{"$-1",		{D(51)},	BIN|POS},	// ALU something
	{"CARRY",	{D(53)},	BIN|NEG},	// ALU cary out
	{"SARYT",	{C(69)},	BIN|POS},	// ALU M
	{"P16",		{C(58)},	BIN|NEG},	// ALU carry into 8-11

	{"SxH",		.d.reg=SH,	DEC|NEG},	// ALU high S input
	{"SxL",		.d.reg=SL,	DEC|NEG},	// ALU low S input

	{"A",		.d.reg=A,	DEC|NEG},	// A bus input select
	{"BAA",		{C(92)},	BIN|NEG},	// A bus select 10-15
	{"BAB",		{C(90)},	BIN|NEG},	// A bus select 8-9
	{"BAC",		{C(93)},	BIN|NEG},	// A bus select 0-7

	{"AS2",		{D(54)},	BIN|POS},	// AT select S1

	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPS (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t LP[] = {
	C(89), C(90), 0
};
const __flash struct signal FPS[] = {
	{"F1",		{C(73)},	BIN|POS},
	{"F2",		{C(74)},	BIN|POS},
	{"F3",		{C(72)},	BIN|POS},
	{"F4",		{C(75)},	BIN|POS},
	{"F5",		{C(94)},	BIN|POS},
	{"F6",		{C(76)},	BIN|POS},
	{"F7",		{C(93)},	BIN|POS},
	{"F8",		{C(92)},	BIN|POS},
	{"F10",		{C(88)},	BIN|POS},
	{"F11",		{C(69)},	BIN|POS},
	{"F12",		{C(70)},	BIN|POS},
	{"F13",		{C(91)},	BIN|POS},
	{"S1",		{C(71)},	BIN|POS},
	{"LP",		.d.reg=LP,	DEC|POS},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPM (right) ------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t FD[] = {
	C(21), C(22), C(23), C(24), C(39), C(40), C(41), C(42), 0
};
const int8_t FIC1[] = {
	C(44), C(45), C(47), C(46), 0
};
const __flash struct signal FPMR[] = {
	{"D",		.d.reg=FD,	DEC|POS},
	{"FIC1",	.d.reg=FIC1,DEC|POS},
	{"SGN",		{D(21)},	BIN|POS},
	{"WT",		{C(25)},	BIN|POS},
	{"WDT",		{C(26)},	BIN|POS},
	{"D-1",		{C(27)},	BIN|POS},
	{"D-2",		{C(28)},	BIN|POS},
	{"CK",		{C(29)},	BIN|POS},
	{"PM",		{C(43)},	BIN|POS},
	{"WC",		{C(48)},	BIN|POS},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPM (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t FIC2[] = {
	C(51), C(50), 0
};
const __flash struct signal FPML[] = {
	{"G",		{C(49)},	BIN|POS},
	{"FIC2",	.d.reg=FIC2,DEC|POS|(4<<SIG_SHIFT_POS)},
	{"DI",		{C(52)},	BIN|POS},
	{"IDI",		{C(53)},	BIN|POS},
	{"M-1",		{C(54)},	BIN|POS},
	{"D&",		{C(55)},	BIN|POS},
	{"END",		{C(56)},	BIN|POS},
	{"WS",		{C(57)},	BIN|POS},
	{"CI",		{C(58)},	BIN|POS},
	{"FWZ",		{D(57)},	BIN|POS},
	{"T-1",		{D(58)},	BIN|POS},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPA (right) ------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t T1[] = {
	D(7), D(6), C(2), D(4), C(4), D(7), C(8), C(9), C(21), C(10), C(22), C(20), C(23), C(25), C(26), C(24), C(27), C(41), C(29), C(39), C(42), C(44), C(28), C(40), C(47), C(48), 0
};
const __flash struct signal FPAR[] = {
	{"T1",		.d.reg=T1,	DEC|POS|(14<<SIG_SHIFT_POS)},
	{"TAB",		{C(1)},		BIN|NEG},
	{"TAA",		{D(1)},		BIN|NEG},
	{"CLKTA",	{D(2)},		BIN|NEG},
	{"M0",		{C(3)},		BIN|POS},
	{"FP0",		{D(3)},		BIN|POS},
	{"CLKM",	{C(5)},		BIN|NEG},
	{"FAB",		{D(5)},		BIN|POS},
	{"FC0",		{D(6)},		BIN|NEG},
	{"C1",		{D(8)},		BIN|POS},
	{"MA",		{D(9)},		BIN|NEG},
	{"M15",		{D(10)},	BIN|POS},
	{"M14",		{D(20)},	BIN|POS},
	{"P*16",	{D(21)},	BIN|NEG},
	{"CP",		{D(22)},	BIN|POS},
	{"FRB",		{D(23)},	BIN|POS},
	{"FRA1",	{D(24)},	BIN|POS},
	{"M*32",	{C(33)},	BIN|POS},
	{"P*32",	{D(37)},	BIN|NEG},
	{"FAA",		{C(43)},	BIN|NEG},
	{"CLKTB",	{C(45)},	BIN|NEG},
	{"TRB",		{C(46)},	BIN|NEG},
	{NULL}
};

// -----------------------------------------------------------------------
// ---- FPA (left) -------------------------------------------------------
// -----------------------------------------------------------------------
const int8_t T2[] = {
	C(49), C(50), C(58), C(53), C(52), C(54), C(68), C(69), C(70), C(72), C(89), C(88), C(86), C(71), 0
};
const __flash struct signal FPAL[] = {
	{"T2",		.d.reg=T2,	DEC|POS},
	{"0>M",		{C(55)},	BIN|NEG},
	{"F9KA",	{C(56)},	BIN|POS},
	{"LKB",		{C(57)},	BIN|POS},
	{"T>C",		{C(73)},	BIN|POS},
	{"MB",		{C(74)},	BIN|NEG},
	{"M*40",	{C(75)},	BIN|POS},
	{"M39",		{C(76)},	BIN|POS},
	{"M38",		{C(87)},	BIN|POS},
	{"CLKTC",	{C(90)},	BIN|POS},
	{"P*40",	{C(92)},	BIN|NEG},
	{NULL}
};

// vim: tabstop=4 shiftwidth=4 autoindent
