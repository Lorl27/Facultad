// =======================================================
// FUNCION GENERICA: CONDUCCION DE CALOR CON FACTORIZACION LU
// =======================================================
// Resuelve: A * x(k+1) = x(k)
// donde A es tridiagonal con (1+2c) en la diagonal y -c en las diagonales vecinas.
// -------------------------------------------------------
// Parámetros:
//   n      -> número de puntos (dimensión del sistema)
//   c      -> constante física
//   x0     -> vector inicial de temperaturas (n×1)
//   pasos  -> cantidad de pasos (iteraciones)
// -------------------------------------------------------
// Devuelve:
//   A      -> matriz tridiagonal
//   L, U   -> factorización LU de A
//   X_hist -> matriz con las soluciones (cada columna es x^(k))
// =======================================================

function [A, L, U, X_hist] = conduccion_LU_generica(n, c, x0, pasos)
    if size(x0,1) <> n then
        error("El tamaño de x0 debe coincidir con n");
    end

    // --- Construcción de A tridiagonal ---
    A = (1 + 2*c)*eye(n, n) - c*diag(ones(n-1,1), 1) - c*diag(ones(n-1,1), -1);

    // --- Factorización LU ---
    [L, U] = lu(A);

    // --- Inicialización de resultados ---
    X_hist = zeros(n, pasos+1);
    X_hist(:,1) = x0;

    // --- Bucle temporal ---
    for k = 1:pasos
        y = L \ X_hist(:,k);     // resolver L*y = x(k)
        X_hist(:,k+1) = U \ y;   // resolver U*x(k+1) = y
    end

    // --- Mostrar resultados ---
    disp("========================================");
    mprintf("Simulación de conducción (n=%d, c=%g)\n", n, c);
    disp("========================================");
    disp("Matriz A:");
    disp(A);
    mprintf("Determinante de A: %.6f\n", det(A));

    disp("Matriz L:");
    disp(L);
    disp("Matriz U:");
    disp(U);

    for k = 1:pasos
        mprintf("\nTemperaturas x^(%d):\n", k);
        disp(X_hist(:,k+1));
    end
endfunction

//---
// Ejecutar ejemplo genérico
n = 5;
c = 1;
x0 = [10; 12; 12; 12; 10];
pasos = 4;

[A, L, U, X_hist] = conduccion_LU_generica(n, c, x0, pasos);


//=================================
function [A, L, U, X_hist] = conduccion_LU_ciclica(n, x0, pasos)
    // Construye matriz tridiagonal con términos cíclicos
    A = 2*eye(n, n) - diag(ones(n-1,1), 1) - diag(ones(n-1,1), -1);
    A(1,n) = -1;  // conexión cíclica arriba-derecha
    A(n,1) = -1;  // conexión cíclica abajo-izquierda

    // RHS en este caso (temperaturas nuevas)
    rhs = zeros(n,1);  // según tu ejemplo

    // Factorización LU
    [L, U] = lu(A);

    // Evolución temporal (x(k+1) = A^{-1} * x(k))
    X_hist = zeros(n, pasos+1);
    X_hist(:,1) = x0;

    for k = 1:pasos
        y = L \ X_hist(:,k);
        X_hist(:,k+1) = U \ y;
    end

    // Mostrar
    disp("Matriz A cíclica:");
    disp(A);
    disp("L:");
    disp(L);
    disp("U:");
    disp(U);
    for k = 1:pasos
        mprintf("\nTemperaturas x^(%d):\n", k);
        disp(X_hist(:,k+1));
    end
endfunction

//-----------
// Ejecutar ejemplo genérico ciclica - 1 arriba y 1 abajo - bordes conectdos entre is
n = 6;
x0 = [1; 2; 3; 4; 5; 6];
pasos = 3;

[A, L, U, X_hist] = conduccion_LU_ciclica(n, x0, pasos);

//--------
n = 5;
c = 0.5;             // o el valor físico que quieras
x0 = [10; 12; 12; 12; 10];
pasos = 4;

[A, L, U, X_hist] = conduccion_LU_generica(n, c, x0, pasos);


