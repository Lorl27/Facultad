/* Al poder tomar una fraccion , greddy es optimo!

sea : vi/wi el valor de unidad por peso, lo calculalos para cada objeto
lo ordenamos de mayor a menor
tomamos objtos completos
cuando el siugiente ya no entra entero:tomar la fraccion

TIempo: O(n*log(n)) peor caso. si estaba ordenado: O(n)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int peso;
    int valor;
    double relacion;
}Objeto;

int comparar(const void *a,const void *b){

    Objeto *x=(Objeto*)a;
    Objeto *y=(Objeto*)b;

    if(x->relacion < y->relacion)
        return 1;

    if(x->relacion > y->relacion)
        return -1;

    return 0;
}

double mochilaFraccionaria(Objeto obj[],int n,int W){

    for(int i=0;i<n;i++){
        obj[i].relacion= (double)obj[i].valor/obj[i].peso;
    }

    qsort(obj,n,sizeof(Objeto),comparar);

    double valorTotal=0;
    int bandera=0;

    for(int i=0;i<n && !bandera;i++){

        if(W>=obj[i].peso){ //entra entero
            W-=obj[i].peso;
            valorTotal+=obj[i].valor;
        }else{ //tomar la fraccion
            valorTotal+=obj[i].relacion*W;
            bandera=1;
        }
    }

    return valorTotal;
}

int main(){

    Objeto obj[]={
        {10,60},
        {20,100},
        {30,120}
    };

    printf("%.2lf\n", mochilaFraccionaria(obj,3,50));

    return 0;
}