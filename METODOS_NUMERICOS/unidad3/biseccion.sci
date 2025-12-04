function raiz = biseccion(fun, a, b, tol)
    fa = fun(a);
    fb = fun(b);
    if fa*fb > 0 then
        error("Las imágenes de los puntos no tienen signos opuestos.");
    end
    c = (a + b) / 2;
    fc = fun(c);
    i = 0
    delta = b - c;
    while abs(delta) > tol 
        if fa*fc < 0 then 
            b = c;
            fb = fc;
        else 
            a = c;
            fa = fc;
        end
        c = (a + b) / 2;
        fc = fun(c)
        delta = b - c;
        i = i + 1;
    end
    disp("Número de iteraciones: " + string(i));
    raiz = c;
endfunction

deff('y=r(x)','y=exp(-x)-x^4');
biseccion(r,0,1,0.01);


///----
function raiz = biseccion_2(fun, a, b, tol)
    // Evaluar extremos iniciales
    fa = fun(a);
    fb = fun(b);
    
    // Verificar signos opuestos
    if fa * fb > 0 then
        error("Las imágenes de los extremos no tienen signos opuestos.");
    end
    
    // Inicialización
    i = 0;
    delta = b - a;
    c = (a + b) / 2;
    fc = fun(c);
    
    // Bucle principal
    while abs(delta) > tol
        if fa * fc < 0 then
            b = c;
            fb = fc;
        else
            a = c;
            fa = fc;
        end
        
        c = (a + b) / 2;
        fc = fun(c);
        delta = b - a;
        i = i + 1;
    end
    
    // Mostrar resultados
    mprintf("\nMétodo de bisección\n");
    mprintf("===================\n");
    mprintf("Iteraciones realizadas: %d\n", i);
    mprintf("Raíz aproximada: %.6f\n", c);
    mprintf("f(raíz) = %.6e\n", fc);
    mprintf("Error estimado: %.6e\n", abs(delta));
    
    raiz = c;
endfunction

// Ejemplo de uso
deff('y=r(x)', 'y = exp(-x) - x^4');
raiz = biseccion_2(r, 0, 1, 0.01);


deff('y=p(x)', 'y = log(x) - x+1');
raiz = biseccion_2(p, 1, 1, 0.01);
