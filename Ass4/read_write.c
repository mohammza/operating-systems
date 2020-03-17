#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define TRILLION 1000000000

/*
*Implement  a  program  to  measure  the  impact  of  application-level buffer  sizes  on  *readtime. This involves writing to and reading from a large file (say, 2 GB). Vary the appli-*cation buffer size (say, from 64 bytes to 4 KB). Use timing measurement routines *(suchasgettimeofdayandgetitimeron UNIX) to measure the time taken for different buffersizes. *Analyze the results and report your findings: does buffer size make a differenceto the overall *write time and per-write time?
*/

int main(int argc, char *argv[]){
	struct timespec start_time, end_time;
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

	// record start time 	
    	if ( clock_gettime(CLOCK_MONOTONIC, &start_time) ){
        	perror("get start_time");
    	}

	//read input and store into the input_buffer
	if( read(fd, input_buffer, offset) == -1){
		perror("Error reading file\n");
		exit(EXIT_FAILURE);
	}

 	// record end time
        if ( clock_gettime(CLOCK_MONOTONIC, &end_time) ){
            perror("get end_time");
        }
	
	//store read time
	float rtime = ((end_time.tv_sec - start_time.tv_sec) * TRILLION +(end_time.tv_nsec - start_time.tv_nsec))*1.0/TRILLION;
	//printf(" Read took %f seconds \n", ((end_time.tv_sec - start_time.tv_sec) * TRILLION +(end_time.tv_nsec - start_time.tv_nsec))*1.0/TRILLION);
	printf("Read took %f seconds \n", rtime);

	//close the input file
	if( close(fd) == -1){
		perror("Error closing file\n");
		exit(EXIT_FAILURE);
	}
	
	//store results of input_buffer to ouput_buffer
	off_t i = 0;
	while( i <= offset){
		output_buffer[i] = input_buffer[i];
		i++;
	}
	


	//open new file
	if( (fd = open("FILE_READ", O_WRONLY | O_CREAT, 0666)) == -1){
		perror("Error opening new file\n");
		exit(EXIT_FAILURE);
	}

	// record start time 	
    	if ( clock_gettime(CLOCK_MONOTONIC, &start_time) ){
        	perror("get start_time");
    	}
	
	//write out_buffer to new file
	if( write(fd, output_buffer, offset) == -1){
		perror("Error writing to new file\n");
		exit(EXIT_FAILURE);
	}
	
	// record end time
        if ( clock_gettime(CLOCK_MONOTONIC, &end_time) ){
            perror("get end_time");
        }
        

	//close new file
	if (close(fd) == -1) {
		perror("Error closing writable file\n");
		exit(EXIT_FAILURE);
	}
	
        float wtime = ((end_time.tv_sec - start_time.tv_sec) * TRILLION +(end_time.tv_nsec - start_time.tv_nsec))*1.0/TRILLION;
        printf("Write took %f seconds \n", wtime);
        
        
        
        //Combined time taken for both operations
        printf("=======================================\n");
        printf("Time taken to read and write: %f seconds\n", rtime+wtime);
	
	return 0;
}
