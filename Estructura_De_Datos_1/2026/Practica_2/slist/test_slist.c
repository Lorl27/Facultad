#include "slist.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

/**
 * Función auxiliar para verificar que una lista contiene los elementos
 * esperados en el orden correcto.
 */
void slist_assert_equals(SList lista, int slist_len, ...) {
  va_list args;
  va_start(args, slist_len);

  SNodo *nodo = lista;
  for (int i = 0; i < slist_len; i++) {
    int expected = va_arg(args, int);
    assert(nodo != NULL);
    assert(nodo->dato == expected);
    nodo = nodo->sig;
  }

  assert(nodo == NULL);
  va_end(args);
}

/**
 * Computa el cuadrado del entero dado.
 */
int cuadrado(int n) { return n * n; }

/**
 * Computa el doble del entero dado.
 */
int doble(int n) { return n * 2; }

/**
 * Tests para la función slist_map verificando que transforma correctamente
 * todos los elementos de una lista aplicando una función de transformación.
 */
void test_map_cuadrado(void) {
  SList lista = slist_crear();
  lista = slist_agregar_inicio(lista, 5);
  lista = slist_agregar_inicio(lista, 4);
  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);

  lista = slist_map(lista, cuadrado);

  slist_assert_equals(lista, 5, 1, 4, 9, 16, 25);

  slist_destruir(lista);
}

/**
 * Tests para la función slist_map con una transformación diferente (doble) para
 * validar que funciona con múltiples tipos de transformaciones.
 */
void test_map_doble(void) {
  SList lista = slist_crear();
  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);

  lista = slist_map(lista, doble);

  slist_assert_equals(lista, 3, 2, 4, 6);

  slist_destruir(lista);
}

/**
 * Tests para la función slist_partir verificando que divide correctamente
 * una lista de tamaño impar en dos mitades sin modificar la lista original.
 */
void test_slist_partir(void) {
  SList lista = slist_crear();
  lista = slist_agregar_inicio(lista, 5);
  lista = slist_agregar_inicio(lista, 4);
  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);

  SList primera = slist_crear();
  SList segunda = slist_crear();

  //slist_partir(lista, &primera, &segunda);

  slist_assert_equals(primera, 3, 1, 2, 3);
  slist_assert_equals(segunda, 2, 4, 5);
  slist_assert_equals(lista, 5, 1, 2, 3, 4, 5);

  slist_destruir(lista);
  slist_destruir(primera);
  slist_destruir(segunda);
}

/**
 * Tests para la función slist_partir2 verificando que trunca la lista original
 * de tamaño par a la mitad y retorna un puntero a la segunda mitad.
 */
void test_slist_partir2(void) {
  SList lista = slist_crear();
  lista = slist_agregar_inicio(lista, 6);
  lista = slist_agregar_inicio(lista, 5);
  lista = slist_agregar_inicio(lista, 4);
  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);

  SList segunda = slist_partir2(lista);

  slist_assert_equals(lista, 3, 1, 2, 3);
  slist_assert_equals(segunda, 3, 4, 5, 6);

  slist_destruir(lista);
  slist_destruir(segunda);
}

/**
 * Función auxiliar para imprimir un entero, utilizada como función visitante en
 * los tests de recorrido.
 */
void imprimir_int(int dato) { printf("%d ", dato); }

/**
 * Tests para la función slist_recorrer verificando que recorre correctamente
 * una lista y aplica la función visitante a cada elemento en el orden correcto.
 */
void test_slist_recorrer(void) {
  SList lista = slist_crear();
  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);

  printf("IMPRESION ESPERADA: 1 2 3\n");
  printf("IMPRESION OBTENIDA: ");
  slist_recorrer(lista, imprimir_int);
  printf("\n");

  slist_destruir(lista);
}

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  test_map_cuadrado();
  test_map_doble();
  test_slist_partir();
  test_slist_partir2();
  test_slist_recorrer();

  printf("Tests OK\n");
  return 0;
}