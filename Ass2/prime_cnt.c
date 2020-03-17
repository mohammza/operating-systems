#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

#define TRILLION 1000000000

int is_prime(int n);	//helper function for counting prime numbers
void *prime_cnt(void *);	//counts the number of prime numbers between an interval

struct thread_data{
    int n;
    int low;
    int high;
};


int main(int argc, char *argv[]){
	
	int high, low;
	struct timespec start_time, end_time;


    	if(argc != 4){
    		printf("Usage: %s low high num_thread\n", argv[0]);
    		return -1;
    	}
    	
    	//parameters are passed in as strings, convert to integers
    	low = atoi(argv[1]);
    	high = atoi(argv[2]);
    	int THREAD_CNT = atoi(argv[3]);
    	
    	pthread_t thread_id[THREAD_CNT];
    	
    	// simple sanity check
	if ( low > high ){
        int i;
		i = low;
		low = high;
		high = i;
	}

	if ( low < 2 )
		low = 2;
		
	//record start time
	if(clock_gettime(CLOCK_MONOTONIC, &start_time)){
		perror("get start_time");
	}
	
	
	//split the job for each thread to do here
	int interval;
	int n_low;
	int n_high;
	
	if(THREAD_CNT > 1){
		interval = (high-low) / THREAD_CNT;	//interval to split the cnt evenly for each 			thread to do work		
		n_low = low;
		n_high = n_low + interval;
        	struct thread_data data[THREAD_CNT];
		


		for(int i = 0; i < THREAD_CNT; i++){
			//sleep(2);
			if(i != 0)
				pthread_join(thread_id[i-1], NULL);
            		data[i].n = i;
			/*printf("Entering thread %d with range: %d to %d\n", data[i].n,
				n_low, n_high);*/
            		data[i].low = n_low;
            		data[i].high = n_high;
			// real work
			pthread_create(&thread_id[i], NULL, prime_cnt, (void *) &data[i]);
			
			//return pthread_join(thread_id[i], NULL); //wait until thread is finished
           		//reincrement
			n_low = n_high + 1;
			n_high = n_low + interval;
			if (n_high > high) n_high = high;
		}
		for (int j = 0; j < THREAD_CNT; j++){
			pthread_join(thread_id[j], NULL); 
		}
	
	}  

	//record end time
	if(clock_gettime(CLOCK_MONOTONIC, &end_time)){
		perror("get end_time");
	}
	
	printf("Counting took %f seconds \n", ((end_time.tv_sec - start_time.tv_sec) * TRILLION + (end_time.tv_nsec - start_time.tv_nsec))*1.0/TRILLION);
	
    	
    	
}


int is_prime(int n){
	int i;

	for(i=2; i<=sqrt(n); i++){
		if(n%i == 0)
			return(0);
	}
	return(1);
}

void *prime_cnt(void *threadarg){
    	struct thread_data *data = (struct thread_data*) threadarg;
      

	int num_prime = 0, i, low, high;
    	low = data->low;
    	high = data->high;

	printf("From Thread %d: ", data->n);
	for (i=low; i<=high; i++){
		if(is_prime(i)){
			num_prime++;
		}
	}
	printf("there are %d prime numbers between %d to %d\n", num_prime, low, high);
	//return(num_prime);
}


