#include "kv.h"

#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "hash.h"
#include "ll.h"

//*put-del-get
//* i:indice seccion que me toco , m: nro mutex
//* i%m  ?
//* sup tengo 3 mutex
/*
[indi%n] == indice hash (1/2/3/1/2/3)
*/
//! ESTE TENEMOS Q EDITAR
//? Hay que pensar, la cant de mutex que pondremos...

// SECTION

#define MAX 10

pthread_mutex_t mutex_tabla[MAX];

pthread_mutex_t mutex_lru;

struct bin {
    /* Una lista de struct kv, sin orden en particular */
    struct list vals;
};

static int TableSZ;
static struct bin *Table;
static struct list LRU = LIST_INIT(LRU);

long kv_keys() {
    long r = 0;
    int i;
    /* Recorremos todos los bins contando cuantos pares KV tenemos */

    for (i = 0; i < TableSZ; i++) {
        struct list *p;
        list_for_each(p, &Table[i].vals)
            r++;
    }

    return r;
}

static int binof(u64 hash) {
    return hash % TableSZ;
}

/* Refcounting */
static void kv_free(struct kv *kv) {
    /* El nodo YA DEBE estar deslinkeado de ambas listas */

    assert(kv->lru.next == NULL);
    assert(kv->lru.prev == NULL);
    assert(kv->list.next == NULL);
    assert(kv->list.prev == NULL);

    /* log(0, "free"); */
    free(kv->v);
    free(kv->k);
    free(kv);
}

static inline void kv_grab(struct kv *kv) {
    pthread_mutex_lock(&mutex_tabla[0]);  // NOTE - 0
    kv->nrefs++;

    pthread_mutex_unlock(&mutex_tabla[0]);
}

void __kv_release(struct kv *kv) {
    pthread_mutex_lock(&mutex_tabla[1]);  // NOTE -  1
    assert(kv->nrefs > 0);

    kv->nrefs--;
    pthread_mutex_unlock(&mutex_tabla[1]);

    if (kv->nrefs == 0) {
        /*
         * Si nrefs == 0, no puede estar en la tabla
         * ni LRU, así que es seguro liberarlo.
         */
        kv_free(kv);
    }
}

void kv_release(struct kv *kv) {
    int bin = kv->bin;
    __kv_release(kv);
}
/* / Refcounting */

/* Retorna una cota inferior de los bytes liberados */
static int kv_evict1() {
    struct list *p;
    struct kv *kv;
    int bin;

    /*
     * Nota: hacemos trylock dentro del bucle para evitar
     * un posible deadlock, ya que hay un ciclo en el
     * orden de los recursos.
     */

    log(2, "EVICT1 comenzando");

    pthread_mutex_lock(&mutex_lru);
    for (p = LRU.prev; p != &LRU; p = p->prev) {
        kv = list_entry(p, struct kv, lru);
        bin = kv->bin;

        /* Intentar tomar lock, si falla seguimos */
        if (pthread_mutex_trylock(&mutex_tabla[2]) < 0) {  // NOTE - 2
            log(1, "evitamos error");
            continue;
        }

        /*
         * Si está tomado por alguien (aparte de la misma
         * tabla), lo ignoramos
         */

        if (kv->nrefs < 0) {
            log(1, "ignorado...");
            continue;
        }

        pthread_mutex_unlock(&mutex_tabla[2]);

        /* Si no, listo, liberamos este. Salimos con lock tomado */
        break;
    }
    pthread_mutex_unlock(&mutex_lru);

    /* Si entramos acá, no encontramos nada, y no tenemos ningún lock. */
    if (p == &LRU) {
        log(1, "LRU vacía!?!?");

        return 0;
    }
    pthread_mutex_lock(&mutex_tabla[3]);  // NOTE 3

    int r = kv->klen + kv->vlen;

    /* Lo sacamos de la LRU y del mapa, y soltamos la ref de la tabla. */
    list_unlink(&kv->lru);
    list_unlink(&kv->list);
    __kv_release(kv);

    pthread_mutex_unlock(&mutex_tabla[3]);

    pthread_mutex_unlock(&mutex_lru);

    return r;
}

void *galloc(size_t size) {
    void *ret;
    int laps = 0;

    ret = malloc(size);
    pthread_mutex_lock(&mutex_tabla[4]);  // NOTE 4
    while (!ret && laps < 10) {
        kv_evict1();
        ret = malloc(size);
        laps++;
    }
    pthread_mutex_unlock(&mutex_tabla[4]);

    if (!ret)
        log(2, "galloc no anduvo!!");

    return ret;
}

void *memdup(const void *p, int len) {
    void *r = galloc(len);
    if (!r) {
        log(2, "memdup OOM");
        return NULL;
    }
    memcpy(r, p, len);
    return r;
}

static bool kmatch(int klen1, const char *k1, int klen2, const char *k2) {
    if (klen1 != klen2)
        return false;

    return (memcmp(k1, k2, klen1) == 0);
}

struct kv *__kv_lookup(u64 hash, int idx, int klen, const char *k) {
    struct list *p;

    pthread_mutex_lock(&mutex_tabla[5]);  // NOTE 5
    list_for_each(p, &Table[idx].vals) {
        struct kv *kv = list_entry(p, struct kv, list);
        /* log(2, "loop k = %s", kv->k); */
        if (hash != kv->hash)
            continue;

        if (kmatch(klen, k, kv->klen, kv->k)){
            pthread_mutex_unlock(&mutex_tabla[5]);
            return kv;
            }
    }
    pthread_mutex_unlock(&mutex_tabla[5]);

