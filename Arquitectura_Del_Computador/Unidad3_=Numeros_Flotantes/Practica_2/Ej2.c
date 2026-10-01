// 2) Haga dos funciones o macros de C para extraer la fracci ́on y el exponente de un float sin
// usar variables auxiliares.
// Sugerencia: utilice corrimientos de bits y m ́ascaras. Luego use los tipos definidos en la cabe-
// cera ieee754.h para corroborar.

#include <stdio.h>
#include <stdint.h>

//Float : Precision simple.  k=8(exponente con sesgo) y t=23 bits (significando/fraccion). 
//32 bits totales: 31(s)-30_23(k)-22_0(t)
uint32_t significando(float num){
    uint32_t p= *(uint32_t *)&num;
    int mascara=0b00000000011111111111111111111111;//0x7FFFFF
    return p&mascara;
}

uint32_t signo(float num){
    uint32_t p= *(uint32_t *)&num;
    p>>=31;
    return p&1;
}

uint32_t exponente(float num){
    uint32_t p= *(uint32_t *)&num;
    p>>=23;
    return p&0xFF;
}


// -- Double(64 bits)
// k=11 , t=52
// 63(signo)_62-52(k)_51-0(t)

// Significando: Ocupa los 52 bits de la derecha. Solo aplicamos la máscara.
uint64_t significando_double(double num){
    return (*(uint64_t *)&num) & 0xFFFFFFFFFFFFF; 
}

// Signo: Desplazamos 63 posiciones a la derecha y enmascaramos 1 bit.
uint64_t signo_double(double num){
    return (*(uint64_t *)&num >> 63) & 1;
}

// Exponente: Desplazamos 52 posiciones a la derecha y enmascaramos 11 bits.
uint64_t exponente_double(double num){
    return (*(uint64_t *)&num >> 52) & 0b11111111111; //0x7FF
}


// -- MACRO PARA CUADRUPLE(128 bits)
//k=15, t=112
// 127(signo)_126-112(k)_111-0(t)

#define EXTRAER_SIGNIFICANDO_CUADRUPLE(num) ( (*(unsigned __int128 *)&(num)) & (~((unsigned __int128)0) >> 16) )
#define EXTRAER_SIGNO_CUADRUPLE(num)(  (*(__uint128_t*)&num >> 127 & 1)   )
#define EXTRAER_EXPONENTE_CUADRUPLE(num)( ( *(__uint128_t*)&num>>112 & 0x7FFF))


int main(void) {
    _Float128 x = 15.0f;
    
    printf("Significando crudo: %u\n", EXTRAER_SIGNIFICANDO_CUADRUPLE(x));
    printf("Fraccion cruda (en hexa): 0x%X\n", EXTRAER_EXPONENTE_CUADRUPLE(x));
    
    return 0;
}