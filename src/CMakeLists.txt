cmake_minimum_required(VERSION 3.10)
project(standalone_crypto CXX)

set(CMAKE_CXX_STANDARD 20) # Crucial: Set to C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++20") # Explicit flag (if needed)

# Set include directories (Crucial!)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})       # For files like uint256.h, etc. in root
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/compat)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/crypto)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/util)

# Create the shared library (ONLY .cpp files here!)
add_library(crypto SHARED
    base58.cpp
    crypto_wrapper.cpp
    hash.cpp
    uint256.cpp
    crypto/hex_base.cpp
    crypto/ripemd160.cpp
    crypto/sha256.cpp
    util/strencodings.cpp
    util/string.cpp
)

# Set the target properties for header file installation
set_target_properties(crypto PROPERTIES
    PUBLIC_HEADER "crypto_wrapper.h" # Only the public header
    OUTPUT_NAME "crypto"
)

# Install targets (install header files)
install(TARGETS crypto
    EXPORT crypto-export
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES
    attributes.h
    base58.h
    crypto_wrapper.h
    hash.h
    prevector.h
    serialize.h
    span.h
    uint256.h
    compat/assumptions.h
    compat/byteswap.h
    compat/endian.h
    crypto/common.h
    crypto/hex_base.h
    crypto/ripemd160.h
    crypto/sha256.h
    util/strencodings.h
    util/string.h
    DESTINATION include
)

install(EXPORT crypto-export
    FILE crypto-targets.cmake
    NAMESPACE crypto::
    DESTINATION lib/cmake/crypto
)