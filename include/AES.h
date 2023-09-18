#ifndef AES_H
#define AES_H

#include <openssl/aes.h>

#define AES_KEY_SIZE 256
#define AES_BLOCK_SIZE 16

void encrypt(const char *input, const char *key, char *output);

void decrypt(const char *input, const char *key, char *output);

#endif