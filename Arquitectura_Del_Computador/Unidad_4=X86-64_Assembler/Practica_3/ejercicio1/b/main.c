#include <stdio.h>

int main(void){
    unsigned char a=0xFE;
    unsigned char b= -1;
    a+=b;
    b++;
    return a;
}