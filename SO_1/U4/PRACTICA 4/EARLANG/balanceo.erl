% Ej. 3 (Balanceo de Carga). La siguiente funci´on implementa un balanceo de carga sobre una lista de
% servidores. Al recibir un pedido de la forma {req, Arg, Pid}, lo reenv´ıa aleatoriamente a uno de los
% servidores y espera su respuesta. Luego, reenv´ıa la respuesta al cliente que origin´o el pedido.

-module(balanceo).
-export([bal/1]).

bal(Servs) ->
    receive
        {req, Arg, Pid} ->
            Proc = lists:nth(rand:uniform(length(Servs)), Servs),
            Proc ! { req, Arg, self() },
            receive %recibir msg
                Reply -> Pid ! Reply
            end
    end,



bal(Servs).

% Explique el problema con esta implementaci´on. Proponga una soluci´on e implem´entela.
% El problema es que la conexión entre procesos requiere que ambos conozcan sus resp. PID, cosa que no pasa acá.
