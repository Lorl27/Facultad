function [x, cont] = gauss_seidel(A, b, x0, eps)
    n = size(A, 1);
    cont = 0;
    x = x0;
    xk = x;
    
    for i=1:n
        suma = 0; 
        for j = 1:n
            if (j ~= i)
                suma = suma + A(i,j) * x(j);
            end
        end
        x(i) = 1/A(i,i) * (b(i) - suma);
    end
    cont = cont + 1;
    
    while (norm(x - xk) > eps)
        xk = x;
        for i=1:n
            suma = 0; 
            for j = 1:n
                if (j ~= i)
                    suma = suma + A(i,j) * x(j);
                end
            end
            x(i) = 1/A(i,i) * (b(i) - suma);
        end
        cont = cont + 1;
    end
    
    x0 = x;
endfunction

function [x0, it] = SOR(A, b, x0, iter, tol, w)
    n = size(A, 1);
    x = x0;
    
    x0(1) = (1-w)*x0(1) + w*(b(1) - A(1, 2:n)*x0(2:n))/A(1, 1);
    for i = 2:(n-1)
        x0(i) = (1-w)*x0(i) + w*(b(i) - A(i, 1:i-1)*x0(1:i-1) - A(i, i+1:n)*x0(i+1:n))/A(i, i);
    end
    x0(n) = (1-w)*x0(n) + w*(b(n) - A(n, 1:n-1)*x0(1:n-1))/A(n, n);
    
    it = 1;
    err = norm(x0 - x);
    
    while (err > tol) && (it < iter)
        x = x0;
        x0(1) = (1-w)*x0(1) + w*(b(1) - A(1, 2:n)*x0(2:n))/A(1, 1);
        for i = 2:(n-1)
            x0(i) = (1-w)*x0(i) + w*(b(i) - A(i, 1:i-1)*x0(1:i-1) - A(i, i+1:n)*x0(i+1:n))/A(i, i);
        end
        x0(n) = (1-w)*x0(n) + w*(b(n) - A(n, 1:n-1)*x0(1:n-1))/A(n, n);
        it = it + 1;
        err = norm(x0 - x);
    end
    
    x0 = x0;
endfunction

function w = omega_opt(A)
    // A es una matriz definida positiva y tridiagonal
    n = size(A)(1);
    T_j = eye(n,n) - diag(1./diag(A))*A;
    autovalores = spec(T_j);
    rho = max(abs(autovalores)); // ver help eigs
    w = 2/(1+sqrt(1-rho**2))
endfunction

// Parcial 2: 2024
// Ejercicio 5)a)
function rho = r_SOR(w)
    A = [10 5 0 0; 5 10 -4 0; 0 -4 8 -1; 0 0 -1 5];
    D = diag(diag(A));
    L = tril(A, -1);
    U = triu(A, 1);
    
    T = inv(D + w*L)*[(1 - w)*D - w*U];
    autovalores = spec(T);
    rho = max(abs(autovalores));
endfunction

A = [10 5 0 0; 5 10 -4 0; 0 -4 8 -1; 0 0 -1 5];
w = omega_opt(A);
rho = r_SOR(w);
disp("El radio espectral de la mátriz del método de relajación es p = " + string(rho));

// Ejercicio 5)b)
// Primero calculamos rho para el método de Gauss-Seidel (w = 1)
rho_GS = r_SOR(1);

// Ahora evaluamos rho(w) en un rango de w
omegas = linspace(1, 1.5, 100);
radios = [];
for w = omegas
    radios = [radios, r_SOR(w)];
end

// Ahora graficamos
scf();
plot(omegas, radios, 'b-', 'LineWidth', 2);
plot(1, rho_GS, 'ro', 'MarkerSize', 8);
xlabel("w");
ylabel("p(w)");
title("Radio espectral de SOR vs. Gauss-Seidel");
legend(["SOR", "Gauss-Seidel (w=1)"]);

// Encontramos el intervalo óptimo
indices = find(radios < rho_GS);
omega_opt_interval = [min(omegas(indices)), max(omegas(indices))];
disp("Intervalo óptimo: w ∈ " + string(omega_opt_interval));

// Ejercicio 5) c)
disp("El valor de w óptimo es w = " + string(w));

// Ejercicio 5) d)
x0 = zeros(4, 1);
b = [6; 25; -11; -11];
tol = 10^(-6);
[x_GS, cont] = gauss_seidel(A, b, x0, tol);
disp("Solución por Gauss-Seidel")
for i = 1:4
    disp("x" + string(i) + " = " + string(x_GS(i)));
end
disp("Cantidad de iteraciones: " + string(cont));

// Ejercicio 5) e)
x0 = zeros(4, 1);
b = [6; 25; -11; -11];
tol = 10^(-6);
iter = 100;
[x_SOR, it] = SOR(A, b, x0, iter, tol, w);
disp("Solución por SOR")
for i = 1:4
    disp("x" + string(i) + " = " + string(x_SOR(i)));
end
disp("Cantidad de iteraciones: " + string(it));
