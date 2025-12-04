function [x,a,count] = gausselim(A,b)
// Esta función obtiene la solución del sistema de ecuaciones lineales A*x=b, 
// dada la matriz de coeficientes A y el vector b.
// La función implementa el método de Eliminación Gaussiana sin pivoteo.  

[nA,mA] = size(A) 
[nb,mb] = size(b)


if nA<>mA then
    error('gausselim - La matriz A debe ser cuadrada');
    abort;
elseif mA<>nb then
    error('gausselim - dimensiones incompatibles entre A y b');
    abort;
end;

a = [A b]; // Matriz aumentada

// Eliminación progresiva
n = nA;
count=0;
for k=1:n-1
    for i=k+1:n
        for j=k+1:n+1
            a(i,j) = a(i,j) - a(k,j)*a(i,k)/a(k,k);
            count=count+3; //div-mult-resta
        end;
        for j=1:k        // no hace falta para calcular la solución x
            a(i,j) = 0;  // no hace falta para calcular la solución x
        end              // no hace falta para calcular la solución x
    end;
end;

// Sustitución regresiva
x(n) = a(n,n+1)/a(n,n);
count=count+1; //div
for i = n-1:-1:1
    sumk = 0
    for k=i+1:n
        sumk = sumk + a(i,k)*x(k);
        count=count+2; //resta-div
    end;
    x(i) = (a(i,n+1)-sumk)/a(i,i);
end;

mprintf("\nTotal de operaciones aritméticas: %d\n", count);

endfunction

///====================================0
// Ejemplos de aplicación
A = [3 -2 -1; 6 -2 2; -9 7 1]
b = [0 6 -1]'

A = [1 1 0 3; 2 1 -1 1; 3 -1 -1 2; -1 2 3 -1]
b = [4 1 -3 4]'

[x,a] = gausselim(A,b)
disp(x)
disp(a)

A2 = [0 2 3; 2 0 3; 8 16 -1]
b2 = [7 13 -3]'

A2 = [1 -1 2 -1; 2 -2 3 -3; 1 1 1 0; 1 -1 4 3]
b2 = [-8 -20 -2 4]'

//[x2,a2] = gausselim(A2,b2)

// !--error 27 
//Division by zero...
//at line      24 of function gausselim called by :  
//[x2,a2] = gausselim(A2,b2)


//================================================

//EJERCICIO 2:
//Se provee el m´etodo de eliminaci´on de Gauss programado en Scilab en la funci´on GaussElim.
//(a) Estudiar el c´odigo de la funci´on GaussElim.
//(b) Aplicarlo para resolver los siguientes sistemas Ax = b
// (c) Modificar la funci´on GaussElim a fin de contar el n´umero de operaciones realizadas.

A1=[1 1 0 3 ; 2 1 -1 1 ; 3 -1 -1 2 ; -1 2 3 -1];
b1=[4 ; 1 ; -3 ; 4];

[x1,a1]=gausselim(A1,b1);

mprintf("\nSolución del sistema (x):\n");
disp(x1);

mprintf("\nMatriz aumentada triangular (a):\n");
disp(a1);

//------------------

A2=[1 -1 2 -1 ; 2 -2 3 -3 ; 1 1 1 0 ; 1 -1 4 3];   //ES NECESARIO PIVOTEAR!
b2=[-8 ; -20 ; -2 ; 4];

[x2,a2]=gausselim(A2,b2);

mprintf("\nSolución del sistema (x):\n");
disp(x2);

mprintf("\nMatriz aumentada triangular (a):\n");
disp(a2);

//-------------------

A3=[1 1 0 4 ; 2 1 -1 1 ; 4 -1 -2 2 ; 3 -1 -1 2];
b3=[2 ; 1 ; 0 ; -3];

[x3,a3,count]=gausselim(A3,b3);

mprintf("\nSolución del sistema (x):\n");
disp(x3);

mprintf("\nMatriz aumentada triangular (a):\n");
disp(a3);

mprintf("\nOperaciones totales realizadas: %d\n", count);

