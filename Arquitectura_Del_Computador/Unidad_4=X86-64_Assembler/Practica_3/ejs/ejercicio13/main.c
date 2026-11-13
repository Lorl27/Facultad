#include <stdio.h>

unsigned long fact1(unsigned long);
unsigned long fact2(unsigned long);

int main(void) {
    unsigned long x;
    if (scanf("%lu", &x) == 1) {
        printf("fact1: %lu\n", fact1(x));
        printf("fact2: %lu\n", fact2(x));
    }
    return 0;
}


// gcc -no-pie fact.s main.c -o programa
// ./programa