//EJERCICIO 2  - PRACTICA 5:

//PARA CALCULAR LU Y PODER UTILZIAR N=D+L EN GAUUS -SEIDEL;


function [L, U, P, X, detA] = LU(A, varargin)
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
    
endfunction



        
//================================

A=[1 1 1 ; 1 1 0 ; 1 0 1];

 [L, U, P, X, detA] = LU(A)


//
//  "Se detectó pivote pequeño: se aplicó pivoteo parcial (PA = LU)."
//
//--- RESULTADOS ---
//
//  "Matriz L:"
//
//   1.   0.   0.
//   1.   1.   0.
//   1.   0.   1.
//
//  "Matriz U:"
//
//   1.   1.   1.
//   0.  -1.   0.
//   0.   0.  -1.
//
//  "Matriz P (permutación):"
//
//   1.   0.   0.
//   0.   0.   1.
//   0.   1.   0.




// vemos si podemos obtener la inversa de N=D+L
N=[1 0 0 ; 1 1 0 ; 1 0 1];

function invA = inversa_matriz(A)
    // Verificar si A es cuadrada
    [n, m] = size(A);
    if n <> m then
        error("❌ Error: la matriz no es cuadrada, no se puede calcular la inversa.");
        return
    end

    // Verificar si el determinante es distinto de cero
    detA = det(A);
    if detA == 0 then
        error("❌ Error: la matriz es singular (determinante = 0), no tiene inversa.");
        return
    end

    // Si pasa las comprobaciones, calcular la inversa
    invA = inv(A);
    disp("✅ La matriz es invertible. Su inversa es:");
    disp(invA);
endfunction

invN=inversa_matriz(N);

///RESULTADOS:
//  "✅ La matriz es invertible. Su inversa es:"
//
//   1.   0.   0.
//  -1.   1.   0.
//  -1.   0.   1.


function norma_inf = normaInfinito(A)
    // Obtener dimensiones de A
    [m, n] = size(A)
    
    // Calcular la suma de los valores absolutos por fila
    suma_filas = zeros(m, 1)
    for i = 1:m
        suma_filas(i) = sum(abs(A(i, :)))
    end
    
    // La norma infinito es el máximo de esas sumas
    norma_inf = max(suma_filas)
    
    // Mostrar el resultado
    disp("✅ La norma infinito de la matriz es: " + string(norma_inf))
endfunction


//calculamos la norma infinito de B=I-N (inversa) A
R1=invN*A
I=[1 0 0 ; 0 1 0; 0 0 1]
R2=I - R1
norma_inf = normaInfinito(R2)


//RESULTADOS:

//  "✅ La norma infinito de la matriz es: 2"




/// AHORA, CALCULAREMOS LA CONVERGENCIA DEL METODO DE JACOBI:



invc=inversa_matriz(I)
C=invc*A
xd=I-C
norma_inf = normaInfinito(xd)

//RESULTADOS:

//  "✅ La norma infinito de la matriz es: 2"

//// PROBAEMOS LAS DISTINTAS FILAS INTERCAMBIADAS , PARA VER SI LOGRAMOS LA CONVERGENCIA:

A1=[1 1 1 ; 1 0 1 ; 1 1 0] // f2<->F3
A2=[1 1 0 ; 1 1 1 ; 1 0 1] // F1<->F2
A3=[1 0 1 ; 1 1 0; 1 1 1] // F1<->F3
A4=[1 1 0 ; 1 0 1 ; 1 1 1] // F<->F3 Y F3<->F2

D1=[1 0 0 ; 0 0 0 ; 0 0 0];
D2=[1 0 0 ; 0 1 0 ; 0 0 1];
D3=[1 0 0 ; 0 1 0 ; 0 0 1];
D4=[1 0 0 ; 0 0 0 ; 0 0 1];
/// METODO DE JACOBI:

invA1=inversa_matriz(D1);
CA1=invA1*A1
xdA1=I-CA1
norma_inf = normaInfinito(xdA1);

//RESULTADOS:
//❌ Error: la matriz es singular (determinante = 0), no tiene inversa.

invA2=inversa_matriz(D2);
CA2=invA2*A2
xdA2=I-CA2
norma_inf = normaInfinito(xdA2);

//RESULTADOS:
//✅ La matriz es invertible. Su inversa es:"
//
//   1.   0.   0.
//   0.   1.   0.
//   0.   0.   1.
//
//-->CA2=invA2*A2
// CA2  = 
//
//   1.   1.   0.
//   1.   1.   1.
//   1.   0.   1.
//
//-->xdA2=I-CA2
// xdA2  = 
//
//   0.  -1.   0.
//  -1.   0.  -1.
//  -1.   0.   0.
//
//-->norma_inf = normaInfinito(xdA2);

//  "✅ La norma infinito de la matriz es: 2"

invA3=inversa_matriz(D3)
CA3=invA3*A3
xdA3=I-CA3
norma_inf = normaInfinito(xdA3)

//RESULTADOS:
//"✅ La matriz es invertible. Su inversa es:"
//
//   1.   0.   0.
//   0.   1.   0.
//   0.   0.   1.
// invA3  = 
//
//   1.   0.   0.
//   0.   1.   0.
//   0.   0.   1.
//
//-->CA3=invA3*A3
// CA3  = 
//
//   1.   0.   1.
//   1.   1.   0.
//   1.   1.   1.
//
//-->xdA3=I-CA3
// xdA3  = 
//
//   0.   0.  -1.
//  -1.   0.   0.
//  -1.  -1.   0.
//
//-->norma_inf = normaInfinito(xdA3)
//
//  "✅ La norma infinito de la matriz es: 2"
// norma_inf  = 
//
//   2.

