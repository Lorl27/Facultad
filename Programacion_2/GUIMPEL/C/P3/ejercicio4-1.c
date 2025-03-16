// 2. Punteros:

#include <stdio.h>
#include <stdlib.h>

int main () {
int * pi = malloc ( sizeof ( int ) ) ;
int * pj = malloc ( sizeof ( int ) ) ;
* pi = 11;
pj = pi ;
printf ( " * pi= %d , * pj= %d " , * pi , * pj ) ;
free ( pj ) ;

if (pj!=pi) {free (pi);}

return 0;
}