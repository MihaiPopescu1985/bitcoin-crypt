# About

The files inside this repository are extracted from the the bitcoin repository: https://github.com/bitcoin-core/gui/tree/master/src
The purpose is to have a standalone executable that implements the ecoding/hashing functions.
Slightly changes were needed, but the 99.99% of the original files are kept.

The main.cpp provides an interface to these functions.

# Build

I only tested on Debian 12

```
sudo apt install cmake
cd ./src
mkdir build && cd build
cmake ..
make
```

The build can also be done in a Docker container by running `./docker.sh`.

# Usage

```
# if not already inside the build folder where the executable was created
cd ./src/build

# call the executable
./btc_crypt
```

This will print a short usage message:
```
Usage: ./btc_crypt [--as_hex] <command> <input>
Commands: encode58, decode58, sha256, ripemd160
```

The `--as_hex` flag will cause the provided input to be treated as a hexadecimal value instead of a string.

The available commands:
- encode58
- decode58
- sha256
- ripemd160

# Examples

```
./btc_crypt encode58 aa
8Qp

./btc_crypt decode58 8Qp
aa

./btc_crypt --as_hex encode58 aa
3w

./btc_crypt --as_hex decode58 3w
aa

./btc_crypt sha256 aa
961b6dd3ede3cb8ecbaacbd68de040cd78eb2ed5889130cceb4c49268ea4d506

./btc_crypt --as_hex sha256 aa
bceef655b5a034911f1c3718ce056531b45ef03b4c7b1f15629e867294011a7d

./btc_crypt ripemd160 aa
fc596101aa50c992c88f53a497fe4feafa8677dd

./btc_crypt --as_hex ripemd160 aa
b88178b2da8a0f03d4dc0dcc85c10e7616dd522c
```
