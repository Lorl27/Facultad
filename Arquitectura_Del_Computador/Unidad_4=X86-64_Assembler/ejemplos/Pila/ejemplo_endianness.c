#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint32_t x = 0x41424344;  // 'A' 'B' 'C' 'D'

    printf("Valor de x: 0x%08X\n", x);

    printf("Bytes en memoria: \n");
    unsigned char *p = (unsigned char *)&x;

    for (int i = 0; i < 4; i++)
        printf("%c\n", p[i]);

    printf("\n");

    return 0;
}