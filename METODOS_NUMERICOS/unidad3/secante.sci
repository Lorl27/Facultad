function raiz = secante(fun, a, b, tol, iter)
    fa = fun(a);
    fb = fun(b);
    c = b - fb * (b - a) / (fb-fa);
    fc = fun(c);
    i = 0;
    while abs(fc)>tol && i < iter
        i = i + 1;
        a = b;
        fa = fb;
        b = c;
        fb = fc;
        c = b - fb * (b - a) / (fb-fa);
        fc = fun(c);
    end
    if (i >= iter) then 
        disp("Se alcanzo el maximo de iteraciones. La raíz no será precisa.");
    end
    disp("Número de iteraciones: " + string(i));
    disp("📍 Raíz encontrada: " + string(c));

    raiz = c;
endfunction

deff('y=r(x)', 'y = x.^2/4 - sin(x)');
secante(r,1,2,0.01,5);
