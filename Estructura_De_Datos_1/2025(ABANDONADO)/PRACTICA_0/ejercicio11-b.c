//b

#include <stdio.h>

int main(){
    char *ptr = "hola mundo";
    ptr[0] = 's';  //ERROR , no podemos modificarlo al estar reservada en "only read"
    printf("%s\n", ptr);  //SEGMENTION FAULT
    return 0;
}

// Resultado:
// i. hola mundo
// ii. sola mundo
// iii. Segmentation fault   <-- RTA
// iv. Ninguna de las anteriores

