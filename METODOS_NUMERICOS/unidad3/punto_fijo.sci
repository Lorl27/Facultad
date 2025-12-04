function raiz = punto_fijo(fun, a, tol, iter)
    b = a;
    i = 0;
    while abs(fun(b) - b) > tol && i < iter
        c = fun(b);
        b = c;
        i = i + 1;
    end
    if i >= iter then
        disp("Se alcanzo el maximo de iteraciones. El punto fijo no será preciso");
    end
     disp ("Número de iteraciones: " + string(i));
     raiz = b;
     disp("RAIZ:"+string(b));
endfunction

deff('y=g(x)', 'y = 2.^(x-1)');
punto_fijo(g,1,0.01,95);

/// EJERCICIO 7 DE P3:

// Definimos g(l)
deff('y=g(l)', 'y = (122.5/%pi)*tanh((8*%pi)/l)');

// Aplicamos el método
punto_fijo(g, 1, 0.01, 100);


deff('y=m(x)','y=(exp(x) - x)/( 2)');
punto_fijo(m, -1, 0.001,10);


//------------------


function puntos = todos_puntos_fijos(g, a, b, paso, tol, iter)
    x = a:paso:b;
    f = g(x) - x;
    puntos = [];
    for i = 1:length(x)-1
        if f(i)*f(i+1) <= 0 then  // cambio de signo
            xi = x(i);
            xf = x(i+1);
            // Aplicamos punto fijo a partir del valor inicial xi
            raiz = punto_fijo(g, xi, tol, iter);
            puntos = [puntos, raiz];
        end
    end
    puntos = unique(fix(puntos*1e4)/1e4); // redondea a 4 decimales
    disp("Todos los puntos fijos encontrados:");
    disp(puntos);
endfunction



// 1) Tu función de ejemplo m(x)
deff('y=m(x)', 'y = (exp(x) - x)/2');
todos_puntos_fijos(m, -2, 2, 0.1, 0.001, 50);
todos_puntos_fijos(m, -2, 3, 0.01, 0.001, 50);


///------




