
%en header
-record(nuevoId,{nombre,cid}).


%en code
% {nuevoId, Nombre, CId} -> CId ! {ok,N},
%                                   servnombres(maps:put(N,Nombre,Map),N+1);
-include("sr_hrl").
#nuevoId{nombre=Nombre,cid=CId}->
    #nuevoId.cid ! {ok,N},



nuevoNombre(Nombre) ->
    server!#nuevoId{nombre= Nombre, cid=self()},
    receive
        {ok,Id} -> io:format(" Se asocio el id ~p al nombre ~p~n ",[Id,Nombre]);
        _-> error
    end.
