#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "prototypes.h"

void filetrans(char* musicPath){
	/* variable declaration */
	DIR *dp; //pointer to struct
	//DIR *fp;
	struct dirent *ent; // stuct of type dirent pointing to entry
	struct stat st = {0}; // stuct of type buff
	const char s[2] = "-"; // used a delimiter to split the file into the artist data
	const char ch[4] = ".mp3"; // used as a delimiter to check if file is an MP3
	char *token; // a token to capture the split variable 
	char *trackNum; // the track number of the artist
	char *artist; // the name of the artist
	char *year; // the year of the album
	char *album; // the name of the album
	char *trackName; // name of the song
	char libPath[1024]; // file path that is used to mkdir
	char temp[256]; // temp variable to be used in the rename function
	char softLinkYear[256]; // file path for use in setting up the soft link year folders
	char softLinkFinal[256]; // the old file path for the soft link funtion
	char finalFormat[256]; // the new file path for the soft link function
	int ret; // a variable to error check
	int check; // a variable to error check

	/* Open the file, check to see if the directory path is valid */
	dp = opendir(musicPath); // oprn directory
	if(dp == NULL){ // If the directory is equivalent to NUll throw error
		fprintf(stderr, "Error in directory or unspecified argument.\n"); // print error message
		exit(1); // exit program
	}
	
	chdir(musicPath); // change the directory to the argument that was passed
	


	/* While not null read files into */
	while((ent = readdir(dp)) != NULL){
		strcpy(temp, musicPath); // copy the passed argument to temp
		char *artistData= (char *)malloc(256); //allocate size for the array that holds the artists information
		strcpy(libPath, temp); // copy the musicPath and pass it to libPath array
		strcpy(softLinkYear, musicPath); // copy the music path that will be used for the soft links
		strcpy(artistData, ent->d_name); // copy the current directory we are on to artist data

		if(artistData[0] == '.'){ // if when copying the string it picks up the hard link to the parent directory
			continue; //dismiss it and continue back up to the while
		}
		if(check = strrchr(artistData, ch[0]) == NULL){ // if the files doesn't have a .mp3 extension, skip it. 
			continue; //dismiss it and continue back up to the while
		}

		token = strtok(artistData, s); //take artist data and "split" it by the dash
		trackNum = token; // assign the first split to the track number of the artist
		token = strtok(NULL, s); // take the remainder of the data and split it again by the dash
		artist = token; // assign the second split, which is the name of the artist to that variable
		token = strtok(NULL, s); // take remaining string and split by the dasg again
		year = token; // assign third split, which is album year, to that variable
		token = strtok(NULL, s); // take remandier again and split by the dash
		album = token; // the fourth split it the album by the artist, assign it to that variable
		token = strtok(NULL, s); // take the rest of the string and split it and assign it to track name
		trackName = token;

		strcat(softLinkYear, "/"); // appends a back slash to the file path used to pass to softL function
		strcat(softLinkYear, year); // appends the year building the file path used for softL function
		strcat(libPath, "/"); // appends a back slash to the libary path, which has the musicPath already
		strcat(libPath, artist); // appends the artist name to the end of the file path for making directories

		if (stat(libPath, &st) == -1) { // see if the directory exists, if not create it
    		mkdir(libPath, 0777); // use the libPath for the tree and assign 0777(full) permissions to directory
		}

		if(stat(softLinkYear, &st) == -1){ // see if a directory for year exists, if not create it
			mkdir(softLinkYear, 0777); // create directory of year used for soft links
		}

		strcat(libPath, "/"); // appends a back slash to the file year
		strcat(libPath, year); // append the year variable to the file path

		if(stat(libPath, &st) == -1){ // see if the directory exists, if not create it
			mkdir(libPath, 0777); // create a directory using the file path with full permissions
		}

		strcat(libPath, "/"); // append a backslash to the file path
		strcat(libPath, album); // appends the name of the album to the end of the file path

		if((ret = stat(libPath, &st)) == -1){ // check to see if the directory exists for the album
			mkdir(libPath, 0777); // if not then create it with full permissions
		}

		strcat(temp, "/"); // append backslash to temp variable that has music path
		strcat(temp, ent->d_name); // append the file name to the end 
		strcat(libPath, "/"); // take the libpath and append it with a back slash
		strcat(libPath, trackNum); // add the track name to the file path to use with the rename function
		strcat(libPath, " - "); // add a space dash space to the file path
		strcat(libPath, trackName); // append the track name for use with the rename function
		rename(temp, libPath); // rename and move the MP3 files into the correct folder

		if(ret != -1){ // if it already exisits
			continue; // dismiss it and continue to the while
		}

		strcpy(finalFormat, "./"); // copy/overwrite dot backslash to start the new file path for symlink
		strcat(finalFormat, year); // append the year variable to
		strcat(finalFormat, "/"); // append back slash
		strcat(finalFormat, artist); // append artist
		strcat(finalFormat, " - "); // append dash for the format
		strcat(finalFormat, album); // append album name for completion of the new file path string

		strcpy(softLinkFinal, "../"); // append dot dot slash for old file path used for symlink
		strcat(softLinkFinal, artist); // append artist name 
		strcat(softLinkFinal, "/"); // append back slash 
		strcat(softLinkFinal, year); // append year to the file path
		strcat(softLinkFinal, "/"); // append backslash
		strcat(softLinkFinal, album); // append album name

		softL(softLinkFinal, finalFormat); // pass new and old file path to create softlinks

		 free(artistData); // free the memory allocated by artist data
}

 closedir(dp); //close the directory

	}