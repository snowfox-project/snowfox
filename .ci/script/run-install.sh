#!/bin/bash

travis_retry() {
  local result=0
  local count=1
  while [ $count -le 3 ]; do
    [ $result -ne 0 ] && {
      echo -e "\n${ANSI_RED}The command \"$@\" failed. Retrying, $count of 3.${ANSI_RESET}\n" >&2
    }
    "$@"
    result=$?
    [ $result -eq 0 ] && break
    count=$(($count + 1))
    sleep 1
  done

  [ $count -gt 3 ] && {
    echo -e "\n${ANSI_RED}The command \"$@\" failed 3 times.${ANSI_RESET}\n" >&2
  }

  return $result
}

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
