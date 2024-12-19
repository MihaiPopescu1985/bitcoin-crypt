cmake_minimum_required(VERSION 3.10)
project(btc_crypt CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

# Find the GCC include directory for cpuid.h
execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} -print-file-name=include
    OUTPUT_VARIABLE GCC_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_executable(btc_crypt
    base58.cpp
    hash.cpp
    main.cpp
    uint256.cpp
    crypto/hex_base.cpp
    crypto/hmac_sha512.cpp
    crypto/ripemd160.cpp
    crypto/sha256.cpp
    crypto/sha512.cpp
    util/strencodings.cpp
    util/string_util.cpp
)

# TODO: for static linking
# set_target_properties(btc_crypt PROPERTIES LINKER_LANGUAGE CXX) # Not necessary, CXX is the default
# set_target_properties(btc_crypt PROPERTIES LINK_FLAGS "-static")

target_include_directories(btc_crypt
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/compat
    ${CMAKE_CURRENT_SOURCE_DIR}/crypto
    ${GCC_INCLUDE_DIR}
)

target_link_libraries(btc_crypt PRIVATE Threads::Threads)

# TODO: for static linking
# if(UNIX AND NOT APPLE)
#     set_target_properties(btc_crypt PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++")
# endif()