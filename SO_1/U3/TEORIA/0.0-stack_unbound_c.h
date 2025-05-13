/*
Concurrente: thread-safe (w/ rc) [NUestro trabajo es asegurar que ocurra eso]
*/

//OBjetivo: stack sin límite (pila==    FILO)

#include <stdlib.h>

// A structure to represent a stack
// here we use a linked list to represent the unbound stack

#ifndef STACK_UNBOND_H
#define STACK_UNBOND_H

struct StackNode{
    int data;
    struct STrackNode* next;
};

struct ConcurrentStack{
    struct StackNode *stack;
    pthread_mutex_t mutex_v;
};



void concurrent_stack_init(struct ConcurrentStack* concurrentStack);

int concurrent_isEmpty(struct ConcurrentStack* concurrentStack);

void concurrent_push(struct ConcurrentStack* concurrentStack, int data);

int concurrent_pop(struct ConcurrentStack* concurrentStack);

int concurrent_top(struct ConcurrentStack* concurrentStack);

void concurrent_stackFree(struct ConcurrentStack* concurrentStack);

#endif /*CURRECT_STACK_H*/