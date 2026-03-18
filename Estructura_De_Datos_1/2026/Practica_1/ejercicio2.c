#include <stdio.h>
#include <stdlib.h>

int string_len(char * str){
    int longitud=0;
    for(int x=0;str[x]!='\0';x++){
        longitud+=1;
    }
    return longitud;
}


// longitud = 5
// a  b   c   d   e
// x x+1 x+2 x+3 x+4
// e d c b a
// longitud-1

// iterar hasta la mitad porque sino, revertimos lo revertido!!
void string_reverse(char * str){
    int longitud=string_len(str);
    for (int x=0;x<longitud/2;x++){
        int copy=str[x];
        str[x]=str[longitud-1-x]; //-x necesario porque sino siempre estariamos intercambianod con el ùltimo...
        str[longitud-1-x]=copy;
    }
}

int string_concat(char * str1, char * str2, int max){
    int fin_str1 = string_len(str1); 
    int i = 0;

    while (i < max && str2[i] != '\0') {
        str1[fin_str1 + i] = str2[i]; 
        i++;
    }

    str1[fin_str1 + i] = '\0'; 

    return i; 
}

//se comparan carácter por carácter según el orden del alfabeto
int string_compare(char * str1 , char * str2){
    int contador=0;
    while(str1[contador]!='\0' || str2[contador]!='\0'){
        if(str1[contador]<str2[contador]){ //a<b
            return -1;
        }
        if(str1[contador]>str2[contador]){ //b>a
            return 1;
        }
        contador++;
    }
    return 0; //son iguales.
}

int string_compare_mas_directo(char * str1 , char * str2){
    int i = 0;
    while(str1[i] == str2[i] && str1[i] != '\0') {
        i++;
    }
    if (str1[i] < str2[i]) return -1;
    if (str1[i] > str2[i]) return 1;
    return 0;
}

int string_subcadena( char * str1, char * str2){
    if(str1 == NULL || str2 == NULL) return -1;

    int largo1 = string_len(str1);
    int largo2 = string_len(str2);

    for (int x=0;x<(largo1 - largo2)+1;x++){
       int j = 0;
        // Si hay coincidencia, seguimos mirando las siguientes letras
        while (j < largo2 && str1[x + j] == str2[j]){
            j++;
        }
        // Si el contador 'j' llegó al largo total de str2, ¡encontramos la palabra completa!
        if (j == largo2) {
            return x; 
        }
    }

    return -1; //no encontrada.

}


void string_unir(char * arregloStrings[], int n, char * sep, char * res){
    res[0] = '\0'; // Inicializamos 'res' como una cadena vacía para poder concatenar
    int max_seguro = 1000;

    for(int x=0;x<n;x++){
        string_concat(res,arregloStrings[x],max_seguro);
        
        //separador (excpeto si es la ult palabra)
        if (x<n-1) {
            string_concat(res, sep, max_seguro);
        }
    }

}


