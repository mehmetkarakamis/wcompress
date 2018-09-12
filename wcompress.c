#include <dirent.h> // scan folder
#include <stdio.h>
#include <stdlib.h> // 
#include <string.h> // strcmp
#include <sys/stat.h> // stat and mkdir
#include <unistd.h> // getcwd

#define MAX 2048
#define MAX_BY2 1024
#define MAX_BY4 512
#define MAX_BY8 256
// argv[0] = program
// argv[1] = file type (html,css,js)
// argv[2] = input file or --all
// argv[3] = compression method (7,4,2,1..)

/* ===================================
Global variables-functions and libs
==================================== */
char version_number[4] = "0.1";
char backup_folder[10] = "fbackup/";
#include "lib/functions.h"
#include "lib/help.h"

#include "lib/backup.h"
#include "lib/css.h"
#include "lib/html.h"
#include "lib/js.h"
/* ===================================
Main
==================================== */
int main(int argc, char *argv[]) {
// Local variables
	int isOk_to_Compress;
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
				isOk_to_Compress = findAll(cwd, fileList, ".html", 0);
				if(isOk_to_Compress) {
					compressHTML(fileList, argv);
				}
				free(fileList);
			}
			// if specific input
			else {
				isOk_to_Compress = checkFile(argv[2], ".html", 0);
				if(isOk_to_Compress) {
					compressHTML(NULL, argv);
				}
			}
			//end
		}
		// CSS //
		else if(strcmp(argv[1], "css") == 0) {
			printf("CSS compression has been started!\n");
			isOk_to_Compress = checkFile(argv[2], ".css", 0);
			if(isOk_to_Compress)
				compressCSS();
			//end
		}
		// JS //
		else if(strcmp(argv[1], "js") == 0) {
			printf("JS compression has been started!\n");
			isOk_to_Compress = checkFile(argv[2], ".js", 0);
			if(isOk_to_Compress)
				compressJS();
			//end
		}
		else if(strcmp(argv[1], "all") == 0) {
				
		}
		else {
			printf("%s not identified as an output file. To get help type:\nwcompressor --help", argv[1]);
			// end
		}
	}
	else {
		printf("Invalid arguments please make sure you read guide, type: \nwcompressor --help");
		// end
	}

	printf("\n");
	return 0;
}