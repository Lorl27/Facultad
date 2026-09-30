#include <stdio.h>

int main() {
    char x = 127;
    char y = x + 1;

    printf("x = %hhd\n", x);
    printf("y(signed) = %hhd, y(unsigned)= %hhu\n", y, y);

    return 0;
}
