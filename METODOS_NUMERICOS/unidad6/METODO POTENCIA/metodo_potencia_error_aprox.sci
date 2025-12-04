function [valor, zn, error_iter, iter] = mpotencia_error(A, z0, eps, maxiter)
    
    autovalores_exactos = spec(A);
    mayor_autovalor = max(abs(autovalores_exactos));

    // Inicialización
    valor = 0;
    iter = 1;
    w = A*z0;
    zn = w / norm(w, %inf);
    [m, j] = max(abs(w));
    valor = w(j) / z0(j);
    zn = w / valor;
    
    error_iter(iter) = abs(mayor_autovalor - valor);
    
    while (iter <= maxiter) & (norm(z0 - zn, %inf) > eps)
        z0 = zn;
        w = A * z0;
        zn = w / norm(w, %inf);
        [m, j] = max(abs(w));
        valor = w(j) / z0(j);
        zn = w / valor;
        
        iter = iter + 1;

        error_iter(iter) = abs(mayor_autovalor - valor);
    end
    
    disp("Iteraciones realizadas: ", iter);
endfunction
