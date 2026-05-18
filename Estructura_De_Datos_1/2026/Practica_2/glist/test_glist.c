#include "glist.h"
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

/**
 * Función auxiliar para verificar que una lista contiene los elementos esperados en el orden correcto.
 */
void glist_assert_equals(FuncionComparadora comparar, GList lista, int glist_len, ...) {
  va_list args;
  va_start(args, glist_len);

  GNode *nodo = lista;
  for (int i = 0; i < glist_len; i++) {
    void *expected = va_arg(args, void*);
    assert(nodo != NULL);
    assert(comparar(nodo->data, expected) == 0);
    nodo = nodo->next;
  }

  assert(nodo == NULL);
  va_end(args);
}

char caracteres[] = {'A', 'B', 'C', 'D'};

/**
 * Imprime un caracter.
 */
void char_print(void *data) { printf("%c ", *(char *)data); }

/**
 * Retorna el mismo puntero sin copiarlo físicamente.
 */
void *char_copy(void *data) { return data; }

/**
 * Destructor no-op para caracteres estáticos.
 */
void char_destroy(void *data) {
  (void)data;
  return;
}

/**
 * Función comparadora para caracteres.
 */
int char_compare(void *a, void *b) {
  char char_a = *(char *)a;
  char char_b = *(char *)b;
  if (char_a < char_b)
    return -1;
  else if (char_a > char_b)
    return 1;
  else
    return 0;
}

/**
 * Tests para la función glist_reverso.
 */
void test_glist_reverso(void) {
  GList lista = glist_crear();
  lista = glist_agregar_inicio(lista, &caracteres[3], char_copy);
  lista = glist_agregar_inicio(lista, &caracteres[2], char_copy);
  lista = glist_agregar_inicio(lista, &caracteres[1], char_copy);
  lista = glist_agregar_inicio(lista, &caracteres[0], char_copy);

  GList reverso = glist_reverso(lista, char_copy);

  glist_assert_equals(char_compare, reverso, 4, &caracteres[3], &caracteres[2], &caracteres[1], &caracteres[0]);

  glist_destruir(lista, char_destroy);
  glist_destruir(reverso, char_destroy);
}

/**
 * Tests para la función glist_eliminar.
 */
void test_glist_eliminar(void) {
  GList lista = glist_crear();

  lista = glist_agregar_inicio(lista, &caracteres[3], char_copy);
  lista = glist_agregar_inicio(lista, &caracteres[2], char_copy);
  lista = glist_agregar_inicio(lista, &caracteres[1], char_copy);
  lista = glist_agregar_inicio(lista, &caracteres[0], char_copy);

  lista = glist_eliminar(lista, char_destroy, 0);

  glist_assert_equals(char_compare, lista, 3, &caracteres[1], &caracteres[2], &caracteres[3]);

  lista = glist_eliminar(lista, char_destroy, 1);

  glist_assert_equals(char_compare, lista, 2, &caracteres[1], &caracteres[3]);

  lista = glist_eliminar(lista, char_destroy, 9);

  glist_assert_equals(char_compare, lista, 2, &caracteres[1], &caracteres[3]);

  glist_destruir(lista, char_destroy);
}

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  test_glist_reverso();
  test_glist_eliminar();

  printf("Tests OK\n");
  return 0;
}