int main() {
    printf("=== INICIANDO BATERIA DE PRUEBAS ===\n\n");

    // Prueba A: string_len
    char palabra1[] = "Estructuras";
    printf("A) string_len: La longitud de '%s' es: %d\n", palabra1, string_len(palabra1));

    // Prueba B: string_reverse
    char palabra_invertir[] = "Algoritmos";
    printf("\nB) string_reverse: '%s' invertido es -> ", palabra_invertir);
    string_reverse(palabra_invertir);
    printf("'%s'\n", palabra_invertir);

    // Prueba C: string_concat
    // IMPORTANTE: Le damos un tamaño enorme [50] para que tenga "espacio de sobra" 
    // y no nos tire un error de memoria al concatenar.
    char base[50] = "Hola "; 
    char agregar[] = "Mundo de C";
    int copiados = string_concat(base, agregar, 5); // Solo copiamos 5 letras ("Mundo")
    printf("\nC) string_concat: Despues de copiar %d letras, el resultado es -> '%s'\n", copiados, base);

    // Prueba D: string_compare
    char cmp1[] = "Gato";
    char cmp2[] = "Perro";
    char cmp3[] = "Gato";
    printf("\nD) string_compare:\n");
    printf("   '%s' vs '%s' -> Resultado: %d\n", cmp1, cmp2, string_compare(cmp1, cmp2)); // -1 (G es menor que P en ASCII)
    printf("   '%s' vs '%s' -> Resultado: %d\n", cmp1, cmp3, string_compare(cmp1, cmp3)); // 0 (Son iguales)

    // Prueba E: string_subcadena
    char texto_largo[] = "Buscando a Nemo en el oceano";
    char a_buscar[] = "Nemo";
    char no_existe[] = "Dory";
    printf("\nE) string_subcadena:\n");
    printf("   Buscando '%s' en el texto -> Indice: %d\n", a_buscar, string_subcadena(texto_largo, a_buscar));
    printf("   Buscando '%s' en el texto -> Indice: %d\n", no_existe, string_subcadena(texto_largo, no_existe));

    // Prueba F: string_unir
    // Arreglo de punteros a cadenas (como si fuera un array bidimensional)
    char *palabras[] = {"Manzana", "Naranja", "Banana", "Uva"}; 
    char separador[] = " - ";
    char resultado_final[200]; // Espacio gigante para guardar la union
    
    string_unir(palabras, 4, separador, resultado_final);
    printf("\nF) string_unir:\n");
    printf("   Arreglo unido -> '%s'\n", resultado_final);

    printf("\n=== PRUEBAS FINALIZADAS ===\n");
    return 0;
}


/* G: 
Sí, en todos los casos el número de operaciones elementales depende directamente de la longitud de los arreglos. 
En C, al no saber dónde terminan las cadenas, estamos obligados a recorrerlas paso a paso.


(llamemos N a la longitud del primer arreglo y M a la longitud del segundo)

*string_len(str)
Comportamiento: El bucle for da exactamente una vuelta por cada letra hasta encontrar el \0.
Dependencia: Si la palabra tiene 10 letras, hace 10 operaciones. Si tiene 1 millón, hace 1 millón. 
Su rendimiento es lineal respecto al tamaño de N

*string_reverse(str)
Comportamiento: El bucle for da vueltas exactamente hasta la mitad de la palabra (longitud / 2).
Dependencia: Sigue dependiendo linealmente de N. Si la palabra tiene 100 letras, hace 50 operaciones de intercambio. 
Crece proporcionalmente al tamaño del arreglo.

*string_concat(str1, str2, max)
Comportamiento: Primero llamas a string_len(str1) (eso ya cuesta N operaciones). 
Luego, el while copia letra por letra de str2 (costando hasta M operaciones o el límite max).
Dependencia: Depende de la suma de ambas longitudes (N + M). Si el primer texto es muy largo, tardará mucho solo en encontrar el final antes de empezar a copiar.

* string_compare(str1, str2)
Comportamiento: El while recorre ambas palabras al mismo tiempo. Se detiene apenas encuentra una letra diferente o cuando llega al final de la palabra más corta.
Dependencia: En el mejor caso (la primera letra es diferente), hace 1 operación. En el peor caso (son palabras idénticas), depende de la longitud exacta de la palabra (N).

* string_subcadena(str1, str2)
Comportamiento: ¡Alerta de rendimiento! Aquí tienes un bucle for adentro de otro bucle while. Por cada letra de la frase (N), podrías llegar a comparar todas las letras de la palabra buscada (M).
Dependencia: Altamente dependiente de ambas. En el peor caso (ej: buscar "aaaaB" dentro de "aaaaaaaaaaaaB"), las operaciones se multiplican. 
Haría aproximadamente N*M operaciones. Es el algoritmo más "costoso" de todos los que escribiste.

* string_unir(arregloStrings, n, sep, res)
Comportamiento: Un bucle recorre la cantidad de palabras (K), y por cada iteración, llama a string_concat, la cual (como vimos en el punto C) tiene que recorrer toda la cadena res desde el principio para encontrar el final una y otra vez.
Dependencia: A medida que res se hace más grande, las concatenaciones finales tardan mucho más que las primeras.

*/