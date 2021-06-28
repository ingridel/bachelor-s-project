#include "aes.h"

#include <stdio.h> // de scos

void g4_mul11(uint32_t stack[][CHANNELS], uint32_t *a1, uint32_t *a0, uint32_t *b1, uint32_t *b0) {
    uint32_t e[CHANNELS];

    XOR(b1, b0, e);
    MOV(e, stack[3]);

    AND(e, stack[8], e);
    AND(a1, b1, a1);
    AND(a0, b0, a0);

    XOR(a1, e, a1);
    XOR(a0, e, a0);
}

void g4_mul12(uint32_t stack[][CHANNELS], uint32_t *a1, uint32_t *a0, uint32_t *b1, uint32_t *b0) {
    uint32_t e[CHANNELS];

    XOR(b1, b0, e);
    MOV(e, stack[5]);

    AND(e, stack[10], e);

    AND(a1, b1, a1);
    AND(a0, b0, a0);

    XOR(a1, e, a1);
    XOR(a0, e, a0);
}

void g4_mul21(uint32_t stack[][CHANNELS], uint32_t *a1, uint32_t *a0, uint32_t *b1, uint32_t *b0) {
    uint32_t e[CHANNELS];

    AND(stack[7], stack[3], e);

    AND(a1, b1, a1);
    AND(a0, b0, a0);

    XOR(a1, e, a1);
    XOR(a0, e, a0);
}

void g4_mul22(uint32_t stack[][CHANNELS], uint32_t *a1, uint32_t *a0, uint32_t *b1, uint32_t *b0) {
    uint32_t e[CHANNELS];

    AND(stack[9], stack[5], e);

    AND(a1, b1, a1);
    AND(a0, b0, a0);

    XOR(a1, e, a1);
    XOR(a0, e, a0);
}

void g4_mul_store_x7x6_x3x2(uint32_t stack[][CHANNELS], uint32_t *a1,
                            uint32_t *a0, uint32_t *b1, uint32_t *b0) {
    uint32_t e1[CHANNELS], e0[CHANNELS];

    XOR(a1, a0, e1);
    MOV(e1, stack[7]);

    XOR(b1, b0, e0);
    MOV(e0, stack[8]);

    AND(e1, e0, e1);
    AND(a1, b1, a1);
    AND(a0, b0, a0);
    XOR(a1, e1, a1);
    XOR(a0, e1, a0);
}

void g4_mul_store_x5x4_x1x0(uint32_t stack[][CHANNELS], uint32_t *a1,
                            uint32_t *a0, uint32_t *b1, uint32_t *b0) {
    uint32_t e1[CHANNELS], e0[CHANNELS];

    XOR(a1, a0, e1);
    MOV(e1, stack[9]);

    XOR(b1, b0, e0);
    MOV(e0, stack[10]);

    AND(e1, e0, e1);
    AND(a1, b1, a1);
    AND(a0, b0, a0);
    XOR(a1, e1, a1);
    XOR(a0, e1, a0);
}

void g16_mul1(uint32_t stack[][CHANNELS], uint32_t *r3, uint32_t *r2, uint32_t *r1,
                uint32_t *r0, uint32_t *s3, uint32_t *s2, uint32_t *s1, uint32_t *s0) {
    uint32_t t2[CHANNELS], t1[CHANNELS], t0[CHANNELS];

    MOV(stack[2], t2);
    XOR(s3, s1, t1);
    MOV(t1, stack[2]);

    AND(t2, t1, t2);
    XOR(s0, s2, t0);
    MOV(t0, stack[6]);

    XOR(t1, t0, t1);
    MOV(t1, stack[11]);

    AND(t0, stack[3], t0);
    XOR(t2, t0, t2);
    AND(t1, stack[5], t1);
    XOR(t1, t0, t1);

    g4_mul11(stack, r3, r2, s3, s2);
    XOR(r3, t1, r3);
    XOR(r2, t2, r2);

    g4_mul12(stack, r1, r0, s1, s0);
    XOR(r1, t1, r1);
    XOR(r0, t2, r0);
}

