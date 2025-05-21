-module(min).
-export([min/1]).

%minimo de una lista
min([Hd])-> Hd;
min([Hd|Tl]) ->
    Rest=min(Tl),
    if
        (Hd < Rest) -> 
            Hd;
        true -> %else
            Rest
    end.