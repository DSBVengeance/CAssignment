#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "blocked_stack_int.h"

struct node
{
	struct node *next;			//creates pointer to previous node
	int *data;				//
	int top;				
};

struct stack_int_implementation
{
	struct node * top;			//
	int size;
	int block_size;
};

stack_int * new_blocked_stack_int(int block_size){
	stack_int * s = (stack_int *)malloc(sizeof(stack_int));	
	s->top = NULL; 							
	s->size = 0;	
	s->block_size = block_size;						
}

int stack_int_isempty(stack_int *s){
	assert(s!=NULL);
	return (s->size == 0);	
}

int  stack_int_size(stack_int *s){
	assert(s!=NULL);
	return(s->size);	
	
}

void stack_int_push(stack_int *s, int x){
	assert(s != NULL);
	if (s->top == NULL || s->top->top == (s->block_size)) {
		struct node *next = (struct node *)malloc(sizeof(struct node));
		if(next==NULL){
			printf("stack_int error:\n");
			exit(1);
		}
		next->data = (int*)malloc(s->block_size * sizeof(int));
		next->top = 0;
		next->next = s->top;
		s->top = next;
	}
	s->top->data[s->top->top] = x;	
	s->size++;	
	s->top->top++;	 
}

void stack_int_pop(stack_int *s){
	assert(s!=NULL);
	if(stack_int_isempty(s)){
		printf("No value can be popped as stack is empty\n");
	}
	s->top->top--;
	s->size--;
	if(s->top->top == 0) {
		struct node * p = s->top;
		s->top = s->top->next;
		free(p->data);
		free(p);
	}
	
}

int stack_int_top(stack_int *s)
{
        assert(s!=NULL);                      
        if (stack_int_isempty(s)) {
                printf("stack_int_top error: stack is currently empty.\n");
        }
        else {       	
        	return (s->top->data[(s->top->top) - 1]);
        }
}

void stack_int_display(stack_int *s){
	assert(s!=NULL);
	int i=0;
	printf("Stack=\n -----\n");
	if(!stack_int_isempty(s)){
		struct node * p = s->top;
		while (p != NULL){
			printf("[");
			int count = 0;
			for(count = p->top - 1; count >= 0; count++){
				printf("%i, ", p->data[count]);
			}
			printf("]\n");
			p = p->next;			
		}
	}
	else{
		printf("EMPTY");
	}
	printf("-----------------");
}

void stack_int_release(stack_int *s)
{
	assert(s!=NULL);
	free(s);
}
