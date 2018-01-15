#!/bin/bash

cd $(dirname $(readlink -f $0))

exec ("../build/bin/test-host")
