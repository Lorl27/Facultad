% Ej. 9 (Lanzar Procesos en Anillos). Escriba un programa que lance N procesos en anillos. Cada
% proceso recibir´a dos clases de mensajes:
% {msg, N} donde N es un entero. Deber´a decrementarlo y enviarlo al siguiente proceso en el anillo si
% N es mayor que cero. En caso contrario deber´a enviar un mensaje exit y terminar cuando todos los
% dem´as lo hayan hecho.
% exit cuando el proceso debe terminar.

% Modifique el programa para que el mensaje enviado gire una vez alrededor del anillo y sea descartado por
% el que inici´o el env´ıo.

-module(ej9).
-export([anillo/1, crear/1]).

% anillo(0)->ok;
% anillo(N)-> %n=proceso
%         %Pid = spawn(ej9,anillo,[]),
%     receive
%         {msg,N} -> 
%             if( N>0) -> 
%                 anillo(N-1);
%             true->  self() ! {exit},
%                     ok
%             end;
%         {exit} -> ok
%     end.

%  anillo(0)->ok;
%  anillo(N)-> 
%      receive
%          {exit, N} -> 
%              ! {fin, self()}

Lista = [].



crear(0) -> ok;
crear(N) ->
    proceso = spawn(ej9, anillos, []),
    crear(N-1).