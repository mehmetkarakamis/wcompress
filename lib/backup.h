int getBackup(char *argv[], char cwd[]) {
	printf("\n");
	// Create folder
	printf("Creating backup folder...\n");

    struct stat buf; // check if exist

    	// If file not exists, then try to create one
    if (stat(backup_folder, &buf) == -1) {
    	// If succeed get cwd and print ok
    	if(mkdir(backup_folder,0775) == 0) {
			printf("\"%s\" folder created successfully on: \n\"%s\"\n", backup_folder, cwd);
    	}
    	else {
    		printf("Error: Backup folder cannot be created, it might be because of write permissions.\n");
    		printf("You may need to run the program with sudo priviliges.");
    		// end
    		return 0;
    	}
    }
	else {
		printf("Error: There is folder named \"%s\" please move the folder.", backup_folder);
		// end
		return 0;
	}

	// Copy files to backup folder
	char *new_file = strcat(backup_folder,argv[2]);
	char copy;

	FILE *original_html = fopen(argv[2], "r");
	FILE *backup_html = fopen(new_file, "w");

	if(original_html == NULL) {
		printf("Error: The HTML page is empty or does not exist, fcompress has been stopped!");
		fprintf(backup_html,"<!-- Encountered with an error -->");
		// end
	}
	else {
		while(fscanf(original_html, "%c", &copy) != EOF) {
			fprintf(backup_html, "%c", copy);
		}
		printf("Getting backup was successfully.\n");
	}
	fclose(original_html);
	fclose(backup_html);

	return 1;
}