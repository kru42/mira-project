FROM ubuntu:22.04

# Set environment variable to avoid tzdata prompt
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    wget \
    cmake \
    binutils \
    netcat \
    clang \
    llvm \
    lld \
    lldb \
    clang-tidy \
    clang-tools \
    cppcheck \
    libprotobuf-c-dev \
    libprotobuf-c1 \
    protobuf-c-compiler \
    protobuf-compiler


# Fetch the OpenOrbis toolchain and extract it
RUN wget -O /tmp/OpenOrbis.tar.gz https://github.com/OpenOrbis/OpenOrbis-PS4-Toolchain/releases/download/v0.5.2/v0.5.2.tar.gz
RUN tar -xvf /tmp/OpenOrbis.tar.gz -C /opt

# # Fetch protobuf-c repo, build and install it
# RUN git clone https://github.com/protobuf-c/protobuf-c.git /tmp/protobuf-c
# RUN cd /tmp/protobuf-c && ./autogen.sh && ./configure && make && make install

# Set environment variables
ENV OO_PS4_TOOLCHAIN=/opt/OpenOrbis

# Clean up
RUN apt-get clean && rm -rf /var/lib/apt/lists/* && rm /tmp/OpenOrbis.tar.gz

# Set bash vi-mode
RUN echo 'set -o vi' >> ~/.bashrc
