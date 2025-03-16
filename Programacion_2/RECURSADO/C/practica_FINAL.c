//PRAWCTICA:
//realizar las las sig funciones de <string.h>

#include <stdio.h>
#include <string.h>

//Diseño de datos: buscar si s1 esta en s2. retorna 1 si no está - 0 si está
int contencion(char s1[], char s2[]){
    int len1=strlen(s1);
    int len2=strlen(s2);

    if(len1>len2){
        return 1; //Es más grande->No contenida.
    }

    int x=0;
    while(x<=len2-len1){

        int y=0;
        while(y<len1 && s2[x+y]==s1[y]){
            y++;
        }

        if(y==len1){
            return 0; //FULL CONTENIDA!
        }
        x++;
    } 

    return 1; //No hallada dsp de buscar en todo el array.
}

//DISEÑO DE DATOS: revisar si 2 strings son = o no. retorna 1 si son diferentes  y 0 si son iguales
int comparacion(char s1[],char s2[]){
    int len1=strlen(s1);
    int len2=strlen(s2);

    if(len1!=len2){return 1;} //tienen distitno longitud: no puedewn ser iguales!

    for(int x=0;x<len1;x++){
        if(s1[x]!=s2[x]){
            return 1; //no iguales
        }
    }

    return 0; //iguales!
}

//DISEÑO DE DATOS: concatena s2 al final de s1:
void concatenar(char s1[],char s2[]){
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    for(int x=0;x<len2;x++){
        s1[len1+x]=s2[x];
    }
    s1[len1+len2]='\0';
}

//DISEÑO DE DATOS: Busca en s cualquier ocurrencia de c, siendo c una plaabra compuesta de varias letras, busca letra x letra
void buscar_p(char s[], char c[]){
    int len1=strlen(s);
    int len2=strlen(c);

    int x=0;
    while(x<=len1-len2){
        int y=0;
        while(y<len2 && s[x+y]==c[y]){
            y++;
        }
        if(y==len2){
            printf("%s",&s[x]);
            return; //Se encontro la cadena e  imprime desde ahi
        }
        x++;
    }
    printf("Subcadena no encontrada.\n");
}

//-----------


void test_contencion() {
    char s1[] = "hola";
    char s2[] = "hola soy yo";
    printf("Test contencion: %d\n", contencion(s1, s2)); // Esperado: 0 (contenida)
}

void test_comparacion() {
    char s1[] = "hola";
    char s2[] = "hola";
    char s3[] = "hello";
    printf("Test comparacion: %d\n", comparacion(s1, s2)); // Esperado: 0 (iguales)
    printf("Test comparacion: %d\n", comparacion(s1, s3)); // Esperado: 1 (diferentes)
}

void test_concatenar() {
    char s1[50] = "hola soy yo";
    char s2[] = "Mi mama me mima";
    concatenar(s1, s2);
    printf("Test concatenar: %s\n", s1); // Esperado: "hola soy yoMi mama me mima"
}

void test_buscar() {
    char s1[] = "hola soy yo";
    char s2[] = "soy";
    buscar_p(s1,s2); // Esperado: "soy yo"
}

int main(void){

    test_contencion();
    test_comparacion();
    test_concatenar();
    test_buscar();

    /*
    char s1[]="hola soy yo";
    char s2[]="Mi mama me mima";
    char s3[]="hola soy yoMi mama me mima";

    printf("%s \n\n",strstr(s1,s2)); //NULL: s2 no en s1
    printf("espacio1: ");
    printf("%s \n\n",strcat(s1,s2)); //s2 al final de s1 ("hola soy yoMi mama me mima")
    printf("espacio2: ");
    printf("%d \n\n",strcmp(s1,s3)); //1:son distintas y 0:iguales
    printf("espacio3: ");
    printf("%s \n\n",strchr(s1,'a')); //devuelve a partir de esa coincidencia ("a soy yoMi mama me mima")
    printf("espacio4: ");
    printf("%s \n\n",strpbrk(s1,"ing")); //Imprime "i mama me mima"
    */

    return 0;

}