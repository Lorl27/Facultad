function raices = resolverCuadratica(a, b, c)
    // Verifica si es realmente cuadrática
    if a == 0 then
        if b == 0 then
            if c == 0 then
                raices = "Infinitas soluciones";
            else
                raices = "Sin solución";
            end
        else
            raices = -c / b; // Lineal
        end
        return;
    end

    // Discriminante
    D = b^2 - 4*a*c;

    // Raíces según el discriminante
    if D > 0 then
        x1 = (-b + sqrt(D)) / (2*a);
        x2 = (-b - sqrt(D)) / (2*a);
        raices = [x1; x2]; // Reales distintas
    elseif D == 0 then
        x = -b / (2*a);
        raices = [x; x]; // Reales iguales
    else
        realPart = -b / (2*a);
        imagPart = sqrt(-D) / (2*a);
        x1 = complex(realPart, imagPart);
        x2 = complex(realPart, -imagPart);
        raices = [x1; x2]; // Complejas conjugadas
    end
endfunction
//--
a = -1; b = 23; c = -130;
r = resolverCuadratica(a, b, c);
disp(r);
