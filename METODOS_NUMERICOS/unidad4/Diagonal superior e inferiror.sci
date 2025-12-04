function x = diag_sup(A, b) //Ax=b, A triangular superior
    n = length(b); 
    x(n) = b(n)/A(n,n);
    for i=n-1:-1:1; //empezamos ec final - recorre hacia arriba
        x(i) = (b(i) - A(i,i+1:n)*x(i+1:n))/A(i,i);
    end
endfunction

function x = diag_inf(A, b)  //Ax=b, A triangular inferior
    n = length(b); 
    x(1) = b(1)/A(1,1); // empezamos ec inial, recorre hacia abajo
    for i=2:1:n;
        x(i) = (b(i) - A(i,1:i-1)*x(1:i-1))/A(i,i);
    end
endfunction

// ==== EJERCICIO 1: ======
//Escribir una funci´on en Scilab para resolver un sistema triangular superior, y otra funci´on para resolver un sistema triangular inferior.

A_sup = [2 1 -1; 0 3 2; 0 0 4];
b = [1; 7; 8];
x = diag_sup(A_sup, b)
disp('Ax=b',A_sup,b,x);

A_inf = [3 0 0; 1 2 0; 4 -1 1];
b = [3; 5; 2];
x = diag_inf(A_inf, b)

//////----------

// Verificación
x_sup = diag_sup(A_sup, b);
disp("Solución x_sup =");
disp(x_sup);

disp("Comprobación A*x = ");
disp(A_sup*x_sup);

disp("Vector b original = ");
disp(b);

// Verificamos que A*x ≈ b
if norm(A_sup*x_sup - b) < 1e-10 then
    disp("✅ Verificación correcta: A*x = b");
else
    disp("❌ Error: la solución no satisface A*x = b");
end
