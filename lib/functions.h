int getSize(char file[]) {
	int i = 0;
	char buff;
	FILE *fp = fopen(file,"r");
	while(fscanf(fp,"%c",&buff) != EOF)
		i++;
	return sizeof(char)*i;
}
int createFolder() {
	struct stat buf;
    // If file not exists, then try to create one
    if (stat(folder, &buf) == -1) {
    	if(mkdir(folder,0775) == 0) {
			printf("\"%s\" folder created successfully!\n", folder);
			return 1;
    	}
    	else {
    		printf("Error: \"%s\" cannot be created, it might be because of write permissions.\n", folder);
    		printf("You may need to run the program with sudo priviliges.\n");
    		printf("Please also check you don't have \"%s\" file or folder in directory.", folder);
    		return 0;
    		// end
    	}
    }
	else {
		printf("Error: There is folder named \"%s\" please move the folder.", folder);
		return 0;
		// end
	}
}
int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}
// First paramater the file
// Second parameter is the type (".css",".html",".js")
// Third is --all so we skip errors and continue (1 = all, 0 else)
int checkFile(char file[], char type[], int all) {
	// check if input file include dot in it
	int i = 0;
	int hasDot = 0;
	while(i < strlen(file)) {
		if(file[i] == '.') {
			hasDot = 1;
			break;
		}
		i++;
	}
	if(hasDot) {
		// if html,css,js
		char *ext = strrchr(file, '.');
		if(strcmp(ext, type) == 0) {
			return 1;
		}
		else {
			if(!all) {
				printf("Error: The input file \"%s\" doesn't have %s extension.", file, type);
			}
			return 0;
		}
	}
	else {
		if(!all) {
			printf("Error: The input file \"%s\" doesn't have %s extension.", file, type);
		}
		return 0;
		// end
	}
}
// First parameter cwd
// Second parameter filelist that this function will fill
// Third is file type
// i if findAll continues recursively else 0
static int ask_sub = 0;
int findAll(char cwd[], char **fileList, char type[], int i) {
	char want_sub;
	while(want_sub != 'y' && want_sub != 'n' && ask_sub == 0) {
		printf("Do you want to compress files in subdirectories (y or n) ? ");
		scanf(" %c", &want_sub);
	}
	ask_sub = 1;
	// Search the directory
	DIR *d;
	struct dirent *dir;
	d = opendir(cwd);
	printf("\nSearching %s\n",cwd);
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
				if(isDirectory(dir->d_name) && want_sub == 'y') {
					char temp_cwd[MAX] = {0};
					strcat(temp_cwd, cwd);
					strcat(temp_cwd, "/");
					strcat(temp_cwd, dir->d_name);
					findAll(temp_cwd, fileList, type, i);
				}
				else if(checkFile(dir->d_name, type, 1)) {
					fileList[i] = (char *)malloc(sizeof(char)*MAX_BY4);
					strcat(*(fileList+i), cwd);
					strcat(*(fileList+i), "/");
					strcat(*(fileList+i), dir->d_name);
					printf("[%d] Found %s\n", i, fileList[i]);
					i++;
				}
			}
		}
		closedir(d);
	}
	return i;
}
void writeString(char cwd[], char string[]) {
	char new_cwd[MAX];
	strcpy(new_cwd, folder);
	strcat(new_cwd, cwd);

	FILE *fp = fopen(new_cwd, "w");
	int length = strlen(string);
	int i = 0;
	while(i < length) {
		fprintf(fp,"%c",string[i]);
		i++;
	}
	fclose(fp);
}
// Delete the breaks from HTML and JS
void deleteBreaks(char source[], char *destination) {
	printf("Deleting breaks...");
	FILE *fp_source = fopen(source,"r");
	char buff[MAX];
	while(fscanf(fp_source, "%s", buff) != EOF) {
		strcat(destination, buff);
		strcat(destination, " ");
	}
	fclose(fp_source);
	printf("Done!\n");
}