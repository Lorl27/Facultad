#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define TAM 200 //Definimos un tamaño máximo para el nombre.


//Definición de la estructura.
typedef struct cumple {
    char nombre[TAM];
    int mes;
    int dia;
    int year;
} Cumple;

//Própositos de las funciones:
Cumple crear_cumple(char name[], int mes, int dia, int year);
void imprimir_cumple(Cumple c);
void busqueda_cumple(Cumple c[5], int dia, int mes);


/*
    DISEÑO DE DATOS:

    c: estructura tipo Cumple

    Signatura:
    crear_cumple: char[], int,int,int -> Cumple

    Próposito: Según los parámetros pasados, se crea un objeto en la estructura tipo Cumple.

    EJEMPLOS:
        crear_cumple("ana",27,6,1999)=={"ana",27,6,1999};
        crear_cumple("mirta juana",2,2,2002)=={"mirta juana",22,2,2002};
 */
Cumple crear_cumple(char name[], int mes, int dia, int year){
    Cumple c;
    strcpy(c.nombre,name);
    c.mes=mes;
    c.dia=dia;
    c.year=year;

    return c;
}

void test_crear_cumple(void){
    Cumple c1={"ana",6,27,1999};
    Cumple c1_Crear=crear_cumple("ana",6,27,1999);

    assert(strcmp(c1.nombre,c1_Crear.nombre)==0 && c1.mes==c1_Crear.mes && c1.dia==c1_Crear.dia && c1.year==c1_Crear.year); //Comparamos para verificar su igualdad

    Cumple c2={"mirta juana",2,2,2002};
    Cumple c2_Crear=crear_cumple("mirta juana",2,2,2002);

    assert(strcmp(c2.nombre,c2_Crear.nombre)==0 && c2.mes==c2_Crear.mes && c2.dia==c2_Crear.dia && c2.year==c2_Crear.year);
}

/*
    DISEÑO DE DATOS:

    Signatura:
    imprimir_cumple: Cumple -> void

    Próposito: Devuelve un 'pretty print' de la estructura tipo Cumple pasada por párametro.

    EJEMPLOS:
        Cumple c1={"ana",27,6,1999}
        imprimir_cumple(c1) -> (SE MUESTRA POR PANTALLA) "La persona "ana" cumple el día 27 del mes 6. Nació en 1999"

        Cumple c2={"mirta juana",22,2,2002}
        imprimir_cumple(c2) -> (SE MUESTRA POR PANTALLA) "La persona "mirta juana" cumple el día 22 del mes 2. Nació en 2002"

*/

void imprimir_cumple(Cumple cu){
    printf("La persona \"%s\" cumple el día %d del mes %d. Nació en %d \n\n",cu.nombre,cu.dia,cu.mes,cu.year);
}


/* DISEÑO DE DATOS:
    cantidad_que_cumplen: int , indicará la cantidad de personas que cumplen en esa fecha determinada.

    Signatura:
    busqueda_cumple: Cumple char[], int, int -> void

    Próposito: Indicar la cantidad de personas que cumplen en la fecha pasada por párametro.

    EJEMPLOS:
        *Sea cumpleanios1 un array con 5 elementos que con tiene las 5 fechas de cumpleaños de los amigos, almacenadas en la estructura tipo Cumple.
        -En donde, 
        - amigo 1 cumple el día 27 del mes 7
        - amigo 2 cumple el día 5 del mes 9
        - amigo 3 cumple el día 10 del mes 10
        - amigo 4 cumple el día 6 del mes 11
        - amigo 5 cumple el día 3 del mes 2

        busqueda_cumple(cumpleanios1,6,2) -> (SE IMPRIMIRÁ POR PANTALLA) "NO hay ningún amigx con esa fecha de cumpleaños.."

        *Sea cumpleanios2 un array con 5 elementos que con tiene las 5 fechas de cumpleaños de los amigos, almacenadas en la estructura tipo Cumple.
        -En donde, 
        - amigo 1 cumple el día 27 del mes 7
        - amigo 2 cumple el día 27 del mes 7
        - amigo 3 cumple el día 10 del mes 10
        - amigo 4 cumple el día 6 del mes 11
        - amigo 5 cumple el día 3 del mes 2

        busqueda_cumple(cumpleanios2,27,7) -> (SE IMPRIMIRÁ POR PANTALLA) "La cantidad de amigos que cumplen esa fecha es de: 2 amigos"

        *Sea cumpleanios3 un array con 5 elementos que con tiene las 5 fechas de cumpleaños de los amigos, almacenadas en la estructura tipo Cumple.
        -En donde, 
        - amigo 1 cumple el día 27 del mes 7
        - amigo 2 cumple el día 5 del mes 9
        - amigo 3 cumple el día 10 del mes 10
        - amigo 4 cumple el día 6 del mes 2
        - amigo 5 cumple el día 3 del mes 2

        busqueda_cumple(cumpleanios3,6,2) -> (SE IMPRIMIRÁ POR PANTALLA) "Solo hay un amigo que cumpla esa fecha."
*/

void busqueda_cumple(Cumple c[5], int dia, int mes){
    int cantidad_que_cumplen=0;

    for(int x=0;x<5;x++){
        if(c[x].dia==dia && c[x].mes==mes){
            cantidad_que_cumplen+=1;
        }
    }

    if(cantidad_que_cumplen==0){
        printf("NO hay ningún amigx con esa fecha de cumpleaños...\n");
    }
    else if(cantidad_que_cumplen==1){
        printf("Solo hay un amigo que cumpla esa fecha. \n");
    }
    else{
        printf("La cantidad de amigos que cumplen esa fecha es de: %d amigos \n",cantidad_que_cumplen);
    }
}

int main(void){
    //TESTS:
    test_crear_cumple();
    
    Cumple cumpleanios[6]; //Arreglo de estructuras, almaneca las fechas de cumpleaños de los 5 amigos.


    //CREAMOS EL ARRAY DE ESTRUCTURAS:
    for(int x=0;x<5;x++){

        //Inicializamos los valores:
        char nam[TAM];
        int mes=0,dia=0,year=0;

        printf("Ingrese los datos de su amigo nro %d: \n",x+1);
        
        printf("Ingrese su nombre: \n");
        fgets(nam, TAM, stdin);
        nam[strcspn(nam, "\n")] = '\0'; // Eliminamos el salto de líneascanf(" %[^\n]",nam);

        printf("Ingrese su dia de nacimiento: \n");
        scanf("%d",&dia);

        printf("Ingrese su mes de nacimiento (EN NÚMEROS): \n");
        scanf("%d",&mes);

        printf("Ingrese su año de nacimiento: \n");
        scanf(" %d",&year);

        Cumple cump=crear_cumple(nam,mes,dia,year);
        imprimir_cumple(cump);

        cumpleanios[x]=cump;

        printf("--------------------------------------------------\n\n");

        // Limpiar el buffer de entrada
        while (getchar() != '\n');

    }

    //Inicializamos los valores para la búsqueda:
    int mes_a_buscar=0,dia_a_buscar=0;

    printf("Ingrese los datos para saber cuántos amigos cumplen en la fecha determinada: \n");
    printf("Ingrese el mes: ");
    scanf("%d",&mes_a_buscar);
    printf("Ingrese el día: ");
    scanf("%d",&dia_a_buscar);

    busqueda_cumple(cumpleanios,dia_a_buscar,mes_a_buscar);

    return 0;
}