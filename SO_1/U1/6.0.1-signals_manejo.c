/**NOTE - 
 *   Veamos un programa que:
 1. Registra un handler (handleSignals) para capturar o manejar las señales SIGINT (CTRL + C) o SIGQUIT 
(CTRL + \)
 2. Si el usuario genera la señal SIGQUIT (utilizando el comando kill o con CTRL + \), el handler 
simplemente imprime el mensaje.
 3. Si el usuario genera la señal SIGINT (utilizando el comando kill o con CTRL + C) por primera vez, se 
captura la señal mostrando un mensaje en pantalla y se restablece la acción de la señal con el 
comportamiento por defecto (con SIG_DFL).
 4. Si el usuario genera la señal SIGINT por segunda vez, realiza la finalización del programa.
 -----------
 To terminate this program, perform the following:
 1. Open another terminal
 2. Issue command: kill 74 or issue CTRL+C 2 times (second time it terminates)
 ^C
 You pressed CTRL+C
 Now reverting SIGINT signal to default action
 To terminate this program, perform the following:
 1. Open another terminal
 2. Issue command: kill 74 or issue CTRL+C 2 times (second time it terminates)
 ^\You pressed CTRL+\
 To terminate this program, perform the following:
 1. Open another terminal
 2. Issue command: kill 120
 Terminate
 --------------
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler_sig1(int signum) {
    printf("Apretaste CTRL+\\ (SIGQUIT)\n");
    printf("To terminate this program, perform the following:\n");
    printf("1. Open another terminal\t");
    printf("2. Issue command: kill %d\n", getpid());
}

void handler_sig2(int signum) {
    static int sigint_count = 0;
    sigint_count++;

    if (sigint_count == 1) {
        printf("Apretaste CTRL+C (SIGINT)\n");
        printf("Now reverting SIGINT signal to default action\n");
        printf("To terminate this program, perform the following:\n");
        printf("1. Open another terminal\t");
        printf("2. Issue command: kill %d or issue CTRL+C 2 times (second time it terminates)\n", getpid());

        signal(SIGINT, SIG_DFL);  // Restaura SIGINT a su comportamiento por defecto
    }
}

int main() {
    signal(SIGQUIT, handler_sig1);
    signal(SIGINT, handler_sig2);

    printf("Process running... (PID: %d)\n", getpid());
    printf("Press CTRL+C once to see the message, twice to exit.\n");
    printf("Press CTRL+\\ to see a message.\n");

    // Mantener el programa corriendo para que pueda capturar señales
    while (1) {
        sleep(1);
    }

    return 0;
}
