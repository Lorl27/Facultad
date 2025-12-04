//ejercicio 3;:

function [centros, radios, rho_cota,rho_min, solapados] = gershgorin_info_plot(A, show_eig)
    // Verifica que A sea cuadrada
    [n, m] = size(A);
    if n <> m then
        error("La matriz debe ser cuadrada.");
    end

    centros = zeros(n,1);
    radios = zeros(n,1);
    
    solapados = %f; // flag de solapamiento
    rho_cota = 0;
    rho_min=%inf;

    clf(); // Limpia la figura
    theta = linspace(0, 2*%pi, 200); // Ángulo para trazar círculos

    for i = 1:n
        centros(i) = A(i,i);
        radios(i) = sum(abs(A(i,:))) - abs(A(i,i));
        rho_cota = max(rho_cota, abs(centros(i)) + radios(i));
        rho_min=min(rho_min, abs(centros(i)) - radios(i));

        // Coordenadas del círculo
        x = real(centros(i)) + radios(i) * cos(theta);
        y = imag(centros(i)) + radios(i) * sin(theta);

        // Traza el círculo
        plot(x, y, 'b-');
        // Marca el centro
        plot(real(centros(i)), imag(centros(i)), 'ko');
    end
    
    
    // Verifica solapamiento entre círculos
    for i = 1:n
        for j = i+1:n
            dist = abs(centros(i) - centros(j));
            if dist < radios(i) + radios(j) then
                solapados = %t;
            end
        end
    end

    // Opcional: muestra autovalores
    if argn(2) >= 2 & show_eig then
        lambda = spec(A);
        disp("Autovalores encontrados con spec: ",lambda);
        plot(real(lambda), imag(lambda), 'r*');
        legend(["Círculos de Gershgorin", "Centros", "Autovalores"]);
    else
        legend(["Círculos de Gershgorin", "Centros"]);
    end

    // Ajusta ejes
    a = gca();
    a.isoview = "on";
    a.grid = [1 1];
    xtitle("Círculos de Gershgorin en el plano complejo");
    
    // Mensajes interpretativos
        disp("Cota inferior posible para el radio espectral (min |centro| - radio): " + string(rho_min));
    disp("Cota superior para el radio espectral (máx |centro| + radio): " + string(rho_cota));
        disp("➡️ Intervalo estimado de autovalores ≈ [" + string(rho_min) + ", " + string(rho_cota) + "]");

    if rho_cota < 1 then
        disp("✅ Posible convergencia: todos los círculos están dentro del disco unidad.");
    else
        disp("⚠️ Al menos un círculo excede el disco unidad: revisar autovalores reales.");
    end

    if solapados then
        disp("🔄 Hay círculos solapados: los autovalores pueden estar agrupados o desplazados.");
    else
        disp("🟢 Los círculos están separados: cada autovalor probablemente cerca de su centro.");
    end
endfunction

///---
A = [-2 1 0 0 ; 0 2 0 1; 1 0 -1.5 0 ; 0 0 0.5 3.5 ];
[centros, radios, rho_cota,rho_min, solapados] = gershgorin_info_plot(A, %t);
disp("Centros:");
disp(centros);
disp("Radios:");
disp(radios);


//RESULTADOS (ADEMAS DEL PLOT CGUARDADO COMO IMAGEN)
//
//"Autovalores encontrados con spec: "
//
//  -2.0412521 + 0.i
//  -1.4469788 + 0.i
//   3.5119705 + 0.i
//   1.9762605 + 0.i
//
//  "Cota inferior posible para el radio espectral (min |centro| - radio): 0.5"
//
//  "Cota superior para el radio espectral (máx |centro| + radio): 4"
//
//  "➡️ Intervalo estimado de autovalores ≈ [0.5, 4]"
//
//  "⚠️ Al menos un círculo excede el disco unidad: revisar autovalores reales."
//
//  "ð Hay círculos solapados: los autovalores pueden estar agrupados o desplazados
//  "Centros:"
//
//  -2.
//   2.
//  -1.5
//   3.5
//
//  "Radios:"
//
//   1.
//   1.
//   1.
//   0.5
