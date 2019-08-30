/* Copyright 2019 (c) Adam McKenney - See LICENSE for details */
/* cat but it only reads up to a certain size, and only from stdin */
/* used like: cat /dev/random | ./a.out > test.1mb.o  */

#include <stdio.h>   
#include <stdlib.h>
#include <string.h>
#define DEFAULT_SIZE 1000000
void cat(FILE *fp, size_t size){
/* loops through the file and puts the data one byte at a time into stdout until fread() returns 0 */
	char p = 0;
	size_t i;
	for(i=0; i < size*sizeof(char); i++){
		if(!fread(&p, 1, 1, fp) || !fwrite(&p, 1, 1, stdout)) break; //if we were unable to read or write, we are done. Size must be 1 for binary files
	}
}
int main(int argc, char *argv[]){
	char size_s[11] = {'\0'};
	size_t size = DEFAULT_SIZE;
	if(argc > 2){
		fprintf(stderr, "Usage: cat foo | %s <size>\n", argv[0]);
		return 1;
	} else if(argc == 2) {
		strncpy(size_s, argv[1], 11);
		size_s[10] = '\0';
		size = atol(size_s);
		if(size == 0){
			fprintf(stderr, "%s: Invalid size '%s'\n", argv[0], argv[1]);
			return 1;
		}
	}
	fprintf(stderr, "Writing %ld bytes to stdout\n", size*sizeof(char));
	cat(stdin, size);
	return 0;
}

