
// ======= Construir matriz tridiagonal =======
function [A, b] = sistema_tridiagonal(n)
    A = 2*eye(n,n) - diag(ones(n-1,1),1) - diag(ones(n-1,1),-1);
    b = ones(n,1);
endfunction

// ======= Método de Gauss-Seidel =======
function [x, iter] = gauss_seidel_tridiagonal(A, b, eps)
    n = size(A,1);
    x = zeros(n,1);
    x_old = x;
    iter = 0;

    while %t
        iter = iter + 1;
        for i = 1:n
            suma = 0;

            if i > 1 then
                suma = suma + A(i,1:i-1)*x(1:i-1);
            end
            if i < n then
                suma = suma + A(i,i+1:n)*x_old(i+1:n);
            end

            x(i) = (b(i) - suma)/A(i,i);
        end

        if norm(x - x_old, "inf") < eps then
            break;
        end
        x_old = x;
    end
endfunction

// ======= Ejemplo =======
[A,b] = sistema_tridiagonal(10);
[x, iter] = gauss_seidel_tridiagonal(A,b,1e-6);
disp(x);
disp(iter);
