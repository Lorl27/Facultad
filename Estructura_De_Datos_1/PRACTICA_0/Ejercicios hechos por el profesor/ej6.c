#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READSIZE 10
#define STR(s) STR2(s)
#define STR2(s) #s

// Funcion para leer una linea de la entrada estandar (hasta un '\n') mediante
// scanf. Retorna un puntero a la cadena ingresada. El llamante debe liberar la
// memoria pedida por malloc.
char *getnewline1() {
  char buffer[READSIZE + 1], *linea = NULL;
  scanf("%[^\n]", buffer);
  linea = malloc(sizeof(char) * (strlen(buffer) + 1));
  strcpy(linea, buffer);
  return linea;
}

// Arregla el desbordamiento del buffer.
char *getnewline2() {
  char buffer[READSIZE + 1], *linea = NULL;
  scanf("%9[^\n]", buffer);
  linea = malloc(sizeof(char) * (strlen(buffer) + 1));
  strcpy(linea, buffer);
  return linea;
}

// Arregla el desbordamiento de una manera mas elegante.
char *getnewline3() {
  char buffer[READSIZE + 1], *linea = NULL;
  scanf("%" STR(READSIZE) "[^\n]", buffer);
  linea = malloc(sizeof(char) * (strlen(buffer) + 1));
  strcpy(linea, buffer);
  return linea;
}

// Maneja la linea vacia.
char *getnewline4() {
  char buffer[READSIZE + 1], *linea = NULL;
  int i;
  i = scanf("%" STR(READSIZE) "[^\n]", buffer);
  if (i == 0)
    buffer[0] = '\0';
  linea = malloc(sizeof(char) * (strlen(buffer) + 1));
  strcpy(linea, buffer);
  return linea;
}

// Version no estandar (compilar con -pedantic).
char *getnewline5() {
  char *linea = NULL;
  scanf("%m[^\n]", &linea);
  return linea;
}

// Funcion para leer una linea de la entrada estandar (hasta un '\n') mediante
// fgets. Retorna un puntero a la cadena ingresada. El llamante debe liberar la
// memoria pedida por malloc.
char *getnewline6() {
  char buffer[READSIZE + 1], *linea = NULL;
  fgets(buffer, READSIZE + 1, stdin);
  linea = malloc(sizeof(char) * (strlen(buffer) + 1));
  strcpy(linea, buffer);
  return linea;
}

// Arregla el '\n' final.
char *getnewline7() {
  char buffer[READSIZE + 1], *linea = NULL, *ptr = NULL;
  fgets(buffer, READSIZE + 1, stdin);
  ptr = strchr(buffer, '\n');
  if (ptr != NULL)
    *ptr = '\0';
  linea = malloc(sizeof(char) * (strlen(buffer) + 1));
  strcpy(linea, buffer);
  return linea;
}

// Maneja lineas de longitud arbitraria.
char *getnewline8() {
  char buffer[READSIZE + 1], *linea = NULL, *ptr = NULL;
  size_t largoTotal = 0, largoActual;
  int seguir = 1;
  while (seguir) {
    fgets(buffer, READSIZE + 1, stdin);
    ptr = strchr(buffer, '\n');
    if (ptr != NULL) {
      *ptr = '\0';
      seguir = 0;
    }
    largoActual = strlen(buffer);
    linea = realloc(linea, sizeof(char) * (largoTotal + largoActual + 1));
    strcpy(linea + largoTotal, buffer);
    largoTotal += largoActual;
  }
  return linea;
}

int main() {
  printf("Ingrese una linea de texto: ");
  char *linea = getnewline8();
  printf("Se ingreso: %s\n", linea);
  free(linea);
  return 0;
}
