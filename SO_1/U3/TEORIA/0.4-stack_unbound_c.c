// C program for linked list implementation of stack
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "0.0-stack_unbound_c.h"
#include "0.3-stack_unbound.h"

// source: https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
 

void concurrent_stack_init(struct ConcurrentStack* concurrentStack){
    concurrentStack->stack=NULL;
    pthread_mutex_init(&concurrentStack->mutex_v,NULL);

}

 
int concurrent_isEmpty(struct ConcurrentStack* concurrentStack)
{
    return isEmpty(concurrentStack->stack)->stack;
}

void concurrent_push(struct ConcurrentStack* concurrentStack, int data){

    pthread_mutex_lock(&concurrentStack->mutex_v);
    push(&concurrentStack->stack,data);

    pthread_mutex_unlock(&concurrentStack->mutex_v);
}



int concurrent_pop(struct ConcurrentStack* concurrentStack){
    pthread_mutex_lock(&concurrentStack->mutex_v);
    int data=pop(&concurrentStack->stack);

    pthread_mutex_unlock(&concurrentStack->mutex_v);

    return data;
}


 
int top(struct StackNode* root)
{
    if (isEmpty(root))
        return INT_MIN;
    return root->data;
}

void concurrent_stackFree(struct ConcurrentStack* concurrentStack)
{
  // we free the stack just popping all the elements
  while(!concurrent_isEmpty(&concurrentStack))
  {
	  concurrent_pop(&concurrentStack);
  }
}
