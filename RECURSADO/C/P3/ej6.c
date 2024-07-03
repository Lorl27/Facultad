// Ejercicio 6. Una Persona

#include <stdio.h>
#include <string.h>

// 1. Proponer una representación con estructuras para modelar una persona.
typedef struct person {
    char nombre[50];
    char apellido[50];
    int dni;
    int telefono;
    int edad;
} Persona;

// 2. Escriba una función de creación de un elemento del tipo Persona, el cual toma cinco datos de una
// persona, como por ejemplo, nombre, apellido, dni, teléfono, y edad, y retorna una elemento de tipo
// Persona válido.

Persona crear_Persona(char name[],char apellido[], int dni, int tel, int edad){
    Persona p;

    strcpy(p.nombre,name);
    strcpy(p.apellido, apellido);
    p.dni = dni;
    p.telefono = tel;
    p.edad = edad;

    return p;
}

// 3. Escriba la función imprimir_Persona:Persona → void, la cual muestra en pantalla los datos de un
// elemento del tipo Persona.

void imprimir_Persona(Persona p){
    printf("P: Nombre:\"%s\" , Apellido:\"%s\", DNI:%d , Tel:%d, edad:%d \n\n",p.nombre,p.apellido,p.dni,p.telefono,p.edad);
}

// 4. Escriba la función igual_Identidad:Persona → Persona →Int, la cual compara si dos datos de tipo
// persona son iguales, basándose en que coincidan su número de dni.

int igual_Identidad(Persona p1, Persona p2){
    return (p1.dni == p2.dni);
}

// 5. Escriba una función que indique si dos Personas son familiares. Una persona es familiar de otra,
// si tiene el mismo apellido, y apellido.

int familiares(Persona p1, Persona p2){
    return(strcmp(p1.nombre,p2.nombre)==0 && strcmp(p1.apellido,p2.apellido)==0);
}


// 6. Diseñe las siguientes tres estructuras para que contengan al tipo Persona como dato: 
//Estudiante, Empleado, Socio, y para ellas defina las siguientes funciones,
// reutilizando las funciones antes definidas para la estructura Persona:
// Creación de elementos de la estructura.
// Impresión de datos de la estructura.

typedef struct estudiante{
    Persona persona;
} Estudiante;

typedef struct empleado{
    Persona persona;
} Empleado;

typedef struct socio{
    Persona persona;
} Socio;

Estudiante crear_Estudiante(char name[],char apellido[],int dni, int tel, int edad){
    Estudiante est={crear_Persona(name,apellido,dni,tel,edad)};

    return est;
}

void imprimir_Estudiante(Estudiante est){
    imprimir_Persona(est.persona);
}

Empleado crear_Empleado(char name[],char apellido[],int dni, int tel, int edad){
    Empleado em;
    em.persona = crear_Persona(name, apellido, dni, tel, edad);

    return em;
}

void imprimir_Empleado(Empleado em){
    imprimir_Persona(em.persona);
}

Socio crear_Socio(char name[],char apellido[],int dni, int tel, int edad){
    Socio soc={crear_Persona(name,apellido,dni,tel,edad)};

    return soc;
}

void imprimir_Socio(Socio soc){
    imprimir_Persona(soc.persona);
}

//----------------------

int main(void) {
    Persona p1 = crear_Persona("Juan", "Perez", 12345678, 987654321, 30);
    Persona p2 = crear_Persona("Maria", "Perez", 87654321, 123456789, 28);

    imprimir_Persona(p1);
    imprimir_Persona(p2);

    if (igual_Identidad(p1, p2)) {
        printf("Las personas tienen la misma identidad.\n");
    } else {
        printf("Las personas no tienen la misma identidad.\n");
    }

    if (!familiares(p1, p2)) {
        printf("Las personas son familiares.\n\n");
    } else {
        printf("Las personas no son familiares.\n\n");
    }

    Estudiante est = crear_Estudiante("Carlos", "Gomez", 11223344, 445566778, 20);
    Empleado emp = crear_Empleado("Ana", "Lopez", 22334455, 998877665, 25);
    Socio sc = crear_Socio("Luis", "Martinez", 33445566, 556677889, 35);

    printf("Estudiante: ");
    imprimir_Estudiante(est);
    printf("Empleado: ");
    imprimir_Empleado(emp);
    printf("Socio: ");
    imprimir_Socio(sc);

    return 0;
}