#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <errno.h>

#define PORT 3942
#define MAX_CLIENTS 10
#define MAX_KEY 100
#define MAX_VALUE 100
#define STORE_SIZE 100

typedef struct {
    char key[MAX_KEY];
    char value[MAX_VALUE];
} KeyValue;

typedef struct {
    KeyValue store[STORE_SIZE];
    int count;
} SharedStore;

SharedStore *shared_store;
sem_t *sem;

void quit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void handle_client(int client_sock) {
    char buffer[256];
    int rc;

    while ((rc = read(client_sock, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[rc] = '\0';
        char *cmd = strtok(buffer, " \n");
        char *key = strtok(NULL, " \n");
        char *value = strtok(NULL, " \n");
        
        if (!cmd || !key) {
            write(client_sock, "EINVAL\n", 7);
            continue;
        }
        
        sem_wait(sem);
        if (strcmp(cmd, "PUT") == 0 && value) {
            int found = 0;
            for (int i = 0; i < shared_store->count; i++) {
                if (strcmp(shared_store->store[i].key, key) == 0) {
                    strncpy(shared_store->store[i].value, value, MAX_VALUE);
                    found = 1;
                    break;
                }
            }
            if (!found && shared_store->count < STORE_SIZE) {
                strncpy(shared_store->store[shared_store->count].key, key, MAX_KEY);
                strncpy(shared_store->store[shared_store->count].value, value, MAX_VALUE);
                shared_store->count++;
            }
            write(client_sock, "OK\n", 3);
        } else if (strcmp(cmd, "GET") == 0) {
            int found = 0;
            for (int i = 0; i < shared_store->count; i++) {
                if (strcmp(shared_store->store[i].key, key) == 0) {
                    char response[128];
                    snprintf(response, sizeof(response), "OK %s\n", shared_store->store[i].value);
                    write(client_sock, response, strlen(response));
                    found = 1;
                    break;
                }
            }
            if (!found) write(client_sock, "NOTFOUND\n", 10);
        } else if (strcmp(cmd, "DEL") == 0) {
            int found = 0;
            for (int i = 0; i < shared_store->count; i++) {
                if (strcmp(shared_store->store[i].key, key) == 0) {
                    shared_store->store[i] = shared_store->store[shared_store->count - 1];
                    shared_store->count--;
                    write(client_sock, "OK\n", 3);
                    found = 1;
                    break;
                }
            }
            if (!found) write(client_sock, "NOTFOUND\n", 10);
        } else {
            write(client_sock, "EINVAL\n", 7);
        }
        sem_post(sem);
    }
    close(client_sock);
    exit(0);
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in serv_addr;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) quit("socket");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(server_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        quit("bind");

    if (listen(server_sock, MAX_CLIENTS) < 0)
        quit("listen");

    int shm_fd = shm_open("/shared_store", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SharedStore));
    shared_store = mmap(0, sizeof(SharedStore), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_store == MAP_FAILED) quit("mmap");
    shared_store->count = 0;

    sem = sem_open("/sem_store", O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) quit("sem_open");

    printf("Servidor escuchando en el puerto %d\n", PORT);

    while (1) {
        client_sock = accept(server_sock, NULL, NULL);
        if (client_sock < 0) quit("accept");

        if (fork() == 0) {
            close(server_sock);
            handle_client(client_sock);
        }
        close(client_sock);
    }
    return 0;
}
