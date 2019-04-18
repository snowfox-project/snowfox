#!/bin/bash
sudo apt-get update
sudo apt-get install cmake lcov libboost-all-dev
gem install coveralls-lcov
lcov --version
g++ --version
