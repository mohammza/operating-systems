#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	int pid;
	pid = fork();
	if(pid == 0){
		if(getppid() == 1)
			exit(-1);
			
		printf("Child: parent process ID while parent is running: %d\n", getppid());
		sleep(1);
		printf("Child: parent process ID after parent exits: %d\n", getppid());
		exit(0);
	}
	else if (pid > 0){
		printf("Parent process ID while running is: %d\n", getpid());
		exit(0);
	}
	else{
		perror("Could not create child process\n");
		exit(0);
	}
	return 0;

}
