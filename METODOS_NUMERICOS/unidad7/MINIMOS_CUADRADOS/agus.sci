// Ejercicio 1) a)
// Valores de la tabla
x = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
y = [32.9, 30.8, 26.4, 24.2, 19.2, 16.5, 19.3, 21.0, 23.0, 26.2];

// Función para construir matriz de vandermonde A
function A = A_mc(x, grado)
    // p = grado+1
    m = length(x);
    A = ones(m, 1);
    for j=2:(grado + 1)
        A = [A,(x').^(j-1)];
    end
endfunction

// Matriz del metodo de mínimo cuadrados polinomial
function p = MinCuad_pol(A, b) //b = vector y
    a = inv(A'*A) * A'*b';
    p = poly(a, "x", "coeff");
endfunction

// Función constructora de los polinomios por grado pedido
function p = minimos_cuadrados(x, y, grado)
    A = A_mc(x, grado)
    p = MinCuad_pol(A, y)
endfunction

p3 = minimos_cuadrados(x, y, 3);
p5 = minimos_cuadrados(x, y, 5);
p7 = minimos_cuadrados(x, y, 7);
p9 = minimos_cuadrados(x, y, 9);
disp("Polinomio de grado 3: " + string(p3));
disp("Polinomio de grado 5: " + string(p5));
disp("Polinomio de grado 7: " + string(p7));
disp("Polinomio de grado 9: " + string(p9));

// Graficación
xx = 1:0.1:10; // Espaciado de 0.1

scf(0); // Crear nueva figura
plot(x, y, 'ro'); // Puntos originales
plot(xx, horner(p3, xx), 'b-'); // p3
plot(xx, horner(p5, xx), 'g-'); // p5
plot(xx, horner(p7, xx), 'm-'); // p7
plot(xx, horner(p9, xx), 'c-'); // p9

xlabel('Mes');
ylabel('Temperatura máxima (°C)');
title('Aproximación por mínimos cuadrados (método AᵀA)');
legend(['Datos', 'p3(x)', 'p5(x)', 'p7(x)', 'p9(x)'], 2);

// Ejercicio 1) b)
// Halla las matrices Q y R de A
function [Q, R] = fact_qr(A)
    [nA,mA] = size(A)
    Q = zeros(nA, mA);
    R = zeros(mA, mA);
    
    Q(:, 1) = A(:, 1)/norm(A(:, 1));
    
    for k = 1:mA
        suma = 0;
        for i = 1:k-1
            suma = suma + (A(:,k)'*Q(:,i))*Q(:,i);
        end
        vk = norm(A(:,k) - suma);
        Q(:,k) = (A(:,k) - suma) / vk;
        R(k,k) = vk;
        R(k, k+1:mA) =(A(:,k+1:mA)' * Q(:, k))';
    end
endfunction

// Matriz del metodo de mínimo cuadrados polinomial con matriz QR
function p = MinCuad_pol_QR(A, b) //b = vector y
    [Q, R] = fact_qr(A);
    a = inv(R)*Q'*b';
    p = poly(a, "x", "coeff");
endfunction

// Función constructora de los polinomios por grado pedido
function p = minimos_cuadrados_QR(x, y, grado)
    A = A_mc(x, grado)
    p = MinCuad_pol_QR(A, y)
endfunction

p3_QR = minimos_cuadrados_QR(x, y, 3);
p5_QR = minimos_cuadrados_QR(x, y, 5);
p7_QR = minimos_cuadrados_QR(x, y, 7);
p9_QR = minimos_cuadrados_QR(x, y, 9);
disp("Polinomio de grado 3 con matriz QR: " + string(p3_QR));
disp("Polinomio de grado 5 con matriz QR: " + string(p5_QR));
disp("Polinomio de grado 7 con matriz QR: " + string(p7_QR));
disp("Polinomio de grado 9 con matriz QR: " + string(p9_QR));

// Graficación
scf(1); // Nueva figura
plot(x, y, 'ro'); // Puntos originales
plot(xx, horner(p3_QR, xx), 'b-'); // p3
plot(xx, horner(p5_QR, xx), 'g-'); // p5
plot(xx, horner(p7_QR, xx), 'm-'); // p7
plot(xx, horner(p9_QR, xx), 'c-'); // p9

xlabel('Mes');
ylabel('Temperatura máxima (°C)');
title('Aproximación por mínimos cuadrados (método QR)');
legend(['Datos', 'p3(x)', 'p5(x)', 'p7(x)', 'p9(x)'], 2);
