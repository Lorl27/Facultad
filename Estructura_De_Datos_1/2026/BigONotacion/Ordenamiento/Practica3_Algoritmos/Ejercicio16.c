#define MAX 1000


/*

COmo la mochila no esta acotada: podemos usar infinitos obtejos de cada tipo.

sea dp[p]: max valor que podemos conseguir usando una mochila de capacidad p

queremos dp[W] / W: capacidad maxima.

dp[0]=0

para una capacidad p , podemos agregar cualquit tipo de objeto y,
gadstamos wi de capacidad
ganamos vi de valor

dp[p]=max(dp[p-wi]+ vi) / wi<=p

Tiempo: O(n*W)
Memoria:O(W)
*/
int mochilaNoAcotada(int W, int n, int peso[], int valor[]){

    int dp[MAX];

    // caso base
    dp[0]=0;

    for(int capacidad=1; capacidad<=W; capacidad++){
        dp[capacidad]=0;
        for(int i=0;i<n;i++){
            if(peso[i]<=capacidad){
                dp[capacidad]=max(dp[capacidad],dp[capacidad-peso[i]]+valor[i]);
            }
        }
    }


    return dp[W];
}
