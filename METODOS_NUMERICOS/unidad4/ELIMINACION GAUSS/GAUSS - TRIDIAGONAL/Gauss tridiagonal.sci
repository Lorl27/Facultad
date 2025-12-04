function [x,a] = gauss_tri(A, b)   //matriz 2×2 o 3×3 muy específica
    [nA,mA] = size(A);
    [nb,mb] = size(b);
    if nA<>mA then 
        error("La matriz A debe ser cuadrada");
        abort;
    elseif mA<>nb then 
        error("Dimensiones incompatibles entre A y b");
        abort;
    end
    
    a = [A b];
    n = nA;
    contador = 0;

    for k=1:n-1 do
        mkk=a(k+1,k)/a(k,k);
        a(k+1,k+1)=a(k+1,k+1)-mkk*a(k,k+1);
        a(k+1,n+1)=a(k+1,n+1)-mkk*a(k,n+1);
        contador=contador+5;
    end

    x(n)=a(n,n+1)/a(n,n);
    contador=contador+1;
    for k=n-1:-1:1 do
        x(k)=(a(k,n+1)-a(k,k+1)*x(k+1))/a(k,k);
        contador=contador+3;
    end
    disp(contador);
endfunction

//--
A2=[1 1 0  ; 2 1 -1  ; 4 -1 -2 ];
b2=[2 ; 1 ; 0 ];

[x2, a2] = gauss_tri(A2, b2);
mprintf("x2:");
disp(x2);
mprintf("a2:");
disp(a2);

/// == ejercicio 6 ===
//Construir un algoritmo espec´ıfico para resolver por el m´etodo de Gauss el problema Ax =
//b, cuando la matriz A es una matriz tridiagonal:
//A =
{
//b1 c1 0 · · · · · · 0
//a2 b2 c2 0 · · · 0
//0 a3 · · · · · · 0
//.
//0 · · · an−1 bn−1 cn−1
//0 0 · · · 0 an bn}

//Contar la cantidad de operaciones que se realizan en este caso. Se espera no operar con las entradas nulas.

