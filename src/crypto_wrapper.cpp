#include "crypto_wrapper.h"
#include "crypto/sha256.cpp"
#include "crypto/ripemd160.cpp"
#include "crypto/base58.cpp"
#include "cleanse.cpp"
#include "uint256.h"
#include "hash.h"
#include "util/strencodings.cpp"
#include "util/string.cpp"

#include <cstring> // Include cstring here
#include <string>
#include <vector>
#include <span>

// C++ helper functions (outside extern "C")
static std::string EncodeBase58_cpp(const unsigned char* pbegin, const unsigned char* pend) {
    return EncodeBase58(std::span<const unsigned char>(pbegin, pend - pbegin));
}

// C wrapper functions
extern "C" char* EncodeBase58(const unsigned char* pbegin, const unsigned char* pend) {
    std::string encoded = EncodeBase58_cpp(pbegin, pend); // Call the C++ helper
    char* result = new char[encoded.length() + 1];
    std::strcpy(result, encoded.c_str()); // Use std::strcpy
    return result;
}

extern "C" bool DecodeBase58(const char* psz, unsigned char* vchRet, size_t* retLen, size_t maxLen) {
    std::vector<unsigned char> decoded;
    if (DecodeBase58(psz, decoded, maxLen)) {
        if (decoded.size() > maxLen) {
            return false;
        }
        *retLen = decoded.size();
        std::memcpy(vchRet, decoded.data(), decoded.size()); // Use std::memcpy
        return true;
    }
    return false;
}

extern "C" void free_encoded_string(char* str) {
    delete[] str;
}