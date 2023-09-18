#include "../include/base64.h"

char *base64_encode(const unsigned char *data, int data_len) {
    BIO *bio, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    if (!b64) {
        //TODO: Handle error here
        return NULL;
    }

    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new(BIO_s_mem());
    if (!bio) {
        //TODO: Handle error here and free b64
        BIO_free(b64);
        return NULL;
    }

    bio = BIO_push(b64, bio);

    BIO_write(bio, data, data_len);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bptr);

    char *buffer = (char *)malloc(bptr->length + 1);
    if (!buffer) {
        //TODO: Handle error here and free bio and b64
        BIO_free_all(bio);
        return NULL;
    }

    memcpy(buffer, bptr->data, bptr->length);
    buffer[bptr->length] = 0;

    BIO_free_all(bio);
    return buffer;
}

char *base64_decode(const char *input) {
    BIO *bio, *b64;
    int decode_len = strlen(input);
    unsigned char *buffer = (unsigned char *)malloc(decode_len);
    memset(buffer, 0, decode_len);

    bio = BIO_new_mem_buf(input, -1);
    if (!bio) {
        //TODO: Handle error here
        free(buffer);
        return NULL;
    }

    b64 = BIO_new(BIO_f_base64());
    if (!b64) {
        //TODO: Handle error here and free bio
        BIO_free(bio);
        free(buffer);
        return NULL;
    }

    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_push(b64, bio);

    BIO_read(bio, buffer, decode_len);

    BIO_free_all(bio);
    return (char *)buffer;
}