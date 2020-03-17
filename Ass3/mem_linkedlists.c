/*
	Name: Mohammed Hamza
	Fun with Process and Memory
	Managing Free Memory with Linked List : Then test your program using the following memory 		use pattern by printing out the linked list after each memory use or free event: there are 		in total 10 memory units, and the memory's use pattern is as follows: A (use 2		    units),B(use 3 units), C (use 4 units), D (free 3 units of B), E (use 1 unit), F (free 4 units of 		C), G (free 2 units of A) and H (use 5 units). 


*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


struct node{
	int size;
	char process;
	struct node* next;
};

struct node* getNode(int n){
	struct node *temp = (struct node *) malloc(sizeof(struct node));
	temp->size = n;
	temp->process = '\0';	// '\0' represents a blank char
	temp->next = NULL;
	return temp;
}

void freeNode(struct node *head, char process){
	struct node *temp = head;
	while(temp != NULL){
		if(temp->process == process){
			temp->process = '\0';
			break;
		}
		temp = temp->next;
	}
}

void allocateMem(struct node *head, int size, char process){
	struct node *temp = head;
	bool flag = false;
	while(temp!=NULL){
		if(temp->process == '\0'){
			if(temp->size == size){
				temp->process = process;
				flag = true;
				break;
			}
			else if(temp->size > size){
				struct node *newNode = getNode(temp->size - size);
				temp->size = size;
				newNode->next = temp->next;
				temp->next = newNode;
				temp->process = process;
				flag = true;
				break;
			}
		}
		temp = temp->next;
	}
	if(!flag){
		printf("\n");
		printf("Current process cannot be accomated\n");
		return;
	}
}

void printMem(struct node *head){
	struct node *temp = head;
	printf("\n");
	while(temp != NULL){
		if(temp->process == '\0')	//If at the end of list, unused memory
			printf("Free memory: %d units, ",temp->size);
		else				//Else print process and units being used
			printf("%c: %d units, ",temp->process,temp->size);
		
		temp = temp->next;
	}


}

int main(int argc, char *argv[]){
	struct node *head = getNode(10);
	printMem(head);
	printf("\n======Begin A=========");
	allocateMem(head,2,'A');	//A uses 2 units
	printMem(head);			
	printf("\n======End A===========\n");
	printf("\n======Begin B=========");
	allocateMem(head,3,'B');	//B uses 3 units
	printMem(head);
	printf("\n======End B===========\n");
	printf("\n======Begin C=========");
	allocateMem(head,4,'C');	//C uses 4 units
	printMem(head);
	printf("\n======End C===========\n");
	printf("\n======Begin D=========");
	freeNode(head,'B');		//D frees 3 units of B
	printMem(head);
	printf("\n======End D===========\n");
	printf("\n======Begin E=========");
	allocateMem(head,1,'E');	//E uses 1 unit
	printMem(head);
	printf("\n======End E===========\n");
	printf("\n======Begin F=========");
	freeNode(head,'C');		//F frees 4 units of C
	printMem(head);
	printf("\n======End F===========\n");
	printf("\n======Begin G=========");
	freeNode(head,'A');		//G frees 2 units of A
	printMem(head);
	printf("\n======End G===========\n");
	printf("\n======Begin H=========");
	allocateMem(head,5,'H');	//H uses 5 units
	printf("======End H===========\n");
	return 0;



}
