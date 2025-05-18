#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

sem_t tabaco, papel, fosforos;
sem_t fumador_tabaco, fumador_papel, fumador_fosforos;
sem_t otra_vez;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int hay_tabaco = 0, hay_papel = 0, hay_fosforos = 0;

void *agente() {
  srandom(time(NULL));
  while (1) {
    sem_wait(&otra_vez);
    int caso = random() % 3;
    if (caso != 0)
      sem_post(&fosforos);
    if (caso != 1)
      sem_post(&papel);
    if (caso != 2)
      sem_post(&tabaco);
  }

  return NULL;
}

void chequear_combinacion() {
  if (hay_tabaco && hay_papel) {
    hay_tabaco = hay_papel = 0;
    sem_post(&fumador_fosforos);
  } else if (hay_tabaco && hay_fosforos) {
    hay_tabaco = hay_fosforos = 0;
    sem_post(&fumador_papel);
  } else if (hay_papel && hay_fosforos) {
    hay_papel = hay_fosforos = 0;
    sem_post(&fumador_tabaco);
  }
}

void *detector_tabaco(void *arg) {
  while (1) {
    sem_wait(&tabaco);
    pthread_mutex_lock(&mutex);
    hay_tabaco = 1;
    chequear_combinacion();
    pthread_mutex_unlock(&mutex);
  }
}

void *detector_papel(void *arg) {
  while (1) {
    sem_wait(&papel);
    pthread_mutex_lock(&mutex);
    hay_papel = 1;
    chequear_combinacion();
    pthread_mutex_unlock(&mutex);
  }
}

void *detector_fosforos(void *arg) {
  while (1) {
    sem_wait(&fosforos);
    pthread_mutex_lock(&mutex);
    hay_fosforos = 1;
    chequear_combinacion();
    pthread_mutex_unlock(&mutex);
  }
}

void fumar(int fumador) {
  printf("Fumador %d: Puf! Puf! Puf!\n", fumador);
  fflush(stdout);
  sleep(1);
}

void *fumador_con_tabaco(void *arg) {
  while (1) {
    sem_wait(&fumador_tabaco);
    fumar(1);
    sem_post(&otra_vez);
  }
}

void *fumador_con_papel(void *arg) {
  while (1) {
    sem_wait(&fumador_papel);
    fumar(2);
    sem_post(&otra_vez);
  }
}

void *fumador_con_fosforos(void *arg) {
  while (1) {
    sem_wait(&fumador_fosforos);
    fumar(3);
    sem_post(&otra_vez);
  }
}

int main() {
  pthread_t s1, s2, s3;
  pthread_t d1, d2, d3;
  pthread_t ag;

  sem_init(&tabaco, 0, 0);
  sem_init(&papel, 0, 0);
  sem_init(&fosforos, 0, 0);

  sem_init(&fumador_tabaco, 0, 0);
  sem_init(&fumador_papel, 0, 0);
  sem_init(&fumador_fosforos, 0, 0);

  sem_init(&otra_vez, 0, 1);

  pthread_create(&s1, NULL, fumador_con_tabaco, NULL);
  pthread_create(&s2, NULL, fumador_con_papel, NULL);
  pthread_create(&s3, NULL, fumador_con_fosforos, NULL);

  pthread_create(&d1, NULL, detector_tabaco, NULL);
  pthread_create(&d2, NULL, detector_papel, NULL);
  pthread_create(&d3, NULL, detector_fosforos, NULL);

  pthread_create(&ag, NULL, (void *)agente, NULL);
  pthread_join(ag, NULL);

  return 0;
}