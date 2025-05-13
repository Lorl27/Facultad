#include <semaphore.h>
#include <stdlib.h>
#include "rwlock.h"
#include <pthread.h>


struct rwlock
{
	int nr;			   // nro lectores
	int num_esc;
	int num_esc_ent;
	//pthread_cond_t sn; // read
	pthread_cond_t sl; // escritor
	// pthread_mutex_t *mutex_es;
	pthread_mutex_t mutex_v;
};

struct rwlock *rwlock_init()
{
	struct rwlock *rwl = malloc(sizeof (struct rwlock));
	pthread_mutex_init(&rwl->mutex_v, NULL);
	//pthread_cond_init(&rwl->sn, NULL);
	pthread_cond_init(&rwl->sl, NULL);

	rwl->nr = 0;
	rwl->num_esc = 0;
	rwl->num_esc_ent = 0;
	return rwl;
}

void rwlock_destroy(struct rwlock *rwl)
{
	//pthread_cond_destroy(&rwl->sn);
	pthread_cond_destroy(&rwl->sl);

	pthread_mutex_destroy(&rwl->mutex_v);

	free(rwl);
}

void lock_r(struct rwlock *rwl)
{
	pthread_mutex_lock(&rwl->mutex_v);

	while (rwl->num_esc != 0 || rwl->num_esc_ent != 0) {
		pthread_cond_wait(&rwl->sl, &rwl->mutex_v); // espera q el escritor no escriba
	}
	rwl->nr++;
	pthread_mutex_unlock(&rwl->mutex_v);
}

void unlock_r(struct rwlock *rwl)
{
	pthread_mutex_lock(&rwl->mutex_v);
	rwl->nr--;
	pthread_mutex_unlock(&rwl->mutex_v);
}

void lock_w(struct rwlock *rwl)
{
	pthread_mutex_lock(&rwl->mutex_v);
	while(rwl->num_esc != 0){
		rwl->num_esc_ent++;
		pthread_cond_wait(&rwl->sl, &rwl->mutex_v);
		rwl->num_esc_ent--;
	}
	rwl->num_esc++;
	pthread_mutex_unlock(&rwl->mutex_v);
}

void unlock_w(struct rwlock *rwl)
{
	pthread_mutex_lock(&rwl->mutex_v);
	rwl->num_esc--;
	pthread_cond_broadcast(&rwl->sl); // mando señal: ya escribi.
	pthread_mutex_unlock(&rwl->mutex_v);
}
