
/* This is a sample program to demo how to read various parameters from command line
   The program is as, and the author is not responsible for any damages it may cause ( it won't )
   You may use this program in anyway you like
   by Lihao Xu, all rights reserved, Feb. 14, 2020
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int argv_cnt = 1;

void print_help(char **argv)
{

	printf("use: %s -e|-d -k key -in input -out output\n", argv[0]);
	exit(1);
}


void handle_option(int argc, char **argv)
{

	switch(argv[argv_cnt][0]){
		case '-':

			if (strcmp(argv[argv_cnt]+1,"e") == 0 ){
				printf(" encoding = 1 \n");
			}
			else if (strcmp(argv[argv_cnt]+1,"d") == 0 ){
				printf(" decoding = 1 \n");
			}
			else if (strcmp(argv[argv_cnt]+1,"key") == 0 ){
				argv_cnt++;
				if ( argv_cnt == argc )
					print_help(argv);
				printf(" key = %s \n", argv[argv_cnt]);
			}
			else if (strcmp(argv[argv_cnt]+1,"in") == 0 ){
				argv_cnt++;
				if ( argv_cnt == argc ){
					printf("no input is specified\n");
				 	print_help(argv);
				}
				printf(" input = %s \n", argv[argv_cnt]);
			}
			else if (strcmp(argv[argv_cnt]+1,"out") == 0 ){
				argv_cnt++;
				if ( argv_cnt == argc )
					print_help(argv);
				printf(" output = %s \n", argv[argv_cnt]);
			}
			else if (strcmp(argv[argv_cnt]+1,"help") == 0 ){
				print_help(argv);
			}
			else {
				printf("%s: unknown option\n", argv[argv_cnt]);
				print_help(argv);
			}

			argv_cnt++;
			break;

		default:
			printf("%s: unknown option\n", argv[argv_cnt]);
			print_help(argv);
			break;
	}

	return;

}


int main(int argc, char **argv)
{

	if ( argc == 1 )
		print_help(argv);

	while( argv_cnt < argc )
		handle_option(argc, argv);

	return(0);

}

