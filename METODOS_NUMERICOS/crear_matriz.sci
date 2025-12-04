function [A, b, x0] = crear_matriz(n)
    A = 2*diag(ones(n, 1), 0) - diag(ones(n-1,1), 1) - diag(ones(n-1,1), -1);
    A(1, n) = 1;
    A(n, 1) = 1;
    
    b = zeros(n, 1);
    b(n) = 1;
    
    x0 = zeros(n, 1);
endfunction
