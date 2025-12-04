// Método de Gauss-Seidel con impresión de iteraciones
// xi^{k+1} = 1/aii * (bi - sum_{j=1}^{i-1} aij*xj^{k+1} - sum_{j=i+1}^{n} aij*xj^{k})
function x = gauss_seidel_verbose(A, b, x0, eps)
    n = size(A, 1);
    cont = 0;
    x = x0;
    xk = x0;
    
    disp("Iteración inicial:");
    disp(x0);

    while %t
        cont = cont + 1;
        printf("\nIteración %d:\n", cont);
        
        for i = 1:n
            suma = 0;
            for j = 1:n
                if (j ~= i) then
                    suma = suma + A(i,j)*x(j); // usa valores actualizados
                end
            end
            x(i) = (b(i) - suma) / A(i,i);
            printf("  x(%d) = %.6f\n", i, x(i));
        end
        
        // Condición de parada
        if norm(x - xk, "inf") < eps then
            break;
        end
        xk = x;
    end
    
    printf("\n✅ Convergió en %d iteraciones.\n", cont);
    disp("Solución aproximada:");
    disp(x);
endfunction

//------- == EJERCICIO P5-1.C ======
A=[1 -1 0; -1 2 -1 ; 0 -1 1.1]
b=[0 ; 1 ; 0]
x0=[0 ;1/2 ;0]
x=gauss_seidel_verbose(A,b,x0,0.01)


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

x = gauss_seidel_verbose(A, b, x0, eps);


A=[10 3 1 ; 2 -10 3 ; 1 3 10]
b=[14 ; -5 ; 14]
x0=[0 ;0 ;0]
x = gauss_seidel_verbose(A,b,x0,0.01);


//=====
A=[2 -1 0 ; -2 -5 -1 ; -1 0 3]
b=[1 ; -6 ; 2]
x0=[0 ;0 ;0]
x=gauss_seidel_verbose(A,b,x0,0.01)
disp(x);
