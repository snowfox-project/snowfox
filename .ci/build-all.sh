#!/bin/bash
cd $(dirname $(readlink -f $0))

(exec "scripts/run-pre-build.sh" )
(exec "scripts/run-build.sh"     )
(exec "scripts/run-post-build.sh")



