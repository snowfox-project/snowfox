#!/bin/bash

cd $(dirname $(readlink -f $0))

mkdir -p ../build/report/cppcheck
cd ../build/report/cppcheck

cppcheck --enable=warning --xml-version=2 ../../../src 2> cppcheck.xml
cppcheck-htmlreport --file=cppcheck.xml --report-dir=./ --source-dir=../../../src
