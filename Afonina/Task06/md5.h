#ifndef __MD5_H_
#define __MD5_H_

#include <stdint.h>
#include <stdlib.h>

void to_bytes(uint32_t val, uint8_t *bytes);
uint32_t to_int32(const uint8_t *bytes);
void md5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest);

#endif
