#include "../include/AES.h"

void encrypt(const char *input, const char *key, char *output) {
    AES_KEY aesKey;
    AES_set_encrypt_key((const unsigned char *)key, AES_KEY_SIZE, &aesKey);
    AES_encrypt((const unsigned char *)input, (unsigned char *)output, &aesKey);
}

void decrypt(const char *input, const char *key, char *output) {
    AES_KEY aesKey;
    AES_set_decrypt_key((const unsigned char *)key, AES_KEY_SIZE, &aesKey);
    AES_decrypt((const unsigned char *)input, (unsigned char *)output, &aesKey);
}