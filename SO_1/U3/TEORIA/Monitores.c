typedef struct monitor{
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} monitor_t;

void monitor_init(monitor_t *monitor){
    monitor->value = 0;
    pthread_mutex_init(&monitor->mutex, NULL);
    pthread_cond_init(&monitor->cond, NULL);
}

void monitor_increment(monitor_t *monitor){
    pthread_mutex_lock(&monitor->mutex);
    monitor->value++;
    pthread_cond_signal(&monitor->cond); // Signal waiting threads 
    pthread_mutex_unlock(&monitor->mutex);
}

int monitor_get_value(monitor_t *monitor){
    pthread_mutex_lock(&monitor->mutex);
    while (monitor->value == 0){
        pthread_cond_wait(&monitor->cond, &monitor->mutex);
    }
    
    int val = monitor->value;
    pthread_mutex_unlock(&monitor->mutex);
    return val;
}
