-module(srv_socket).  %%PÁSIVO

-define(PUERTO,1880).

-export([start/0,receptor/1,echo/1]).


start()->
    {ok,Socket}=gen_tcp:listen(?PUERTO,[binary,{active,false}]),
    spawn(?MODULE,receptor,[Socket]). %start().


receptor(Socket)->
    case gen_tcp:accept(Socket) of
        {ok,CSocket} ->  spawn(?MODULE,echo,[CSocket]);
        {error,_}->error
    end,
    receptor(Socket).

echo(Socket)->
    case gen_tcp:recv(Socket,0)  of 
        {ok,Paquete} -> io:format("recibi ~p~n",[Paquete]),
        gen_tcp:send(Socket,Paquete),
        echo(Socket);
        {error,closed}->o:format("chau conex ~n")
    end.