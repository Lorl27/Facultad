-define (MACRO,exp).
-define(FUNMACRO,).

% ?MODULE macro, con ? accedemos a ella

% -- ejemplo-----------------------------
-define(TIMEOUT,500).  %definicion

after
    ?TIMEOUT   %USO
%---------------------------

%activar bandera c(modulo,[{d,Flag}].