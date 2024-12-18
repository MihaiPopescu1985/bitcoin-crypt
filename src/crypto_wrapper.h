#ifndef CRYPTO_WRAPPER_H
#define CRYPTO_WRAPPER_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" { // Start of extern "C" block
#endif

// SHA256
typedef struct {
    uint32_t s[8];
    unsigned char data[64];
    size_t datalen;
    uint64_t bitlen;
} SHA256_CTX;

void SHA256_Init(SHA256_CTX* ctx);
void SHA256_Update(SHA256_CTX* ctx, const unsigned char* data, size_t len);
void SHA256_Final(SHA256_CTX* ctx, unsigned char hash[32]);

// RIPEMD160
typedef struct {
    uint32_t state[5];
    unsigned char buffer[64];
    uint64_t count;
} RIPEMD160_CTX;

void RIPEMD160_Init(RIPEMD160_CTX* ctx);
void RIPEMD160_Update(RIPEMD160_CTX* ctx, const unsigned char* data, size_t len);
void RIPEMD160_Final(RIPEMD160_CTX* ctx, unsigned char hash[20]);

// Base58
char* EncodeBase58(const unsigned char* pbegin, const unsigned char* pend);
bool DecodeBase58(const char* psz, unsigned char* vchRet, size_t* retLen, size_t maxLen);
void free_encoded_string(char* str);

#ifdef __cplusplus
} // End of extern "C" block
#endif

#endif