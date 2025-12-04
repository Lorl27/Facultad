// Método de Jacobi con impresión de valores por iteración
function x = jacobi_verbose(A, b, x0, eps)
    n = size(A, 1);
    cont = 0;
    x = x0;
    xk = x0;
    
    disp("Iteración inicial:");
    disp(xk);

    while %t
        cont = cont + 1;
        printf("\nIteración %d:\n", cont);
        
        // calcular nuevo x
        for i = 1:n
            suma = 0;
            for j = 1:n
                if j ~= i then
                    suma = suma + A(i,j)*xk(j);
                end
            end
            x(i) = (b(i) - suma) / A(i,i);
            printf("  x(%d) = %.6f\n", i, x(i)); // muestra cada componente
        end
        
        // criterio de parada
        if norm(x - xk, "inf") < eps then
            break;
        end
        
        xk = x;
    end
    
    printf("\nConvergió en %d iteraciones.\n", cont);
    disp("Solución aproximada:");
    disp(x);
endfunction

//------- == EJERCICIO P5-1.C ======
A=[1 -1 0; -1 2 -1 ; 0 -1 1.1]
b=[0 ; 1 ; 0]
x0=[0 ;1/2 ;0]
x=jacobi_verbose(A,b,x0,0.01)

///====== EJERCICIO 2
// MATRIZ A
A = [10  1   2   3   4;
     1   9  -1   2  -3;
     2  -1   7   3  -5;
     3   2   3  12  -1;
     4  -3  -5  -1  15];

// VECTOR b
b = [12; -27; 14; -17; 12];

// VECTOR INICIAL x0
x0 = zeros(5,1);

// TOLERANCIA
eps = 1e-6;

x = jacobi_verbose(A, b, x0, eps);

