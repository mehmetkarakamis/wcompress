int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}
// First paramater the file
// Second parameter is the type (".css",".html",".js")
// Third is --all so we skip errors and continue (1 = all)
// returns 1 if file pairs else 0
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
// Second parameter filelist that this function will fill.
// Third is file type
// i if findAll continues recursively else 0
int findAll(char cwd[], char **fileList, char type[], int i) {
	char want_sub;
	while(want_sub != 'y' && want_sub != 'n') {
		printf("Do you want to compress files in subdirectories at\n-> %s\n", cwd);
		printf("If there is no subdirectories you may simply press \"n\" skip.\n");
		printf("(y or n) ");
		scanf(" %c", &want_sub);
	}
	// Search the directory
	DIR *d;
	struct dirent *dir;
	d = opendir(cwd);
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
				if(isDirectory(dir->d_name)) {
					// maybe dynamic memory allocation, later?
					char temp_cwd[MAX];
					strcat(temp_cwd,cwd);
					strcat(temp_cwd,"/");
					strcat(temp_cwd, dir->d_name);
					findAll(temp_cwd, fileList, type, i);
				}
				else if(checkFile(dir->d_name, type, 1)) {
					fileList[i] = (char *)malloc(sizeof(char)*MAX_BY4);
					strcat(*(fileList+i), cwd);
					strcat(*(fileList+i), "/");
					strcat(*(fileList+i),dir->d_name);
				}
				i++;
			}
		}
		closedir(d);
	}
}