# **- erl  (vm)**

***

## Sintaxis

* **Fin sentencia**:             ` .`
* **Casos:**             ` ;`
* **Para separar, dentro de misma línea:** `,`
* **Comentarios**: `%algo`

***

## Indicar cosas

##### Indica el nombre

```Erlang
-module(factorial).
```

Nota: Debe coincidir con el nombre del archivo, este nombre también se usará en `spawn`

##### Indica la cantidad de argumentos que toma, en este caso:1

```Erlang
-export ([fact/1]).
```

##### Etiquetas  a PID

```Erlang
PidPong = spawn(procesos,pong,[]).
```

***

## Compilar

##### Iniciar

```Erlang
c(factorial).
```

##### Ejecutar

```Erlang
factorial:fact(5).
```

##### Salir

```Erlang
q().
```

***

## DATOS

##### LISTA

`[]`

## USANDO IF

```Erlang
min([Hd|Tl]) ->
    Rest=min(Tl),
    if
        (Hd < Rest) -> 
            Hd;
        true -> %else
            Rest
    end.
```

## Send n Receive

```Erlang
ping() ->
    receive
        {fin, \_} ->
            io:fwrite("END ping \~n") ,
            pingok;
        {N,PidPong} ->
            io:fwrite("Ping!"),
            PidPong ! {N,self()},
            ping()
    end.
```

```Erlang
play()->
    PidPong = spawn(procesos,pong,\[]),
    PidPing= spawn(procesos,ping,\[]),
    PidPong ! {10,PidPing},
playok.
```

***

# ¿Qué es un lenguaje funcional no puro?

Es un lenguaje que no tiene transparencial referencial, es decir que los mismos argumentos pueden tener diferentes resultados debido al modelo de factores (presentan efectos colaterales).

Un ejemplo es la función clock() , que cada vez que la llamas devuelve distintos resultados.

**Tranparencia funcional**&#x20;


Son características de los lenguajes puros, son computables ya que el mismo argumento devuelve SIEMPRE el mismo resultado.
Un ejemplo son las funciones matemáticas.

~~//FIXME : depende solamente de las entradas y no del contexto . (no me acuerdo si era que tiene o no tiene tranparencia esto)~~
