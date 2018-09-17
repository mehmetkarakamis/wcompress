void deleteComments_HTML() {
	printf("Deleting comments..\n");
}
// First parameter is NULL where there is single file, filelist otherwise
// Second parameter is specific input like "index.html"
void compressHTML(char **fileList, char *argv[]) {
	int power;
	if(argv[3] != NULL)
		power = atoi(argv[3]);
	else
		power = 1;

	createFolder();
	// Single file
	if(fileList == NULL) {

		char file_write[MAX_BY4];
		strcpy(file_write, folder);
		strcat(file_write, argv[2]);

		FILE *html_read = fopen(argv[2], "r");
		FILE *html_write = fopen(file_write, "w");
		// Power -- deleting comments
		if(power == 1) {
			deleteBreaks(html_read, html_write, ".html");
		}
		else if(power == 2) {

		}
		else if(power == 3) {

		}
		else if(power == 4) {

		}
		else if(power == 5) {

		}
		else if(power == 6) {

		}
		else if(power == 7) {

		}
		// default
		else {

		}
		fclose(html_read);
		fclose(html_write);
	}
	// Filelist
	else {

	}
}