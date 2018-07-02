#!/bin/bash

source travis_retry.sh
WGET="travis_retry wget --continue --tries=20 --waitretry=10 --retry-connrefused --no-dns-cache --timeout 300"

sudo apt-get update

sudo apt-get install cppcheck
sudo apt-get install lcov
gem install coveralls-lcov
lcov --version
g++ --version

sudo apt-get install cmake

$WGET http://atiselsts.github.io/resources/avr-gcc-4.9.2-compiled.tar.bz2
tar xjf avr-gcc*.tar.bz2 -C /tmp/
sudo cp -f -r /tmp/avr-gcc/* /usr/local/
rm -rf /tmp/avr-gcc avr-gcc*.tar.bz2
avr-gcc --version
