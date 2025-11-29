# Base image
FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install essential dependencies
# - clang, lld, llvm: Required compilers and linkers
# - git, wget, make: Build tools
# - python3, python3-pip: Required by OpenOrbis scripts
# - vim, nano: Text editors
# - socat: generic utility often used in payload deployment
RUN apt-get update && apt-get install -y \
    build-essential \
    binutils \
    clang \
    llvm \
    git \
    wget \
    curl \
    make \
    cmake \
    python3 \
    python3-pip \
    vim \
    nano \
    sudo \
    unzip \
    libelf-dev \
    && rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/OpenOrbis/OpenOrbis-PS4-Toolchain/releases/download/v0.5.3/toolchain-llvm-14.zip -O /tmp/toolchain-llvm-14.zip && \
    unzip /tmp/toolchain-llvm-14.zip -d /tmp/oo && \
    tar -xvf /tmp/oo/toolchain-llvm-14.tar.gz -C /opt && \
    rm -rf /tmp/toolchain-llvm-14.zip /tmp/oo

# Clean up
RUN apt-get clean && rm -rf /var/lib/apt/lists/*
	
# Create a user for development
ARG USERNAME=ps4dev
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

USER $USERNAME
WORKDIR /home/$USERNAME/workspace

# Set environment variables
ENV OO_PS4_TOOLCHAIN=/opt/OpenOrbis

# Set bash vi-mode
RUN echo 'set -o vi' >> ~/.bashrc

# Default command
CMD ["/bin/bash"]