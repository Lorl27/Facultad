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

struct StackNode* newNode(int data);

int isEmpty(struct StackNode * root);

void push(struct StackNode ** root, int data);

void pop(struct StackNode ** root);

int top(struct StackNode * root);

void stackFree(struct StackNode * root);

#endif /*CURRECT_STACK_H*/