// =====================================================
// Factorización LU automática con detección de pivote pequeño
// Permite uso con A sola o con A y b (resuelve A*x=b)
// =====================================================

function [L, U, P, X, detA] = LU_auto(A, varargin)
    // --------------------------------------------------
    // Entradas:
    //   A : matriz cuadrada
    //   b : (opcional) vector o matriz de términos independientes
    //
    // Salidas:
    //   L, U, P : factorización (PA = LU)
    //   X       : (opcional) solución del sistema A*x=b
    //   detA    : determinante de A
    // --------------------------------------------------

    [n, m] = size(A);
    if n <> m then
        error("La matriz A debe ser cuadrada");
        abort;
    end

    // Inicialización
    U = A;
    L = eye(n, n);
    P = eye(n, n);
    pivoteo_usado = 0;
    intercambios = 0;
    tol = 1e-12;

    // === Eliminación con detección de pivote pequeño ===
    for k = 1:n-1
        if abs(U(k, k)) <= tol then
            [maxval, ind] = max(abs(U(k:n, k)));
            ind = ind + k - 1;
            if maxval == 0 then
                error("LU_auto: matriz singular (columna nula)");
            end

            // Intercambio de filas
            U([k ind], :) = U([ind k], :);
            P([k ind], :) = P([ind k], :);
            L([k ind], 1:k-1) = L([ind k], 1:k-1);
            pivoteo_usado = 1;
            intercambios = intercambios + 1;
        end

        // Eliminación progresiva
        for i = k+1:n
            L(i, k) = U(i, k) / U(k, k);
            U(i, :) = U(i, :) - L(i, k) * U(k, :);
        end
    end

    // === Determinante ===
    detA = prod(diag(U));
    if pivoteo_usado then
        detA = detA * (-1)^intercambios;
    end

    // === Si no se pasa b, solo mostrar resultados ===
    X = [];
    if argn(2) == 1 then
        if pivoteo_usado then
            disp("Se detectó pivote pequeño: se aplicó pivoteo parcial (PA = LU).");
        else
            disp("Pivotes válidos: se usó factorización LU sin pivoteo.");
        end

        mprintf("\n--- RESULTADOS ---\n");
        disp("Matriz L:");
        disp(L);
        disp("Matriz U:");
        disp(U);
        if pivoteo_usado then
            disp("Matriz P (permutación):");
            disp(P);
        end
        mprintf("Determinante de A: %f\n", detA);
        return; // Fin si no hay b
    end

    // === Si se pasa b, resolver el sistema ===
    b = varargin(1);

    if pivoteo_usado then
        disp("Se detectó pivote pequeño: se aplicó pivoteo parcial (PA = LU).");
        c = P * b;
    else
        disp("Pivotes válidos: se usó factorización LU sin pivoteo.");
        c = b;
    end

    // Sustituciones hacia adelante y atrás
    y = sust_inf(L, c);
    X = sust_sup(U, y);

    // Mostrar resultados
    mprintf("\n--- RESULTADOS ---\n");
    disp("Matriz L:");
    disp(L);
    disp("Matriz U:");
    disp(U);
    if pivoteo_usado then
        disp("Matriz P (permutación):");
        disp(P);
    end
    disp("Solución del sistema:");
    disp(X);
    mprintf("Determinante de A: %f\n", detA);
endfunction


// =====================================================
// FUNCIONES AUXILIARES
// =====================================================

function y = sust_inf(L, b)
    n = length(b);
    y = zeros(n, 1);
    for i = 1:n
        y(i) = (b(i) - L(i, 1:i-1) * y(1:i-1)) / L(i, i);
    end
endfunction

function x = sust_sup(U, y)
    n = length(y);
    x = zeros(n, 1);
    for i = n:-1:1
        if i == n then
            x(i) = y(i) / U(i, i);
        else
            if i+1 <= n then
                x(i) = (y(i) - U(i, i+1:n) * x(i+1:n)) / U(i, i);
            else
                x(i) = y(i) / U(i, i);
            end
        end
    end
endfunction


//=====================================================0

// PRACTICA 4  - EJERCICIO 1


A=[1 2 -2 1 ; 4 5 -7 6 ; 5 25 -15 -3 ; 6 -12 -6 22];

