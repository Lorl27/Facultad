-module(servid_template).

%acepta 4 tipos de pedidos: nuevoId(name,id)->nuevo id , buscarId(id, pid cli)-> devuelve name aso al id, finalizar->chau srv,rsp con ok, verLista(pid cliente)-> envio mapa-to-list



%%%%%%
%% Pequeño ejercicio de clase
%% el servidor aceptara 4 tipos de pedidos/mensajes:
%% + nuevoId(Nombre, PidResp) -> Se generará un nuevo identificar para `Nombre` y se responderá al cliente.
%% + buscarId(Id, PidResp) -> Se responde a `PidResp` el nombre asociado a `Id`.
%% + verLista(PidResp) -> Se envía a `Pidresp` la lista de pares (Id,Nombre).
%% + finalizar(PidResp) -> Se finaliza el servicio y se responde con un `ok`.
%%

%% Creación y eliminación del servicio
-export([iniciar/0, finalizar/0, servnombres/2]).

%% Servidor
-export([serverinit/1]).

%% Librería de Acceso
-export([nuevoNombre/1, quienEs/1, listaDeIds/0]).

%% Funciones de testing
-export([test/0,client/0]).

% Iniciar crea el proceso servidor, y devuelve el PId.
iniciar() -> 
    PId= spawn(?MODULE,serverinit,[self()]),
    register(server,PId).%,
    %-> server.

%%%%%%%%%%%%%% Librería de Acceso
%% Dado un nombre y un servidor le pide que cree un identificador único.
nuevoNombre(Nombre) ->
  server!{nuevoId, Nombre, self()},
  receive
    {ok,Id} -> io:format(" Se asocio el id ~p al nombre ~p~n ",[Id,Nombre]);
    _-> error
end.


%% Función que recupera el nombre desde un Id
quienEs(Id) ->
  server!{buscarId, Id, self()},
  receive
    {ok,Nombre} -> io:format(" El nombre recuperado desde el id ~p es ~p~n ",[Nombre,Id]);
    _-> error
end.


%% Pedimos la lista completa de nombres e identificadores.
listaDeIds() ->
  server!{verLista,self()},
    receive
    {ok,Lista} -> io:format(" Lista-srv : ~p~n ",[Lista]);
    _-> error
end.

% Ya implementada :D!
finalizar() ->
    server!{finalizar,self()},
    receive
      fin -> io:format(" FINISH!!!!!!!! ~n ",[]);
      _-> error
  end.

%%%%%%%%%%% Servidor
%% Función de servidor de nombres.
serverinit(PInit) -> %PInit : quién llamo a la f. main
    %% Comenzamos con un mapa nuevo, y un contador en 0.
    PInit ! ok,
    servnombres(maps:new(),0).  %indica id dispo - el proximo a dar.

servnombres(Map, N) ->
    receive
        %% Llega una petición para crear un Id para nombre
        {nuevoId, Nombre, CId} -> CId ! {ok,N},
                                  servnombres(maps:put(N,Nombre,Map),N+1);
        %% Llega una petición para saber el nombre de tal Id
        {buscarId, NId, CId} ->  
          %CId ! maps...
            case maps:find(NId,Map) of
                {ok,Nombre} -> CId ! {ok,Nombre};
                error -> CId ! error
              end,
              servnombres(Map, N);
        %% Entrega la lista completa de Ids con Nombres.
        {verLista, CId} -> CId ! {ok,maps:to_list(Map)},
                          servnombres(Map, N);
        %% Cerramos el servidor.
        {finalizar, CId } -> CId ! fin;


        _ -> io:format(" error - no.~n"),
              servnombres(Map, N)
    end.

client() ->
  nuevoNombre(pepa),
  listaDeIds(),
  nuevoNombre(pepe),
  listaDeIds(),
  quienEs(0),
  quienEs(1),
  finalizar(),
  ok.

test() ->
  servid_template:iniciar(),
  spawn(?MODULE, client, []),
  ok_test.
