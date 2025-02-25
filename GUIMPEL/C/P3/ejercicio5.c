// 4. Estructuras y Punteros
// Ejercicio 5. Dadas las siguientes definiciones de estructura y asignaciones

 struct estudiante
{
     char *apellido;
     int anio_ingreso;
     char division;

};

 struct estudiante nuevo, *pest = &nuevo;
 nuevo.apellido = "Lopez";
 nuevo.anio_ingreso = 1998;
 nuevo.division = 'A';

// Determine si las siguientes sentencias son correctas. En caso de ser incorrectas explique por
// qué, en caso de ser correctas indique cuál es el valor que representan.
// a. nuevo->apellido  (no. nuevo no es un puntero)
// b. pest->division (si. devolvera 'A')
// c. (*pest)->apellido (error.)
// d. *pest->apellido+2 (error)
// e. *(pest->apellido+2)  (corecto, cevolvera 'p')  IGUAL QUE F
// f. pest->apellido[2] (correcto, devolvera 'p')