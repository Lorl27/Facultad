### - erl  (vm)

# fin sentencia: .
# casos ;
# dentro de linea, separar: ,


## Indicar cosas

# Indica el nombre
-module(factorial).  
# Indica la cantidad de argumentos que toma, en este caso:1
-export ([fact/1]). 

# Etiquetas  a PID
[...]

## Compilar
# Iniciar
c(factorial).  
# Ejecutar  
factorial:fact(5).   

# Salir
q().   


## DATOS

# LISTA
[]

# USANDO IF
``
min([Hd|Tl]) ->
    Rest=min(Tl),
    if
        (Hd < Rest) -> 
            Hd;
        true -> %else
            Rest
    end.
``

# Send n Receive
ping() -> 
    receive
        {fin, _} ->
            io:fwrite("END ping ~n") ,
            pingok;
        {N,PidPong} -> 
            io:fwrite("Ping!"),
            PidPong ! {N,self()},
            ping()
    end.

play()->
    PidPong = spawn(procesos,pong,[]),
    PidPing= spawn(procesos,ping,[]),
    PidPong ! {10,PidPing},
    playok.


###NOTE - ¿Qué es un lenguaje funcional no puro?
Es un lenguaje que no tiene transparencial referencial, es decir que los mismos argumentos pueden tener diferentes resultados debido al modelo de factores (presentan efectos colaterales).
Un ejemplo es la función clock() , que cada vez que la llamas devuelve distintos resultados.

**tranparencia funcional**  
Son características de los lenguajes puros, son computables ya que el mismo argumento devuelve SIEMPRE el mismo resultado. 
Un ejemplo son las funciones matemáticas.

//FIXME -  - depende solamente de las entradas y no del contexto . (no me acuerdo si era que tiene o no tiene tranparencia esto)