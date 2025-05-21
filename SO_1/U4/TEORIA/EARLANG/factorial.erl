-module (factorial).
-export ([fact/1]).

% funcion x pattern matching (se prueba x casos)
fact(0) -> 1;
fact(N) -> N*fact(N-1).