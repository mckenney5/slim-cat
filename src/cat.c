/* Copyright 2021 (c) Adam McKenney - See LICENSE for details */
/* A way slimmer version of cat without the GNU bloat features that I have never used nor needed */
#include <stdio.h> //fprintf, perror
#include <stdlib.h> //exit
#include <unistd.h> //read, write, close
#include <fcntl.h> //open

#define NAME "slimcat"   //Program name, can be changed so a user can keep their bloated version of cat
#define HELP "Usage: " NAME " [-hu] [file...]\nWe concatenate files(s) to standard output with less than 50 lines of code.\n\nWith no file, or when file is -, read standard input.\nExamples:\n  " NAME " -h     Displays the help\n  " NAME " -u     Tells the OS that we dont want a buffer (warning may be a lot slower with a large file).\n  " NAME " x - y  Output x's contents, then standard input, then y's contents.\n  " NAME "        Copy standard input to standard output."
#define BUFF_SIZE 10000 //a larger buffer trades memory for speed

void throw_error(char* extra_msg, int exit_code){
/* function to writes the program name, optionally extra info, then the error to stderr */
	if(extra_msg != NULL) fprintf(stderr, "%s: %s: ", NAME, extra_msg);
	else fprintf(stderr, "%s: ", NAME);
	perror("");
	if(exit_code) exit(exit_code); //allows non-fatal errors to keep going
}
void cat(int fd, char no_buf){
/* reads from the file descriptor into buf, until zero bytes are read  */
	char buf[BUFF_SIZE];
	size_t r = 0, size = BUFF_SIZE;
	if(no_buf) size = sizeof(char);
	while((r=read(fd, buf, size)) > 0)
		if(write(1, buf, r) != r) throw_error(NULL, 3); //if writing stops for some reason
	if(r == -1) throw_error(NULL, 1); //if read(2) throws an error
}
int get_file(char* file_name, char no_buf){
/* tries to open the user's file, then calls cat() with its file pointer */
	int fd = -1;
	fd = open(file_name, O_RDONLY);
	if(fd == -1) throw_error(file_name, 1);
	cat(fd, no_buf);
	close(fd);
	return 0;
}
int main(int argc, char *argv[]){
	size_t i = 0;
	char no_buf = 0; //-u option
	for(i=1; i < argc; i++){ //step through all the vars
		if(argv[i][0] == '-' && argv[i][1] != '\0'){ //if its a command line arg
			if(argv[i][1] == 'h') { puts(HELP); return 0; }
			else if(argv[i][1] == 'u') no_buf = 1; //required by POSIX, turns off buffered output
			else { fprintf(stderr, "%s: unknown command line arg '%s'\n", NAME, argv[i]); return 2;}
		} else break;
	}
	if(argv[i] == NULL) cat(STDIN_FILENO, no_buf); //if no args
	else for( ; i < argc; i++) get_file(argv[i], no_buf); //step through each arg as if it's a file
	return 0;
}

