#!/bin/bash
# Copyright 2023 (c) Adam McKenney - See LICENSE for details #
# Tests the speed of cats, calls itself recursively if the user is missing some files

test_file="/tmp/test.100mb.o"

if [ -f $test_file ]; then
	echo "Running your system's cat to /dev/null"
	time cat $test_file > /dev/null
	echo "--"
	
	echo "Running slim-cat to /dev/null"
	time ./cat.out $test_file > /dev/null
	echo "--"

	echo "Running slim-cat -u (unbuffered) to /dev/null"
	time ./cat.out -u $test_file > /dev/null
	echo "--"
	
	echo "Done."
else
	if [ -f a.out ]; then
		echo "Generating file...this may take awhile"
		cat /dev/random | ./a.out 100000000 > $test_file
		./times.sh
	else
		if [ -f size_cat.c ]; then
			echo "Compiling size_cat.c"
			cc size_cat.c
			./times.sh
		else
			echo "Cannot find size_cat.c"
			exit 1
		fi
	fi
fi

