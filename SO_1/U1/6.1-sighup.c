/*NOTE - 

    Ejemplo: Comunicación entre 2  procesos utilizando señales
 El Parent debe enviarle una señal al Child y esperar a que el Child termine. El Child al recibir la 
señal, debe imprimir en pantalla que la señal fue recibida y terminar.
 Probar primero con la señal SIGHUP, esto probablemente genere un race condition 
porque si el Parent ejecuta primero y envía la señal antes que el Child se suscriba 
entonces se ejecutara el comportamiento por defecto de la señal que es terminal el 
proceso.
 Para solucionar esto puede utilizar la señal SIGCHLD (que el comportamiento por 
defecto es que sea ignorada) o poner un sleep() en el parent antes de enviar la señal.
 Observar que la comunicación a través de señales es muy limitada ya que las 
señales NO permiten enviar datos.

*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void handler_sighup(int sig) {
    printf("Señal SIGHUP recibida por el hijo\n");
    exit(0); 
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed"); // Por si ocurre un error al crear el hijo
        exit(1);
    }

    if (pid == 0) {  
        signal(SIGHUP, handler_sighup);

        printf("Hijo: esperando señal...\n");
        
        while (1) {
            pause(); // Espera indefinidamente hasta que reciba una señal
        }

    } else {  // Este es el proceso padre
        // Esperamos un momento para asegurarnos de que el hijo esté listo para recibir la señal
        //sleep(1);

        // Manejo de SIGCHLD en el padre para evitar la terminación por defecto del hijo
        signal(SIGCHLD, SIG_IGN);   //! sin esto, directamente NUNCA entra en hijo (pq termina su proceso)

        // El padre envía la señal SIGHUP al hijo
        printf("Padre: enviando SIGHUP al hijo\n");
        kill(pid, SIGHUP);  // Enviar la señal SIGHUP al hijo

        // Esperamos a que el hijo termine antes de finalizar el padre
        wait(NULL);
        printf("Padre: El hijo ha terminado.\n");
    }

    return 0;
}
