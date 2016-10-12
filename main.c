#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "prototypes.h"

char *musicPath; // captures the command line file path

int main (int argc, char *argv[]){

	if(argc < 1 || argc > 2){ // send error if there ins't a correct amount of arguments
		fprintf(stderr, "Amount of command line arguments does not meet specifications.\n");
		exit(1); // exit program on error
	}

	if(argc == 1){ 	/* if not argument, run organizer on current directory */
		filetrans(".");
	}else{ 	/* other wise pass the file path to the function */
		musicPath = argv[1]; // assign argument to file path
		filetrans(musicPath); // pass the file path to the function
	}

return(0); // return an int
}