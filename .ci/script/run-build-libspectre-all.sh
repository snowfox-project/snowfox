#!/bin/bash
##########################################################################
cd $(dirname $(readlink -f $0))
set -e
##########################################################################
declare -a ARCH_LIST=("config/at90can32-default.cmake"
                      "config/at90can64-default.cmake"
                      "config/at90can128-default.cmake"
                      "config/atmega640-default.cmake"
                      "config/atmega1280-default.cmake"
                      "config/atmega2560-default.cmake"
                      "config/atmega164p-default.cmake"
                      "config/atmega324p-default.cmake"
                      "config/atmega644p-default.cmake"
                      "config/atmega1284p-default.cmake"
                      "config/atmega328p-default.cmake"
                      "config/atmega16u4-default.cmake"
                      "config/atmega32u4-default.cmake"
#                     "config/atmega3209-default.cmake"
#                     "config/atmega4809-default.cmake"
                     )

NUM_LIST_ENTRIES=${#ARCH_LIST[@]}

RED='tput setaf 1'
RESET='tput sgr0'

for (( i=0; i<${NUM_LIST_ENTRIES}; i++ ));
do
  $RED
  echo "[ " $(($i+1)) " / " ${NUM_LIST_ENTRIES} " ] " ${ARCH_LIST[$i]}
  $RESET
  ./run-build-libspectre.sh ${ARCH_LIST[$i]}
done

##########################################################################

