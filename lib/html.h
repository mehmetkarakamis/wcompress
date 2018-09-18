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
	// Check if folder has been created successfully
	int checkFolder = createFolder();

	// Single file
	if(fileList == NULL && checkFolder) {
		// Create an array
		int byte = getSize(argv[2]);
		char *file = (char *)malloc(byte);

		switch(power) {
			case 1: deleteBreaks(argv[2], file);
					break;
			// case 2: deleteComments_HTML();
			// 		break;
			// case 3:
			// 		deleteBreaks(argv[2], file);
			// 		deleteComments_HTML();
			// 		break;
		}
		writeString(argv[2], file);
	}
	// Filelist
	else if (fileList != NULL && checkFolder) {

	}
	printf("HTML compression finished!");
	// end
}