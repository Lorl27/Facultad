//  Ej. 4. Que pasa cuando un proceso no libera su memoria (con free()) antes de terminar?

// La memoria queda bloqueada, volviendose basura in-accesible. Pero, luego el SO la borrará al terminar el programa(no se produce fuga de memoria"