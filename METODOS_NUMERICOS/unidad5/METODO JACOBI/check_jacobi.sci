function convergencia = check_jacobi(a, b)
    // construye A
    A = [1, a, 0;
         1, 1, 1;
         0, b, 1];

    // matriz de iteración Jacobi (D = I)
    B = - (A - eye(3,3));

    // autovalores y radio espectral
    ev = spec(B);
    rho = max(abs(ev));

    // mostrar resultados
    disp("A = "); disp(A);
    disp("Matriz de iteración B = "); disp(B);
    disp("Autovalores de B = "); disp(ev');
    printf("Radio espectral ρ(B) = %.6f\n", rho);

    if rho < 1 then
        disp("=> Jacobi CONVERGE (ρ(B) < 1).");
        convergencia = %t;
    else
        disp("=> Jacobi NO GARANTIZA convergencia (ρ(B) >= 1).");
        convergencia = %f;
    end
endfunction

// Ejemplo
check_jacobi(0.2, 0.3); // debe converger
check_jacobi(0.8, 0.5); // no converge
