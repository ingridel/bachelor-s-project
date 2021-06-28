#include "key_expansion.h"

static uint8_t expanded_key[EXPANDED_KEY_LENGTH] = {0};

uint8_t *expand_key(uint8_t key[KEY_LENGTH]) {
    uint8_t rc_index, i;
    uint8_t g0, g1, g2, g3;

    for (i = 0; i < KEY_LENGTH; i++)
        expanded_key[i] = key[i];

    for (i = 16; i < EXPANDED_KEY_LENGTH; i += WORD_LENGTH) {
        if (i % KEY_LENGTH == 0) {
            rc_index = i / KEY_LENGTH - 1;
            g0 = sbox[expanded_key[i - WORD_LENGTH + 1]] ^ rc[rc_index];
            g1 = sbox[expanded_key[i - WORD_LENGTH + 2]];
            g2 = sbox[expanded_key[i - WORD_LENGTH + 3]];
            g3 = sbox[expanded_key[i - WORD_LENGTH]];
        } else {
            g0 = expanded_key[i - WORD_LENGTH];
            g1 = expanded_key[i - WORD_LENGTH + 1];
            g2 = expanded_key[i - WORD_LENGTH + 2];
            g3 = expanded_key[i - WORD_LENGTH + 3];
        }

        expanded_key[i]     = g0 ^ expanded_key[i - KEY_LENGTH];
        expanded_key[i + 1] = g1 ^ expanded_key[i - KEY_LENGTH + 1];
        expanded_key[i + 2] = g2 ^ expanded_key[i - KEY_LENGTH + 2];
        expanded_key[i + 3] = g3 ^ expanded_key[i - KEY_LENGTH + 3];
    }

    return expanded_key;
}
