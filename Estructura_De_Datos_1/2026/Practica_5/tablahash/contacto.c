#include "contacto.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Contacto *contacto_crear(char *nombre, char *telefono, unsigned int edad) {
  Contacto *nuevo = malloc(sizeof(Contacto));

  if(nuevo!=NULL){
    nuevo->nombre = malloc(sizeof(char) * (strlen(nombre) + 1));
    if(nuevo->nombre!=NULL) strcpy(nuevo->nombre, nombre);

    nuevo->tel = malloc(sizeof(char) * (strlen(telefono) + 1));
    if(nuevo->tel!=NULL) strcpy(nuevo->tel, telefono);

    nuevo->edad = edad;
  }

  return nuevo;
}

Contacto *contacto_copia(Contacto *contacto) {
  Contacto *copia =contacto_crear(contacto->nombre, contacto->tel, contacto->edad);
  return copia;
}

int contacto_comparar(Contacto *c1, Contacto *c2) {
  return strcmp(c1->nombre, c2->nombre);
}

void contacto_destruir(Contacto *contacto) {
  free(contacto->nombre);
  free(contacto->tel);
  free(contacto);
}

unsigned contacto_heashear(Contacto *contacto) {
  return KRHash(contacto->nombre);
}

void contacto_imprimir(Contacto *contacto) {
  printf("{%s, %s, %d}", contacto->nombre, contacto->tel, contacto->edad);
}