#!/bin/bash

cd $(dirname $(readlink -f $0))

../../build/test-host
