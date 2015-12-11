
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "blocked_stack_int.h"
/**********************************************************************************/

struct node
{
	struct node *next;			//creates pointer to previous node
	int *data;				//
	int top;				
};
/**********************************************************************************/
struct stack_int_implementation
{
	struct node * top;			//
	int size;
	int block_size;
};
/**********************************************************************************/

stack_int * new_blocked_stack_int(int block_size){
	stack_int * s = (stack_int*)malloc(sizeof(block_size));	//allocates memory for the stack 
	s->top = 0; 								//this makes it so the top of the stack holds no value on creation							
	s->size = 0;									//sets the size of the stack to zero
	s->block_size = block_size;						//assigns block_size and the block size 
	return s;
};

/**********************************************************************************/
int stack_int_isempty(stack_int *s){
	assert(s!=NULL);			//check if s is defined before dereferencing
	return (s->size == 0);			//returns true or false dependant on whether
						//size is zero or not
}
/**********************************************************************************/
int  stack_int_size(stack_int *s){
	assert(s!=NULL);
	return(s->size);		//returns how many items are in the stack

}
/**********************************************************************************/
void stack_int_push(stack_int *s, int x){
	assert(s!=NULL);
	if (s->size == 0 || s->top->top >= (s->block_size)) {
		struct node *next = (struct node *)malloc(s->block_size * sizeof(int));	//creates new block with pointer to previous block
	}
	else {
		s->top->data[s->top->top] = x;		//points to the next available
							//space in the s->items array.
							//make it equal to x (the next item to be added.
		(s->top->top)++;			//Go to next free space index
		(s->size)++; 
	}
}

/**********************************************************************************/
void stack_int_pop(stack_int *s){
	assert(s!=NULL);
	if(stack_int_isempty(s)){
		printf("No value can be popped as stack is empty");
		exit(1);
	}
	else{
	s->top->data[s->top->top]--;
	(s->size)--;
	}

}
/**********************************************************************************/
int  stack_int_top(stack_int *s){



}
/**********************************************************************************/
void stack_int_display(stack_int *s){
	assert(s!=NULL);
	struct node *p = s->top;
	printf("Stack=/n -----");
	if(p!=NULL){		
		while (p->next!=NULL){
			printf("[");
			printf("%i ", p->data);
			p = p->next;
			printf("]/n");
		}
		printf("%i", p->data);
	}
	printf("-----------------");
}
/**********************************************************************************
void stack_int_release(stack_int *s)
{

}*/
