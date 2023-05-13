#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <linux/limits.h>

void usage(int argc, char** argv);
void find_file(char* dir_name, char* file_to_find);

int main(int argc, char** argv)
{
	DIR* dp;
	struct dirent* dirp;

	// check if this application is being used properly
	usage(argc, argv);

	// check to see if provided directory is accessible
	errno = 0;
	dp = opendir(argv[1]);
	if(dp == NULL) {
		switch(errno) {
			case EACCES:
				fprintf(stderr, "Permission denied\n");
				break;
			case ENOENT:
				fprintf(stderr, "Directory does not exist\n");
				break;
			case ENOTDIR:
				fprintf(stderr, "'%s' is not a directory\n", argv[1]);
				break;	
		}
	}

	// print all files in the directory
	int cnt = 0;
	while((dirp = readdir(dp)) != NULL) {
		fprintf(stdout, "%d: %s", cnt, dirp->d_name);
		if(dirp->d_type == DT_DIR) {
			printf("\t directory");
		}
		printf("\n");
		cnt++;
	}

	// close the directory 
	closedir(dp);


	// now, recursivey traverse the directory structure to find the provided
	// file name
	char* file_to_find = argv[2];
	find_file(argv[1], file_to_find);

	return 0;
}


void usage(int argc, char** argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: ./%s directory_name file_to_find\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

void find_file(char* dir_name, char* file_to_find)
{
    DIR* dp;
    struct dirent* dirp;
    char* path;
    char buffer[PATH_MAX];

    // Open the directory
    dp = opendir(dir_name);
	
    // Loop through all entries in the directory
    while((dirp = readdir(dp)) != NULL) {
        // Ignore "." and ".." directories
        if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            continue;

        // Construct the full path of the current entry
        snprintf(buffer, sizeof(buffer), "%s/%s", dir_name, dirp->d_name);
        path = buffer; //path is just a holder variable

        // If the current entry is a directory, recursively search it
        if(dirp->d_type == DT_DIR) {
            find_file(path, file_to_find);
        }
        // If the current entry is a regular file and its name matches the
        // file we're looking for, print its path(making sure its not a directory)
        else if(dirp->d_type == DT_REG && strcmp(dirp->d_name, file_to_find) == 0) {
            printf("Found %s in %s\n", file_to_find, dir_name);
        }
    }

    // Close the directory
    closedir(dp);
}
