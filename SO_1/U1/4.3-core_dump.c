#include <stdlib.h>
#include <stdio.h>

int main() {
    abort();  // Genera SIGABRT -> Core dump
    return 0;
}
