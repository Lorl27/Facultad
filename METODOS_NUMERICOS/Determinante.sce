function detA = deter(A)
    [n, m] = size(A);
    if n <> m then
        error("La matriz A debe ser cuadrada");
        abort;
    end

    detA = 1; // inicializo producto
    for k = 1 : n-1
        if A(k,k) == 0 then
            error("Pivote nulo: no se puede continuar sin pivoteo");
        end
        for i = k+1 : n
            m = A(i,k) / A(k,k);
            A(i,k+1:n) = A(i,k+1:n) - m * A(k,k+1:n);
        end
    end

    // Producto de la diagonal principal
    for i = 1 : n
        detA = detA * A(i,i);
    end
endfunction

//----
function detA = deter_gauss_pivot(A)
    [n, m] = size(A);
    if n <> m then
        error("La matriz A debe ser cuadrada");
        abort;
    end

    detA = 1;
    signo = 1;

    for k = 1 : n-1
        // Pivoteo parcial
        [amax, krel] = max(abs(A(k:n,k)));
        kpivot = krel + k - 1;
        if amax == 0 then
            detA = 0;
            return;
        end
        if kpivot <> k then
            temp = A(k,:);
            A(k,:) = A(kpivot,:);
            A(kpivot,:) = temp;
            signo = -signo; // cambiar de signo por intercambio de filas
        end

        for i = k+1 : n
            m = A(i,k) / A(k,k);
            A(i,k+1:n) = A(i,k+1:n) - m * A(k,k+1:n);
        end
    end

    // Producto de la diagonal
    for i = 1 : n
        detA = detA * A(i,i);
    end

    detA = signo * detA;
endfunction

//============EJERCICIO 4====
//4. Se puede demostrar que el determinante de una matriz se obtiene multiplicando los elementos en la diagonal principal de la matriz triangular superior resultante de la etapa de
//eliminaci´on progresiva del procedimiento de eliminaci´on Gaussiana. Escribir una funci´on
//que calcule el determinante de una matriz por eliminaci´on Gaussiana suponiendo que no
//hay pivoteo.

A = [1 2 3; 3 -2 1; 4 2 -1];

det_sin_pivot = deter(A)
det_con_pivot = deter_gauss_pivot(A)
det_real = det(A) // función interna de Scilab para comparar

disp('det_sin_pivot:'); disp(det_sin_pivot);
disp('det_con_pivot:'); disp(det_con_pivot);
disp('det real:'); disp(det_real);

A2 = [0 2 3; 2 0 3; 8 16 -1]
det_sin_pivot = deter(A2)
det_con_pivot = deter_gauss_pivot(A2)
det_real = det(A2) // función interna de Scilab para comparar

disp('det_sin_pivot:'); disp(det_sin_pivot);
disp('det_con_pivot:'); disp(det_con_pivot);
disp('det real:'); disp(det_real);


disp("det",deter_gauss_pivot([0 0 0 ; 1 -1 0 ; 1 -1 2]))