invA4=inversa_matriz(D4)
CA4=invA4*A4
xdA4=I-CA4
norma_inf = normaInfinito(xdA4)

// RESULTADOS:
//❌ Error: la matriz es singular (determinante = 0), no tiene inversa.

//===============

// METODO DE GAUSS-SEIDEL: N=D+L

 [LA1, UA1, PA1, X, detA] = LU(A1);
 
 // RESULTADOS:
//  "Pivotes válidos: se usó factorización LU sin pivoteo."
//
//--- RESULTADOS ---
//
//  "Matriz L:"
//
//   1.   0.   0.
//   1.   1.   0.
//   1.   0.   1.
//
//  "Matriz U:"
//
//   1.   1.   1.
//   0.  -1.   0.
//   0.   0.  -1.

LA1=[0 0 0 ; 1 0 0 ; 1 0 0];
NA1=LA1+D1

invA1=inversa_matriz(NA1)
CA1=invA1*A1
xdA1=I-CA1
norma_inf = normaInfinito(xdA1)

//RESULTADOS:
//❌ Error: la matriz es singular (determinante = 0), no tiene inversa.
   
 [LA2, UA2, PA2, X, detA] = LU(A2);
//   "Se detectó pivote pequeño: se aplicó pivoteo parcial (PA = LU)."
//
//--- RESULTADOS ---
//
//  "Matriz L:"
//
//   1.   0.   0.
//   1.   1.   0.
//   1.   0.   1.
//
//  "Matriz U:"
//
//   1.   1.   0.
//   0.  -1.   1.
//   0.   0.   1.
//
//  "Matriz P (permutación):"
//
//   1.   0.   0.
//   0.   0.   1.
//   0.   1.   0.
// 
 LA2=[0 0 0 ; 1 0 0 ; 1 0 0];
NA2=LA2+D2

invA2=inversa_matriz(NA2)
CA2=invA2*A2
xdA2=I-CA2
norma_inf = normaInfinito(xdA2)
 
 
 //RESULTADOS:
// "✅ La matriz es invertible. Su inversa es:"
//
//   1.   0.   0.
//  -1.   1.   0.
//  -1.   0.   1.
// invA2  = 
//
//   1.   0.   0.
//  -1.   1.   0.
//  -1.   0.   1.
//
//-->CA2=invA2*A2
// CA2  = 
//
//   1.   1.   0.
//   0.   0.   1.
//   0.  -1.   1.
//
//-->xdA2=I-CA2
// xdA2  = 
//
//   0.  -1.   0.
//   0.   1.  -1.
//   0.   1.   0.
//
//-->norma_inf = normaInfinito(xdA2)
//
//  "✅ La norma infinito de la matriz es: 2"
// norma_inf  = 
//
//   2.

 [LA3, UA3, PA3, X, detA] = LU(A3);
 //RESULTADOS:
// "Pivotes válidos: se usó factorización LU sin pivoteo."
//
//--- RESULTADOS ---
//
//  "Matriz L:"
//
//   1.   0.   0.
//   1.   1.   0.
//   1.   1.   1.
//
//  "Matriz U:"
//
//   1.   0.   1.
//   0.   1.  -1.
//   0.   0.   1.

 
 LA3=[0 0 0 ; 1 0 0 ; 1 1 0];
NA3=LA3+D3

invA3=inversa_matriz(NA3)
CA3=invA3*A3
xdA3=I-CA3
norma_inf = normaInfinito(xdA3)

  
  //RESULTADOS:
//   "✅ La matriz es invertible. Su inversa es:"
//
//   1.   0.   0.
//  -1.   1.   0.
//   0.  -1.   1.
// invA3  = 
//
//   1.   0.   0.
//  -1.   1.   0.
//   0.  -1.   1.
//
//-->CA3=invA3*A3
// CA3  = 
//
//   1.   0.   1.
//   0.   1.  -1.
//   0.   0.   1.
//
//-->xdA3=I-CA3
// xdA3  = 
//
//   0.   0.  -1.
//   0.   0.   1.
//   0.   0.   0.
//
//-->norma_inf = normaInfinito(xdA3)
//
//  "✅ La norma infinito de la matriz es: 1"
// norma_inf  = 
//
//   1.
//  

  [LA4, UA4, PA4, X, detA] = LU(A4);
  
  //RESULTADOS:
//  "Pivotes válidos: se usó factorización LU sin pivoteo."
//
//--- RESULTADOS ---
//
//  "Matriz L:"
//
//   1.   0.   0.
//   1.   1.   0.
//   1.   0.   1.
//
//  "Matriz U:"
//
//   1.   1.   0.
//   0.  -1.   1.
//   0.   0.   1.

  LA4=[0 0 0 ; 1 1 0 ; 1 0 0];
NA4=LA4+D4

invA2=inversa_matriz(NA4)
CA4=invA4*A4
xdA4=I-CA4
norma_inf = normaInfinito(xdA4)


//RESULTADOS:
//"✅ La matriz es invertible. Su inversa es:"
//
//   1.   0.   0.
//  -1.   1.   0.
//  -1.   0.   1.
// invA2  = 
//
//   1.   0.   0.
//  -1.   1.   0.
//  -1.   0.   1.
//
//-->CA4=invA4*A4
// CA4  = 
//
//   1.   1.   0.
//   1.   0.   1.
//   1.   1.   1.
//
//-->xdA= 
//4=I-CA4
// xdA4  
//   0.  -1.   0.
//  -1.   1.  -1.
//  -1.  -1.   0.
//
//-->norma_inf = normaInfinito(xdA4)
//
//  "✅ La norma infinito de la matriz es: 3"
// norma_inf  = 
//
//   3.
