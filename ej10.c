#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

pid_t child_pid;  // Variable global para almacenar el PID del hijo

void handle_signal(int signo) {
    if (signo == SIGUSR1) {
        printf("Proceso %d recibió SIGUSR1\n", getpid());
        if (getpid() == child_pid) {
            // Si soy el hijo, le envío SIGUSR1 al padre
            kill(getppid(), SIGUSR1);
        } else {
            // Si soy el padre, le envío SIGUSR1 al hijo
            kill(child_pid, SIGUSR1);
        }
    }
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    
    sigaction(SIGUSR1, &sa, NULL);

    child_pid = fork();

    if (child_pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Proceso hijo: espera señales
        while (1) pause();  
    } else {
        // Proceso padre: envía la primera señal al hijo
        sleep(1);  
        kill(child_pid, SIGUSR1);
        
        while (1) pause();  
    }

    return 0;
}
