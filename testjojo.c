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
        s->top = NULL;                                                  //sets top of stack to NULL as there should be no stack yet
        s->size = 0;                                                    //size should be 0 as nothing is in the stack yet
        s->block_size = block_size;                                     //assign block_size as the block size
}
 
/****************************************************************************
* ~IsEmpty
* Parameters
* s     - pointer to the header node
*
* Description:
* Checks to see if the stack is empty. Returns true if it is empty.
*****************************************************************************/
 
int stack_int_isempty(stack_int *s)
{
        assert(s!=NULL);                        //check s is defined before dereferencing
        return (s->size == 0);                  //returns true or false depending on whether
}                                               //the size of the array is 0 or not.
 
/****************************************************************************
* ~Size
* Parameters
* s     - pointer to the header node
*
* Description:
* Returns the size of the stack. It is similar to top.
*****************************************************************************/
 
int stack_int_size(stack_int *s)
{
        assert(s!=NULL);                        //check s is defined before dereferencing
        return (s->size);                       //return the size of the stack
}
 
/****************************************************************************
* ~Push
* Parameters
* s     - pointer to the header node
* x     - value to be pushed onto the stack
*
* Description:
* Checks if the stack is full first. Then pushes an item onto the stack
* if it isn't full. If it is full it shall display an error message and exit
* the program.
*****************************************************************************/
void stack_int_push(stack_int *s, int x)
{
          assert(s!=NULL);
  
  
  //But we need to check if there is space first.... or even if a node exists
  //So... IF there is not a node i.e the top pointer in the stack is still NULL OR the node thats at the ****TOP*** is FULL then we need to create a new node. <--- think more about what i've said
  if (s->top == NULL || s->top->top==s->block_size) {
    
  	struct node *next = (struct node *)malloc(sizeof(struct node));//this right for making a new one? your not making anINT your making a node we dont need that? We are only making 1 node so dont need to do that. ok
    if(next==NULL) {
      printf("stack_int error: memory allocation failed.\n"); // change this message because this is from my code
      exit(1);
    }
    
    //Whats next? We need to set all the values within the node.... items, top & next
    next->items = (int*)malloc(s->block_size * sizeof(int));//same as when we define the things at the top? Yeah items is a POINTER to an array. oh xD
    next->top = 0; // this is an INDEX rather than a memory location so the default for this should be 0 when you create the node you are going to be at index 0 in the array... agree? yup
    next->next = s->top; //this is the link the nodes in the chain so that we dont loose them next should always point to the previous node.. how can we easily get what node was on the TOP?
    s->top = next; //Now we just need to set the s->top value to the new node because this one will be taking over the top spot. Dont need the top because 'next' stores the location to this node already
  } //This about right for push? yup thats it we dont need an else because we've always checked first we have somewhere to insert the element... so there is always space. ok then the 3 steps just stay out of everything im guessing yeh
  //as thats the logic we set out above... step 2 follows the first 3 steps excellent I actually get it now xD I think my other func  
  //There is 3 steps in the logic that is going to be ran EVERY TIME the push function is called Agree your going to do this every time?
  s->top->items[s->top->top] = x;  //1. Add the item to the items array...
  s->size++; //2. Increment the total size of the stack (size)
  s->top->top++; //3. INcrement the top value of the node (the index of the array)
  //yup, so this would be put outside the if statement?  bingo
}
 
/****************************************************************************
* ~Pop
* Parameters
* s     - pointer to the header node
*
* Description:
* Checks if the stack is empty first. Then pops the top item off the stack
* if it isn't empty. If it is empty it shall display an error message and exit
* the program.
*****************************************************************************/
 
