/*

Sea dp[i][j] la distancia minima para transformar los primeros i caracteres de v en los primeros j caracteres de w

Si una palabra esta vacia : dp[0][j]=j 
Para borrar todas las letras: dp[i][0]=i

dp[i][j]=dp[i-1][j-1] 
si son iguales, no hacemos nada

si son dististintos:

1. borrar: dp[i-1][j]+1
2. insertar: dp[i][j-1]+1
3. reemplazar: dp[i-1][j-1]+1

por lo que dp[i][j] es el min de los 3 casos.

*/

#define MAX 105

/*
Tiempo: O(m*n)
Memoria: O(m*n)
*/
int distanciaEdicion(char v[], char w[]){

    int n=strlen(v);
    int m=strlen(w);

    int dp[MAX][MAX];

    for(int i=0;i<=n;i++){
        dp[i][0]=i;
    }

    for(int j=0;j<=m;j++){
        dp[0][j]=j;
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(v[i-1]==w[j-1]){ //son iguales
                dp[i][j]=dp[i-1][j-1];
            }else
                dp[i][j]=min3(dp[i-1][j]+1,dp[i][j-1]+1,dp[i-1][j-1]+1);
        }
    }

    return dp[n][m];
}