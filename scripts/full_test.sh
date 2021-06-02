#!/bin/bash
# This does a full test before release

echo "### Creating cat.out ###"
gcc ../src/cat.c -g -o cat.out

echo "### Checking for memory leaks ###"
echo "Type in input, then hit Ctrl-D, do this twice"
valgrind -q ./cat.out - ../src/cat.c -

echo "### Doing consistancy test ###"
./check12.sh
./unbuf.check12.sh

echo "### Doing speed test ###"
./times.sh

echo "### Cleaning up ###"
rm -v cat.out

echo "\nDone."
