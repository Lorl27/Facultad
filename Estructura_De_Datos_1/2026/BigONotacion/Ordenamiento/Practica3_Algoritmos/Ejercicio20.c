/*

Estrategia Greedy : ejecutar primero lso procesos mañs cortos.

Ordenamos los tiempos de menor a mayor, 
recorremos acumuilando el tiempo
sumar todos los de finalizaciokn
dividir por n.

Tiempo: O(n*log(n))

*/
void planificar(int t[], int n){

    qsort(t,n,sizeof(int),comparar);

    int acumulado=0;
    int suma=0;

    printf("Orden de ejecucion:\n");

    for(int i=0;i<n;i++){
        printf("%d ",t[i]);

        acumulado+=t[i];
        suma+=acumulado;
    }

    printf("\n");

    printf("Tiempo promedio = %.2f\n",(double)suma/n);
}
