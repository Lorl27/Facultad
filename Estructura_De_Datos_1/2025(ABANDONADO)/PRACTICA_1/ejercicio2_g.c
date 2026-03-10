// g) Con el objetivo de medir el rendimiento de las funciones reci ́en definidas, agregue un contador
// de operaciones. Es decir, una variable que se incremente cada vez que realizamos una operaci ́on
// elemental. En cada caso, ¿depende este n ́umero de la longitud del arreglo (o de los arreglos) que
// pasamos como argumento?

#include <stdio.h>
#include <stdlib.h>

int contador_op=0;

int string_len(char* str){
    
    if(str==NULL){
        return 0;
    }

    int contador=0;
    contador_op++;
    for(int x=0;str[x]!='\0';x++){
        contador++;
        contador_op++;
    }
    return contador;
}


// idea: str=domingo -> copia=ognimod domingo[0]=copia[ultimo] , domingo[ultimo]=copia[0]
void string_reverse(char *str){
    int longitud =string_len(str);
    contador_op++;
    char *copia=malloc(sizeof(char)*(longitud+1)); //+1 porque string_leng no tiene en cuenta el '\0'
    contador_op++;

    for(int x=0;x<longitud;x++){ //Copiamos la cadena 
        copia[x]=str[longitud-1-x]; //longitud-1 = último valor, x=0 --> copia[0]=str[ultimo]
        contador_op++;
    }

    copia[longitud]='\0';
    contador_op++;

    for(int x=0;x<=longitud;x++){ //Copiamos la cadena 
        str[x]=copia[x];
        contador_op++;
    }
    
    free(copia);
    contador_op++;
    
}

int string_concat2(char *str1, char *str2, int max){
    if(str1==NULL||str2==NULL ||max<=0){
        return 0;
    }

    int len1=string_len(str1);
    contador_op++;
    char *aux=malloc(sizeof(char)*(max+1));
    contador_op++;
    if(aux==NULL){
        printf("fallo en asignar memoria");
        return 0;
    }
    
    int x;
    contador_op++;
    for(x=0;x<max && str2[x]!='\0' ;x++){  //solo copiamos la cant. de caracteres que queremos
        aux[x]=str2[x];
        contador_op++;
    }

    aux[x]='\0';
    contador_op++;
    //ahora debemos incorporar aux al final de str1.


    for(int i=0;aux[i]!='\0';i++){
        str1[len1+i]=aux[i];
        contador_op++;
    }

    str1[len1+x]='\0';
    contador_op++;

    free(aux);  //ya no lo necesitamos.
    contador_op++;
    return x; //cant. caracteres que copiamos

}

int string_compare(char* str1,char* str2){
    
    if(str1==NULL || str2==NULL){
        return -2;
    }

    int len1=string_len(str1);
    contador_op++;
    int len2=string_len(str2);
    contador_op++;

    int max_long;
    contador_op++;
    len1>len2?(max_long=len1):(max_long=len2);
    contador_op++;

    for(int x=0;x<max_long;x++){
        if(str1[x]>str2[x]){
            contador_op++;
            return 1;
        }

        if(str1[x]<str2[x]){
            contador_op++;
            return -1;
        }

        contador_op++;
    }

    return 0;
}

int string_subcadena(char* str1,  char* str2){
    int len1=string_len(str1);
    contador_op++;
    int len2=string_len(str2);
    contador_op++;

    for(int x=0;x<len1;x++){
        contador_op++;
        for(int y=0;y<len2;y++){
            contador_op++;
            if(str1[x]==str2[y]){
                contador_op++;
                return x; //encontrado
            }
        }
    }

    return -1; //no encontrado
}

void string_unir(char *arregloStrings[], int n, char *sep, char *res){
    int index=0;
    contador_op++;

    for(int x=0;x<n;x++ ){ 
        contador_op++;
        char *string=arregloStrings[x]; 

        for(int y=0;string[y]!='\0';y++){
            contador_op++;
            res[index++]=string[y]; //copiamos cada carácter.
        }

        if(x < n-1){ //si no es el último: agregamos sep
            for(int k=0;sep[k]!='\0';k++){
                contador_op++;
                res[index++]=sep[k];
            }
            contador_op++;
        }

        res[index]='\0';
        contador_op++;
    }

    
}

int main(){

    char a[]="mi";
    char b[]="c";
    char *c[]={"chau","hola","domingo"};
    char var[100];

    string_len(a);
    printf("el contador total de op  dsp de string_leng es: %d \n",contador_op);
    string_reverse(a);
    printf("el contador total de op dsp de string_reverse es: %d \n",contador_op);
    string_concat2(a,b,3);
    printf("el contador total de op dsp de string_concat es: %d \n",contador_op);
    string_compare(a,b);
    printf("el contador total de op dsp de string_compare es: %d \n",contador_op);
    string_subcadena(a,b);
    printf("el contador total de op dsp de string_subcadena es: %d \n",contador_op);
    string_unir(c,1,"__",var);
    printf("el contador total de op es: %d \n",contador_op);

    return 0;
}


//RTA: Sí! depende totalmente del nro de de la longitud del arreglo y de los parámetrods que le pasamos
// si hay bucles aninados, sera n*parametros de operaciones.