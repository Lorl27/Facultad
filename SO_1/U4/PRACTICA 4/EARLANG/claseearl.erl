-module(claseearl).
-export(broadcast).
-export([iniciar/0,finalizar/1]).
-export([broadcast/2,registrar/1]).
-export([loopBroadcast/1]).

iniciar() ->
    spawn(broadcast, loopBroadcast, [[]]).

finalizar(PidServer) ->
    PidServer ! {fin}.

registrar(PidServer) ->
    PidServer ! {register, self()}.

broadcast(PidServer, Msg) ->
    PidServer ! {send, Msg}.

loopBroadcast(ListClientes) ->
    receive
        {register, PidCliente} -> 
            loopBroadcast([PidCliente | ListClientes]); %++

        {send, Msg} -> 
            lists:foreach(fun(Pid)->Pid!Msg end, ListClientes)
        loopBroadcast(ListClientes);

        fin -> ok 
    end.