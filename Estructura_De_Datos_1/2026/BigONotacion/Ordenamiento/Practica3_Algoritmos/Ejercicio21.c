/*

Se resulve con DP.

Queremos construir un ABB que minice la sumatorio de i=0 hasta n-1 de
pi*di / pi: prob de buscar clave ki , di:profundidad de esa clave

Las claves con mayor probabilidad deberian quedar más cera de la raíz.

sea dp[i][j] : costo min para costuir un ABB con las claves i hasta j

si el intervalo esta vacio con i>j: dp[i][j]=0

probamos cada clave r del intervalo como raiz:

sea S(i,j)= sumatoria de k=1 hasta j de pk  ; la suma de probabilidad del intervalo

entonces dp[i][j]= min (dp[i][r-1]+dp[r+1][j]+ S(i,j)) con r=i hasta j.

Tiempo: O(n³)
Memoria: O(n²)

para longitud = 1 hasta n
    para cada intervalo (i,j)
        dp[i][j] = infinito

        para r = i hasta j
            costo =
                dp[i][r-1] +
                dp[r+1][j] +
                sumaProb(i,j)

            quedarse con el mínimo

*/