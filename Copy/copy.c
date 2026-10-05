#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main (int argc, char *argv[]){
	if (argc < 3){
		printf("Usage: ./copy sourcefile destinationfile");
		exit(EXIT_FAILURE);
	}

	char *source_file = argv[1];
	char *destination_file = argv[2];
	ssize_t num_read;

	char buffer[BUFFER_SIZE];	
	int openFlag = O_CREAT | O_WRONLY | O_TRUNC;


	int source_fd = open(source_file, O_RDONLY);
	if (source_fd < 0){
		printf("Error opening: %s", source_file);
		exit(EXIT_FAILURE);
	}

	int destination_fd = open(destination_file, openFlag, 0666);
	if (destination_fd < 0){
		printf("Error opening: %s", destination_file);
		exit(EXIT_FAILURE);
	}

	while ((num_read = read(source_fd, buffer, BUFFER_SIZE)) > 0){
		if (write(destination_fd, buffer, num_read) != num_read){
			printf("could not write the whole buffer");
			exit(EXIT_FAILURE);
		}
	}

	close(source_fd);
	close(destination_fd);
	printf("Done copying file");
}
