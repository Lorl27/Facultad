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


// =====================================================
// === PRUEBAS ===
// =====================================================

// Caso 1: solo factorización
A = [2 1 1 0;
     4 3 3 1;
     8 7 9 5;
     6 7 9 8];

[L, U, P, , detA] = LU_auto(A);

// Separador
mprintf("\n============================\n");

// Caso 2: con resolución del sistema
A = [0 2 3; 2 0 3; 8 16 -1];
b = [7; 13; -3];
[L, U, P, X, detA] = LU_auto(A, b);

//------------------------
//================= EJERCICIO NRO (8):

//8. Factorizar las siguientes matrices usando el algoritmo dise˜nado en el Ejer. 7 y comparar
//los resultados con la implementaci´on de Scilab de la factorizaci´on LU.
//a) ={1.012 −2.132 3.104
//−2.132 4.096 −7.013
//3.104 −7.013 0.014
//}
// b) ={
//2.1756 4.0231 −2.1732 5.1967
//−4.0231 6.0000 0 1.1973
//−1.0000 5.2107 1.1111 0
//6.0235 7.0000 0 4.1561 }




A8=[1.012 -2.132 3.104;
    -2.132 4.096 -7.013;
    3.104 -7.013 0.014];

[L8, U8, P8,X8 , detA8]=LU_auto(A8);



A81=[2.1756 4.0231 -2.1732 5.1967;
    -4.0231 6.0000 0 1.1973;
    -1.0000 5.2107 1.1111 0;
    6.0235 7.0000 0 4.1561];

[L81, U81, P81,X81 , detA81]=LU_auto(A81);


//============================== EJERCICIO NRO 9 : ===================================================
//9. Considerar el sistema Ax = b donde
//A ={
//1 2 −2 1
//4 5 −7 6
//5 25 −15 −3
//6 −12 −6 22
//}
// , b ={
//1
//2
//0
//1
//}
//(a) Resuelva el sistema mediante el m´etodo de eliminaci´on de Gauss. En caso de realizar
//intercambios de ecuaciones, calcule la matriz de permutaci´on P correspondiente.

A =[
    1 2 -2 1;
    4 5 -7 6;
    5 25 -15 -3;
    6 -12 -6 22]

b =[
    1;
    2;
    0;
    1]
    

[L, U, P,X , detA]=LU_auto(A,b);
    
//(b) A partir de la informaci´on obtenida en la eliminaci´on de Gauss, obtenga la factorizaci´on PA = LU, y utilize dicha factorizaci´on para resolver de forma m´as simple el
//sitema Ax = b˜, donde b˜ = [ 2 2 1 0 ]T

b2 = [2; 2; 1; 0];   // b̃

c = P * b2;           // aplicar la permutación
y = sust_inf(L, c);   // resolver L*y = P*b̃
x2 = sust_sup(U, y);  // resolver U*x = y

disp("Solución para b̃:");
disp(x2);

///-----------  p5 complementaria , ej 4.b
R= [3  -1   0   0   0;
  -1   3  -1   0   0;
   0  -1   3  -1   0;
   0   0  -1   3  -1;
   0   0   0  -1   3]
   
   [L81, U81, P81,X81 , detA81]=LU_auto(R);


///-------------- parcial:
A=[1 2 -3 4 ; 4 8 12 -9 ; 2 3 2 1 ; -3 -1 1 -4];
b=[3 ; 60 ; 1 ;5];
[L, U, P,X , detA]=LU_auto(A,b);
