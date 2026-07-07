/* Resolviendolo en dp:
dp[i] = max suma de un subarreglo que termina en i
tenemos 2 opciones:
1. seguir en el subarreglo terminando en i
2. comerzar uno nuevo en i-1
dp[i]=max(A[i], dp[i-1]+A[i])
Tiempo : O(n)
Memoria : O(1)
*/
int kadane(int A[],int n){

    int mejor=A[0];
    int actual=A[0];

    int inicioActual=0;
    int mejorInicio=0;
    int mejorFin=0;

    for(int i=1;i<n;i++){
        actual=max(A[i],actual+A[i]);
        inicioActual=i;

        if(actual>mejor){
            mejor=actual;
            mejorInicio=inicioActual;
            mejorFin=i;
        }
    }
    
    printf("El intervalo que produjo la suma maxima es: [%d-%d]\n",mejorInicio,mejorFin);

    return mejor;
}