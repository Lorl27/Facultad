// 14. Cree una representaci ́on para una agenda de contactos:
// a) Defina un tipo de datos Contacto que permita almacenar: una cadena para el nombre de una
// persona, una cadena para el n ́umero de tel ́efono, y un entero sin signo para llevar la edad de la
// persona.
// b) Implemente una funci ́on Contacto crear contacto() que pida por teclado los datos pertinentes,
// rellene un nuevo contacto con esos datos, y lo devuelva. Puede usar la funci ́on get new line del
// ejercicio 6.
// c) Implemente una funci ́on void actualizar edad(Contacto *) que dado un puntero a un contacto,
// pida una nueva edad por teclado, y la actualice. ¿Es necesario que su argumento sea un puntero?
// d) Defina un tipo de datos Agenda que almacene un arreglo de contactos y un entero para llevar la
// cantidad de contactos ingresados en la misma.
// e) Implemente una funci ́on void alta contacto(Agenda *) que pida por teclado los datos de un
// contacto a agregar (funci ́on crear contacto) e inserte el resultado en la agenda.
// f ) Implemente una funci ́on void modificar edad(Agenda *) que pida por teclado el nombre del
// contacto a modificar, lo busque en la agenda, y luego actualice su edad (funci ́on actualizar edad).
// g) Implemente una funci ́on void imprimir contactos(Agenda *) que muestre por pantalla los
// datos de los contactos cargados.
// h) Implemente una funci ́on double prom(Agenda *) que devuelva el promedio de la edad de los
// contactos dentro de la agenda

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 500

typedef struct {
    char nombre[400];
    char telefono[15];
    unsigned int edad;
} Contacto;

Contacto crear_contacto(char *name, char *tel , unsigned int age){
    Contacto new;
    strcpy(new.nombre,name);
    strcpy(new.telefono,tel);
    new.edad=age;

    return new;
}

void imprimir_contacto(Contacto c){
    printf("El numero %s pertenece a %s , quien tiene %d años.",c.telefono,c.nombre,c.edad);
}

void actualizar_edad(Contacto *c){
    int edad_n;

    printf("Ingrese la nueva edad: \n");
    scanf("%d",&edad_n);
    getchar();  // Limpia el buffer

    c->edad=edad_n;
}

typedef struct{
    int entero; //cant. contactos en la agenda
    Contacto contactos[TAM_MAX];
} Agenda;

void alta_contacto(Agenda *a){
    if(a->entero >=TAM_MAX){
        printf("Agenda llena! \n");
        return;
    }

    char nombre[400],tel[15];
    unsigned int n;

    printf("Ingrese el nombre: \n");
    fgets(nombre,sizeof(nombre),stdin);
    nombre[strcspn(nombre, "\n")] = 0; 

    printf("Ingrese el teléfono: \n");
    fgets(tel,sizeof(tel),stdin);
    tel[strcspn(tel,"\n")]=0;

    printf("Ingrese la edad: \n");
    scanf("%u",&n);
    getchar();  // Limpia el buffer después de scanf.

    a->contactos[a->entero]=crear_contacto(nombre,tel,n);
    a->entero++; //aumentó 1 contacto
}


void modificar_edad(Agenda *a){
    char n_contact[500];

    printf("Ingrese el nombre del contacto a modificar: \n");
    fgets(n_contact,sizeof(n_contact),stdin);
    n_contact[strcspn(n_contact,"\n")]=0;

    for(int x=0;x<a->entero;x++){
        if(strcmp(a->contactos[x].nombre, n_contact) == 0){
            actualizar_edad(&a->contactos[x]);
            return;
        }
    }

    printf("El contacto no se encontro :(. \n");
}


void imprimir_contactos(Agenda *a){

    if(a->entero==0){
        printf("AGENDA VACIA! \n");
        return;
    }


    for(int x=0;x<a->entero;x++){
        printf("Contacto NRO %d: %s - edad: %d - tel: %s \n",x+1,a->contactos[x].nombre,a->contactos[x].edad,a->contactos[x].telefono);
    }
}

double prom(Agenda *a){
    double cantidad= a->entero;
    double edadT=0,promedio=0;

    for(int x=0;x<cantidad;x++){
        edadT+=a->contactos[x].edad;
    }

    if(cantidad!=0 && edadT!=0){
        promedio=edadT/cantidad;
    }

    return promedio;
}



int main(){
    Agenda agendita={0};

    int alta=1;
    int agregar=1, modificar=0;

    while(alta){
        alta_contacto(&agendita);
    
        printf("¿Desea agregar más contactos?: SI=1, NO=0\t");
        scanf("%d",&agregar);
        getchar();

        if (agregar==0){
            alta=0;
        }
    }

    printf("¿Desea modificar la edad de algún contacto?: SI=1, NO=0\t");
        scanf("%d",&modificar);
        getchar();

        if (modificar==1){
            modificar_edad(&agendita);
            modificar=0;
        }

    imprimir_contactos(&agendita);
    printf("Promedio de edad: %.2f\n", prom(&agendita));

    return 0;
}