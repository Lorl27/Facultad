//Ejercicio 2
//Usando aritm´etica de cuatro d´ıgitos de precisi´on (mantiza decimal de 4 d´ıgitos con redondeo),
//sume la siguiente expresi´on
//0, 9222 · 104 + 0, 9123 · 103 + 0, 3244 · 103 + 0,2849 · 103
//tanto ordenando los n´umeros de mayor a menor (en valor absoluto), como de menor a mayor.
//Realiza cada operaci´on de forma separada, primero igualando exponentes y luego normalizando
//el resultado en cada paso.
//¿Cu´al de las dos posibilidades es m´as exacta? Justifique los resultados que encuentre.

// Redondear a 4 dígitos de mantisa en notación científica
function [m, e] = normaliza_redondea(x)
    if x == 0 then
        m = 0; e = 0;
        return;
    end
    e = floor(log10(abs(x)));
    m = x / 10^e;
    // redondear mantisa a 4 cifras
    m = round(m * 1000) / 1000; // 3 decimales => 4 cifras en total
    // ajustar si mantisa salió 10.000
    if abs(m) >= 10 then
        m = m / 10;
        e = e + 1;
    end
endfunction

// Suma con redondeo a 4 cifras
function [res_m, res_e] = suma_redondeada(m1,e1,m2,e2)
    // igualar exponentes
    if e1 > e2 then
        m2 = m2 * 10^(e2-e1); e2 = e1;
    elseif e2 > e1 then
        m1 = m1 * 10^(e1-e2); e1 = e2;
    end
    // suma mantisas
    s = (m1+m2) * 10^e1;
    [res_m,res_e] = normaliza_redondea(s);
endfunction

// Valores iniciales
m1=0.9222; e1=4;
m2=0.9123; e2=3;
m3=0.3244; e3=3;
m4=0.2849; e4=3;

// ORDEN DESCENDENTE
disp("Orden descendente:");
[m12,e12] = suma_redondeada(m1,e1,m2,e2);
[m123,e123] = suma_redondeada(m12,e12,m3,e3);
[m1234,e1234] = suma_redondeada(m123,e123,m4,e4);
valor_desc = m1234*10^e1234;
disp(valor_desc, "Resultado descendente:");

// ORDEN ASCENDENTE
disp("Orden ascendente:");
[m34,e34] = suma_redondeada(m4,e4,m3,e3);
[m234,e234] = suma_redondeada(m34,e34,m2,e2);
[m1234b,e1234b] = suma_redondeada(m234,e234,m1,e1);
valor_asc = m1234b*10^e1234b;
disp(valor_asc, "Resultado ascendente:");

// Valor exacto
exacto = 9222 + 912.3 + 324.4 + 284.9;
disp(exacto, "Suma exacta:");
disp(exacto-valor_desc, "Error descendente:");
disp(exacto-valor_asc, "Error ascendente:");


//truncamienot:
// Normaliza y trunca mantisa a 4 cifras
function [m, e] = normaliza_trunca(x)
    if x == 0 then
        m = 0; e = 0;
        return;
    end
    e = floor(log10(abs(x)));
    m = x / 10^e;
    // truncar en lugar de redondear
    m = floor(m*1000)/1000;  // corta en 4 cifras
    if abs(m) >= 10 then
        m = m / 10;
        e = e + 1;
    end
endfunction

// Suma con truncamiento a 4 cifras
function [res_m, res_e] = suma_truncada(m1,e1,m2,e2)
    if e1 > e2 then
        m2 = m2 * 10^(e2-e1); e2 = e1;
    elseif e2 > e1 then
        m1 = m1 * 10^(e1-e2); e1 = e2;
    end
    s = (m1+m2) * 10^e1;
    [res_m,res_e] = normaliza_trunca(s);
endfunction

// Usás suma_truncada en vez de suma_redondeada

