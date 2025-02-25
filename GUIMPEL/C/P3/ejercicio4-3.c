// 4. Estructuras:

#include <stdio.h>
#include <stdlib.h>

struct vector {
    float x , y ;
};

struct vector *normal ( struct vector v ) {
            struct vector *ptr=malloc(sizeof(struct vector));

            if(ptr==NULL){return NULL;}

            else{
            ptr->x = v.x;
            ptr->y = v.y;
            return ptr ;
            free(ptr);}
 }

