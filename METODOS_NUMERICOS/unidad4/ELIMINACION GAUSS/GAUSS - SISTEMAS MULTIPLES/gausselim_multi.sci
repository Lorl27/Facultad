function [X, A_aum, pivoteo_usado] = gausselim_multi(A, B)
    // ---------------------------------------------------------------
    // Resuelve A*X = B para uno o varios sistemas lineales
    // mediante Eliminación Gaussiana con pivoteo parcial automático.
    //
    // Entradas:
    //   A : matriz cuadrada n×n
    //   B : matriz n×m (cada columna es un vector independiente)
    //
    // Salidas:
    //   X : matriz n×m (cada columna es una solución distinta)
    //   A_aum : matriz aumentada luego de la eliminación
    //   pivoteo_usado : booleano (1 = se aplicó pivoteo al menos una vez)
    // ---------------------------------------------------------------

    [nA, mA] = size(A);
    [nB, mB] = size(B);

    if nA <> mA then
        error("gausselim_multi - La matriz A debe ser cuadrada");
        abort;
    elseif nB <> nA then
        error("gausselim_multi - Dimensiones incompatibles entre A y B");
        abort;
    end

    A_aum = [A B];
    n = nA;
    pivoteo_usado = 0;

    // Eliminación progresiva
    for k = 1 : n-1
        // Detección automática de pivote nulo o pequeño
        if abs(A_aum(k,k)) < 1.0E-12 then
            [amax, krel] = max(abs(A_aum(k:n, k)));
            kpivot = krel + k - 1;
            if amax == 0 then
                error("gausselim_multi - Matriz singular (columna nula)");
            end
            if kpivot <> k then
                temp = A_aum(k, :);
                A_aum(k, :) = A_aum(kpivot, :);
                A_aum(kpivot, :) = temp;
                pivoteo_usado = 1;
            end
        end

        // Eliminación hacia adelante
        for i = k+1 : n
            m = A_aum(i, k) / A_aum(k, k);
            A_aum(i, k) = 0;
            A_aum(i, k+1 : n+mB) = A_aum(i, k+1 : n+mB) - m * A_aum(k, k+1 : n+mB);
        end
    end

    // Sustitución regresiva
    X = zeros(n, mB);
    X(n, :) = A_aum(n, n+1 : n+mB) / A_aum(n, n);
    for i = n-1 : -1 : 1
        X(i, :) = (A_aum(i, n+1 : n+mB) - A_aum(i, i+1 : n) * X(i+1 : n, :)) / A_aum(i, i);
    end
endfunction


//======= EJERCICIO 3:
//3. Suponga que queremos resolver los siguientes tres sistemas de ecuaciones:
//S1 = {
//x1 + 2x2 + 3x3 = 14
//3x1 − 2x2 + x3 = 2
//4x1 + 2x2 − x3 = 5 }

//S2= {
//x1 + 2x2 + 3x3 = 9
//3x1 − 2x2 + x3 = −5
//4x1 + 2x2 − x3 = 19}

//S3={
//x1 + 2x2 + 3x3 = −2
//3x1 − 2x2 + x3 = 2
//4x1 + 2x2 − x3 = 12}

//Podemos escribir los tres sistemas de ecuaciones como una ´unica ecuaci´on matricial: AX =B, donde
//A =
//1 2 3
//3 −2 1
//4 2 −1
//, X =
//x11 x12 x13
//x21 x22 x23
//x31 x32 x33
// , B =

//14 9 −2
//2 −5 2
//5 19 12
//------------------------------------------
//(a) Modificar el m´etodo de eliminaci´on Gaussiana a fin de resolver m´ultiples sistemas de
//ecuaciones lineales. La matriz aumentada para este caso es Aaum = [A B], donde A
//es una matriz de n × n, y B es una matriz de n × m. La soluci´on es una matriz de
//n × m.
//(b) Utilizar el m´etodo programado en el item anterior para resolver los tres sistemas
//lineales dados.

// Matriz A
A = [1 2 3; 3 -2 1; 4 2 -1];

// Matriz B con los tres sistemas S1, S2 y S3
B = [14 9 -2; 2 -5 2; 5 19 12];

// Resolver los tres sistemas simultáneamente
[X, A_aum, piv] = gausselim_multi(A, B);

mprintf("\n=== Resultados ===\n");
mprintf("¿Se usó pivoteo?: %d\n", piv);
mprintf("Soluciones (cada columna corresponde a un sistema):\n");
disp(X);

//(c) Utilizar el m´etodo programado en el item (a) para calcular la inversa de la matriz A
//por eliminaci´on Gaussiana.

I = eye(size(A,1), size(A,1));
[invA, AA, pivoteado] = gausselim_multi(A, I);

mprintf("\nMatriz inversa de A (calculada por eliminación de Gauss):\n");
disp(invA);

disp('comprobancion:'); disp(A * invA);
