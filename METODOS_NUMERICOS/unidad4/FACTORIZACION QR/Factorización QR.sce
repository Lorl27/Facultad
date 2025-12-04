//function [Q, R] = fact_qr(A)
//    [nA,mA] = size(A)
//    Q = zeros(nA, mA);
//    R = zeros(mA, mA);
//    
//    Q(:, 1) = A(:, 1)/norm(A(:, 1));
//    
//    for k = 1:mA
//        suma = 0;
//        for i = 1:k-1
//            suma = suma + (A(:,k)'*Q(:,i))*Q(:,i);
//        end
//        vk = norm(A(:,k) - suma);
//        Q(:,k) = (A(:,k) - suma) / vk;
//        R(k,k) = vk;
//        R(k, k+1:mA) =(A(:,k+1:mA)' * Q(:, k))';
//    end
//endfunction


function [Q, R] = fact_qr(A)
    [nA, mA] = size(A);
    Q = zeros(nA, mA);
    R = zeros(mA, mA);

    for k = 1:mA
        v = A(:, k);
        for j = 1:k-1
            R(j, k) = Q(:, j)' * A(:, k);
            v = v - R(j, k) * Q(:, j);
        end
        R(k, k) = norm(v);
        Q(:, k) = v / R(k, k);
    end
endfunction

//-------------------
function x = resolver_qr(A, b)
    [Q, R] = fact_qr(A);
    y = Q' * b;           // Qᵗ * b
    x = R \ y;            // Resolver R*x = y (sustitución hacia atrás)
    
    disp("Matriz Q:");
    disp(Q);
    disp("Matriz R:");
    disp(R);
    disp("Solución x:");
    disp(x);
endfunction

// ========= EJERCICIO 12 (B):
//(b) Escribir en Scilab una funci´on que resuelva el sistema Ax = b mediante la factorizaci´on QR y resolver el sistema del ´ıtem anterior.

A = [16 -12 8;
    -12 18 -6;
      8  -6  8];
b = [76; -66; 46];

x = resolver_qr(A, b);

