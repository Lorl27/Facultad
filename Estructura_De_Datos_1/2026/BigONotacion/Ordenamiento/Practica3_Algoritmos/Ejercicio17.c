#define MAX 1000

/*

Sea dp[i][c] : max valor usando los primeros i objetoc con capacidad disponivle c


si no tenemos objetos: dp[0][c]=0
si no tenemos capacidad dp[i][0]=0

para el objeto i tenemos 2 opciones:
1. no tomarlo : dp[i-1][c]
2. tomarlo solo si c>=wi , ganamos vi  y usamos la mejor solucon con los objetos anteiores
es decir: dp[i][c]=max(dp[i-1][c], dp[i-1][c-wi]+vi)

Tiempo: O(n*W)
Memoria: O(n*W)

*/
int mochila01(int n, int W, int peso[], int valor[]){
    int dp[MAX][MAX];

    for(int c=0;c<=W;c++){
        dp[0][c]=0;
    }

    for(int i=1;i<=n;i++){
        dp[i][0]=0;
    }

    for(int i=1;i<=n;i++){
        for(int c=1;c<=W;c++){
            if(peso[i-1]<=c){// tomar el objeto
                dp[i][c]=max(dp[i][c],dp[i-1][c-peso[i-1]]+valor[i-1]);
            }else{ //no tomarlo
                dp[i][c]=dp[i-1][c];
            }
        }
    }

    return dp[n][W];
}

/* Mejora tiempo O(W):
for(int i=0;i<n;i++){
    for(int c=W;c>=peso[i];c--){
        dp[c]=max(dp[c],dp[c-peso[i]]+valor[i]);
    }
}
    */

/* Con capacitdad limitada N>1:

SOL 1: Converitr Objetivo A cantidad  4 en : 
A1 - A2 - A4 -A4.
Y luego aplicar mochila 0-1.

SOL 2 (OPTIMA): Descomponer la cantidad en potencias de 2.

Tiempo: O(W * sumatoria de log(N_i))
*/