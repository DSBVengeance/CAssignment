#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "blocked_stack_int.h"

struct node
{
	struct node *next;
	int *items;
	int top;
};

struct stack_int_implementation
{
	struct node * top;
	int size;
	int block_size;
};

stack_int * new_blocked_stack_int(int block_size)
{
	stack_int * s = (stack_int *)malloc(sizeof(stack_int));
	s->top = NULL;							//sets top of stack to NULL as there should be no stack yet
	s->size = 0;							//size should be 0 as nothing is in the stack yet
	s->block_size = block_size;					//assign block_size as the block size
}

/****************************************************************************
* ~IsEmpty
* Parameters
* s	- pointer to the header node
* 
* Description:
* Checks to see if the stack is empty. Returns true if it is empty.
*****************************************************************************/

int stack_int_isempty(stack_int *s)
{
	assert(s!=NULL);			//check s is defined before dereferencing
	return (s->size == 0);			//returns true or false depending on whether
}						//the size of the array is 0 or not.

/****************************************************************************
* ~Size
* Parameters
* s	- pointer to the header node
* 
* Description:
* Returns the size of the stack. It is similar to top.
*****************************************************************************/

int stack_int_size(stack_int *s)
{
	assert(s!=NULL);			//check s is defined before dereferencing
	return (s->size);			//return the size of the stack
}

/****************************************************************************
* ~Push
* Parameters
* s	- pointer to the header node
* x	- value to be pushed onto the stack
* 
* Description:
* Checks if the stack is full first. Then pushes an item onto the stack 
* if it isn't full. If it is full it shall display an error message and exit
* the program.
*****************************************************************************/
void stack_int_push(stack_int *s, int x)
{
	assert(s!=NULL);			//check s is defined before dereferencing
	if (stack_int_size(s) == (s->block_size)) {
		struct node->next = new_blocked_stack_int;	//create new block if the size = block size (fuck knows if ive done it right
	}
	else {
		s->top->items[s->top->top] = x;		//points to the next available
							//space in the s->items array.
							//make it equal to x (the next item to be added.)
		(s->top->top)++;			//Go to next free space index
		(s->size)++;				//increment size so that it is correct
	}
}

/****************************************************************************
* ~Pop
* Parameters
* s	- pointer to the header node
* 
* Description:
* Checks if the stack is empty first. Then pops the top item off the stack 
* if it isn't empty. If it is empty it shall display an error message and exit
* the program.
*****************************************************************************/

void stack_int_pop(stack_int *s)
{
	assert(s!=NULL);				//check s is defined before dereferencing
	struct node * n;
	if (stack_int_isempty(s)) {
		printf("stack_int_pop error: stack is currently empty.\n");
		exit(1);
	}
	else {
		/*n = s->top;
		s->top = s->top->next;
		free(n);
		*/
		
		s->top->items[s->top->top]--;
		//(s->top)--;
		(s->size)--;
	}
}

/****************************************************************************
* ~Top
* Parameters
* s	- pointer to the header node
* top	- pointer to the top of the stack
* items	- pointer to the items in the array
* 
* Description:
* Returns the value at the top of the stack. If the stack is empty it will 
* give an error.
*****************************************************************************/

int stack_int_top(stack_int *s)
{
	assert(s!=NULL);			//check s is defined before dereferencing
	if (stack_int_isempty(s)) {
		printf("stack_int_top error: stack is currently empty.\n");
		exit(1);
	}
	else {
		return (s->top->items);
	}
}

/****************************************************************************
* ~Display
* Parameters
* s	- pointer to the header node
* 
* Description:
* Displays the stack.
*****************************************************************************/

void stack_int_display(stack_int *s)
{
	assert(s!=NULL);			//check s is defined before dereferencing
	int i=0;
	printf("Stack<<[ ");
	if (!stack_int_isempty(s)) {
		while (i<((s->top)-1)) {
			printf("%i, ", (s->top->items[i]));
	}
	printf(" ]");
}

/****************************************************************************
* ~Release
* Parameters
* s	- pointer to the header node
* 
* Description:
* Frees up the pointer s.
*****************************************************************************/

void stack_int_release(stack_int *s)
{
	assert(s!=NULL);			//check s is defined before dereferencing
	free(s);				//frees up the pointer
}
