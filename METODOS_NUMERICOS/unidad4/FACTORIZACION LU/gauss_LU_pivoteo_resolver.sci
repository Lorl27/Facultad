function [L, U, P, X] = gauss_LU_pivoteo_resolver(A, b)
    // --------------------------------------------------------
    // Factorización PA = LU mediante Eliminación de Gauss
    // con pivoteo parcial. Permite opcionalmente resolver A*x=b.
    //
    // Entradas:
    //   A : matriz cuadrada n×n
    //   b : (opcional) vector columna o matriz n×m (uno o varios sistemas)
    //
    // Salidas:
    //   L : matriz triangular inferior (unitaria)
    //   U : matriz triangular superior
    //   P : matriz de permutación
    //   X : (opcional) solución del sistema A*x=b
    //
    // Ejemplo:
    //   [L,U,P] = gauss_LU_pivoteo_resolver(A);
    //   [L,U,P,X] = gauss_LU_pivoteo_resolver(A, b);
    // --------------------------------------------------------

    [n, m] = size(A);
    if n <> m then
        error("La matriz A debe ser cuadrada");
        abort;
    end

    U = A;
    L = eye(n, n);
    P = eye(n, n);

    // === Eliminación con pivoteo parcial ===
    for k = 1 : n-1
        // Selección del pivote máximo en columna k
        [amax, i] = max(abs(U(k:n, k)));
        i = i + k - 1;

        // Intercambio de filas si es necesario
        if i <> k then
            temp = U(k, :);
            U(k, :) = U(i, :);
            U(i, :) = temp;

            temp = P(k, :);
            P(k, :) = P(i, :);
            P(i, :) = temp;

            if k > 1 then
                temp = L(k, 1:k-1);
                L(k, 1:k-1) = L(i, 1:k-1);
                L(i, 1:k-1) = temp;
            end
        end

        // Eliminación progresiva
        for j = k+1 : n
            L(j, k) = U(j, k) / U(k, k);
            U(j, :) = U(j, :) - L(j, k) * U(k, :);
        end
    end

    // === Si se provee b, resolver A*x = b ===
    X = [];
    if argn(2) == 2 then
        // Aplicamos la permutación al vector/matriz b
        b_mod = P * b;

        // Resolución en dos etapas: L*y = P*b  y  U*x = y
        y = L \ b_mod;
        X = U \ y;
    end
endfunction

//----------------------------------------------

A = [0 2 3; 2 0 3; 8 16 -1];
b = [7; 13; -3];

[L, U, P, x] = gauss_LU_pivoteo_resolver(A, b);

mprintf("\nSolución del sistema A*x = b:\n");
disp(x);

//============== EJERCICIO 7:
//Aplicar el algoritmo a la matriz
//A = {
//2 1 1 0
//4 3 3 1
//8 7 9 5
//6 7 9 8}


A = [2 1 1 0;
     4 3 3 1;
     8 7 9 5;
     6 7 9 8];

[L, U, P] = gauss_LU_pivoteo_resolver(A);

mprintf("\nMatriz L:\n");
disp(L);
mprintf("\nMatriz U:\n");
disp(U);
mprintf("\nMatriz P:\n");
disp(P);

// Verificación: P*A ≈ L*U
mprintf("\nVerificación P*A - L*U ≈ 0:\n");
disp(P*A - L*U);
