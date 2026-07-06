/*

A:
Para llegar desde la esquina sup. izq hata la inf. der debemos hacer: M-1 hacía abajo y, N-1 hacía la derecha
Movimientos = M-1 + N-1 = M+N -2 .

¿En cuáles de éstos pongo los movimientos hacía abajo?
Rta= (movimentos) C (M-1)

Si M=N, quedaría: (2N-2)C(N-1) lo que resulta en (4^n)/ sqrt(n) 
*/

//B:
// Como M=N=1000, No recorremos todos los caminos.

#define MAX 1000

//Tiempo O(M*N)
// Memoria O(M*N)
// Sea dp[i][j] el costo minimo hasta pos (i,j),
// dp[i][j]= P[i][j] + min ( d[i-1][j], dp[i][j-1]) con P costo casilla.
int costoMinimo(int P[][MAX], int M, int N){

    int dp[MAX][MAX];

    dp[0][0] = P[0][0];  //Esquina inicial

    for(int i=1;i<M;i++){  //Por cada fila, vamos a la izquierda
        dp[i][0]=dp[i-1][0]+P[i][0];
    }

    for(int j=1;j<N;j++){ //Por cada columna, bajamos.
        dp[0][j]=dp[0][j-1]+P[0][j];
    }


    for(int i=1;i<M;i++){

        for(int j=1;j<N;j++){

            if(dp[i-1][j] < dp[i][j-1])
                dp[i][j]=dp[i-1][j]+P[i][j];
            else
                dp[i][j]=dp[i][j-1]+P[i][j];
        }
    }

    return dp[M-1][N-1];
}



//C: No, ya que no volvemos para atrás.

//D:

// Tiempo O(M*N)+ O(M+N) = O(M*N)
//Memoria O(M*N) + O(M*N) = O(M*N)
//Mientras llenamos dp, guardamos desde dónde llegamos,
//El camino quedará alrevñes
int costoMinimoCamino(int P[][MAX], int M, int N,char padre[][MAX]){

    int dp[MAX][MAX];

    dp[0][0] = P[0][0];  //Esquina inicial

    for(int i=1;i<M;i++){  //Por cada fila, vamos a la izquierda
        dp[i][0]=dp[i-1][0]+P[i][0];
         padre[i][0] = 'U';
    }

    for(int j=1;j<N;j++){ //Por cada columna, bajamos.
        dp[0][j]=dp[0][j-1]+P[0][j];
        padre[0][j] = 'L';
    }


    for(int i=1;i<M;i++){

        for(int j=1;j<N;j++){

            if(dp[i-1][j] < dp[i][j-1]){
                dp[i][j]=dp[i-1][j]+P[i][j];
                padre[i][j]='U';
            }
            else{
                dp[i][j]=dp[i][j-1]+P[i][j];
                padre[i][j]='L';
            }
        }
    }

    return dp[M-1][N-1];
}


void reconstruirCamino(char padre[][MAX], int M, int N){
    int i = M-1, j = N-1;
    while(i > 0 || j > 0){
        printf("(%d,%d) <- ", i, j);
        if(padre[i][j] == 'U') i--;
        else j--;
    }
    printf("(0,0)\n");
}
