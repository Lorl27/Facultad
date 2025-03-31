//? Introduccion a Procesos y Programacion de Sistema en UNIX
//  Ej. 1. Corra en una terminal el comando: echo "$$"
//  Que informacion recibe?

//* recibo un pid (el de la shell en dónde estoy!)

//  Investigue los comandos:
//  env   
//** Nos da las propiedades(variables) de nuestro enviroment
//  ps
//** Nos da la lista de procesos , en conjunto con su pid y tiempo activo(CPU). CMD: Comando ejecutado. TTY: Terminal salida*/
//  tree
//* Nos da un árbol del directorio en donde nos encontramos.
//  strace
//**  rastrea las llamadas al sistema de un programa en ejecución.  
    //* Para rastrear $ strace -p <PID> 