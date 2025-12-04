// Algoritmo de Horner simple
function y = horner2(a, x0)
    // a: vector de coeficientes [a0, a1, ..., an]
    // x0: punto donde evaluar
    n = length(a);
    b = a(n); // b_n = a_n
    for i = n-1:-1:1
        b = a(i) + x0*b;
    end
    y = b; // b0 = p(x0)
endfunction

// Ejemplo:
a = [2, -6, 2, -1]; // p(x) = 2 - 6x + 2x^2 - x^3
x0 = 3;
disp(horner2(a,x0), "p(3) = ");
disp(horner(a,x0), "p(3)_2 = ");

/////
// Horner generalizado: calcula p(x0) y p'(x0)
function [pval, dval] = horner_deriv(a, x0)
    n = length(a);
    b = a(n); // para p(x0)
    c = 0;    // para p'(x0)
    for i = n-1:-1:1
        c = b + x0*c;
        b = a(i) + x0*b;
    end
    pval = b;   // p(x0)
    dval = c;   // p'(x0)
endfunction

// Ejemplo
a = [2, -6, 2, -1]; // p(x) = 2 - 6x + 2x^2 - x^3
x0 = 3;
[pval, dval] = horner_deriv(a, x0);
disp(pval, "p(3) = ");
disp(dval, "p_d(3) = ");
