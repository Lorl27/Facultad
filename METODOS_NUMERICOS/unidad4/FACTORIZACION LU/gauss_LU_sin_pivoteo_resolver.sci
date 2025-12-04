// =====================================================
// Resolución de A*x = b usando factorización LU sin pivoteo
// =====================================================

function [L, U] = gauss_LU_sin_pivoteo(A)
    [n, m] = size(A);
    if n <> m then
        error("La matriz A debe ser cuadrada");
        abort;
    end

    U = A;
    L = eye(n, n);

    for k = 1 : n-1
        if U(k, k) == 0 then
            error("Pivote nulo detectado. Se requiere pivoteo.");
            abort;
        end

        for i = k+1 : n
            L(i, k) = U(i, k) / U(k, k);
            U(i, :) = U(i, :) - L(i, k) * U(k, :);
        end
    end
endfunction


// -----------------------------------------------------
// Sustitución hacia adelante (resuelve L*y = b)
// -----------------------------------------------------
function y = sust_inf(L, b)
    n = length(b);
    y = zeros(n, 1);
    for i = 1 : n
        y(i) = (b(i) - L(i, 1:i-1) * y(1:i-1)) / L(i, i);
    end
endfunction


// -----------------------------------------------------
// Sustitución hacia atrás (resuelve U*x = y)
// -----------------------------------------------------
function x = sust_sup(U, y)
    n = length(y);
    x = zeros(n, 1);
    for i = n : -1 : 1
        x(i) = (y(i) - U(i, i+1:n) * x(i+1:n)) / U(i, i);
    end
endfunction


// -----------------------------------------------------
// Función principal: resuelve A*x = b
// -----------------------------------------------------
function x = resolver_LU(A, b)
    [L, U] = gauss_LU_sin_pivoteo(A);
    y = sust_inf(L, b);
    x = sust_sup(U, y);
endfunction


//-================

A = [2 1 1 0;
     4 3 3 1;
     8 7 9 5;
     6 7 9 8];

b = [4; 7; 11; 9];

// Resuelve el sistema A*x = b
x = resolver_LU(A, b);

// Muestra resultados
disp("Solución del sistema (x):");
disp(x);

[L, U] = gauss_LU_sin_pivoteo(A);
disp("Matriz L:");
disp(L);
disp("Matriz U:");
disp(U);

// Verificación
disp("Comprobación A*x:");
disp(A*x);
disp("Vector b original:");
disp(b);
