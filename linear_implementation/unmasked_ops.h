#define MOV(src, dst)	{   \
	dst[0] = src[0];    \
}

#define NOT(src, dst)	{   \
	dst[0] = ~src[0];    \
}

#define XOR(op1, op2, res)	{   \
	res[0] = op1[0] ^ op2[0];   \
}

#define AND(op1, op2, res)	{   \
	res[0] = op1[0] & op2[0];   \
}

#define ROTATE_LEFT_BYTE(to_rotate, res, bits) {    \
    res[0] = (to_rotate[0] << bits) | (to_rotate[0] >> (8 - bits)); \
}

#define ROTATE_LEFT_WORD(to_rotate, res, bits) {    \
    res[0] = (to_rotate[0] << bits) | (to_rotate[0] >> (32 - bits));    \
}

#define ROTATE_RIGHT_WORD(to_rotate, res, bits) {    \
    res[0] = (to_rotate[0] >> bits) | (to_rotate[0] << (32 - bits));    \
}
