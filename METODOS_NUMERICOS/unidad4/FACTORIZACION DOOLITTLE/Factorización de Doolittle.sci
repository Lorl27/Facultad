function [L, U] = fact_doolittle(A)
    [mA, nA] = size(A);
    if mA <> nA then
        error("La matriz A debe ser cuadrada.");
        abort;
    end
    
    L = eye(mA, mA);    
    U = zeros(mA, mA);
    
    for i = 1:mA
        if i > 1 then
            U(i, :) = A(i, :) - L(i, 1:i-1) * U(1:i-1, :); 
            L(i+1:mA, i) = (A(i+1:mA, i) - L(i+1:mA, 1:i-1) * U(1:i-1, i)) / U(i, i);
        else
            U(i, :) = A(i, :);
            L(i+1:mA, i) = A(i+1:mA, i) / U(i, i);
        end
    end
endfunction



////--
//function [L, U] = fact_doolittle2(A)
//    [n, m] = size(A);
//    if n <> m then
//        error("La matriz A debe ser cuadrada.");
//        abort;
//    end
//
//    L = eye(n, n);
//    U = zeros(n, n);
//
//    for i = 1:n
//        // Calcular elementos de U en la fila i
//        for j = i:n
//            suma = 0;
//            for k = 1:i-1
//                suma = suma + L(i, k) * U(k, j);
//            end
//            U(i, j) = A(i, j) - suma;
//        end
//
//        // Calcular elementos de L en la columna i (debajo de la diagonal)
//        for j = i+1:n
//            suma = 0;
//            for k = 1:i-1
//                suma = suma + L(j, k) * U(k, i);
//            end
//            L(j, i) = (A(j, i) - suma) / U(i, i);
//        end
//    end
//endfunction


//=============================================== EJERCICIO NRO 10:
//10. Construir un algoritmo para resolver sistemas lineales mediante la factorizaci´on LU de
//Doolittle y utilizarlo para resolver el sistema Ax = b de forma m´as simple, donde
//A ={
//1 2 3 4
//1 4 9 16
//1 8 27 64
//1 16 81 256} 
// b ={
//2
//10
//44
//190}

A =[
    1 2 3 4;
    1 4 9 16;
    1 8 27 64;
    1 16 81 256]
 b =[
    2;
    10;
    44;
    190]
    
 [L, U] = fact_doolittle(A);
  
disp("L =",L);
disp("U =",U);

// Resolución del sistema A·x = b
y = L\b;
x = U\y;
disp("x =",x);
