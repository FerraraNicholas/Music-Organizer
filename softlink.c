#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "prototypes.h"

void softL(char* softLinkFinal, char* finalFormat){

	int ret; // error check variable

	if(ret = symlink(softLinkFinal, finalFormat) != 0){ // create a softlink 
		fprintf(stderr, "No symlink establish.\n"); // if it isn't create send error
		exit(1); // exit program on error

	}

}