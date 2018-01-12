#!/bin/bash
cd $(dirname $(readlink -f $0))

(exec "scripts/run-pre-build.sh"                           )
(exec "scripts/run-build.sh"     "at90can128-default.cmake")
(exec "scripts/run-build.sh"     "atmega328p-default.cmake")
(exec "scripts/run-build.sh"     "host-default.cmake"      )
(exec "scripts/run-post-build.sh"                          )



