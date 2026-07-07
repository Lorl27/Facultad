/*

En cada etapa hay 2 posibilidades: me quedo en la misma linea ó me cambio

sea la matriz c[i][j] /
 i=0 ó 1 : linea 1 ó 2
j= 0.. n-1 : etapa de fabricacion

queremos minimizar el tiempo total

subproblemas:
dp1[i]: tiempo minimo para llegar a la maquina i desde linea 1
dp2[i]: desde linea 2.
*/

#define LINEA1 0
#define LINEA2 1

/*
Tiempo  : O(n)
Memoria: O(n)
*/
void lineaEnsamble(int C[2][100], int N, int T){

    int dp1[100], dp2[100];
    int prev1[100], prev2[100];

    dp1[0] = C[0][0]; //primera maquina
    dp2[0] = C[1][0]; //primera maquina

    prev1[0] = LINEA1;
    prev2[0] = LINEA2;

    for(int i=1;i<N;i++){

        // Llegar a línea 1
        if(dp1[i-1] <= dp2[i-1] + T){ //veniamos de la linea 1
            dp1[i] = dp1[i-1] + C[0][i];
            prev1[i] = LINEA1;
        }else{  //veniamos de la 2
            dp1[i] = dp2[i-1] + T + C[0][i];
            prev1[i] = LINEA2;
        }

        // Llegar a línea 2
        if(dp2[i-1] <= dp1[i-1] + T){
            dp2[i] = dp2[i-1] + C[1][i];
            prev2[i] = LINEA2;
        }else{
            dp2[i] = dp1[i-1] + T + C[1][i];
            prev2[i] = LINEA1;
        }
    }

    printf("Tiempo minimo: ");

    int linea;

    if(dp1[N-1] <= dp2[N-1]){
        printf("%d\n", dp1[N-1]);
        linea = LINEA1;
    }else{
        printf("%d\n", dp2[N-1]);
        linea = LINEA2;
    }

    printf("\nCamino (de atras hacia adelante):\n");

    for(int i=N-1;i>=0;i--){
        printf("Etapa %d -> Linea %d\n", i+1, linea+1);

        if(i>0){
            if(linea==LINEA1)
                linea = prev1[i];
            else
                linea = prev2[i];
        }
    }
}