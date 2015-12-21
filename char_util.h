#ifndef CHAR_UTIL_H
#define CHAR_UTIL_H
#include "stdint.h"

static const uint32_t nucpos_arr[128] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4, 1, 4, 4,
		4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		0, 4, 1, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4};

#define ARGMAX_STR "ACGTN"
#define num2nuc(index) ARGMAX_STR[index]
#define rc_string  "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNTNGNNNCNNNNNNNNNNNNANNNNNNNNNNNNTNGNNNCNNNNNNNNNNNNANNNNNNNNNNN"
#define nuc2num(character) nucpos_arr[(int8_t)character]
#define nuc_cmpl(character) rc_string[(int8_t)character]


static inline int nuc_cmp(char forward, char reverse)
{
	return (int)(forward - reverse);
}

#endif
