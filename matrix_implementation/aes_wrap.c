#include <stdio.h>

#include "aes.h"
#include "key_expansion.h"


uint32_t bitsliced_state[REGISTER_NO][CHANNELS] = {{0}};
uint32_t bitsliced_key[(ROUNDS_NO + 1) * REGISTER_NO][CHANNELS]= {{0}};

void convert_to_bitsliced(uint8_t *msg0, uint8_t *msg1, uint32_t bitsliced[][CHANNELS]) {
    uint8_t index, i, j, mask = 1;

    for (index = 0; index < REGISTER_NO; index++) {
        int k = 31;

        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                bitsliced[index][0] |= ((msg0[4 * j + i] & mask) >> index) << k;
                k--;
                bitsliced[index][0] |= ((msg1[4 * j + i] & mask) >> index) << k;
                k--;
            }
        }

        mask <<= 1;
    }
}


void convert_from_bitsliced(uint32_t bitsliced[][CHANNELS], uint8_t *msg0, uint8_t *msg1) {
    uint8_t index, i, j;

    for (index = 0; index < REGISTER_NO; index++) {
        uint32_t k = 31;

        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                msg0[4 * j + i] |= ((bitsliced[index][0] >> k) & 0x01) << index;
                k--;
                msg1[4 *j + i] |= ((bitsliced[index][0] >> k) & 0x01) << index;
                k--;
            }
        }
    }
}

void aes_wrap() {
    uint8_t *key, i;
    uint8_t m0[BLOCK_SIZE] = {0},  m1[BLOCK_SIZE] = {0};

    for (i = 0; i < BLOCK_SIZE; i++)
        printf("%02x ", msg0[i]);
    printf("\n");

    for (i = 0; i < BLOCK_SIZE; i++)
        printf("%02x ", msg1[i]);
    printf("\n");

    key = expand_key(starting_key);

    convert_to_bitsliced(msg0, msg1, bitsliced_state);

    for (i = 0; i < ROUNDS_NO + 1; i++) {
        convert_to_bitsliced(&key[i * BLOCK_SIZE], &key[i * BLOCK_SIZE], &bitsliced_key[i * REGISTER_NO]);
    }

#ifndef UNMASKED
    for (i = 0; i < REGISTER_NO; i++) {
        bitsliced_state[i][1] = rand();

		bitsliced_state[i][0] ^= bitsliced_state[i][1];
    } 
#endif

    encrypt(bitsliced_state, bitsliced_key);

#ifndef UNMASKED
	for(i = 0; i < REGISTER_NO; i++)
	{
		bitsliced_state[i][0] ^= bitsliced_state[i][1];
	}
#endif

    convert_from_bitsliced(bitsliced_state, m0, m1);

    printf("\n");

    for (i = 0; i < BLOCK_SIZE; i++)
        printf("%02x ", m0[i]);
    printf("\n");

    for (i = 0; i < BLOCK_SIZE; i++)
        printf("%02x ", m1[i]);
    printf("\n");
}


int main() {
    aes_wrap();
    return 0;
}
