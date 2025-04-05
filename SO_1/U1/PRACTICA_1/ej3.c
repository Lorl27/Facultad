// Ej. 3. El comando yes imprime lineas conteniendo una "y" infinitamente. Es usado para simular una
//  respuesta afirmativa para instaladores o programas similares (i.e. "si a todo" ) haciendo simplemente
//  yes | ./installer. Como piensa que esta implementado? Al ejecutar un pipeline como el anterior
//  como es el uso de CPU del proceso yes?

//  Simplemente con un printf("Y") en bucle, ya que es una salida estándar.

// Cuando se ejecuta el pipeline , el comando "Y" genera líneas de texto rápidamente y las redirige al stdin del instalador. El uso de CPU de yes es relativamente bajo si consideramos solo la tarea de imprimir "y" repetidamente. Sin embargo, dado que yes está en un bucle infinito, el proceso consumirá un núcleo de CPU al máximo mientras esté en ejecución. Esto ocurre porque el proceso no tiene ninguna operación de bloqueo