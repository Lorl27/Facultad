#define N 1024

typedef struct channel {
    int buff[N];
    int ind_esc, ind_lec, cant_elem;

    pthread_mutex_t mutex;
    pthread_cond_t buffer_no_lleno;
    pthread_cond_t buffer_no_vacio;
} Channel;

void channel_init(Channel *c) {
    c->ind_esc = c->ind_lec = c->cant_elem = 0;
    pthread_mutex_init(&c->mutex, NULL);
    pthread_cond_init(&c->buffer_no_lleno, NULL);
    pthread_cond_init(&c->buffer_no_vacio, NULL);
}

void chan_write(Channel *c, int *value) {
    pthread_mutex_lock(&c->mutex);

    while (c->cant_elem == N)
        pthread_cond_wait(&c->buffer_no_lleno, &c->mutex);

    c->buff[c->ind_esc] = *value;
    c->ind_esc = (c->ind_esc + 1) % N;
    c->cant_elem++;

    pthread_cond_signal(&c->buffer_no_vacio);
    pthread_mutex_unlock(&c->mutex);
}

int *chan_read(Channel *c) {
    pthread_mutex_lock(&c->mutex);

    while (c->cant_elem == 0)
        pthread_cond_wait(&c->buffer_no_vacio, &c->mutex);

    int *p = malloc(sizeof(int));
    *p = c->buff[c->ind_lec];
    c->ind_lec = (c->ind_lec + 1) % N;
    c->cant_elem--;

    pthread_cond_signal(&c->buffer_no_lleno);
    pthread_mutex_unlock(&c->mutex);

    return p;
}
