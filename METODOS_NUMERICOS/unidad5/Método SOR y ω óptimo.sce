//-----------
//5. M´etodo de sobrerrelajaci´on (SOR). Sea Ax = b un sistema n × n de ecuaciones lineales y
//sea w ∈ R+. Considerar la siguiente modificaci´on del esquema de Gauss-Seidel, conocida
//como el m´etodo de sobrerrelajaci´on-
//Si A es una matriz definida positiva y tridiagonal se demuestra que la elecci´on ´optima para
//el par´ametro w del m´etodo SOR viene dada por
//w =
//2
//1 + p
//1 − ρ(TJ )
//2
//siendo TJ = (I − D−1A) la matriz del m´etodo de Jacobi.
//Resolver el siguiente sistema lineal usando el algoritmo SOR con una tolerancia de 10−2
//{4x1 + 3x2 = 24
//3x1 + 4x2 − x3 = 30
//− x2 + 4x3 = −24}
//cuya soluci´on es x = (3, 4, −5)T. Partiendo de un mismo vector inicial calcular cu´antas
//iteraciones se necesitan para aproximar la soluci´on con una precisi´on de siete lugares
//decimales empleando:
//a) el m´etodo de Gauss-Seidel
//b) el m´etodo de SOR con el par´ametro de relajaci´on ´optimo
// ==========================
// SOR vs Gauss-Seidel (Ejercicio SOR pequeño)
// ==========================

// --------- Funciones auxiliares ---------

// Gauss-Seidel: devuelve x, número de iteraciones
function [x, it] = gauss_seidel_count(A, b, x0, tol, maxit)
    n = size(A,1);
    x = x0;
    it = 0;
    while it < maxit
        it = it + 1;
        x_old = x;
        for i = 1:n
            // s1 = A(i,1:i-1)*x(1:i-1)   (valores actualizados)
            // s2 = A(i,i+1:n)*x_old(i+1:n)
            if i > 1 then
                s1 = A(i,1:i-1) * x(1:i-1);
            else
                s1 = 0;
            end
            if i < n then
                s2 = A(i,i+1:n) * x_old(i+1:n);
            else
                s2 = 0;
            end
            denom = A(i,i);
            if abs(denom) < %eps then
                error("Pivote nulo en fila "+string(i));
            end
            x(i) = (b(i) - s1 - s2)/denom;
        end
        if norm(x - x_old, "inf") <= tol then
            return
        end
    end
    warning("No convergió en maxit iteraciones (Gauss-Seidel).");
endfunction

// SOR: devuelve x, número de iteraciones
function [x, it] = SOR_count(A, b, x0, w, tol, maxit)
    n = size(A,1);
    x = x0;
    it = 0;
    while it < maxit
        it = it + 1;
        x_old = x;
        // actualización SOR (valores inmediatamente actualizados)
        for i = 1:n
            if i > 1 then
                s1 = A(i,1:i-1) * x(1:i-1);
            else
                s1 = 0;
            end
            if i < n then
                s2 = A(i,i+1:n) * x_old(i+1:n);
            else
                s2 = 0;
            end
            denom = A(i,i);
            if abs(denom) < %eps then
                error("Pivote nulo en fila "+string(i));
            end
            gi = (b(i) - s1 - s2)/denom; // Gauss-Seidel candidate
            x(i) = (1 - w)*x_old(i) + w*gi;
        end
        if norm(x - x_old, "inf") <= tol then
            return
        end
    end
    warning("No convergió en maxit iteraciones (SOR).");
endfunction

// ω óptimo según el teorema (para matrices SPD tridiagonales) --     // A es una matriz definida positiva y tridiagonal
// calcula TJ y su rho
function w = omega_opt(A)
    n = size(A,1);
    Dinv = diag(1./diag(A));
    TJ = eye(n,n) - Dinv * A;
    // spec devuelve autovalores; si no existe en tu versión usa evect/eigen
    aut = spec(TJ);
    disp("autovalores:",aut);
    rho = max(abs(aut)); // ver help eigs
    // proteger si rho>1 por redondeos (no debería si A SPD tridiagonal)
    if rho >= 1 then
        warning("rho(TJ) >= 1 (rho = "+string(rho)+"); ω óptimo no definido con esta fórmula.");
        w = 1.0; // fallback
        return
    end
    w = 2 / (1 + sqrt(1 - rho^2));
endfunction

//==========================================================
A=[10 -3 0 ; -3 10 -2 ; 0 -2 10];
b=[2 ; 2; 5];
x=[0.2;0.2;0.3];
x_0=[0;0;0];
w=omega_opt(A);
disp(w);
[x_sor, it]=SOR_count(A,b,x_0,w,0.01,5);

printf("SOR (ω = %g): iter = %d, x = [%g, %g, %g]\n", w, it, x_sor(1), x_sor(2), x_sor(3));
disp(x0);

[x_gs, it_gs] = gauss_seidel_count(A, b, x_0, 0.01, 3);
printf("\nGauss-Seidel: iter = %d, x = [%g, %g, %g]", it_gs, x_gs(1), x_gs(2), x_gs(3));
//====================================

   // --------- ejercicio 5 ---------

// Matriz y vector del enunciado
A = [ 4  3  0;
      3  4 -1;
      0 -1  4 ];
b = [24; 30; -24];

// solución exacta conocida (para comparar)
x_exact = [3; 4; -5];

// parámetros
x0 = zeros(3,1);       // vector inicial (puedes cambiar)
tol = 1e-7;            // siete decimales
maxit = 10000;

// 1) Gauss-Seidel
[x_gs, it_gs] = gauss_seidel_count(A, b, x0, tol, maxit);
err_gs = norm(x_gs - x_exact, "inf");
printf("\nGauss-Seidel: iter = %d, x = [%g, %g, %g], err_inf = %g\n", it_gs, x_gs(1), x_gs(2), x_gs(3), err_gs);

// 2) ω óptimo por la fórmula (válido aquí porque A es SPD tridiagonal)
w_opt = omega_opt(A);
printf("ω_opt calculado = %g\n", w_opt);

// 3) SOR con ω_opt
[x_sor, it_sor] = SOR_count(A, b, x0, w_opt, tol, maxit);
err_sor = norm(x_sor - x_exact, "inf");
printf("SOR (ω = %g): iter = %d, x = [%g, %g, %g], err_inf = %g\n", w_opt, it_sor, x_sor(1), x_sor(2), x_sor(3), err_sor);


