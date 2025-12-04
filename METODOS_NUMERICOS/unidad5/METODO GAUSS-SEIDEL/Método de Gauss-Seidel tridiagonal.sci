function x = gauss_seidel_tridiagonal(d ,n, tol, max_iter)
    A = d*diag(ones(n, 1), 0) - diag(ones(n-1,1), 1) - diag(ones(n-1,1), -1);
    A(1, n) = 1;
    A(n, 1) = 1;
    
    N = d*diag(ones(n, 1), 0) - diag(ones(n-1,1), -1);
    N(n, 1) = 1;
    
    b = zeros(n, 1);
    b(n) = 1;
    
    x0 = zeros(n, 1);
    x = x0;
    xk = x;
    
    x(1) = 1/2 * (x(2) - x(n));
    for i = 2:n-1
        x(i) = 1/2 * (x(i-1) + x(i+1));
    end
    x(n) = 1/2 *(1 - x(1) + x(n-1));
    cont = 1; 
    
    while cont < max_iter && norm(x - xk, "inf") > tol
        xk = x;
        x(1) = 1/2 * (x(2) - x(n));
        for i = 2:n-1
            x(i) = 1/2 * (x(i-1) + x(i+1));
        end
        x(n) = 1/2 *(1 - x(1) + x(n-1));
        cont = cont + 1;
    end
    
    if cont == max_iter
        disp("Se llegó al máximo de iteraciones.");
    end
    disp("Número de iteraciones: ");
    disp(cont);
    
    autovalores = spec(N);
    abs_autovalores = abs(autovalores);
    rho = max(abs_autovalores);
    disp("El radio espectral de N es: ");
    disp(rho);
endfunction
