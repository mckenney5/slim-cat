/* Copyright 2019 (c) Adam McKenney - See LICENSE for details */
/* A way slimmer version of cat without the GNU bloat features that I have never used nor needed */
#include <stdio.h>   //fgetc, putchar, FILE, fopen, perror, fclose, puts, fprintf
#include <string.h>  //strncat
#include <limits.h>  //PATH_MAX (4096 for Linux)
#define HELP "Usage: cat [-hu] [file...]\nWe concatenate files(s) to standard output with less than 55 lines of code.\n\nWith no file, or when file is -, read standard input.\nExamples:\n  cat -h     Displays the help\n  cat -u     Ignored, this program doesn't wait to display output.\n  cat x - y  Output x's contents, then standard input, then y's contents.\n  cat        Copy standard input to standard output."
void cat(FILE *fp){
/* loops through the file and puts the data one byte at a time into stdout until fread returns 0 is found */
	void *p[1];
	int status = 0;
	do {
		status = fread(p, 1, 1, fp);
		if(status != 0) fwrite(p, 1, 1, stdout);
	} while(status != 0);
}
int get_file(char* file_name){
/* tries to open the user file, then calls cat() with its file pointer */
	FILE *fp = NULL;
	if(file_name[0] == '-' && (file_name[1] == '\0' || file_name[1] == 'u')) fp = stdin;
	else fp = fopen(file_name, "r");

	if(fp == NULL){
		char mesg[PATH_MAX+6] = "cat: \0";
		strncat(mesg, file_name, PATH_MAX);
		perror(mesg);
		return -1;
	}
	cat(fp);
	fclose(fp);
	return 0;
}
int command_arg(char* arg){
/* just shows the help arg '-h' */
	if(arg[1] == 'h') puts(HELP);

	else {
		fprintf(stderr, "cat: unknown command line arg '%s'\n", arg);
		return 2;
	}
	return 0;
}
int main(int argc, char *argv[]){
	if(argc < 2) cat(stdin);
	else {
		int i;
		for(i=1; i < argc; i++){
			if(argv[i][0] == '-' && argv[i][1] != '\0' && argv[i][1] != 'u') return command_arg(argv[i]); //if its a command line arg
			else break;
		}
		if(i != 1) i++;
		for(i=i; i < argc; i++) get_file(argv[i]); //step through each arg as if its a file
	}
	return 0;
}

