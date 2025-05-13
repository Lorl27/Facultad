#include <unistd.h>  //sleep
#include <stdlib.h>  //exit y malloc
#include <stdio.h>  //f. básicas como print
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/un.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>  //same as mman
#include <sys/select.h>
#include <sys/mman.h>  //memoria compartida entre sockets-procesos
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h> //API: MUTEX POSIX. incluir en gcc -pthread
#include <assert.h>
#include <sys/epoll.h> 
#include <limits.h>
#include <semaphore.h>
#include <omp.h>  //gcc -fopenmp 4.0-omp.c -o omp_program