    return NULL;
}

static void bump(struct kv *kv) {
    assert(kv);
    struct list *l = &kv->lru;

    pthread_mutex_lock(&mutex_tabla[6]);  // NOTE 6
    assert(l->next);
    assert(l->prev);
    list_unlink(l);

    list_add_head(&LRU, l);
    pthread_mutex_unlock(&mutex_tabla[6]);
}

struct kv *kv_lookup(int klen, const char *k) {
    u64 hash = hash_buf(klen, k);
    int idx = binof(hash);

    pthread_mutex_lock(&mutex_tabla[7]);  // NOTE 7

    struct kv *ret = __kv_lookup(hash, idx, klen, k);
    if (ret) {
        kv_grab(ret);
        bump(ret);
    }
    pthread_mutex_unlock(&mutex_tabla[7]);

    return ret;
}

/* devuelve .list y .lru sin inicializar */
static struct kv *new_node(u64 hash, int idx, int klen, char *k, int vlen,
                           char *v) {
    /* No estaba, crear e insertar */
    struct kv *node = galloc(sizeof *node);
    if (!node)
        return NULL;

    node->hash = hash;
    node->bin = idx;
    node->klen = klen;
    node->k = k;
    node->vlen = vlen;
    node->v = v;
    node->nrefs = 0;

    return node;
}

int kv_add(int klen, char *k, int vlen, char *v) {
    assert(k);
    assert(v);
    u64 hash = hash_buf(klen, k);
    int idx = binof(hash);

    /*
     * Siempre creamos un nodo nuevo, borramos el nodo existente si
     * lo había, y luego insertamos.
     *
     * Por qué esta lógica? Es más facil por el conteo de referencias...
     * porque para cambiarle el valor al nodo actual, tendríamos que
     * sobreescribir kv->v, y liberar el viejo, pero el mismo puede estar
     * siendo usado. En vez de agregar *otro* conteo de referencias para
     * kv->v, simplemente hacemos un nodo KV nuevo.
     */

    struct kv *new = new_node(hash, idx, klen, k, vlen, v);
    if (!new) {
        log(2, "kv_add oom");
        return -1;
    }
    kv_grab(new);

    struct kv *old = __kv_lookup(hash, idx, klen, k);

    /* Si existía algo en esta clave, lo removemos. */
    if (old) {
        list_unlink(&old->list);
        list_unlink(&old->lru);
        __kv_release(old);
    }

    pthread_mutex_lock(&mutex_tabla[8]);  // NOTE 8
    list_add_head(&Table[idx].vals, &new->list);
    pthread_mutex_lock(&mutex_lru);  // NOTE 9
    list_add_head(&LRU, &new->lru);

    pthread_mutex_unlock(&mutex_lru);
    pthread_mutex_unlock(&mutex_tabla[8]);

    return 0;
}

/*
 * No hay free! Sólo saca el elemento del mapa. El llamante
 * debe usar eventualmente kv_release para borrarlo.
 */
struct kv *kv_take(int klen, const char *k) {
    u64 hash = hash_buf(klen, k);
    int idx = binof(hash);

    struct kv *ret = __kv_lookup(hash, idx, klen, k);
    pthread_mutex_lock(&mutex_lru);  // NOTE 10
    if (ret) {
        /* Quitar de la tabla */

        list_unlink(&ret->list);
        list_unlink(&ret->lru);

        /*
         * Nota: no tocamos el refcount. Canjeamos la referencia
         * desde la tabla por la referencia desde el código cliente,
         * quedando el refcount igual.
         */
    }
    pthread_mutex_unlock(&mutex_lru);

    return ret;
}

bool kv_remove(int klen, const char *k) {
    /* Quitar y soltar, nada más */
    struct kv *kv = kv_take(klen, k);
    if (kv) {
        kv_release(kv);
        return true;
    } else {
        return false;
    }
}

void kv_clear_all() {
    struct list *p, *swap;
    int i;

    log(3, "CLEAR ALL");

    for (i = 0; i < TableSZ; i++) {
        pthread_mutex_lock(&mutex_tabla[9]);  // NOTE 11
        list_for_each_safe(p, swap, &Table[i].vals) {
            pthread_mutex_lock(&mutex_lru);  // NOTE 12
            struct kv *kv = list_entry(p, struct kv, list);

            list_unlink(&kv->list);
            list_unlink(&kv->lru);
            __kv_release(kv);
            pthread_mutex_unlock(&mutex_lru);
        }
        pthread_mutex_unlock(&mutex_tabla[9]);
    }
}

int kv_init(int tablesz) {
    int i;

    TableSZ = tablesz;
    Table = malloc(TableSZ * sizeof Table[0]);
    if (!Table)
        quit("malloc kv_init");

    /*INICIALIZAR LOCKS*/
    for (int x = 0; x < MAX; x++) {
        pthread_mutex_init(&mutex_tabla[x], 0);
    }

    for (i = 0; i < TableSZ; i++) {
        list_init(&Table[i].vals);
    }

    pthread_mutex_init(&mutex_lru, 0);
    return 0;
}

int kv_finish() {
    free(Table);

    for (int x = 0; x < MAX; x++) {
        pthread_mutex_destroy(&mutex_tabla[x]);
    }

    pthread_mutex_destroy(&mutex_lru);

    return 0;
}

//! SECTION