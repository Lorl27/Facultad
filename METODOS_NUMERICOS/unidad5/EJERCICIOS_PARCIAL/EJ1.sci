// ---------------------------
// Datos
A = [10 3 1; 2 -10 3; 1 3 10];
b = [14; -5; 14];
x0 = zeros(3,1);
tol = 1e-6;
maxit = 1000;

// Matrices D, L, U
D = diag(diag(A));
L = tril(A,-1);
U = triu(A,1);

// Matrices de iteracion
BJ = -inv(D)*(L+U);
BGS = -inv(D+L)*U;

// radios espectrales
evJ = spec(BJ);
evGS = spec(BGS);
rhoJ = max(abs(evJ));
rhoGS = max(abs(evGS));
disp("Autovalores BJ:"); disp(evJ');
disp("rho(BJ) = " + string(rhoJ));
disp("Autovalores BGS:"); disp(evGS');
disp("rho(BGS) = " + string(rhoGS));

// Funciones iterativas
function [x, history] = jacobi_iter(A,b,x0,maxit)
    D = diag(diag(A));
    R = A - D;
    x = x0;
    history = x';
    for k=1:maxit
        xnew = inv(D)*(b - R*x);
        history($+1,:) = xnew';
        x = xnew;
    end
endfunction

function [x, history, it] = gauss_seidel_iter(A,b,x0,tol,maxit)
    n = size(A,1);
    x = x0;
    history = x';
    for it = 1:maxit
        xold = x;
        for i=1:n
            if i>1 then s1 = A(i,1:i-1)*x(1:i-1); else s1 = 0; end
            if i<n then s2 = A(i,i+1:n)*xold(i+1:n); else s2 = 0; end
            x(i) = (b(i) - s1 - s2)/A(i,i);
        end
        history($+1,:) = x';
        if norm(x - xold, "inf") < tol then
            break;
        end
    end
endfunction

// Ejecutar Jacobi paso a paso y medir iteraciones hasta tol
[xj_all, l] = jacobi_iter(A,b,x0,100); // tomamos 100 iteraciones y luego comprobamos
// calcular iteraciones necesarias con criterio ||x_{k+1}-x_k||<tol
it_j = 0;
for k=1:size(xj_all,1)-1
    if norm(xj_all(k+1,:)' - xj_all(k,:)', "inf") < tol then
        it_j = k;
        break;
    end
end
if it_j == 0 then it_j = 100; end

// Ejecutar Gauss-Seidel hasta convergencia
[xgs, hgs, it_gs] = gauss_seidel_iter(A,b,x0,tol,1000);

// mostrar primeras iteraciones (0..5)
disp("Jacobi k=0..5");
n_jacobi = size(xj_all,1);
if n_jacobi < 6 then
    disp("Jacobi convergió en menos de 6 iteraciones.");
end
////for k=1:n_jacobi
////    printf("k=%d: [%g, %g, %g]\n", k-1, xj_all(k,1), xj_all(k,2), xj_all(k,3));
////end
disp("Gauss-Seidel k=0..5");
for k=1:min(6,size(hgs,1))
    printf("k=%d: [%g, %g, %g]\n", k-1, hgs(k,1), hgs(k,2), hgs(k,3));
end

printf("Iteraciones hasta tol (Jacobi, aproximado) = %d\n", it_j);
printf("Iteraciones hasta tol (Gauss-Seidel) = %d\n", it_gs);
