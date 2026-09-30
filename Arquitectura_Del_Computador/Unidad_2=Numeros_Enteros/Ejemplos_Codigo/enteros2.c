#include <stdio.h>
int main (){
char a =127;
printf (" %hhd %hhu\n",a,a);
a =++ a;
printf (" %hhd %hhu\n",a,a);
unsigned char b =128;
printf (" %hhd %hhu\n",b,b);
b =++ b;
printf (" %hhd %hhu\n",b,b);
return 0;
}