/*

A:

Tenemos una matiz t_ij / es la tasa de cambio.

Para cada par de monedas (Mi,Mj) queremos encontrar el camino cuya tasa sea máquima

mejor(i,j)= max(mejor(i,j), mejor(i,k)Xmejor(k,j))

dp[i][j]: mejor tasa posible para cambiar de i a j.

Es lo mismo que ej6, solo que multiplicamos y maximizamos
en vez de sumar y minimizar.

Tiempo: O(n^3)
Memoria: O(n^2)
*/
void mejorTasa(int n, double t[n][n]){
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(t[i][j] < t[i][k] * t[k][j]){
                    t[i][j] = t[i][k] * t[k][j];
                }
            }
        }
    }
}


/*

B:

El algoritmo en sì no cambia, solo la mutliplicacion : tij -> tij(1-p) / p es la comisión.

C:
2 caminos con la misma tasa pueden tener != comisión

Ahora el problema si cambia, ya que ahora esta el dinero obtenido y la cant. de cambios para tener en cuenta
un camino con màs trasnscciones puede quedar descartado porque a pesar de tener mejores tasas, la comision acumulada lo hace poco rentable.*/
