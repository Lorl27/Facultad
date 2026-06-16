#include "ArregloEnteros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Elimine todos los números impares del arreglo, ajustando la capacidad.
void arreglo_enteros_filtrar_pares(ArregloEnteros *arreglo){
    if(arreglo==NULL) return;

    int y=0;

    for(int x=0;x<arreglo->capacidad;x++){
        if(arreglo->direccion[x]%2==0){
            arreglo->direccion[y]=arreglo->direccion[x];
            y++;
        }
    }
    arreglo_enteros_ajustar(arreglo,y);
}

//Implementa una función que reciba dos ArregloEnteros y, 
///devuelva un nuevo ArregloEnteros que contenga los elementos de ambos concatenados.
ArregloEnteros* arreglo_enteros_fusionar(ArregloEnteros *arr1, ArregloEnteros *arr2){
    if(arr1 == NULL || arr2 == NULL) return NULL;

    ArregloEnteros * array=arreglo_enteros_crear(arr1->capacidad+arr2->capacidad);

    int indice=0;
    for(int x=0;x<arr1->capacidad;x++){
        arreglo_enteros_escribir(array,indice,arr1->direccion[x]);
        indice++;
    }
    for(int x=0;x<arr2->capacidad;x++){
        arreglo_enteros_escribir(array,indice,arr2->direccion[x]);
        indice++;
    }

    return array;
}

/*
Crea una función que reciba un string y un carácter delimitador (por ejemplo, un espacio ' ' o una coma ','),
 y devuelva un arreglo dinámico de strings (char ), 
 donde cada posición es una de las palabras separadas.

Ejemplo: string_split("Hola,mundo,C", ',', &cant) debe 
devolver un arreglo con ["Hola", "mundo", "C"] y guardar un 3 en la variable cant.
*/
char** string_split(char* str, char delimitador, int *cantidad_palabras){
    if(str==NULL) return NULL;

    *cantidad_palabras = 1;
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == delimitador) (*cantidad_palabras)++;
    }

    char ** array = malloc(sizeof(char*)* (*cantidad_palabras));

    int inicio_palabra = 0;
    int indice_arreglo = 0;

    for(int i = 0; i <= strlen(str); i++) {
        // Si encontramos el delimitador o el final de la cadena (\0)
        if(str[i] == delimitador || str[i] == '\0') {
            int largo_palabra = i - inicio_palabra;
            
            // Creamos la "caja" para esta palabra (+1 para el \0)
            array[indice_arreglo] = malloc(sizeof(char) * (largo_palabra + 1));
            
            // Copiamos las letras
            strncpy(array[indice_arreglo], &str[inicio_palabra], largo_palabra);
            array[indice_arreglo][largo_palabra] = '\0'; // Sellamos el string
            
            indice_arreglo++;
            inicio_palabra = i + 1; // La próxima palabra empieza después del delimitador
        }
    }

    return array;
}

//Invierte el orden de sus elementos.
void arreglo_enteros_invertir(ArregloEnteros *arreglo){
    if(arreglo==NULL) return;

    for(int x=0;x<arreglo->capacidad/2;x++){
        int temp = arreglo->direccion[x];
        arreglo->direccion[x] = arreglo->direccion[arreglo->capacidad-1-x];
        arreglo->direccion[arreglo->capacidad-1-x] = temp;
    }
}

/*
Haz una función que reciba un string y le quite todos los espacios del principio y del final, pero que deje intactos los del medio.
*/
void string_trim(char *str){
    if(str == NULL) return;
    
    int inicio = 0;
    int fin = string_len(str) - 1; 

    // 1. Avanzar 'inicio' hasta encontrar una letra
    while(str[inicio] == ' ') {
        inicio++;
    }

    // 2. Retroceder 'fin' hasta encontrar una letra
    while(fin >= inicio && str[fin] == ' ') {
        fin--;
    }

    // 3. Mover los caracteres útiles al principio del arreglo
    int i = 0;
    while(inicio <= fin) {
        str[i] = str[inicio];
        i++;
        inicio++;
    }

    // 4. Sellar el string con el terminador nulo
    str[i] = '\0';
}

/*
Haz una función que reciba dos cadenas de caracteres y construya una tercera nueva (usando malloc) 
donde las letras de ambas cadenas se vayan intercalando. 
Si una cadena es más larga que la otra, simplemente se agregan las letras sobrantes al final.
*/
char* string_intercalar(char *str1, char *str2){
    if(str1==NULL || str2==NULL) return NULL;

    int n1=strlen(str1);
    int n2=strlen(str2);
    
    char * str_resultado=malloc(sizeof(char)* (n1 + n2 + 1));
    if(str_resultado == NULL) return NULL;

    int i = 0; // Índice para str1
    int j = 0; // Índice para str2
    int x=0;

    while(i < n1 || j < n2){
        if(i < n1){
            str_resultado[x] = str1[i];
            x++;
            i++;
        }
        if(j < n2){
            str_resultado[x] = str2[j];
            x++;
            j++;
        }
    }

    str_resultado[x]='\0';

    return str_resultado;
}


/*
Supongamos que tu ArregloEnteros está ordenado de menor a mayor, pero tiene números repetidos (por ejemplo: [1, 1, 2, 3, 3, 3, 4, 5, 5]).

El objetivo es crear una función que elimine todos los duplicados in-place (modificando el arreglo original sin usar malloc para crear uno nuevo)
 y que, al finalizar, ajuste la capacidad del arreglo al tamaño exacto de los números únicos que quedaron ([1, 2, 3, 4, 5]).
*/
void arreglo_enteros_compactar(ArregloEnteros *arreglo){
    if(arreglo==NULL) return;

    int y=1;
    for(int x=1;x<arreglo->capacidad;x++){
        if(arreglo->direccion[x]!=arreglo->direccion[y-1]){
            arreglo->direccion[y]=arreglo->direccion[x];
            y++;
        }
        
    }

    arreglo_enteros_ajustar(arreglo,y);
}


