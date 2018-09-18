#include <dirent.h> // scan folder
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/stat.h> // stat and mkdir
#include <unistd.h> // getcwd

#define MAX 2048
#define MAX_BY2 1024
#define MAX_BY4 512
#define MAX_BY8 256
// argv[0] = program
// argv[1] = file type (html,css,js)
// argv[2] = input file or --all (index.html)
// argv[3] = compression method (7,4,2,1..)

/* ===================================
Global variables-functions and libs
==================================== */
char version_number[4] = "0.1";
char folder[10] = "wcompress/";
#include "lib/functions.h"
#include "lib/help.h"

#include "lib/css.h"
#include "lib/html.h"
#include "lib/js.h"
/* ===================================
Main
==================================== */
int main(int argc, char *argv[]) {
// Local variables
	int is_ok;
	char cwd[MAX];
	getcwd(cwd, sizeof(cwd));

	char **fileList = (char **)malloc(sizeof(char *)*MAX_BY4);
// Welcoming
	printf("Welcome to wcompress!\n");
	printf("Version: %s", version_number);
	printf("\n\n");
// Check for argcs
	if(argc == 1) {
		printf("Please specify file type that you want to compress, to get help type:\nwcompressor --help");
		// end
	}
	else if (argc == 2) {
		if(strcmp(argv[1], "--help") == 0)
			helpPage();
		else
			printf("Please specify input file. To get help type:\nwcompressor --help");
		// end
	}
	else if (argc == 3 || argc == 4) {
		// HTML //
		if(strcmp(argv[1], "html") == 0) {
			printf("HTML compression has been started!\n");
			// if all selected
			if(strcmp(argv[2], "--all") == 0) {
				is_ok = findAll(cwd, fileList, ".html", 0);
				if(is_ok >= 1) {
					compressHTML(fileList, argv);
				}
				free(fileList);
			}
			// if specific input
			else {
				is_ok = checkFile(argv[2], ".html", 0);
				if(is_ok) {
					compressHTML(NULL, argv);
				}
			}
			//end
		}
		else {
			printf("%s not identified as an input file. To get help type:\nwcompressor --help", argv[1]);
			// end
		}
	}
	else {
		printf("Invalid arguments please make sure you read the guide, type: \nwcompressor --help");
		// end
	}
	printf("\n");
	return 0;
}