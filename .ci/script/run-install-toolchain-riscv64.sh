#!/bin/bash
sudo apt-get update
sudo apt-get install cmake
mkdir -p "${TRAVIS_BUILD_DIR}/toolchain"
cd "${TRAVIS_BUILD_DIR}/toolchain"
wget https://static.dev.sifive.com/dev-tools/riscv64-unknown-elf-gcc-8.2.0-2019.02.0-x86_64-linux-ubuntu14.tar.gz
tar -xzvf riscv64-unknown-elf-gcc-8.2.0-2019.02.0-x86_64-linux-ubuntu14.tar.gz
