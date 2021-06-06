#include <stdint.h>

uint32_t tmp0, tmp1;

#define MOV(src, dst)	{   \
	dst[0] = src[0];    \
    dst[1] = src[1];    \
}

#define NOT(src, dst)	{   \
	dst[0] = ~src[0];    \
}

#define XOR(op1, op2, res)	{   \
	res[0] = op1[0] ^ op2[0];   \
    res[1] = op1[1] ^ op2[1];   \
}

// TODO rand
#define AND(op1, op2, res)	{   \
	tmp0 = op1[0] & op2[0];   \
    tmp1 = op1[0] & op2[1];   \
    res[0] = 1971352;   \
    tmp0 ^= res[0];   \
    tmp0 ^= tmp1;   \
    tmp1 = op1[1] & op2[0];   \
    tmp0 ^= tmp1;   \
    tmp1 = op1[1] & op2[1];   \
    tmp0 ^= tmp1;   \
    res[1] = tmp0;    \
}

#define ROTATE_LEFT_BYTE(to_rotate, res, bits) {    \
    res[0] = (to_rotate[0] << bits) | (to_rotate[0] >> (8 - bits)); \
    res[1] = (to_rotate[1] << bits) | (to_rotate[1] >> (8 - bits)); \
}

#define ROTATE_LEFT_WORD(to_rotate, res, bits) {    \
    res[0] = (to_rotate[0] << bits) | (to_rotate[0] >> (32 - bits));    \
    res[1] = (to_rotate[1] << bits) | (to_rotate[1] >> (32 - bits));    \
}

#define ROTATE_RIGHT_WORD(to_rotate, res, bits) {    \
    res[0] = (to_rotate[0] >> bits) | (to_rotate[0] << (32 - bits));    \
    res[1] = (to_rotate[1] >> bits) | (to_rotate[1] << (32 - bits));    \
}
