#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>
#include <string_view>
#include <stdexcept>

#include "span.h"

#include "crypto/sha256.h"
#include "crypto/ripemd160.h"
#include "base58.h"
#include "util/strencodings.h"


int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <command> <input>\n";
        std::cerr << "Commands: encode58, decode58, sha256, ripemd160\n";
        return 1;
    }

    std::string command = argv[1];
    std::string input_str = argv[2];
    size_t input_len = input_str.length(); // Calculate the length directly

    std::cout << "Command: " << command << std::endl;
    std::cout << "Input string: " << input_str << std::endl;
    std::cout << "Input length: " << input_len << std::endl;

    unsigned char* input = reinterpret_cast<unsigned char*>(input_str.data());

    if (command == "encode58") {
        // Correct span creation and casting using your custom functions
        auto input_span = MakeUCharSpan(std::basic_string_view<char>(reinterpret_cast<char*>(input), input_len));
        std::string encoded = EncodeBase58(input_span);
        std::cout << encoded << std::endl;
    } else if (command == "decode58") {
        std::vector<unsigned char> decoded;
        if (DecodeBase58(input_str.c_str(), decoded, input_len)) {
            std::string decoded_str(decoded.begin(), decoded.end());
            std::cout << decoded_str << std::endl;
        } else {
            std::cerr << "Decoding failed" << std::endl;
        }
    } else if (command == "sha256") {
        unsigned char hash[CSHA256::OUTPUT_SIZE];
        CSHA256 sha256;
        sha256.Write(input, input_len);
        sha256.Finalize(hash);
        for (size_t i = 0; i < CSHA256::OUTPUT_SIZE; i++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }
        std::cout << std::endl;
    } else if (command == "ripemd160") {
        unsigned char hash[CRIPEMD160::OUTPUT_SIZE]; // Allocate space for the hash output
        CRIPEMD160 ripemd160; // Create a CRIPEMD160 object
        ripemd160.Write(input, input_len); // Write the input data to the hasher
        ripemd160.Finalize(hash); // Finalize the hash calculation and store the result in 'hash'

        // Print the hash in hex format (similar to SHA256)
        for (size_t i = 0; i < CRIPEMD160::OUTPUT_SIZE; i++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Invalid command: " << command << std::endl;
        return 1;
    }

    return 0;
}