// encryption.c
#include "include/ncu_srun_universal.h"
#include "include/encryption.h"

#include <openssl/hmac.h>
#include <openssl/evp.h>

#include <stdlib.h>
#include <string.h>

const char encryption_paddingchar = '=';
const char *encryption_alphabet = "LVoJPiCN2R8G90yg+hmFHuacZ1OWMnrsSTXkYpUq/3dlbfKwv6xztjI7DeBE45QA";
const char *encryption_hex_alphabet = "0123456789abcdef";

char *encryption_base64(char *src)
{
    size_t len = strlen(src);
    size_t base64_len = (size_t)(len / 3) * 4ull;
    if (len % 3 != 0)
        base64_len += 4ull;
    char *ret = (char *)malloc(sizeof(char) * base64_len + 1);
    ret[base64_len] = '\0';
    size_t pos = 0;

    for (int i = 0; i < (len - (len % 3)); i += 3)
    {
        int magic_num = ((int(src[i]) << 16) | (int(src[i + 1]) << 8) | (int(src[i + 2])));
        ret[pos++] = encryption_alphabet[magic_num >> 18];
        ret[pos++] = encryption_alphabet[(magic_num >> 12) & 63];
        ret[pos++] = encryption_alphabet[(magic_num >> 6) & 63];
        ret[pos++] = encryption_alphabet[magic_num & 63];
    }
    size_t xpos = len - (len % 3);
    if (len % 3 == 1)
    {
        int magic_num = (int(src[xpos]) << 16);
        ret[pos++] = encryption_alphabet[magic_num >> 18];
        ret[pos++] = encryption_alphabet[(magic_num >> 12) & 63];
        ret[pos++] = encryption_paddingchar;
        ret[pos++] = encryption_paddingchar;
    }
    else if (len % 3 == 2)
    {
        int magic_num = ((int(src[xpos]) << 16) | (int(src[xpos + 1]) << 8));
        ret[pos++] = encryption_alphabet[magic_num >> 18];
        ret[pos++] = encryption_alphabet[(magic_num >> 12) & 63];
        ret[pos++] = encryption_alphabet[(magic_num >> 6) & 63];
        ret[pos++] = encryption_paddingchar;
    }
    return ret;
}

char *encryption_md5(const char *password, const char *token)
{
    unsigned int md_len = 0;
    unsigned char *resbox = (unsigned char *)malloc(160 + 1);
    resbox[16] = 0;
    unsigned char *result = HMAC(EVP_md5(), token, strlen(token), (const unsigned char *)password, strlen(password), resbox, &md_len);

    size_t len = md_len * 2LL;
    char *ret = (char *)malloc(len + 1);
    ret[len] = '\0';
    for (unsigned int i = 0; i < md_len; i++)
        ret[2LL * i + 1] = encryption_hex_alphabet[result[i] & 15], ret[2LL * i] = encryption_hex_alphabet[result[i] >> 4];
    return ret;
}