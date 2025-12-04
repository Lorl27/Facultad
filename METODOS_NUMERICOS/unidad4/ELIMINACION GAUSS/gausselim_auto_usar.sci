function [x, a, pivoteo_usado] = gausselim_auto(A, b)
// -----------------------------------------------------------------
// Resuelve el sistema lineal A*x = b mediante Eliminación de Gauss
// con detección automática de pivoteo parcial cuando es necesario.
//
// Entradas:
//   A : matriz cuadrada de coeficientes
//   b : vector columna de términos independientes
//
// Salidas:
//   x : vector solución
//   a : matriz aumentada luego de la eliminación
//   pivoteo_usado : booleano (1 = se usó pivoteo, 0 = no se usó)
//
// -----------------------------------------------------------------

    [nA, mA] = size(A);
    [nb, mb] = size(b);

    // Validaciones
    if nA <> mA then
        error("gausselim_auto - La matriz A debe ser cuadrada");
        abort;
    elseif nb <> nA | mb <> 1 then
        error("gausselim_auto - b debe ser un vector columna compatible con A");
        abort;
    end

    a = [A b];              // Matriz aumentada
    n = nA;
    pivoteo_usado = 0;      // Flag para registrar si se usó pivoteo

    // Eliminación progresiva
    for k = 1 : n-1
        // Si el pivote actual es cero o muy pequeño, hacer pivoteo
        if abs(a(k,k)) < 1.0E-12 then
            [amax, krel] = max(abs(a(k:n, k)));
            kpivot = krel + k - 1;
            if amax == 0 then
                error("gausselim_auto - La matriz A es singular (columna nula)");
            end
            if kpivot <> k then
                temp = a(k, :);
                a(k, :) = a(kpivot, :);
                a(kpivot, :) = temp;
                pivoteo_usado = 1;
            end
        end

        // Proceso de eliminación
        for i = k+1 : n
            m = a(i, k) / a(k, k);
            a(i, k) = 0;
            a(i, k+1 : n+1) = a(i, k+1 : n+1) - m * a(k, k+1 : n+1);
        end
    end

    // Sustitución regresiva
    x = zeros(n, 1);
    x(n) = a(n, n+1) / a(n, n);
    for i = n-1 : -1 : 1
        suma = a(i, i+1:n) * x(i+1:n);
        x(i) = (a(i, n+1) - suma) / a(i, i);
    end

endfunction


//--------
// Sistema 1 (no requiere pivoteo)
A1 = [3 -2 -1; 6 -2 2; -9 7 1];
b1 = [0; 6; -1];
[x1, a1, piv1] = gausselim_auto(A1, b1);
mprintf("\nSistema 1 (sin pivoteo necesario)\n");
disp(x1);
mprintf("¿Se usó pivoteo?: %d\n", piv1);

// Sistema 2 (requiere pivoteo)
A2 = [0 2 3; 2 0 3; 8 16 -1];
b2 = [7; 13; -3];
[x2, a2, piv2] = gausselim_auto(A2, b2);
mprintf("\nSistema 2 (requiere pivoteo)\n");
disp(x2);
mprintf("¿Se usó pivoteo?: %d\n", piv2);

disp(a2);


/// ejercicio 4 - parcial:
A=[1 2 -3 4 ; 4 8 12 -9 ; 2 3 2 1 ; -3 -1 1 -4];
b=[3 ; 60 ; 1 ;5];
[x,a,piv]=gausselim_auto(A,b);
disp("x vale:",x, "se uso pivoteo?",piv);
