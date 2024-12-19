#!/bin/bash

clear

# Attempt to remove the container (ignore errors if it doesn't exist)
docker container rm btc_crypt 2>/dev/null

# Attempt to remove the image (ignore errors if it doesn't exist)
docker image rm btc_crypt 2>/dev/null

docker build -t btc_crypt .

docker run -it --name btc_crypt btc_crypt /bin/bash