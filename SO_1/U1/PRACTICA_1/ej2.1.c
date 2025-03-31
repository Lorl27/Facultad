//  a) Si se cierra el le descriptor de la salida estandar (1) que pasa al escribir al mismo?

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    char cadena[100];
    printf("Intentando cerrar la salida estándar...\n");  //! \n IMPORTA (se queda en el buffer!)
    close(1);
    printf("¿Esto se mostrará?\n");
    fgets(cadena,100,stdin);
    //fflush();
    printf("¿La cadena se imprimio: %s?\n",cadena);
    int numero;
    printf("Ingrese un numero: \n");
    scanf("%i",&numero);
    printf("Se recibio el número %d\n", numero);

    return 0;
}


//* Lo que sucederá es que el primer printf aparecerá pero luego, al cerrar la salida estándar, no podremos ver ningún printf . Solo nos dejará ingresar (entrada entándar abierta) , pero no se mostrará ningún mensaje.