#define MAX 100
#include <limits.h>

/*
dp[i][j]: costo min para multiplicar desde Ai hasta Aj

Si hay una sola matriz: no hay que multiplizar nada -> dp[i][i]=0

Si queremos multiplar Ai Aj , demos elegir donde partir
por lo que el costo sera : costo izq + costo der + costo der* costo izq
es decir: dp[i][j]= min ( dp[i][k] + dp[k+1][j] + p_(i-1)*p_k*p_j) donde i<=k<j


TIempo: O(n^3)
Memoria: O(n^2)
*/
int matrixChain(int p[],int n){

    int dp[MAX][MAX];

    for(int i=1;i<=n;i++){
        dp[i][i]=0;
    }

    for(int len=2;len<=n;len++){
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;

            dp[i][j]=INT_MAX;

            for(int k=i;k<j;k++){
                int costo=dp[i][k]+   dp[k+1][j]+p[i-1]*p[k]*p[j];
                
                if(costo<dp[i][j])
                    dp[i][j]=costo;
            }
        }
    }

    return dp[1][n];
}

