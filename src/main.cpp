#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>
#include <string_view>
#include <stdexcept>
#include <sstream>

#include "span.h"

#include "crypto/sha256.h"
#include "crypto/ripemd160.h"
#include "base58.h"
#include "util/strencodings.h"

// Helper function to convert hex string to byte vector
std::vector<unsigned char> hexToBytes(const std::string& hex) {
    std::vector<unsigned char> bytes;

    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char)std::stoul(byteString, nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

int main(int argc, char* argv[]) {

    bool as_hex = false;
    int input_arg_index = 2; // Default index for input string

    if (argc >= 2 && std::string(argv[1]) == "--as_hex") {
        as_hex = true;
        input_arg_index = 3; // Input is now the 3rd argument
    }

    if (argc < input_arg_index + 1) {
        std::cerr << "Usage: " << argv[0] << " [--as_hex] <command> <input>\n";
        std::cerr << "Commands: encode58, decode58, sha256, ripemd160\n";
        return 1;
    }

    std::string command = argv[input_arg_index - 1];
    std::string input_str = argv[input_arg_index];
    std::vector<unsigned char> input_bytes;
    size_t input_len;

    if (as_hex) {
        try {
            input_bytes = hexToBytes(input_str);
            input_len = input_bytes.size();
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid hexadecimal input: " << e.what() << std::endl;
            return 1;
        } catch (const std::out_of_range& e){
            std::cerr << "Error: Invalid hexadecimal input: " << e.what() << std::endl;
            return 1;
        }
    } else {
        input_len = input_str.length();
    }

    unsigned char* input = reinterpret_cast<unsigned char*>(input_str.data());

    if (command == "encode58") {
        Span<const unsigned char> input_span;
        if (as_hex) {
            input_span = Span<const unsigned char>(input_bytes.data(), input_bytes.size());
        } else {
            input_span = Span<const unsigned char>(reinterpret_cast<const unsigned char*>(input_str.data()), input_str.length());
        }
        std::string encoded = EncodeBase58(input_span);
        std::cout << encoded << std::endl;
    } else if (command == "decode58") {
        std::vector<unsigned char> decoded;
        bool decode_result;

        decode_result = DecodeBase58(input_str.c_str(), decoded, input_len);
        
        if (decode_result) {
            if (as_hex) {
                for (unsigned char byte : decoded) {
                    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
                }
                std::cout << std::dec << std::endl;
            } else {
                std::string decoded_str(decoded.begin(), decoded.end());
                std::cout << decoded_str << std::endl;
            }
        } else {
            std::cerr << "Decoding failed" << std::endl;
        }
    } else if (command == "sha256") {
        unsigned char hash[CSHA256::OUTPUT_SIZE];
        CSHA256 sha256;

        if (as_hex) {
            sha256.Write(input_bytes.data(), input_len);
        } else {
            sha256.Write((const unsigned char*)input_str.data(), input_len);
        }

        sha256.Finalize(hash);

        for (size_t i = 0; i < CSHA256::OUTPUT_SIZE; i++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }
        std::cout << std::dec << std::endl;
    } else if (command == "ripemd160") {
        unsigned char hash[CRIPEMD160::OUTPUT_SIZE];
        CRIPEMD160 ripemd160;

        if (as_hex) {
            ripemd160.Write(input_bytes.data(), input_len);
        } else {
            ripemd160.Write((const unsigned char*)input_str.data(), input_len);
        }

        ripemd160.Finalize(hash);

        for (size_t i = 0; i < CRIPEMD160::OUTPUT_SIZE; i++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }
        std::cout << std::dec << std::endl; // Reset to decimal
    } else {
        std::cerr << "Invalid command: " << command << std::endl;
        return 1;
    }

    return 0;
}