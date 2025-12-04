function [x, iter, rho] = gauss_seidel_ciclico(n, d, tol, max_iter)
    // --- Construcción de la matriz A ---
    A = d*diag(ones(n,1)) - diag(ones(n-1,1),1) - diag(ones(n-1,1),-1);
    A(1,n) = 1;   // término cíclico arriba a la derecha
    A(n,1) = 1;   // término cíclico abajo a la izquierda

    // --- Vector b ---
    b = zeros(n,1);
    b(n) = 1;

    // --- Vector inicial ---
    x = zeros(n,1);
    x_old = x;

    // --- Iteraciones de Gauss-Seidel ---
    iter = 0;
    while iter < max_iter
        iter = iter + 1;

        for i = 1:n
            suma = 0;
            for j = 1:n
                if j <> i then
                    if j < i then
                        suma = suma + A(i,j)*x(j);
                    else
                        suma = suma + A(i,j)*x_old(j);
                    end
                end
            end
            x(i) = (b(i) - suma)/A(i,i);
        end

        // Condición de parada
        if norm(x - x_old, "inf") < tol then
            break;
        end
        x_old = x;
    end

    // --- Mostrar resultados ---
    printf("\n✅ Convergió en %d iteraciones.\n", iter);
    disp("Solución aproximada:");
    disp(x);

    // --- Cálculo del radio espectral ---
    D = diag(diag(A));
    disp("D=",D);
    L = tril(A, -1);
    disp("L=",L);
    U = triu(A, 1);
    disp("U=",U);
    M_GS = -inv(D + L) * U;
    disp("N INV=",M_GS);
    autovalores = spec(M_GS);
    rho = max(abs(autovalores));
    printf("\n📈 Radio espectral = %.6f\n", rho);
endfunction


//------ EJERCICIIO 1 - PRACTICA 5 COMPLEMENTAIRA:
//1) Escribir un programa en Scilab que resuelva espec´ıficamente el siguiente sistema de ecuaciones lineales empleando el m´etodo de Gauss Seidel para cualquier valor de n.
//{
//2 −1 0 0 . . . 0 0 0 1
//−1 2 −1 0 . . . 0 0 0 0
//0 −1 2 −1 . . . 0 0 0 0
//.
//.
//.
//0 0 0 0 . . . −1 2 −1 0
//0 0 0 0 . . . 0 −1 2 −1
//1 0 0 0 . . . 0 0 −1 2} * {
//x1
//x2
//x3
//.
//.
//.
//xn−2
//xn−1
//xn}
//={
//0
//0
//0
//.
//.
//.
//0
//0
//1}
//Se puede demostrar que la soluci´on exacta es xi = −n/4 + i/2, i = 1, 2, . . . , n.
//a) Obtener la f´ormula iterativa del m´etodo de Gauss-Seidel para el sistema dado. Resolver para n = 20 partiendo de x0 = 0. Contar el n´umero de iteraciones.
//b) Obtener la matriz de iteraci´on del m´etodo y determinar su radio espectral.
//c) Repetir los dos items anteriores usando esta vez una matriz con elementos diagonales
//iguales a 4 en lugar de 2. Discutir los resultados.

// Caso (a) matriz con diagonal = 2
[x1, iter1, rho1] = gauss_seidel_ciclico(20, 2, 1e-6, 10000);

// Caso (c) matriz con diagonal = 4
[x2, iter2, rho2] = gauss_seidel_ciclico(20, 4, 1e-6, 10000);

//---
x_exacta = (-20/4) + (1:20)'/2;
error = norm(x1 - x_exacta, "inf");
disp("Error máximo con respecto a la solución exacta:");
disp(error);
