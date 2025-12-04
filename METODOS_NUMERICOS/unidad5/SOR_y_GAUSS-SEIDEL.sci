// ============================================================
// 🔹 COMPARACIÓN MÉTODO SOR vs GAUSS-SEIDEL
// ============================================================

clear; clc;

A = [10 -3 0;
     -3 10 -2;
      0 -2 10];
b = [2; 2; 5];
x0 = [0; 0; 0];
w = 1.0348;
tol = 1e-2;
maxit = 5;

// ============================================================
// 🔸 Gauss-Seidel con impresión paso a paso (sin warnings)
// ============================================================
function [x] = gauss_seidel_show(A, b, x0, tol, maxit)
    n = size(A, 1);
    x = x0;

    printf("\n===== MÉTODO GAUSS–SEIDEL =====\n");
    printf("Iter\t    x1\t\t    x2\t\t    x3\n");
    printf("-------------------------------------------\n");
    printf("%d\t%8.6f\t%8.6f\t%8.6f\n", 0, x(1), x(2), x(3));

    for k = 1:maxit
        x_old = x;
        for i = 1:n
            if i == 1 then
                s1 = 0;
            else
                s1 = A(i,1:i-1)*x(1:i-1);
            end
            if i == n then
                s2 = 0;
            else
                s2 = A(i,i+1:n)*x_old(i+1:n);
            end
            x(i) = (b(i) - s1 - s2)/A(i,i);
        end
        printf("%d\t%8.6f\t%8.6f\t%8.6f\n", k, x(1), x(2), x(3));
        if norm(x - x_old, "inf") < tol then
            break;
        end
    end
    printf("-------------------------------------------\n");
    printf("Resultado aproximado: [%g, %g, %g]\n", x(1), x(2), x(3));
endfunction

// ============================================================
// 🔸 SOR con impresión paso a paso (sin warnings)
// ============================================================
function [x] = SOR_show(A, b, x0, w, tol, maxit)
    n = size(A, 1);
    x = x0;

    printf("\n===== MÉTODO SOR (ω = %g) =====\n", w);
    printf("Iter\t    x1\t\t    x2\t\t    x3\n");
    printf("-------------------------------------------\n");
    printf("%d\t%8.6f\t%8.6f\t%8.6f\n", 0, x(1), x(2), x(3));

    for k = 1:maxit
        x_old = x;
        for i = 1:n
            if i == 1 then
                s1 = 0;
            else
                s1 = A(i,1:i-1)*x(1:i-1);
            end
            if i == n then
                s2 = 0;
            else
                s2 = A(i,i+1:n)*x_old(i+1:n);
            end
            gi = (b(i) - s1 - s2)/A(i,i);
            x(i) = (1 - w)*x_old(i) + w*gi;
        end
        printf("%d\t%8.6f\t%8.6f\t%8.6f\n", k, x(1), x(2), x(3));
        if norm(x - x_old, "inf") < tol then
            break;
        end
    end
    printf("-------------------------------------------\n");
    printf("Resultado aproximado: [%g, %g, %g]\n", x(1), x(2), x(3));
endfunction

// ============================================================
// 🔹 Ejecución
// ============================================================
x_gs = gauss_seidel_show(A, b, x0, tol, 3);
x_sor = SOR_show(A, b, x0, w, tol, 5);
