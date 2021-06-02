#!/bin/bash
# Copyright 2021 (c) Adam McKenney - See LICENSE for details #
# Makes cat.out clone its self with its self 12 times then checks to see if theres a difference

if [ -f cat.out ]; then
	echo "Generating 12 cats..."
	cat cat.out > 1.out
	chmod +x 1.out
	./1.out -u 1.out > 2.out
	chmod +x 2.out
	./2.out -u 2.out > 3.out
	chmod +x 3.out
	./3.out -u 3.out > 4.out
	chmod +x 4.out
	./4.out -u 4.out > 5.out
	chmod +x 5.out
	./5.out -u 5.out > 6.out
	chmod +x 6.out
	./6.out -u 6.out > 7.out
	chmod +x 7.out
	./7.out -u 7.out > 8.out
	chmod +x 8.out
	./8.out -u 8.out > 9.out
	chmod +x 9.out
	./9.out -u 9.out > 10.out
	chmod +x 10.out
	./10.out -u 10.out > 11.out
	chmod +x 11.out
	./11.out -u 11.out > 12.out

	echo "Checking the difference between cat.out UNBUFFERED and its 12th itteration."
	echo "Just an output of '0' means it passed:"
	diff cat.out 12.out
	echo $?
	rm 1.out 2.out 3.out 4.out 5.out 6.out 7.out 8.out 9.out 10.out 11.out 12.out
else
	echo "cat.out not found"
fi

