#!/usr/bin/env bash
set -u

make || exit 1

output="$(./clox tests/expressions.lox 2>&1)"
status=$?

printf '%s\n' "$output"

if [ "$status" -ne 0 ]; then
  exit 1
fi
