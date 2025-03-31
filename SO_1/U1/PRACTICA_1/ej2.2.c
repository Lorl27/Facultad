//  b) Si se cierra el le descriptor de la entrada estandar (0) que pasa al intentar leer del mismo?


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    char cadena[100];
    int numero;
    printf("Ingrese un numero: \n");
    scanf("%i",&numero);
    printf("Se recibio el número %d\n", numero);

    printf("Intentando cerrar la entrada estándar...\n");  //! \n IMPORTA (se queda en el buffer!)
    close(0);
    printf("¿Esto se mostrará?\n");
    fgets(cadena,100,stdin);
    //fflush();
    printf("¿La cadena se imprimio: %s?\n",cadena);

    return 0;
}

//*  Lo que pasará es que antes de cerrar, podremos ingresar el número pero luego, no podremos ingresar nada (y en el último caso, no imprimirá ninguna  cadena puesto que no se permitió almacenar ninguna)