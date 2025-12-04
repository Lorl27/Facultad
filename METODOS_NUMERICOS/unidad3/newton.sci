function salida = newton(fun, a, tol, iter, h)
    i = 0;
    fa = fun(a)
    dfa = (fun(a + h) - fa) / h;
    b = a - fa / dfa
    delta = abs(b - a)
    while delta > tol && i < iter
        i = i + 1;
        a = b;
        fa = fun(a)
        dfa = (fun(a + h) - fa) / h;
        b = a - fa / dfa
        delta = abs(b - a)
    end
    if delta > tol then 
        disp("Se alcanzo el maximo de iteraciones. La raíz no será precisa.");
    end
    disp("Número de iteraciones: " + string(i));
    salida = b;
    disp("RAIZ: " + string(b));
endfunction


// EJ 7.B P3:

// Definimos la función f(l)
deff('y=f(l)', 'y = (2*%pi/5)^2 - 9.8*(2*%pi/l)*tanh((2*%pi*4)/l)');

// Llamamos al método de Newton
newton(f, 27.9, 1e-4, 100, 1e-6);
