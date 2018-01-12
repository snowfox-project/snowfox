#!/bin/bash
cd $(dirname $(readlink -f $0))

#(exec "./run-cppcheck.sh" "-out=xml")

rm -rf ../../build
