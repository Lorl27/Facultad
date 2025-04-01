#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>

#define PORT 4040
#define SHM_NAME "turnos_shm"
#define SEM_NAME "turnos_sem"

void quit(char *s) {
    perror(s);
    abort();
}

int fd_readline(int fd, char *buf) {
    int rc, i = 0;
    while ((rc = read(fd, buf + i, 1)) > 0) {
        if (buf[i] == '\n')
            break;
        i++;
    }
    if (rc < 0)
        return rc;
    buf[i] = 0;
    return i;
}

void handle_conn(int csock, int *U, sem_t *sem) {
    char buf[200];
    int rc;
    while (1) {
        rc = fd_readline(csock, buf);
        if (rc < 0)
            quit("read error");
        if (rc == 0) {
            close(csock);
            return;
        }
        if (!strcmp(buf, "NUEVO")) {
            char reply[20];
            sem_wait(sem); // Bloqueo para modificar U de manera segura
            sprintf(reply, "%d\n", (*U)++);
            sem_post(sem); // Desbloqueo
            write(csock, reply, strlen(reply));
        } else if (!strcmp(buf, "CHAU")) {
            close(csock);
            return;
        }
    }
}

void wait_for_clients(int lsock, int *U, sem_t *sem) {
    while (1) {
        int csock = accept(lsock, NULL, NULL);
        if (csock < 0)
            quit("accept error");
        
        pid_t pid = fork();
        if (pid == 0) { // Proceso hijo
            close(lsock); // No necesita el socket de escucha
            handle_conn(csock, U, sem);
            exit(0);
        } else if (pid < 0) {
            quit("fork error");
        }
        close(csock); // El padre cierra el socket cliente
    }
}

int main() {
    int lsock;
    struct sockaddr_in sa;
    int yes = 1;

    lsock = socket(AF_INET, SOCK_STREAM, 0);
    if (lsock < 0)
        quit("socket error");

    if (setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1)
        quit("setsockopt error");

    sa.sin_family = AF_INET;
    sa.sin_port = htons(PORT);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(lsock, (struct sockaddr *)&sa, sizeof sa) < 0)
        quit("bind error");

    if (listen(lsock, 10) < 0)
        quit("listen error");
    
    // Memoria compartida para el contador de turnos
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd < 0)
        quit("shm_open error");
    ftruncate(shm_fd, sizeof(int));
    int *U = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (U == MAP_FAILED)
        quit("mmap error");
    *U = 0; // Inicializa el contador
    
    // Semáforo para sincronización
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED)
        quit("sem_open error");
    
    wait_for_clients(lsock, U, sem);
    
    close(lsock);
    shm_unlink(SHM_NAME);
    sem_close(sem);
    sem_unlink(SEM_NAME);
    return 0;
}
