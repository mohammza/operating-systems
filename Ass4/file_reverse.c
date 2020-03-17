#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
 * Write a program that reverses the bytes of a file, so that the last byte is
 * now first and the first byte is now last. It must work with an arbitrarily
 * long file, but try to make it reasonably efficient.
*/

int main(int argc, char *argv[]){
	
	int fd;
	off_t offset;
	
	if(argc != 2){
		printf("usage: %s input\n",argv[0]);
		return 1;
	}
	
	//open file
	char *file = argv[1];
	const char *out = argv[2];
	if( (fd = open(file, O_RDONLY)) == -1){
		perror("Error opening file\n");
		exit(EXIT_FAILURE);
	}
	
	//seek to the end
	if( (offset = lseek(fd, 0, SEEK_END)) == -1){
		perror("Error seeking offset\n");
		exit(EXIT_FAILURE);
	}
	
	char *input_buffer = malloc(sizeof(char) * offset);
	char *output_buffer = malloc(sizeof(char) * offset);
	
	//reset file offset
	if( lseek(fd, 0, SEEK_SET) == -1){
		perror("Error resetting file offset\n");
		exit(EXIT_FAILURE);
	}
	
	//read input and store into the input_buffer
	if( read(fd, input_buffer, offset) == -1){
		perror("Error reading file\n");
		exit(EXIT_FAILURE);
	}
	//close the input file
	if( close(fd) == -1){
		perror("Error closing file\n");
		exit(EXIT_FAILURE);
	}
	
	//store results of input_buffer to ouput_buffer
	off_t i = 0;
	while( i <= offset){
		output_buffer[i] = input_buffer[offset - (i+1)];
		i++;
	}
	
	//open new file
	if( (fd = open(file, O_WRONLY, O_TRUNC)) == -1){
		perror("Error opening new file\n");
		exit(EXIT_FAILURE);
	}
	
	//write out_buffer to new file
	if( write(fd, output_buffer, offset) == -1){
		perror("Error writing to new file\n");
		exit(EXIT_FAILURE);
	}
	
	//close new file
	if (close(fd) == -1) {
		perror("Error closing writable file\n");
		exit(EXIT_FAILURE);
	}
	
	
	
	return 0;
}
