# 16) Dado el siguiente programa en C:
# #include <stdio.h>
# int f(char a, int b, char c, long d,
# char e, short f, int g, int h)
# { printf("a: %p\n", &a);
# printf("b: %p\n", &b);
# printf("c: %p\n", &c);
# printf("d: %p\n", &d);
# printf("e: %p\n", &e);
# printf("f: %p\n", &f);
# printf("g: %p\n", &g);
# printf("h: %p\n", &h);
# return 0;
# }
# int main(void)
# {
# return f(’1’, 2, ’3’, 4, ’5’, 6, 7, 8);
# }
# a) Realice un diagrama de la pila cuando se está ejecutando f. Indique en el diagrama la
# ubicación y el espacio utilizado por cada argumento.
# b) Indique la dirección dentro de la pila en donde está almacenada la dirección de retorno
# de f y si es posible verifique con GDB. Sugerencia: utilice el comando si, para avanzar de a una
# instrucción.

# Direcciones
#  Altas (RAM)
#      │
#      │      ┌──────────────────────────────────────────┐
#      ├─────►│  Argumento 8: h (int 8)                 │  24(%rbp)  [8 bytes]
#      │      ├──────────────────────────────────────────┤
#      │      │  Argumento 7: g (int 7)                 │  16(%rbp)  [8 bytes]
#      │      ├──────────────────────────────────────────┤
#      │      │  Dirección de retorno a main             │   8(%rbp)  [8 bytes]
#      │      ├──────────────────────────────────────────┤
#      │      │  %rbp anterior (Frame Pointer de main)   │   0(%rbp)  [8 bytes] ◄── %rbp
#      │      ├──────────────────────────────────────────┤
#      │      │  Copia local de 'd' (long 4)             │  -8(%rbp)  [8 bytes] (de %rcx)
#      │      ├──────────────────────────────────────────┤
#      │      │  Copia local de 'b' (int 2)              │ -12(%rbp)  [4 bytes] (de %esi)
#      │      ├──────────────────────────────────────────┤
#      │      │  Copia local de 'g' / auxiliares         │ -16(%rbp)  ...
#      │      ├──────────────────────────────────────────┤
#      │      │  Copia local de 'f' (short 6)            │ -18(%rbp)  [2 bytes] (de %r9w)
#      │      ├──────────────────────────────────────────┤
#      │      │  Copia local de 'e' (char '5')           │ -19(%rbp)  [1 byte]  (de %r8b)
#      │      ├──────────────────────────────────────────┤
#      │      │  Copia local de 'c' (char '3')           │ -20(%rbp)  [1 byte]  (de %dl)
#      │      ├──────────────────────────────────────────┤
#      │      │  Copia local de 'a' (char '1')           │ -21(%rbp)  [1 byte]  (de %dil)
#      │      └──────────────────────────────────────────┘ ◄── %rsp
#      ▼
# Direcciones
#  Bajas (RAM)