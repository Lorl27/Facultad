// 4. Funciones
// Ejercicio 15. Escribir una función maximo que tome como parámetro dos enteros y devuelva
// el máximo entre ellos. Utilizar esa función para calcular el máximo entre 4 enteros que se le
// soliciten al usuario.
// Ejercicio 16. Tres números positivos pueden ser la medida de los lados de un triángulo si y
// sólo si el mayor de ellos es menor que la suma de los otros dos. Escribir y probar una función
// ladosTriangulo que devuelva 1 si los tres números que se le pasan verifican esta condición, y
// 0 en caso contrario.
// Ejercicio 17. Definir una función esRectangulo que tome tres enteros y devuelva 1 si los
// números que se le pasan pueden ser los lados de un triángulo rectángulo, y 0 en caso contrario. Sugerencia: una manera sería verificar si el cuadrado del mayor es igual la suma de los 
// cuadrados de los otros dos. Sin embargo existe otra manera utilizando solo una vez una función max3, que devuelve el máximo entre tres enteros dados. Definir ambas funciones y probar
// esRectangulo con las entradas (3,5,4), (5,13,12) y (7,3,5).
// Ejercicio 18. La fecha del domingo de Pascua corresponde al primer domingo después de
// la primera luna llena que sigue al equinoccio de primavera. Dado un año, los cálculos que
// permiten conocer esta fecha son:
// A = año
// B = año
// C = año
// D = (19 * A + 24)
// E = (2 * B + 4 * C + 6 * D + 5)
// N = (22 + D + E)
// Donde N indica el número del día del mes de marzo (o abril si N es superior a 31) correspondiente al domingo de Pascua. Escribir un programa que lea un año y muestre el día y el mes
// en el que se celebró o se celebrará el domingo de Pascua ese año.Utilizar una función a la que
// se le pase como parámetro el año y retorne el valor de N. El programa principal realiza el resto
// del proceso.
// Ejercicio 19. La sucesión de Fibonacci se define de la siguiente manera:
// f(n) =
// 
// 
// 
// 0 si n = 0
// 1 si n = 1
// f(n − 1) + f(n − 2) si n > 2
// Escribir una función recursiva f que tome un entero n y devuelva el correspondiente valor
// según la sucesión de Fibonacci.