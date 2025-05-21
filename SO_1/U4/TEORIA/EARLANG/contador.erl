-module(contador).  
-export ([contador/1]).

% soporte objeto contador -> objeto q soporta una operacion que adicicona uno a su valor y, una operacion de consulta del valor

% Nros naturales (RECETA)
contador(0) -> 1;
contador(N) -> 1+contador(N-1).