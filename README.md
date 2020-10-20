slim cat
==========
cat — _still concatenating files and printing on the standard output, just slimmer_

## Description
This is a rewrite of GNU cat where the unused features are removed.

## Project Meta
This software is in a **working stable** state.
The software works as inteded, currenlty bug free.

## License
This code is licensed under the MIT license. See 'LICENSE' for details. 

## Compiling and Testing
This program allows a couple of compiling options.

The simplest way is to compile by `make`

##### Make Options:
* `make`		    : compiles cat.c with the -Ofast flag
* `make debug`		    : adds debugging symbols to the program
* `make install`	    : copies the default cat to cat.bak and moves this cat.out to the /usr/bin file
* `make uninstall`	    : replaces cat with cat.bak from install
* `make unsafe-install`     : moves cat.out to /usr/bin/cat
* `make unsafe-uninstall`   : deletes /usr/bin/cat

## How to contribute
Submit a pull/merge request at the offical repo.

<https://github.com/mckenney5/slim-cat>

