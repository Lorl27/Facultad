#include <stdio.h>

 int main () {
 int * ptr , a =34;
 int * ptr2, b =45;
 ptr2=&b;
 ptr = &a;
 printf ( " %d =?= %d " , a , *ptr ) ;
 return 0;
 }