void g16_mul2(uint32_t stack[][CHANNELS], uint32_t *r3, uint32_t *r2, uint32_t *r1,
                uint32_t *r0, uint32_t *s3, uint32_t *s2, uint32_t *s1, uint32_t *s0) {
    uint32_t t2[CHANNELS], t1[CHANNELS], t0[CHANNELS];

    AND(stack[0], stack[2], t2);
    AND(stack[1], stack[6], t1);

    XOR(t2, t1, t2);
    AND(stack[4], stack[11], t0);

    XOR(t1, t0, t1);

    g4_mul21(stack, r3, r2, s3, s2);
    XOR(r3, t1, r3);
    XOR(r2, t2, r2);

    g4_mul22(stack, r1, r0, s1, s0);
    XOR(r1, t1, r1);
    XOR(r0, t2, r0);
}

void g16_inv(uint32_t *r3, uint32_t *r2, uint32_t *r1, uint32_t *r0) {
    uint32_t r3_r2[CHANNELS], r1_r0[CHANNELS];
    uint32_t d1[CHANNELS], d0[CHANNELS];
    uint32_t e[CHANNELS];

    XOR(r3, r2, r3_r2);
    XOR(r1, r0, r1_r0);
    AND(r3_r2, r1_r0, e);

    XOR(e, r3, e);
    XOR(e, r1, e);

    AND(r3, r1, d1);
    XOR(d1, e, d1);

    AND(r2, r0, d0);
    XOR(d0, e, d0);
    XOR(d0, r2, d0);
    XOR(d0, r0, d0);

    AND(r3, d0, r3);
    AND(r2, d1, r2);
    AND(r1, d0, r1);
    AND(r0, d1, r0);

    XOR(d0, d1, d0);

    AND(r3_r2, d0, r3_r2);
    XOR(r3, r3_r2, r3);
    XOR(r2, r3_r2, r2);

    AND(r1_r0, d0, r1_r0);
    XOR(r1, r1_r0, r1);
    XOR(r0, r1_r0, r0);
}

void g256_newbasis_A2X(uint32_t *a7, uint32_t *a6, uint32_t *a5, uint32_t *a4,
                        uint32_t *a3, uint32_t *a2, uint32_t *a1, uint32_t *a0) {
    uint32_t aux[CHANNELS];

    XOR(a1, a7, aux);
    XOR(a5, a6, a5);
    XOR(a5, a0, a5);
    XOR(a6, a0, a6);
    XOR(a6, a1, a6);
    XOR(a6, a2, a6);
    XOR(a6, a3, a6);
    XOR(a7, a5, a7);
    XOR(a1, a5, a1);
    XOR(a3, a4, a3);
    XOR(a4, a5, a4);
    XOR(a2, aux, a2);
    XOR(a2, a5, a2);
    XOR(a3, aux, a3);
    XOR(a3, a0, a3);
}

void g256_newbasis_X2S(uint32_t *a7, uint32_t *a6, uint32_t *a5, uint32_t *a4,
                        uint32_t *a3, uint32_t *a2, uint32_t *a1, uint32_t *a0) {
    uint32_t aux0[CHANNELS], aux1[CHANNELS], aux2[CHANNELS], aux3[CHANNELS];

    MOV(a6, aux0);
    XOR(a6, a4, a6);
    MOV(a1, aux1);
    XOR(a1, a4, a1);
    MOV(a2, aux2);
    XOR(a1, a5, a1);
    MOV(a3, a4);
    XOR(a4, a7, a4);
    MOV(a4, a2);
    XOR(a2, a5, a2);
    MOV(a2, a7);
    XOR(a7, a6, a7);
    MOV(a0, aux3);
    XOR(a6, aux1, a6);
    MOV(a3, a0);
    XOR(a0, a5, a0);
    MOV(aux0, a5);
    XOR(a5, aux3, a5);
    MOV(a0, a3);
    XOR(a3, a5, a3);
    XOR(a3, aux2, a3);
}

