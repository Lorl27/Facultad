/*

A: Sí, porque existe la moneda de 1 centavo
En el peor caso usamos C monedas de 1.
*/

/*
B: 
Estrategia: tomar siempre la moneda de mayor valor / no supere el monto restante.

Tiempo: O(C)
Memoria: O(1)
*/
void cambioGreedy(int C){

    int monedas[] = {20,10,5,1};
    int n = 4;

    for(int i=0;i<n;i++){
        while(C >= monedas[i]){
            printf("%d ", monedas[i]);
            C -= monedas[i];
        }
    }

    printf("\n");
}


/* 

C: No, hay sistemas donde Greedy falla.
Ej: : monedas {1,3,4}, monto 6. 
Greedy da 4+1+1 (3 monedas) y el óptimo es 3+3 (2 monedas).

D:
COn monedas 1,c,...,c^n sí funciona porque cada moneda vale c veces la anterior.

Entonces es mejor 16 que 8+8  (1 vs 2 monedas)
Nunca conviene reemplazar una grande por varias pequeñas
*/