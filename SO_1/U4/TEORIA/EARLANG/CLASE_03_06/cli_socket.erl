-module(cli_socket).  %%PÁSIVO

-define(PUERTO,1880).
-define (DIR,"localhost").


-export([cliente/0]).


cliente()->
    case gen_tcp:connect(?DIR,?PUERTO,[binary],{active,false}) of
        {ok,Socket} ->
            {ok,Str} = io:fread("enviar;","~s"), %lee x teclado,
        gen_tcp:send(Socket,Str),
        case gen_tcp:recv(Socket,0)  of 
            {ok,Paquete} -> io:format("recibi ~p~n",[Paquete]);
            {err,Reason} -> io:format("error ~p~n",[Reason])
        end,
        gen_tcp:close(Socket),
        ok;
    {err,Reason} -> io:format("error2222 ~p~n",[Reason])
    end.



%processes()