void g256_inv(uint32_t *x7, uint32_t *x6, uint32_t *x5, uint32_t *x4,
                uint32_t *x3, uint32_t *x2, uint32_t *x1, uint32_t *x0) {
    uint32_t a0[CHANNELS], a1[CHANNELS], a2[CHANNELS];
    uint32_t d0[CHANNELS], d1[CHANNELS], d2[CHANNELS], d3[CHANNELS];
    uint32_t stack[12][CHANNELS];

    XOR(x7, x5, a2);
    MOV(a2, stack[0]);
    XOR(x6, x4, a1);
    MOV(a1, stack[1]);
    XOR(x3, x1, d3);
    MOV(d3, stack[2]);
    XOR(x2, x0, d2);
    MOV(d2, stack[3]);
    XOR(a2, a1, d1);
    MOV(d1, stack[4]);

    AND(a1, d2, a1);
    XOR(d2, d3, d2);
    MOV(d2, stack[5]);

    AND(d1, d2, d1);
    AND(a2, d3, a2);
    XOR(a2, a1, a2);
    XOR(a1, d1, a1);

    MOV(x7, d3);
    MOV(x6, d2);
    MOV(x5, d1);
    MOV(x4, d0);

    g4_mul_store_x7x6_x3x2(stack, d3, d2, x3, x2);

    g4_mul_store_x5x4_x1x0(stack, d1, d0, x1, x0);

    MOV(x0, a0);

    XOR(a0, x4, a0);
    XOR(a1, a0, a1);
    XOR(d1, a1, d1);
    XOR(d0, a2, d0);
    XOR(d3, a1, d3);
    XOR(d2, a2, d2);
    XOR(d0, a0, d0);

    MOV(x1, a0);

    XOR(a0, x5, a0);
    XOR(d1, a0, d1);
    XOR(d2, a0, d2);
    XOR(d3, x6, d3);
    XOR(d3, x2, d3);
    XOR(d2, x7, d2);
    XOR(d2, x3, d2);

    g16_inv(d3, d2, d1, d0);

    g16_mul1(stack, x3, x2, x1, x0, d1, d0, d3, d2);

    g16_mul2(stack, x7, x6, x5, x4, d1, d0, d3, d2);
}

void add_round_key(uint32_t *state, uint32_t *key) {
    uint8_t index;
    for (index = 0; index < REGISTER_NO; index++) {
        XOR((state + index * CHANNELS), (key + index * CHANNELS),
            (state + index * CHANNELS));
    }
}

void sub_bytes(uint32_t *state) {
    g256_newbasis_A2X(state + 7 * CHANNELS, state + 6 * CHANNELS,
              state + 5 * CHANNELS, state + 4 * CHANNELS,
              state + 3 * CHANNELS, state + 2 * CHANNELS,
              state + 1 * CHANNELS, state + 0 * CHANNELS);

    g256_inv(state + 2 * CHANNELS, state + 4 * CHANNELS,
         state + 1 * CHANNELS, state + 7 * CHANNELS,
         state + 3 * CHANNELS, state + 0 * CHANNELS,
         state + 5 * CHANNELS, state + 6 * CHANNELS);

    g256_newbasis_X2S(state + 3 * CHANNELS, state + 0 * CHANNELS,
              state + 5 * CHANNELS, state + 6 * CHANNELS,
              state + 2 * CHANNELS, state + 4 * CHANNELS,
              state + 1 * CHANNELS, state + 7 * CHANNELS);

    NOT((state + 0 * CHANNELS), (state + 0 * CHANNELS));
    NOT((state + 1 * CHANNELS), (state + 1 * CHANNELS));
    NOT((state + 5 * CHANNELS), (state + 5 * CHANNELS));
    NOT((state + 6 * CHANNELS), (state + 6 * CHANNELS));
}

void shift_rows(uint32_t *state, bool final) {
    uint8_t row, channel, index;

    for (channel = 0; channel < CHANNELS; channel++) {
        for (index = 0; index < REGISTER_NO; index++) {

            // Row 1
            row = (state[index  * CHANNELS + channel] & 0x00ff0000) >> 16;
            row = (row << 2) | (row >> 6);

            state[index * CHANNELS + channel] &= 0xff00ffff;
            state[index * CHANNELS + channel] |= (uint32_t)row << 16;

            // Row 2
            row = (state[index * CHANNELS + channel] & 0x0000ff00) >> 8;
            row = (row << 4) | (row >> 4);

            state[index * CHANNELS + channel] &= 0xffff00ff;
            state[index * CHANNELS + channel] |= (uint32_t)row << 8;

            // Row 3
            row = state[index * CHANNELS + channel] & 0x000000ff;
            row = (row << 6) | (row >> 2);

            state[index * CHANNELS + channel] &= 0xffffff00;
            state[index * CHANNELS + channel] |= (uint32_t)row;
        }
    }

    if (final)
        return;

    for (index = 0; index < REGISTER_NO; index++) {
        ROTATE_RIGHT_WORD((state + index * CHANNELS), (state + index * CHANNELS), 8);
    }
}