void stack_int_pop(stack_int *s)
{
        assert(s!=NULL);                                //check s is defined before dereferencing
  			if (stack_int_isempty(s)) {
                printf("stack_int_pop error: stack is currently empty.\n");
                exit(1);
        } //If you wana be pretty and put this in xD
  
  			// To pop an item I need to:
  			s->top->top--; //1. Decrease the index of the node its in.
  			s->size--;  //2. Decrease the entire size.
  
  			// If the node is empty I need to:
        if(s->top->top == 0) { //If there are no items.. i.e the index is back at 0 because we've popped em all
          
          //We need to create a temp variable so we dont loose any nodes in the process
          struct node * tempNode = s->top; //Set it to the current top node (The one we are popping from and now is empty)
          
          //1. Set the TOP of the STACK to the previous node... where is the previous node value stored? in next? yeah in stacks, top nodes, next.
          s->top = s->top->next; //Resetting the top of the stack to the previous node as we are about to remove a node.
          
          //2. Free the nodes memory including the items.
          //good job we stored the previous node into a temp value so we can free it now... otherwise we would of lost it.
          //But wait, when we create a node, we create two memory allocations? One for the node itself and one for the items in the node.
          free(tempNode->items);
          free(tempNode); 
        }
}
 
/****************************************************************************
* ~Top
* Parameters
* s     - pointer to the header node
* top   - pointer to the top of the stack
* items - pointer to the items in the array
*
* Description:             
* Returns the value at the top of the stack. If the stack is empty it will
* give an error.
*****************************************************************************/
 
int stack_int_top(stack_int *s)
{
        assert(s!=NULL);                        //check s is defined before dereferencing
        if (stack_int_isempty(s)) {
                printf("stack_int_top error: stack is currently empty.\n");
                exit(1);
        }
        else {
          
        /* return (s->top->items); You are returning the pointer to the items array here..... you need to point to a specific item... */
          
        return (s->top->items[(s->top->top) - 1]);
          
        // Items is an array items[] to get the index of the top element you use the top field so s->top->top but thats always going to be 1 ahead so you have to deduct one...
      	// That will work fine nowis it always ahead one due to being top->top ? peacubecause arent arrays usually behind 1? yeah basically the top is how big the array is but arrays start at 0 not 1
        }
}
 
/****************************************************************************
* ~Display
* Parameters
* s     - pointer to the header node
*
* Description:
* Displays the stack.
*****************************************************************************/
 
void stack_int_display(stack_int *s)
{
        assert(s!=NULL);                        //check s is defined before dereferencing
        int i=0;
  
        printf("Stack<<[ ");//because of this
  
        if (!stack_int_isempty(s)) {
          
          struct node * tempNode = s->top;
          while(tempNode != NULL) { //I.E ITS FOUND A NODE...
            
            //How can we found out the amount of items within the node?
            int count = 0;//top but how do we get the top value? //size is the TOTAL amount of items and size is in the STACK declaration not the NODE declaration. ah. 
            for(count = tempNode->top - 1; count >= 0; count--) { // I think you might have to set count to tempNode->top - 1 cant remember but that seems right yeah, im just gonna change whats inside for presentation yeah of course        
            	    printf("%i", tempNode->items[count]); 
            	    if (count != ){
            	    	    printf(", ");
            	    }
            } //yeah well spotted so while count is bigger than or equal to 0 LOOP
            tempNode = tempNode->next; //Set the temp node to the next node... if this is the last item this will be set to NULL and end the loop
          }
          
          /*       
          	1. Loop though all the nodes/blocks that you have created
            	- Within the loop then loop through all the items that are attached to that node (items)
              
            Little Help...
            
            1. Create a temporary pointer to a node and assign it the s->top (what ever node is at the top of the stack)
            2. Then you can process everything within that node.
            3. Set the temportary pointer to the s->top->next (the next node in the chain) 
            4. Loop this until the temporary node is NULL because s->top->next should be set to NULL on the first node.
              
          */
          
        } else {
                printf("EMPTY");
        }
          
        printf(" ]");
          
}
 
/****************************************************************************
* ~Release
* Parameters
* s     - pointer to the header node
*
* Description:
* Frees up the pointer s.
*****************************************************************************/
 
void stack_int_release(stack_int *s)
{
        assert(s!=NULL);                        //check s is defined before dereferencing
        free(s);                                //frees up the pointer
}
