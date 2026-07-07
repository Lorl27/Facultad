#define MAX 105


/*

Definimos dp[i][j]: longitud de la LCS entre los primeros i caracteres dwe X  y los primeros j de Y

Si alguna de las 2 secuentcia esta vacia : LCS mide o y entonces dp[i][0]=0 y dp[0][j]=0.


Si los ult. carantes son iguales: forma parte de LCS
dp[i][j]= dp[i-1][j-1]+1

Si son distintos, alguno de lso 2 NO forma parte
dp[i][j]=max(dp[i-1][j],dp[i][j-1])

Tiempo: O(m*n)
Memoria: O(m*n)
*/
void LCS(char X[],char Y[]){

    int m=strlen(X);
    int n=strlen(Y);

    int dp[MAX][MAX];

    for(int i=0;i<=m;i++){
        dp[i][0]=0;
    }

    for(int j=0;j<=n;j++){
        dp[0][j]=0;
    }

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(X[i-1]==Y[j-1])
                dp[i][j]=dp[i-1][j-1]+1;
            else
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }

    printf("Longitud = %d\n",dp[m][n]);

    // reconstrucción

    char lcs[MAX];

    int k=dp[m][n];

    lcs[k]='\0';

    int i=m;
    int j=n;

    while(i>0 && j>0){
        if(X[i-1]==Y[j-1]){
            lcs[k-1]=X[i-1];

            i--; //nos movemos en
            j--; //diagonal
            k--;

        }else if(dp[i-1][j]>=dp[i][j-1]){
            i--; //subimos
        }else{
            j--; //a la izq
        }
    }

    printf("LCS = %s\n",lcs);
}
