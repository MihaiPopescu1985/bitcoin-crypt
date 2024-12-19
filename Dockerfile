FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    nano \
    git

# RUN apt-get update && apt-get install -y libcpuid-dev

WORKDIR /app
COPY . /app

WORKDIR /app/src/build
RUN cmake ..
RUN make 2>&1 | tee build.log
