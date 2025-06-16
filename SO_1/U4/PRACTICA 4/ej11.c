// Ej.11(Suma y Consenso por Rotaci´on).Considere en MPI un anillo de N procesos(con N configurable) en el que cada proceso tiene alg´un valor privado(ej.su rango).Queremos computar la suma de todos los valores, y que la misma resulte disponible en cada proceso.Implemente esto haciendo que Como primer paso, cada proceso env´ıa su valor hacia el siguiente proceso del anillo.Cada proceso recibe el valor y lo agrega a su suma.Cada proceso reenv´ıa el mismo valor que recibi´o hacia el siguiente.Al hacer esto, luego de N − 1 pasos, cada proceso deber´ıa tener la suma total computada.

#define procesos 10

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int num_proceso, valor,suma=0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &valor);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proceso);

    //enviar valor al siguiente proceso  //?HOW help
    //recibir valor y agregarlo  - luego,reenviar al sig

    
    printf("Soy el proceso nro %d , con valor%d\n",num_proceso,valor);

    if(num_proceso==procesos-1){
        printf("Total suma: %d", suma);
    }

    MPI_Finalize();

    return 0;

}