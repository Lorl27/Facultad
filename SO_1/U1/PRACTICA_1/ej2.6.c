//  f) Al hacer un malloc de 1GB aumenta el uso de memoria de un proceso? Explique.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
	char *p;
	long i;
	size_t l = 1;

	l <<= 30; // 1GB

	printf("A\n"); getchar();

	p = malloc(l);
	assert(p);
	// Hasta acá no se usó memoria.

	printf("B\n"); getchar();

	// Esto la empieza a usar
	for (i = 0; i < l; i++)
		p[i] = 0;

	printf("C\n"); getchar();

	int x = malloc_trim();

	printf("D %i\n", x); getchar();

	free(p);

	printf("E %i\n", x); getchar();

	x = malloc_trim();

	printf("F %i\n", x); getchar();

	return 0;
}


/* NOTE - 

Punto	Acción	                    ¿   Aumenta el uso de memoria?
A	    Antes de malloc(1GB)	        ❌ No
B	    Después de malloc(1GB)	        ❌ No (solo asigna virtualmente)
C	    Después de escribir en p[i]	    ✅ Sí (1GB usado)
D	    Primer malloc_trim()	        ❓ Depende del sistema -->NO
E	    Después de free(p)	            ❌ (liberado en heap, pero puede seguir ocupado)
F	    Segundo malloc_trim()	        ❓ Depende del sistema -->NO


 */