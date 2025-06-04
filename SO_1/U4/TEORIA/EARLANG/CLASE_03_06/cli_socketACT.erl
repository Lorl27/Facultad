-module(cli_socket).  %%PÁSIVO

-define(PUERTO,1880).
-define (DIR,"localhost").


-export([cliente/0]).


cliente()->
    case gen_tcp:connect(?DIR,?PUERTO,[binary],{active,true}) of
        {ok,Socket} ->
            {ok,Str} = io:fread("enviar;","~s"), %lee x teclado,
        gen_tcp:send(Socket,Str),

        receive
            Msg->io:format("recibi ~p~n",[Msg]);
            after 100 -> io:format("a ~n")
            end,
       
        gen_tcp:close(Socket),
        ok;
    {err,Reason} -> io:format("error2222 ~p~n",[Reason])
    end.



%processes()