void mix_columns(uint32_t *state) {
    uint32_t t[REGISTER_NO][CHANNELS], aux0[CHANNELS], aux1[CHANNELS];

    // t0
    ROTATE_LEFT_WORD((state + 0 * CHANNELS), aux0, 8);
    XOR((state + 0 * CHANNELS), aux0, t[0]);

    // t1
    ROTATE_LEFT_WORD((state + 1 * CHANNELS), aux0, 8);
    ROTATE_LEFT_WORD((state + 1 * CHANNELS), aux1, 16);
    XOR(aux0, aux1, t[1]);

    // t2
    ROTATE_LEFT_WORD((state + 2 * CHANNELS), aux0, 8);
    XOR((state + 2 * CHANNELS), aux0, t[2]);

    // t3
    ROTATE_LEFT_WORD((state + 3 * CHANNELS), aux0, 8);
    ROTATE_LEFT_WORD((state + 3 * CHANNELS), aux1, 16);
    XOR(aux0, aux1, t[3]);

    // t4
    ROTATE_LEFT_WORD((state + 4 * CHANNELS), aux0, 8);
    XOR((state + 4 * CHANNELS), aux0, t[4]);

    // t5
    ROTATE_LEFT_WORD((state + 5 * CHANNELS), aux0, 8);
    ROTATE_LEFT_WORD((state + 5 * CHANNELS), aux1, 16);
    XOR(aux0, aux1, t[5]);

    // t6
    ROTATE_LEFT_WORD((state + 6 * CHANNELS), aux0, 8);
    XOR((state + 6 * CHANNELS), aux0, t[6]);

    // t7
    ROTATE_LEFT_WORD((state + 7 * CHANNELS), aux0, 8);
    ROTATE_LEFT_WORD((state + 7 * CHANNELS), aux1, 16);
    XOR(aux0, aux1, t[7]);

    XOR((state + 2 * CHANNELS), t[1], (state + 2 * CHANNELS));
    XOR(t[1], t[0], t[1]);
    ROTATE_LEFT_WORD(t[1], t[1], 8);
    XOR((state + 1 * CHANNELS), t[1], (state + 1 * CHANNELS));
    ROTATE_LEFT_WORD(t[0], t[0], 16);
    XOR((state + 0 * CHANNELS), t[0], (state + 0 * CHANNELS));
    XOR((state + 4 * CHANNELS), t[3], (state + 4 * CHANNELS));
    XOR(t[3], t[2], t[3]);
    ROTATE_LEFT_WORD(t[3], t[3], 8);
    XOR((state + 3 * CHANNELS), t[3], (state + 3 * CHANNELS));
    ROTATE_LEFT_WORD(t[2], t[2], 16);
    XOR((state + 2 * CHANNELS), t[2], (state + 2 * CHANNELS));
    XOR((state + 6 * CHANNELS), t[5], (state + 6 * CHANNELS));
    XOR(t[5], t[4], t[5]);
    ROTATE_LEFT_WORD(t[5], t[5], 8);
    XOR((state + 5 * CHANNELS), t[5], (state + 5 * CHANNELS));
    ROTATE_LEFT_WORD(t[4], t[4], 16);
    XOR((state + 4 * CHANNELS), t[4], (state + 4 * CHANNELS));
    XOR((state + 0 * CHANNELS), t[7], (state + 0 * CHANNELS));
    XOR((state + 1 * CHANNELS), t[7], (state + 1 * CHANNELS));
    XOR((state + 3 * CHANNELS), t[7], (state + 3 * CHANNELS));
    XOR((state + 4 * CHANNELS), t[7], (state + 4 * CHANNELS));
    XOR(t[7], t[6], t[7]);
    ROTATE_LEFT_WORD(t[7], t[7], 8);
    XOR((state + 7 * CHANNELS), t[7], (state + 7 * CHANNELS));
    ROTATE_LEFT_WORD(t[6], t[6], 16);
    XOR((state + 6 * CHANNELS), t[6], (state + 6 * CHANNELS));
}

void encrypt(uint32_t *state, uint32_t *key) {
    uint8_t i;

    add_round_key(state, key);

    for (i = 0; i < ROUNDS_NO - 1; i++) {
        sub_bytes(state);
        shift_rows(state, false);
        mix_columns(state);
        add_round_key(state, key + 8 * (i + 1) * CHANNELS);
    }

    sub_bytes(state);
    shift_rows(state, true);
    add_round_key(state, key + 80 * CHANNELS);
}
