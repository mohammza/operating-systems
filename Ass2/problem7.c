
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/times.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define TRILLION 1000000000

/**
 * Design and run an experiment to measure the CPU time used by _fork_.
 * (You may want to use the system call _times_.) Also report the CPU of the
 * machine you run the experiment.
 */

int main() {
	struct timespec start_time, end_time;
    // record start time 	
    if ( clock_gettime(CLOCK_MONOTONIC, &start_time) ){
        perror("get start_time");
    }	


	if (fork() == 0) {
        // Arbitrary function calls to burn time
		for (size_t i = 0; i < 1000000000; i++) {
			(void) (time(NULL) + time(NULL));
		}
		exit(EXIT_SUCCESS);
	}
	else {
		wait(NULL);
		// record end time
        if ( clock_gettime(CLOCK_MONOTONIC, &end_time) ){
            perror("get end_time");
        }	
		printf(" Fork took %f seconds \n", ((end_time.tv_sec - start_time.tv_sec) * TRILLION +      (end_time.tv_nsec - start_time.tv_nsec))*1.0/TRILLION);
	}

	return 0;
}
