#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>

#define AES_KEY_SIZE 256 // You can use 128, 192, or 256 bits for AES

int main(int argc, char **args) {
    unsigned char aes_key[AES_KEY_SIZE / 8]; // AES-256 key
    if (RAND_bytes(aes_key, sizeof(aes_key)) != 1) {
        fprintf(stderr, "Error generating random key\n");
        return 1;
    }

    printf("Generated AES Key (Hexadecimal):\n");
    for (int i = 0; i < sizeof(aes_key); i++) {
        printf("%02X", aes_key[i]);
    }
    return 0;
}
