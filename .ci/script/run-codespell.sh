#!/bin/bash
codespell --skip="$1/.git" --skip="$1/test/external" --ignore-words="$1/.ci/codespell/ignore-words-list.txt" "$1"
