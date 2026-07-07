/*

La solución completa tiene 2^n -1 movimientos, 

El movimiento mas grande ocurre en 2^(n-1) 

Si queremos el movimiento i:

si i=2^(n-1)  , mover disco N

si i<2^(n-1) , el movimiento esta en la primera llamda recursiva
es decir Hanoi(N-1)

si i>2^(n-1) , en la segunda. 
Pero debemos descontar los anteriores: i= i - 2^(n-1) 
y buscar en Hanoi(N-1)

Tiempo: O(n) <-> O(log(m)) con m= 2^(n-1)
Memoria: O(n) , ya que es recursiva. 
La iterativa tendra O(1)...
*/
void hanoiPaso(int n, long long paso, char origen, char auxiliar, char destino) {

    if(n == 1){
        if (paso == 1) printf("Mover disco 1 de %c a %c\n", origen, destino);
        return;
    }

    long long mitad = 1LL << (n - 1);   // 2^(n-1)

    if(paso < mitad){
        hanoiPaso(n - 1, paso,origen, destino, auxiliar);
    }
    else if (paso == mitad){
        printf("Mover disco %d de %c a %c\n",n, origen, destino);
    }
    else {
        hanoiPaso(n - 1,paso - mitad,auxiliar, origen, destino);
    }
}