// ======================================================
// FACTORIZACIÓN DOOLITTLE CON PIVOTEO PARCIAL
// ======================================================
function [L, U, P] = fact_doolittle_pivoteo(A)
    [n, m] = size(A);
    if n <> m then
        error("La matriz A debe ser cuadrada.");
    end

    P = eye(n, n); // matriz de permutación
    L = eye(n, n);
    U = A;

    for k = 1:n-1
        // Pivoteo: encontrar fila con mayor valor absoluto en la columna k
        [pivot, fila_max] = max(abs(U(k:n, k)));
        fila_max = fila_max + k - 1;

        // Intercambiar filas en U, P y L (hasta columna k-1)
        if fila_max <> k then
            U([k, fila_max], :) = U([fila_max, k], :);
            P([k, fila_max], :) = P([fila_max, k], :);
            if k > 1 then
                L([k, fila_max], 1:k-1) = L([fila_max, k], 1:k-1);
            end
        end

        // Factorización
        for i = k+1:n
            L(i, k) = U(i, k) / U(k, k);
            U(i, :) = U(i, :) - L(i, k) * U(k, :);
        end
    end
endfunction


//PA=LU  ==> LUx =Pb

A = [1 2 -3 4; 4 8 12 -9; 2 3 2 1; -3 -1 1 -4];
b = [3; 60; 1; 5];

[L, U, P] = fact_doolittle_pivoteo(A);

disp("L ="); disp(L);
disp("U ="); disp(U);
disp("P ="); disp(P);

// Resolver el sistema
y = L \ (P * b);
x = U \ y;
disp("x ="); disp(x);
