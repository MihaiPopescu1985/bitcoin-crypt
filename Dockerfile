FROM gcc:bookworm

# Install build dependencies (only if you are going to build inside the container)
RUN apt-get update && \
    apt-get install -y build-essential cmake git \
                       libc6-dev \
                       && rm -rf /var/lib/apt/lists/*

# Set working directory inside the container
WORKDIR /app

# Copy your project files into the container
COPY . /app

# If you are going to build inside the container uncomment these lines
# Create build directory
# RUN mkdir build

# Configure and build the project
# WORKDIR /app/build
# RUN cmake ..
# RUN make

# If you are only copying files, you don't need a multi-stage build
# You also don't need a CMD if you are just copying files.