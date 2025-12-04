// ==========================
// Ejercicio 4 - Práctica 5
// Métodos: Eliminación de Gauss y Gauss-Seidel
// ==========================

// --- Función para crear la matriz A y el vector b ---
function [A, b] = crear_sistema(N)
    A = 8*eye(N,N) ...
      + 2*diag(ones(N-1,1), 1) + 2*diag(ones(N-1,1), -1) ...
      + diag(ones(N-3,1), 3) + diag(ones(N-3,1), -3);
    b = ones(N,1);
endfunction

// --- Método de Gauss-Seidel (iterativo) ---
function [x, iter, tiempo] = gauss_seidel(A, b, eps)
    tic(); // inicio del cronómetro
    n = size(A,1);
    x = zeros(n,1);
    xk = x;
    iter = 0;
    
    while %t
        iter = iter + 1;
        for i = 1:n
            suma = 0;
            for j = 1:n
                if j <> i then
                    suma = suma + A(i,j)*x(j);
                end
            end
            x(i) = (b(i) - suma)/A(i,i);
        end
        
        if norm(x - xk, "inf") < eps then
            break;
        end
        xk = x;
    end
    tiempo = toc(); // fin del cronómetro
endfunction

// --- Método de Eliminación de Gauss con pivoteo parcial ---
function [x, tiempo] = gauss_pivoteo(A, b)
    tic(); // inicio cronómetro
    n = size(A, 1);
    // Eliminación
    for k = 1:n-1
        // pivoteo parcial
        [max_val, p] = max(abs(A(k:n, k)));
        p = p + k - 1;
        if p <> k then
            A([k p], :) = A([p k], :);
            b([k p]) = b([p k]);
        end
        for i = k+1:n
            m = A(i,k)/A(k,k);
            A(i,k:n) = A(i,k:n) - m*A(k,k:n);
            b(i) = b(i) - m*b(k);
        end
    end
    
    // Sustitución regresiva
    x = zeros(n,1);
    for i = n:-1:1
       if i < n then
         x(i) = (b(i) - A(i, i+1:n)*x(i+1:n)) / A(i,i);
        else
            x(i) = b(i) / A(i,i);
        end
    end
    tiempo = toc(); // fin del cronómetro
endfunction


// ======================
// Ejecución principal
// ======================

epsilones = [1e-6, 1e-11];
Ns = [100, 500];

for nn = 1:length(Ns)
    N = Ns(nn);
    [A, b] = crear_sistema(N);
    printf("\n=============================\n");
    printf("✅ N = %d\n", N);

    // --- Gauss con pivoteo ---
    [x_gauss, t_gauss] = gauss_pivoteo(A, b);
    printf("Método de Gauss con pivoteo: %.6f segundos\n", t_gauss);

    // --- Gauss-Seidel con dos tolerancias ---
    for ee = 1:length(epsilones)
        eps = epsilones(ee);
        [x_gs, iter, t_gs] = gauss_seidel(A, b, eps);
        printf("Método de Gauss-Seidel (ε = %e): %.6f s, %d iteraciones\n", eps, t_gs, iter);
    end
end



///-------------------------
//4. Crear en Scilab la siguiente matrix A de N × N y el vector b:
//A = 8*eye(N,N) + 2*diag(ones(N-1,1),1) + 2*diag(ones(N-1,1),-1)
//+ diag(ones(N-3,1),3) + diag(ones(N-3,1),-3)
//b = ones(N,1)
//Resolver el sistema Ax = b con N = 100 y con N = 500, empleando los m´etodos de
//Eliminaci´on de Gauss con pivoteo parcial y de Gauss-Seidel. Para el m´etodo de GaussSeidel partir de x
//(0) = 0 utilizando como tolerancia kx
//(k) −x
//(k−1)k ≤ ǫ con ǫ = 10−6 y con
//ǫ = 10−11. En cada caso, determinar el tiempo que le lleva a Scilab resolver el sistema,
//para lo cual se puede usar la secuencia de comandos tic(); algoritmo; t=toc()

