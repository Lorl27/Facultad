% El shell de Erlang tambi´en es un proceso; se puede usar self(). para obtener el pid actual.

% Ej. 1 (Intro). Dado el siguiente c´odigo:

-module(intro).
-import(lists,[nth/2]). 
-import(lists,[last/1]).
-export([init/0,match_test/0,nombre/1,apellido/1,string_test/0,filtrar_por_apellido/2]).

match_test() ->
    {A, B} = {5, 4},  %v
    %{C, C} = {5, 4},  %f  - ok
    {B, A} = {4, 5}, %v
    {D, D} = {5, 5}.  %v

string_test() ->
    [
        helloworld == 'helloworld',  %v
        "helloworld" < 'helloworld',  %f
        helloworld == "helloworld",  %f
        [$h, $e, $l, $l, $o, $w, $o, $r, $l, $d] == "helloworld",  %v
        [104, 101, 108, 108, 111, 119, 111, 114, 108, 100] < {104, 101, 108, 108, 111, 119, 111, 114, 108, 100},  %f
        [104, 101, 108, 108, 111, 119, 111, 114, 108, 100] > 1,  %v
        [104, 101, 108, 108, 111, 119, 111, 114, 108, 100] == "helloworld"  %v!  (ASCII)
    ].

apellido({}) -> ok;
apellido(P) -> 
    LISTA=tuple_to_list(P),
    LISTA_APELLIDO = tuple_to_list(last(LISTA)),
    %io:fwrite(nth(2,LISTA_APELLIDO)),
    nth(2,LISTA_APELLIDO).
    
nombre({}) ->    ok;
nombre(P) -> 
    LISTA=tuple_to_list(P),
    LISTA_NOMBRE = tuple_to_list(nth(2, LISTA)),
    %io:fwrite(nth(2,LISTA_NOMBRE)),
    nth(2,LISTA_NOMBRE).


tuple_test(P1, P2) ->
    io:fwrite("El nombre de P1 es ~p y el apellido de P2 es ~p~n", [nombre(P1), apellido(P2)]).  %juan garcia

filtrar_por_apellido({}, {}) -> ok;
filtrar_por_apellido(Personas, Apellido) ->
    lists:foldl
        (fun({persona, {nombre, Nombre}, {apellido, Ap}}, Acumulador) -> 
            case Ap =:= Apellido of
                true -> [Nombre | Acumulador];
                false -> Acumulador
            end
        end,
        [],
        Personas
    ).

init() ->
    P1 = {persona, {nombre, "Juan"}, {apellido, "Gomez"}},
    P2 = {persona, {nombre, "Carlos"}, {apellido, "Garcia"}},
    P3 = {persona, {nombre, "Javier"}, {apellido, "Garcia"}},
    P4 = {persona, {nombre, "Rolando"}, {apellido, "Garcia"}},
    match_test(),
    tuple_test(P1, P2),
    string_test(),
    Garcias = filtrar_por_apellido([P4, P3, P2, P1], "Garcia").  %p2-p3-p4

% a) Justifique cu´ales match de la funci´on match_test deber´ıan ser v´alidos y cu´ales no.

% b) Implemente las funciones nombre/1 y apellido/1 para que devuelvan esos campos de las tuplas
% que obtienen como argumento utilizando pattern matching.

% c) Explique el resultado de cada una de las comparaciones de la funci´on string_test/0 (es decir por
% qu´e dan true o false).

% d) Implemente la funci´on filtrar_por_apellido/2 para que devuelva los nombres (sin el apellido)
% de las personas de la lista Personas cuyo apellido coincide con Apellido utilizando comprensi´on de
% listas.
