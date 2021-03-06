#ifndef __HELPER_H
#define __HELPER_H

#include <stdint.h>
#include <stdbool.h>

#define ROUNDS_NO   10
#define REGISTER_NO 8
#define BLOCK_SIZE  16
// #define UNMASKED

#ifdef UNMASKED
#define CHANNELS 1
#else
#define CHANNELS 2
#endif

static uint8_t msg0[] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 
                         0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};

static uint8_t msg1[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 
                         0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

static uint8_t starting_key[16] = {
    0x2B, 0x7E, 0x15, 0x16,
    0x28, 0xAE, 0xD2, 0xA6,
    0xAB, 0xF7, 0x15, 0x88,
    0x09, 0xCF, 0x4F, 0x3C
};

#endif

