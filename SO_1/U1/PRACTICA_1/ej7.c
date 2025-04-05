//  Ej. 7 (Mini Shell). Implemente una version mnima de una shell. El programa debera esperar lneas
//  por entrada estandar, y al recibir una ejecutar el comando correspondiente, de la misma manera que lo
//  hace, por ejemplo, bash.

//  a) Implemente una version basica que simplemente ejecuta el comando y espera que el mismo termine
//  antes de pedir otro. El comando puede especi carse por su path completo o solamente por su nombre
//  si se encuentra en algun directorio del $PATH (pista: ver execvp()). Ejemplo:
//  $ ls
//  Makefile shell.c shell
//  b) Agregue la posibilidad de pasar argumentos a los comandos, ejemplo:
//  $ ls /
//  bin boot dev etc ...

//  c) Implemente redireccion de la salida estandar. Ahora los comandos pueden tener la forma cmd > file,
//  causando que la salida de cmd sea escrita directamente al archivo file. La shell no debe recibir la
//  salida y escribirla al archivo, sino que a medida que el comando cmd escriba a su salida estandar,
//  esta salida vaya directamente al archivo.
//  Puede usar open("archivo.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644) para abrir (o crear)
//  un archivo con permisos usuales. Otras referencias: man 2 open, man 2 close, man 2 dup.
//  Ejemplo:1
//  $ ls / > salida.txt
//  $ cat salida.txt
//  bin
//  boot
//  dev
//  ...