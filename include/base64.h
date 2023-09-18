#ifndef BASE64_H
#define BASE64_H

#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *base64_encode(const unsigned char *data, int data_len);

char *base64_decode(const char *input);

#endif