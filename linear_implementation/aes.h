#ifndef __AES_H
#define __AES_H

#include "helper.h"

#ifdef UNMASKED
#include "unmasked_ops.h"
#else
#include "masked_ops.h"
#endif

void encrypt(uint32_t *state, uint32_t *key);

#endif

