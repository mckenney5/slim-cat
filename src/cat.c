/* Copyright 2019 (c) Adam McKenney - See LICENSE for details */
/* A way slimmer version of cat without the GNU bloat features that I have never used nor needed */
#include <stdio.h>   //fgetc, putchar, FILE, fopen, perror, fclose, puts, fprintf
#define NAME "cat"   //Program name, can be changed so a user can keep their bloated version of cat
#define HELP "Usage: " NAME " [-hu] [file...]\nWe concatenate files(s) to standard output with less than 50 lines of code.\n\nWith no file, or when file is -, read standard input.\nExamples:\n  " NAME " -h     Displays the help\n  " NAME " -u     Tells the OS that we dont want a buffer (warning may be a lot slower with a large file).\n  " NAME " x - y  Output x's contents, then standard input, then y's contents.\n  " NAME "        Copy standard input to standard output."
static char no_buf = 0; //-u option
void throw_error(const char* extra_msg){
/* function to writes the program name, optionally extra info, then the error to stderr */
	if(extra_msg != NULL) fprintf(stderr, "%s: %s: ", NAME, extra_msg);
	else fprintf(stderr, "%s: ", NAME);
	perror("");
}
void cat(FILE *fp){
/* loops through the file and puts the data one byte at a time into stdout until fread() returns 0 */
	char p = 0;
	if(no_buf) if(setvbuf(fp, &p, _IONBF, 1)) throw_error(NULL); //tell the OS we dont want a buffer
	do 
		if(!fread(&p, 1, 1, fp) || !fwrite(&p, 1, 1, stdout)) break; //if we were unable to read or write, we are done. Size must be 1 for binary files
	while(1);
}
int get_file(const char* file_name){
/* tries to open the user's file, then calls cat() with its file pointer */
	FILE *fp = NULL;
	if(file_name[0] == '-' && file_name[1] == '\0') fp = stdin; //if the user did 'cat -' or 'cat foo - bar'
	else fp = fopen(file_name, "r");

	if(fp == NULL){ throw_error(file_name); return 1; }

	cat(fp);
	fclose(fp);
	return 0;
}
int main(int argc, char *argv[]){
/* takes the args -h for help and -u for unbuffered output */
	size_t i;
	for(i=1; i < argc; i++){ //step through all the vars
		if(argv[i][0] == '-' && argv[i][1] != '\0'){ //if its a command line arg
			if(argv[i][1] == 'h') { puts(HELP); return 0; }
			else if(argv[i][1] == 'u') no_buf = 1; //required by POSIX, turns off buffered output
			else { fprintf(stderr, "%s: unknown command line arg '%s'\n", NAME, argv[i]); return 2;}
		} else break;
	}
	if(argv[i] == NULL) cat(stdin); //if no args
	else for( ; i < argc; i++) get_file(argv[i]); //step through each arg as if it's a file
	return 0;
}

