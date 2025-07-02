/*
	This program works by first prompting the user for the name of the source and destination files.
	Implemented using POSIX API only.
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char *argv[])
{	
	if (argc != 3)
	{
		printf("Error: Two arguments required. <source file> <destination_file>\n");
		return -1;
	}

	char* src_filename = argv[1];
	char* des_filename = argv[2];


	int srcfile_fd = open(src_filename, O_RDONLY);
	int desfile_fd = open(des_filename, O_CREAT | O_RDWR, 0644);

	if (srcfile_fd < 0)
	{
		perror("error opening source file.");
		return -1;
	}

	if (desfile_fd < 0)
	{
		perror("error opening destination file.");
		return -1;
	}


	struct stat src_stat;
	int result = stat(src_filename, &src_stat);
	if (result != 0)
	{
		printf("Something went wrong while stat'ing the source file.\n");
	}


	int size_srcfile = src_stat.st_size;
	char* buffer = (char*) malloc(size_srcfile);

	int num_bytes = read(srcfile_fd, buffer, size_srcfile);
	printf("bytes read: %d\n",num_bytes);

	num_bytes = write(desfile_fd, buffer, num_bytes);
	printf("bytes written: %d\n",num_bytes);


	close(srcfile_fd);
	close(desfile_fd);
	free(buffer);

	return 0;
}