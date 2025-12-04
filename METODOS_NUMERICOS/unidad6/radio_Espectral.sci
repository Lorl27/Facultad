function rho = spectral_radius(A)
    // Verifica que A sea cuadrada
    [m, n] = size(A);
    if m <> n then
        error("La matriz debe ser cuadrada para calcular el radio espectral.");
    end

    // Calcula los autovalores
    lambda = spec(A);

    // Toma el máximo del valor absoluto
    rho = max(abs(lambda));
endfunction

//--
A = [0.5 0.2; 0.1 0.4];
r = spectral_radius(A);
disp("Radio espectral: " + string(r));
//si <1 -> conrge la iteracion .

B = [4 1 -1; 2 3 0 ; 0 1 2];
r = spectral_radius(B);
disp("Radio espectral: " + string(r));
//si <1 -> conrge la iteracion .
