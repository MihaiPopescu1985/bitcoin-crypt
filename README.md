# About

The files inside this repository are extracted from the the bitcoin repository: https://github.com/bitcoin-core/gui/tree/master/src
The purpose is to have a standalone executable that implements the ecoding/hashing functions.
Slightly changes were needed, but the 99.9% of the original files are kept.

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
cd ./src/build # if not already there
./btc_crypt
```

This will print a short usage message:
```
Usage: ./btc_crypt <command> <input>
Commands: encode58, decode58, sha256, ripemd160
```

# Example

```
./btc_crypt sha256 abc

Command: sha256
Input string: abc
Input length: 3
ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad
```
