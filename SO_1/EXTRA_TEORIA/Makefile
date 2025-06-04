

VAR = "My little pony."
GCC =  gcc #declaro var para las cosas q usamos
CFLAGS= -pthread -Wall #-02
.PHONY: example example-var  #declaro los comandos que tengo

example:  # en consola: make example
	echo "teorema 1."

example-var:
	echo $(VAR)

build-old: # construir comando
	gcc ej6_a.c -lpthread -o ejemplo 

# si hago make solo en comando, se ejecuta solo el primero.

build: # construir comando
	$(GCC) ej6_a.c $(CFLAGS) -o ejemplo 

build-optimizado: # todos los archivos .c
	$(GCC) *.c $(CFLAGS) -o ejemplo   

build-openmp: CFLAGS= -fopenmp -Wall
build-openmp:
	$(GCC) ej6_a.c $(CFLAGS) -o ejemplo 


# al escribir un comando...
# comando: requerimientos (primero corre esto)
# 	accion

# make clean : borra archivos que no me interesan.
clean:
	rm ejemplo
	rm -r *.o  
#recursivo

build-optimizado-limp: clean 
	$(GCC) *.c $(CFLAGS) -o ejemplo   



#############################################
#COSAS EN EL MAIN

# $@  nombre target (nombre de comando)
# $^  todos los pre-requerimientos
# $< el 1er pre-requerimiento

rwlock: rwlock-rpref.c lec.c 
	$(GCC) $(CFLAGS) $^ -o $@