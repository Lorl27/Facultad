-module(ej_m).
-export([test/0]).

%-define(DEBUG,debug).  %si no esta def: c(ej_m,[{d,'DEBUG'}]).
-ifdef(DEBUG).
    -define(DBG(String,Arg),io:format(String,Arg)).
-else.
    -define(DBG(String,Arg),ok). %definir....
-endif.


test()->
    ?DBG("jaidj: ~p~n",[test]),
    ok_t.
