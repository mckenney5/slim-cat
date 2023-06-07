slim cat
==========
slimcat — _still concatenating files and printing on the standard output, just slimmer_

## Description
This is a rewrite of GNU cat where the unused features are removed.

## Project Meta
This software is in a **working stable** state.
The software works as intended, _currenlty_ bug free.
No new features will be added. Feel free to send in bug reports as needed

## License
This code is licensed under the MIT license. See 'LICENSE' for details. 

## Compiling and Testing
This program allows a couple of compiling options.

The simplest way is to compile by `make`
You can test cat by running `cd scripts && ./full_test.sh`
This will benchmark your systems cat, against mine.

##### Make Options:
* `make`		    : compiles cat.c with the -Ofast flag
* `make debug`		    : adds debugging symbols to the program
* `make install`            : moves slimcat to the /usr/bin dir and moves the man page
* `make uninstall`          : deletes slimcat and its man page
* `make unsafe-install`	    : copies the default cat to cat.bak and moves this cat.out to the /usr/bin file
* `make unsafe-uninstall`    : replaces cat with cat.bak from install

## How to contribute
Submit a pull/merge request at the offical repo.

<https://github.com/mckenney5/slim-cat>

