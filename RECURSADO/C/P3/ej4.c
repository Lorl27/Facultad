// 2. Definiendo Nuevas Estructuras
// Ejercicio 4. El Tiempo
// 1. Proponer una representación con estructuras para modelar el tiempo: hhhh:mm:ss. No impondremos
// ninguna restricción con respecto a la cantidad de horas almacenadas.
// 2. Escriba una función de creación de un elemento del tipo Tiempo, el cual tome tres datos, la hora,
// los minutos, y los segundos, y retorne un elemento de tipo Tiempo válido.
// 3. Escribir una función imprimir_Tiempo la cual recibe un dato de tipo Tiempo e imprime este con
// el siguiente formato: hh:mm:ss.
// 4. Escribir una función suma_Tiempo que reciba dos tiempos dados y devuelva la suma de éstos.
// 5. Escribir una función resta_Tiempo que reciba dos tiempos dados y devuelva la resta de éstos.
// 6. Escribir una función Tiempo_Dias que reciba un dato de tipo Tiempo, y devuelve la cantidad de
// días que representa. En el caso que la cantidad de horas sea menor a 24 devolverá cero, y si por
// el contrario la cantidad de horas superará los 365 días (8760 horas corresponden a un año), por
// ejemplo, si el dato ingresado fuera 8800 horas 15 min 30 seg, la función deberá retornar, entonces
// devolverá 1 año y 40 días.