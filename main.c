#include <stdio.h>

#include "aes.h"

/* TODO
    2 - sa scap de variabilele care se trimit aiurea    DONE
    1 - sa fac bitslice pentru cheie                    DONE
    4 - sa fac key expansion                            
    3 - sa fac masked                                   DONE
*/

uint32_t bitsliced_state[REGISTER_NO][CHANNELS] = {{0}};
uint32_t bitsliced_key[(ROUNDS_NO + 1) * BLOCK_SIZE][CHANNELS]= {{0}};

void convert_to_bitsliced(uint8_t *msg0, uint8_t *msg1, uint32_t bitsliced[][CHANNELS]) {
    uint8_t mask = 1;

    for (int index = 0; index < REGISTER_NO; index++) {
        int k = 31;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
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
    for (int index = 0; index < REGISTER_NO; index++) {
        int k = 31;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                msg0[4 * j + i] |= ((bitsliced[index][0] >> k) & 0x01) << index;
                k--;
                msg1[4 *j + i] |= ((bitsliced[index][0] >> k) & 0x01) << index;
                k--;
            }
        }
    }
}


int main() {
    uint8_t m0[16] = {0},  m1[16] = {0};

    for (int i = 0; i < 16; i++)
        printf("%02x ", msg0[i]);
    printf("\n");

    for (int i = 0; i < 16; i++)
        printf("%02x ", msg1[i]);
    printf("\n");

    convert_to_bitsliced(msg0, msg1, bitsliced_state);

    for (int i = 0; i < ROUNDS_NO + 1; i++) {
        convert_to_bitsliced(&key[2 * i * BLOCK_SIZE], &key[2 * i * BLOCK_SIZE], &bitsliced_key[i * BLOCK_SIZE]);
    }

#ifndef UNMASKED
    for (int i = 0; i < REGISTER_NO; i++) {
        bitsliced_state[i][1] = 31412;

		bitsliced_state[i][0] ^= bitsliced_state[i][1];
    } 
#endif

    encrypt(bitsliced_state, bitsliced_key);

#ifndef UNMASKED
	for(int i = 0; i < REGISTER_NO; i++)
	{
		bitsliced_state[i][0] ^= bitsliced_state[i][1];
	}
#endif

    convert_from_bitsliced(bitsliced_state, m0, m1);

    printf("\n");

    for (int i = 0; i < 16; i++)
        printf("%02x ", m0[i]);
    printf("\n");

    for (int i = 0; i < 16; i++)
        printf("%02x ", m1[i]);
    printf("\n");

    return 0;
}


// for (int j = 0; j < REGISTER_NO; j++) {
//     printf("%08X ", bitsliced_state[j][0]);
// }
// printf("\n");

// for (int j = 0; j < REGISTER_NO; j++) {
//     printf("\n%08X\t%08X", bitsliced_state[j][0], bitsliced_state[j][1]);
// }
// printf("\n");
