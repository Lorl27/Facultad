/*

A: La estrategia de Ordenar por tamaño creciente e ir agregando mientras entren.
funciona , como quedemos guardar la mayor cantidad conviene empezar por los más chicos.

TIempo: O(n*log(n))
*/
void maxArchivos(int archivos[], int n, int capacidad){

    qsort(archivos,n,sizeof(int),comparar);

    int usados=0;
    int cantidad=0;

    printf("Archivos elegidos: ");

    for(int i=0;i<n;i++){
        if(usados+archivos[i]<=capacidad){
            usados+=archivos[i];
            cantidad++;
            printf("%d ",archivos[i]);
        }
    }

    printf("\nCantidad = %d\n",cantidad);
    printf("Espacio usado = %d\n",usados);
}

/*

B: Queremos maximizar el espacio cupado ,
ordenador de mayor a menor e ir metiendo no funciona
Con greedy :
Archivos: 8 - 6 -4
Greedy: 8. no entra ninguno mas
DP: 6+4=10.

Este problema deja de ser greedy y se vuelve el de la Mochila 0/1

sea dp[i][j]: max espacio ocupado usando los primeros i archivos y capacidad j

si el archivo no entra: dp[i][j]=dp[i-1][j]
si entra: dp[i][j]=max ( dp[i-1][j], dp[i-1][j-l_i]+l_i)

TIempo: O(n*d) / d: capacidad del disco.
*/