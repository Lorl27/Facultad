#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "0.0-stack_unbound_c.h"
#include "0.3-stack_unbound.h"

struct StackNode *root=NULL;
struct ConcurrentSTack concurrentStack;


void *g(void*ar){
    for(int x=0;x<1000;x++){
        //pthread_lock(&mutex_v);
        concurrent_push(&root,x);
        //pthread_unlock(&mutex_v);
    }

    return NULL;
}

void *f(void*ar){
    thread_config* cfg=(thread_config*) data;
    size_t element_count=cfg->element_count;
    struct ConcurrentSTack* stack=cgf->stack;

    for(int x=0;x<element_count;x++){
  
        concurrent_push(stack,x);

    }
    return NULL;
}

typedef struct thread_config{
    size_t element_count;
    struct CurrentStack* stack; 
}thread_config;

int main(){
    struct  ConcurrenStack concurrentStack;
    concurrent_stack_init(&concurrentStack);
    
    thread_config thread_config={ELEMENT_COUNT,&concurrentStack};

    pthread_t m1,m2;
    pthread_create(&m1,NULL,g,NULL);
    pthread_create(&m1,NULL,g,NULL);

    pthread_join(m1,NULL);
    pthread_join(m2,NULL);

    int cont=0;

    while(!concurrent_isEmpty(&concurrentStack)){
        cont++;
        concurrent_pop(&concurrentStack);
    }

    printf("counter final: %d\n", cont);

    concurrent_stackFree(&concurrentStack);



    return 0;
}

//CSTACK : STACK + LOCK  

//gcc -Wall concurrent_stack_unbond_main.c concurrent_stack_unbond_mutex.c stack_unbon.c -pthead -o concurrent_stack_unbond_mutex_main.c