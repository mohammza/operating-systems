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
	if(argc != 2){
		printf("usage: %s input\n",argv[0]);
		return 1;
	}
	
	int fd;
	off_t offset;
	
	fd = open(argv[1], O_RDONLY);
    	if(fd < 0){
		perror("Error opening file\n");
		exit(EXIT_FAILURE);
	}
    	if ((offset = lseek(fd, 0, SEEK_END)) == -1) {
		perror("Error retrieving file offset");
		exit(EXIT_FAILURE);
	}
	
	char *input_buffer = malloc(sizeof(char) * offset);
	
	// record start time 	
    	if ( clock_gettime(CLOCK_MONOTONIC, &start_time) ){
        	perror("get start_time");
    	}
    	
    	if (read(fd, input_buffer, offset) == -1) {
		perror("Error reading file");
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
	//close read only file
	if (close(fd) == -1) {
		perror("Error closing file");
		exit(EXIT_FAILURE);
	}
	
	//open write file
	if ( (fd = open("FILE_READ", O_RDWR | O_CREAT, 0666)) < 0){
		perror("Error opening writeTo file");
		exit(EXIT_FAILURE);
	}
	
	// record start time 	
    	if ( clock_gettime(CLOCK_MONOTONIC, &start_time) ){
        	perror("get start_time");
    	}
	
	//write to file
	if (write(fd, output_buffer, offset) == -1) {
		perror("Error writing file");
		exit(EXIT_FAILURE);
	}
	
	
	// record end time
        if ( clock_gettime(CLOCK_MONOTONIC, &end_time) ){
            perror("get end_time");
        }
        
        
        //close writeTo file
	if (close(fd) == -1) {
		perror("Error closing file");
		exit(EXIT_FAILURE);
	}
        
        
        float wtime = ((end_time.tv_sec - start_time.tv_sec) * TRILLION +(end_time.tv_nsec - start_time.tv_nsec))*1.0/TRILLION;
        printf("Write took %f seconds \n", wtime);
        
        
        
        //Combined time taken for both operations
        printf("=======================================\n");
        printf("Time taken to read and write: %f seconds\n", rtime+wtime);
        

        
}
