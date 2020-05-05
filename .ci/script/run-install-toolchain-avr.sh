#!/bin/bash
sudo apt-get update
sudo apt-get install cmake
cd /opt
sudo wget https://github.com/snowfox-project/snowfox-avr-gcc/releases/download/9.2.0/avr-gcc-9.2.0-x64-linux.tar.gz
sudo tar -xzvf avr-gcc-9.2.0-x64-linux.tar.gz
