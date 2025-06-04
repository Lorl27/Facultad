% Ej. 2 (Temporizaci´on).

% a) Implemente una funci´on wait/1 que tome como argumento una cantidad de milisegundos y espere
% ese tiempo.

% b) Implemente un cron´ometro que reciba tres argumentos, Fun, Hasta y Periodo y ejecute Fun/0 cada
% Periodo milisegundos hasta que hayan pasado Hasta milisegundos sin bloquear el int´erprete.

% Un caso de prueba ser´ıa:
% % cronometro(fun () -> io:fwrite("Tick~n") end, 60000, 5000).
% % % que imprimir´ıa Tick cada 5 segundos durante un minuto.


-module(temporizacion).
-export([wait/1,crono/3]).

wait(0) -> ok;
wait(N)-> 
    receive
    after(1000*N) -> ok
end.

% hasta q pase HASTA , wait(HASTA)  - paralelamente Periodo(Fun(0)
crono(Fun,0,Periodo) -> ok;
crono(Fun, Hasta, Periodo) ->
    if 
       ( Hasta < Periodo) ->
            ok;
        true -> 
            receive
                after(Periodo) -> Fun()
            end,
            crono(Fun,Hasta-Periodo,Periodo)
end.

    
%crono(fun () -> io:fwrite("Tick~n") end, 60000, 5000).
