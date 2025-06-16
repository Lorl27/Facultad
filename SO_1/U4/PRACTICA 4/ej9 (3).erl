% Ej. 9 (Lanzar Procesos en Anillos). Escriba un programa que lance N procesos en anillos. Cada
% proceso recibir´a dos clases de mensajes:
% {msg, N} donde N es un entero. Deber´a decrementarlo y enviarlo al siguiente proceso en el anillo si
% N es mayor que cero. En caso contrario deber´a enviar un mensaje exit y terminar cuando todos los
% dem´as lo hayan hecho.
% exit cuando el proceso debe terminar.

% Modifique el programa para que el mensaje enviado gire una vez alrededor del anillo y sea descartado por
% el que inici´o el env´ıo.

-module(ej99).
-export([anillo/1,todo/0]).

 anillo(0)-> self() ! {exit},
    io:fwrite("Pong! end ~n"),
    ok;
 anillo(N)-> %n=proceso
    receive
        {msg,N} -> 
            io:fwrite("Pong! recv: ~p ~n", [N]),
            Pid = spawn(ej9,anillo,[N-1]),
            io:fwrite("Pong! recv: ~p ~n", [N-1]),
            Pid!{msg,N-1},
            anillo(N-1);
        {exit} -> ok
    end.

todo()->
    PidUno = spawn(procesos,anillo,[]),
    %PidUltimo= spawn(procesos,anillo,[N]),
    self() ! {10,PidUno},
    todook.