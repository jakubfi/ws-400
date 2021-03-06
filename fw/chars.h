#ifndef __CHARS_H_
#define __CHARS_H_

#include <inttypes.h>

#define CH_CURSOR 1
#define CH_HDOT 2
#define CH_VDOT 3
#define CH_CONT 4

extern __flash const uint8_t cursor[];
extern __flash const uint8_t hdot[];
extern __flash const uint8_t vdot[];
extern __flash const uint8_t cont[];

#endif

// vim: tabstop=4 shiftwidth=4 autoindent
