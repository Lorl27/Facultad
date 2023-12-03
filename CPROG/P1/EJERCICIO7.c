// Ejercicio 7. Mediante una única instrucción for y un printf genere la siguiente salida. Em-
// plee 3 variables: una para la cadena de texto, un entero y un char:
// b 5 T
// bu 4 s
// buc 3 R
// bucl 2 q
// bucle 1 P

#include <stdio.h>
#include <string.h>

int main(){
  int entero = 5;
  char letra[] = "TsRqP";
  char cadena[] = "bucle";
  char cadena_m[6];

  for (int x = 0; x < 5; x++){
    cadena_m[x] = cadena[x];
    cadena_m[x + 1] = '\0'; // le vamos añadiendo cada caracter nuevo x bucle
    printf("%s %d %c \n", cadena_m, entero - x, letra[x]);
    }
}