b=[1 ;1 ;1 ;1];
c=[2 ; 2 ; 2 ;2];


// resolvemos el sistema
[L, U, P, X, detA] = LU_auto(A);


/// FACTORIZACION LU OBTENIDA: A=LU 
//--- RESULTADOS ---
//
//  "Matriz L:"
//
//   1.   0.   0.   0.
//   4.   1.   0.   0.
//   6.   8.   1.   0.
//   5.  -5.   0.   1.
//
//  "Matriz U:"
//
//   1.   2.  -2.   1.
//   0.  -3.   1.   2.
//   0.   0.  -2.   0.
//   0.   0.   0.   2.
//
//  "Matriz P (permutación):"
//
//   1.   0.   0.   0.
//   0.   1.   0.   0.
//   0.   0.   0.   1.
//   0.   0.   1.   0.

//RESOLVER Ax=b y AX=C CON LA FACTORIZACION LU OBTENIDA:

//Ax=b :
    yb = sust_inf(L, b);
    Xb = sust_sup(U, yb);
disp("X=",Xb);

//SALIDA SISTEMA:
//
//  "X="
//
//  -1.6666667
//   2.8333333
//   3.5
//   3.


//Ax=c :
    yc = sust_inf(L, c);
    Xc = sust_sup(U, yc);
disp("X=",Xc);

//SALIDA SISTEMA:
//
//  "X="
////
// -3.3333333
//   5.6666667
//   7.
//   6.


//// ITEM B: resolver la matriz ampleada [A b c] con eliminacion de gauss.


// gauss_augmented.sci
// Elimina por Gauss con pivoteo parcial sobre una matriz ampliada [A | B]
// Entrada:
//   A : matriz n x n
//   B : matriz n x m (pueden ser vectores columna b, c concatenados)
// Salida:
//   X : solución n x m tal que A*X = B
//   U, A_mod : (opcionales) para inspección

function [X, A_mod] = gauss_augmented(A, B)
    [n, n2] = size(A);
    if n <> n2 then
        error("A debe ser cuadrada");
    end
    [nB, m] = size(B);
    if nB <> n then
        error("B debe tener el mismo número de filas que A");
    end

    Aug = [A, B]; // matriz ampliada n x (n+m)

    // Eliminación hacia adelante con pivoteo parcial
    for k = 1:n-1
        // buscar pivote máximo en columna k (filas k..n)
        [maxval, idx] = max(abs(Aug(k:n, k)));
        pivot_row = idx + k - 1;
        if maxval == 0 then
            error("Matriz singular o columna nula en paso " + string(k));
        end
        // intercambiar filas k y pivot_row si hace falta
        if pivot_row <> k then
            tmp = Aug(k, :);
            Aug(k, :) = Aug(pivot_row, :);
            Aug(pivot_row, :) = tmp;
        end
        // eliminar debajo de la diagonal
        for i = k+1:n
            mfac = Aug(i, k) / Aug(k, k);
            Aug(i, k:n+m) = Aug(i, k:n+m) - mfac * Aug(k, k:n+m);
        end
    end

    // Comprobación último pivote
    if abs(Aug(n, n)) < 1e-14 then
        error("Pivote final nulo (matriz singular o casi singular)");
    end

    // Sustitución hacia atrás para cada RHS (columnas n+1 .. n+m)
    X = zeros(n, m);
    for col = 1:m
        // construir RHS actual
        rhs = Aug(:, n + col);
        x = zeros(n, 1);
        for i = n:-1:1
            x(i) = (rhs(i) - Aug(i, i+1:n) * x(i+1:n)) / Aug(i, i);
        end
        X(:, col) = x;
    end

    A_mod = Aug; // devolver la matriz triangular resultante si se quiere inspeccionar
endfunction

A = [1 2 -2 1; 4 5 -7 6; 5 25 -15 -3; 6 -12 -6 22];
b = [1;1;1;1];
c = [2;2;2;2];

B = [b, c]; // dos RHS como dos columnas
[X, AugT] = gauss_augmented(A, B);

disp("Soluciones (cada columna corresponde a una RHS):");
disp(X);

// verificar residuo
res = A * X - B;
disp("Residuo A*X - B (debería ser ~0):");
disp(res);
