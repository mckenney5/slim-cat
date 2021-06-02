#!/bin/bash
# Copyright 2021 (c) Adam McKenney - See LICENSE for details #
# Tests the speed of cats, calls itself recursively if the user is missing some files
if [ -f test.100mb.o ]; then
	echo "Running system's cat to /dev/null"
	time cat test.100mb.o > /dev/null
	echo "--"
	
	echo "Running slim-cat to /dev/null"
	time ./cat.out test.100mb.o > /dev/null
	echo "--"

	echo "Running slim-cat -u (unbuffered) to /dev/null"
	time ./cat.out -u test.100mb.o > /dev/null
	echo "--"

	echo "Done."
else
	if [ -f a.out ]; then
		echo "Generating file...this may take awhile"
		cat /dev/random | ./a.out 100000000 > test.100mb.o
		./times.sh
	else
		if [ -f size_cat.c ]; then
			echo "Compiling size_cat.c"
			gcc size_cat.c
			./times.sh
		else
			echo "Cannot find size_cat.c"
			exit 1
		fi
	fi
fi

