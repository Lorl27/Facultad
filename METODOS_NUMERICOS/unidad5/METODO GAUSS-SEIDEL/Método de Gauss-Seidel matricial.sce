function x = gauss_seidel_mat(A, b ,x0, eps)
    n = size(A, 1);
    D = diag(diag(A));
    L = tril(A, -1);
    N = L + D
    inv_N = inv(N);
    I = eye(n, n)
    x = x0;
    iter = 0;
    
    while norm(A*x - b) > eps
        x = inv_N*b + (I - inv_N*A)*x;
        iter = iter + 1;
    end
    
    disp(iter);
endfunction
