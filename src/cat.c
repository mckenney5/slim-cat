/* Copyright 2019 (c) Adam McKenney - See LICENSE for details */
/* A way slimmer version of cat without the GNU bloat features that I have never used nor needed */
#include <stdio.h>   //fgetc, putchar, FILE, fopen, perror, fclose, puts, fprintf
#define NAME "cat"
#define HELP "Usage: " NAME " [-hu] [file...]\nWe concatenate files(s) to standard output with less than 60 lines of code.\n\nWith no file, or when file is -, read standard input.\nExamples:\n  " NAME " -h     Displays the help\n  " NAME " -u     Tells the OS that we dont want a buffer (warning may be a lot slower with a large file).\n  " NAME " x - y  Output x's contents, then standard input, then y's contents.\n  " NAME "        Copy standard input to standard output."
static short no_buf = 0; //-u option
void throw_error(char* extra_msg){
	if(extra_msg != NULL) fprintf(stderr, "%s: %s: ", NAME, extra_msg);
	else fprintf(stderr, "%s: ", NAME);
	perror("");
}
void cat(FILE *fp){
/* loops through the file and puts the data one byte at a time into stdout until fread() returns 0 */
	char p;
	int status = 0;
	if(no_buf) if(setvbuf(fp, &p, _IONBF, 1)) throw_error(NULL); //tell the OS we dont want a buffer
	do {
		status = fread(&p, 1, 1, fp);
		if(status != 0){ 
			fwrite(&p, 1, 1, stdout);
			//if(no_buf) fflush(fp); //-u option
		}
	} while(status != 0);
}
int get_file(char* file_name){
/* tries to open the user file, then calls cat() with its file pointer */
	FILE *fp = NULL;
	if(file_name[0] == '-' && file_name[1] == '\0') fp = stdin;
	else fp = fopen(file_name, "r");

	if(fp == NULL){
		throw_error(file_name);
		return -1;
	}
	cat(fp);
	fclose(fp);
	return 0;
}
int main(int argc, char *argv[]){
	int i;
	for(i=1; i < argc; i++){
		if(argv[i][0] == '-' && argv[i][1] != '\0'){ //if its a command line arg
			if(argv[i][1] == 'h') { puts(HELP); return 0; }
			else if(argv[i][1] == 'u') no_buf = 1;
			else { fprintf(stderr, "%s: unknown command line arg '%s'\n", NAME, argv[i]); return 2;}
		} else break;
	}
	if(argv[i] == NULL) cat(stdin);
	else for(i=i; i < argc; i++) get_file(argv[i]); //step through each arg as if its a file
	return 0;
}