/*
Devuelve un NUEVO ArregloEnteros que contenga únicamente los números que sean estrictamente mayores a ese umbral.
 El arreglo original no debe modificarse.
Regla de Oro: El nuevo arreglo debe nacer con la capacidad exacta necesaria. No puedes crear un arreglo gigante y luego achicarlo.
*/
ArregloEnteros* arreglo_enteros_filtrar_mayores(ArregloEnteros *arreglo, int umbral){
    if(arreglo == NULL) return NULL;

    int capacidad_max=0;
    for(int x=0;x<arreglo->capacidad;x++){
        if(arreglo->direccion[x]>umbral) capacidad_max++;
    }

    ArregloEnteros * nuevo=arreglo_enteros_crear(capacidad_max);
    if(nuevo == NULL) return NULL;

    int y = 0;
    for(int x=0;x<arreglo->capacidad;x++){
        if(arreglo->direccion[x]>umbral){
            arreglo_enteros_escribir(nuevo,y,arreglo->direccion[x]);
            y++;}
    }

    return nuevo;
}

/*
// 'nuevos_datos' es un arreglo estático/dinámico normal de C, y 'cant' es su tamaño.

Tu función insertar original agregaba de a 1 elemento. Ahora te piden insertar un lote entero de números nuevos en una posición específica pos.

Regla de Oro: Debes hacer un único realloc (usando tu función arreglo_enteros_ajustar) sumando la cantidad de elementos nuevos,
 y una única mudanza masiva de los elementos viejos hacia la derecha para hacer el "hueco" gigante.

Pista: Si insertas 3 elementos, los datos viejos no se mueven 1 posición a la derecha (i + 1), se mueven 3 posiciones a la derecha (i + 3).
*/
void arreglo_enteros_insertar_lote(ArregloEnteros *arreglo, int pos, int *nuevos_datos, int cant){
    if(pos < 0 || pos > arreglo->capacidad|| arreglo == NULL || nuevos_datos == NULL || cant <= 0) return;
    
    arreglo_enteros_ajustar(arreglo,arreglo->capacidad+cant);
    

    for(int x=arreglo->direccion+cant-1;x>=pos;x--){
        arreglo->direccion[x]=arreglo->direccion[x-cant];
    }

    for(int x=0;x<cant;x++)arreglo_enteros_escribir(arreglo,pos+x,nuevos_datos[x]);
    
}

/*
Se necesita reorganizar los elementos de un arreglo de forma que
 todos los números pares queden al principio (a la izquierda) y
  todos los números impares queden al final (a la derecha).
(IN PLACE)
*/
void arreglo_enteros_particionar(ArregloEnteros *arreglo){
    if(arreglo==NULL) return;

    int par=0;
    int impar=arreglo->capacidad-1;

    while(impar < par){
        // Si el izquierdo ya es par, está bien ubicado. Avanzamos.
        while(impar < par && arreglo->direccion[impar] % 2 == 0) {
            impar++;
        }
        // Si el derecho ya es impar, está bien ubicado. Retrocedemos.
        while(impar < par && arreglo->direccion[par] % 2 != 0) {
            par--;
        }

        // Si se detuvieron y no chocaron, significa que izq encontró un impar 
        // y der encontró un par. ¡Los intercambiamos!
        if(impar < par){
            int temp = arreglo->direccion[impar];
            arreglo->direccion[impar] = arreglo->direccion[impar];
            arreglo->direccion[impar] = temp;
            impar++;
            par--;
        }
    }
}


ArregloEnteros* arreglo_enteros_fusionar_ordenados(ArregloEnteros *arr1, ArregloEnteros *arr2){
    if(arr1==NULL || arr2==NULL) return NULL;

    int cap1=arr1->capacidad;
    int cap2=arr2->capacidad;
    ArregloEnteros * nuevo =arreglo_enteros_crear(cap1+cap2);

    int i = 0; // Índice para arr1
    int j = 0; // Índice para arr2
    int k = 0; // Índice para nuevo

    while(i < cap1 && j < cap2){
        if(arr1->direccion[i] < arr2->direccion[j]){
            nuevo->direccion[k++] = arr1->direccion[i++];
        } else {
            nuevo->direccion[k++] = arr2->direccion[j++];
        }
    }


    while(i < cap1) {
        nuevo->direccion[k++] = arr1->direccion[i++];
    }
    while(j < cap2) {
        nuevo->direccion[k++] = arr2->direccion[j++];
    }

    return nuevo;
}

/*
Tu función eliminar original borraba un solo elemento.
 Ahora necesitas una función que elimine de golpe todo un bloque continuo de elementos,
  desde el índice inicio hasta el índice fin (ambos inclusive).
*/
void arreglo_enteros_eliminar_rango(ArregloEnteros *arreglo, int inicio, int fin){
    if(arreglo == NULL||inicio < 0 || fin >= arreglo->capacidad|| inicio > fin ) return;

    int longitud=fin-inicio+1;
    for(int x=fin+1;x<arreglo->capacidad;x++){
        arreglo->direccion[x-longitud]=arreglo->direccion[x];
    }

    arreglo_enteros_ajustar(arreglo,arreglo_enteros_capacidad-longitud);
}
