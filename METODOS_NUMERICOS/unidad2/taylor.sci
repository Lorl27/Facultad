//EJERCICO 5
// Función que calcula el polinomio de Taylor de grado n en el punto v
function tval = taylor(f, a, n, v)
    // f : función handle, por ej. f = sin
    // a : punto de expansión
    // n : grado del polinomio
    // v : punto donde evaluar
    tval = 0;
    g = f; // la función actual (0-ésima derivada)
    for k = 0:n
        // evaluar derivada k-ésima en a
        fk = g(a);
        term = fk / factorial(k) * (v - a)^k;
        tval = tval + term;
        // siguiente derivada
        g = derivative(g); 
    end
endfunction

// Aproximar e^x en v=1, expandiendo en a=0 con grado 5
f = exp;
a = 0;
n = 5;
v = 1;
aprox = taylor(f, a, n, v);

disp(aprox, "Aproximación con Taylor:");
disp(exp(1), "Valor real:");
disp(abs(aprox - exp(1)), "Error:");
