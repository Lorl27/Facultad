// Polinomio de Taylor de grado 10 de e^x
function t = taylor_expo_10(x)
    t = 0;
    for k=0:10
        t = t + x^k / factorial(k);
    end
endfunction

// Aproximación
x = -2;
aprox = taylor_expo_10(x);
disp(aprox, "Taylor grado 10 e^(-2)");

// Redondear a 3 dígitos
aprox3 = round(aprox*1000)/1000;
disp(aprox3, "Redondeo a 3 dígitos");

// -----------------------------
// Aproximación de e^(-2) usando Taylor grado 10
// Redondeo a 3 dígitos significativos
// -----------------------------

//clear;
//clc;

// Función para redondear a n dígitos significativos
function y = rd(x, n)
    if x == 0 then
        y = 0;
    else
        e = floor(log10(abs(x)));
        y = round(x * 10^(n-1-e)) / 10^(n-1-e);
    end
endfunction

// Parámetros
x = -2;
n = 10;
dig = 3; // dígitos significativos
sumatoria = 0;

//disp("Término_Termino redondeado_Suma acumulada");

for k = 0:n
    term = x^k / factorial(k);
    term_rd = rd(term, dig);             // redondeo del término
    sumatoria = rd(sumatoria + term_rd, dig); // redondeo de la suma acumulada
    //disp(k + " " + string(term_rd) + " " + string(sumatoria));
end

disp(sumatoria, "Aproximación final T10(-2) con 3 dígitos");
disp(0.135, "Valor exacto 3 dígitos");
