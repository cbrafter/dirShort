/* dirShort.c

A program that allows the working directory string length to be dynamically
shortened

Author: Craig B. Rafter (https://github.com/cbrafter)
Copyright: 2017, Craig Rafter, MIT License
Date: 28/02/17
Useage: Compile this file using:

	gcc -O3 -Wall -std=c99 dirShort.c -o dirShort 

place the executable in the home directory
ensure you give the executeable any relevant permissions (chmod)

Then add following to ~/.bashrc:

	PS1='\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]$($HOME/dirShort "$(dirs)")\[\033[00m\]\$ '
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ioctl.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


int main(int argc, char **argv){
	/*Check only two inputs*/
	if(argc != 2){
		printf("Error incorrect arguments passed");
		return -1;
	}

	/*Variables*/
	char *path;
	char *newPath;
	size_t pathLen = strlen(argv[1]);
	/*Copy argv[1] i.e. path for use - strtok edits so copy needed */
	path = (char*)malloc(pathLen * sizeof(char));
	newPath = (char*)malloc(pathLen * sizeof(char));
	strcpy(path, argv[1]);

	/*store directory tokens and number of tokens*/
	char dirs[32][256];
	const char delim[] = "/";
	unsigned short ntoken = 0;
	
	struct winsize window; /*Window handle*/
    ioctl(0, TIOCGWINSZ, &window); /*Get window size object*/
   	unsigned short cutoff = max(15, 0.4*window.ws_col - 15); /*point at which file path
   	shouldn't go past*/

	/*Tokenise string into dirs*/
    char *token = strtok(path, delim);
    while(token){
    	strcpy(dirs[ntoken], token);
    	ntoken++;
        token = strtok(NULL, delim);
    }

	if(pathLen < cutoff){
		printf("%s\n", argv[1]);
	}
	else if(ntoken > 1){
		unsigned short i, j, terminator;
		
		/*Leading path characters*/
		if(argv[1][0] == '/'){
			sprintf(newPath, "/");
			terminator = 1;
		}
		else{
			terminator = 0;
		}

		for(i=9; i>0; i-=2){
			/*reterminate string on each pass to prevent the new strings being 
			added on to the old one*/
			newPath[terminator] = '\0';
			for(j=0; j<ntoken-1; j++){
				strncat(newPath, dirs[j], i); /*truncate parent folders to i chars*/
				strcat(newPath, "/"); /*add / between folders except last*/
			}
			/*Add final folder in full*/
			strcat(newPath, dirs[ntoken-1]);
			/*if the string is sufficiently shortened then stop*/
			if(strlen(newPath) < cutoff)
				break;
		}
		printf("%s\n", newPath);
	}
	else{
		printf("%s\n", argv[1]);
	}

	return 0;
}