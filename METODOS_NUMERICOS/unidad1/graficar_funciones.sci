//GRAFICA DE FUNCIONES:

function graficar_cuadratica(a, b, c)
    // Grafica f(x) = a*x^2 + b*x + c
    x = -10:0.1:10; // Rango del eje x
    y = a*x.^2 + b*x + c;
    clf(); // Limpia la ventana de gráficos
    plot(x, y, 'b');
    xtitle("f(x) = " + string(a) + "*x^2 + " + string(b) + "*x + " + string(c), "x", "f(x)");
    xgrid();
endfunction

// 🔹 Ejemplo de uso:
graficar_cuadratica(1, -3, 2);  // f(x) = x^2 - 3x + 2

function graficar_potencia(n, a, b, c)
    // Grafica f(x) = a*x^n + b*x + c
    x = -10:0.1:10;
    y = a*x.^n + b*x + c;
    clf();
    plot(x, y, 'r');
    xtitle("f(x) = " + string(a) + "*x^" + string(n) + " + " + string(b) + "*x + " + string(c), "x", "f(x)");
    xgrid();
endfunction

// 🔹 Ejemplo:
graficar_potencia(3, 1, 0, 0); // f(x) = x^3

function graficar_trigonometrica(tipo)
    // tipo puede ser: "sin", "cos" o "tan"
    x = -%pi:0.01:%pi;
    select tipo
        case "sin" then
            y = sin(x);
            color = 2; // verde
            titulo = "f(x) = sin(x)";
        case "cos" then
            y = cos(x);
            color = 5; // magenta
            titulo = "f(x) = cos(x)";
        case "tan" then
            y = tan(x);
            // Eliminar valores extremos para evitar saltos
            y(abs(y) > 10) = %nan;
            color = 12; // rojo
            titulo = "f(x) = tan(x)";
        else
            error("Tipo de función no válido. Usa sin, cos o tan.");
    end
    clf();
    plot2d(x, y, style=color);
    xtitle(titulo, "x", "f(x)");
    xgrid();
endfunction

// 🔹 Ejemplos:
graficar_trigonometrica("sin");
graficar_trigonometrica('tan');

function graficar_exponencial(a, b)
    // Grafica f(x) = a*exp(b*x)
    x = -5:0.1:5;
    y = a*exp(b*x);
    clf();
    plot(x, y, 'b');
    xtitle("f(x) = " + string(a) + "*e^(" + string(b) + "*x)", "x", "f(x)");
    xgrid();
endfunction

// 🔹 Ejemplo:
graficar_exponencial(1, 1);  // f(x) = e^x


function graficar_logaritmica(a, b)
    // Grafica f(x) = a*log(b*x)
    x = 0.1:0.1:10; // empieza en 0.1 para evitar log(0)
    y = a*log(b*x);
    clf();
    plot(x, y, 'k');
    xtitle("f(x) = " + string(a) + "*log(" + string(b) + "*x)", "x", "f(x)");
    xgrid();
endfunction

// 🔹 Ejemplo:
graficar_logaritmica(1, 1); // f(x) = log(x)


function graficar_personal(f)
    // f debe ser una función anónima, por ejemplo: f = @(x) x.^2 + 3*x - 1
    x = -10:0.1:10;
    y = f(x);
    clf();
    plot2d(x, y, style=3); // estilo 3 = cian
    xtitle("Gráfico personalizado", "x", "f(x)");
    xgrid();
endfunction

// 🔹 Ejemplo:
// Definir la función anónima
deff('y = f(x)', 'y = sin(x) + x.^2');

// Llamar a la función de graficado
graficar_personal(f);

function y = g(x)
    y = sin(x) + x.^2;
endfunction

graficar_personal(g);

deff('y=r(x)','y=cos(x).*cosh(x)+1');
graficar_personal(r);


//--------------------------

function graficar_funcion(f, xmin, xmax)
    // ----------------------------------------------------------
    // f : función anónima (por ejemplo @(x) cos(x)*cosh(x) + 1)
    // xmin, xmax : límites del eje X
    // ----------------------------------------------------------

    // Crear eje X
    x = linspace(xmin, xmax, 1000);
    y = f(x);

    // Limpiar gráfico
    clf();

    // Graficar función
    plot(x, y, 'b', 'LineWidth', 2);


    // Dibujar ejes X e Y
    xgrid();
    a = gca();
    a.x_location = "origin";
    a.y_location = "origin";
    a.box = "off";
    a.foreground = color("gray70");

    // Calcular y marcar posibles raíces (puntos donde f(x) cambia de signo)
    raiz_x = [];
    for i = 1:length(x)-1
        if y(i)*y(i+1) < 0 then
            // Hay cambio de signo → posible raíz
            xr = (x(i)+x(i+1))/2;
            raiz_x($+1) = xr;
        end
    end

    // Mostrar puntos aproximados
    if length(raiz_x) > 0 then
        for i = 1:length(raiz_x)
            scatter(raiz_x(i), 0, 50, color("red"), "fill");
        end
        mprintf("\nRaíces aproximadas encontradas:\n");
        disp(raiz_x);
    else
        mprintf("\nNo se encontraron raíces en el intervalo dado.\n");
    end

    // Título automático
    xtitle("Gráfico de la función y aproximación de raíces", "x", "f(x)");
endfunction

deff('y=s(x)','y=cos(x).*cosh(x)+1');
graficar_funcion(s, -10, 10);

deff('y=m(x)','y=(exp(x) - x)/( 2)');
graficar_funcion(m, -1, 1);


//---------

function graficar_texto(expr, xmin, xmax)
    // ---------------------------------------------------------
    // expr  : cadena con la función (por ejemplo: "exp(-x)+(x^2)/4")
    // xmin, xmax : límites del eje x
    // ---------------------------------------------------------
    // ejemplo de uso: graficar_texto("cos(x)*cosh(x)+1", -10, 10)
    // ---------------------------------------------------------

    // Convertir la cadena en una función evaluable f(x)
    deff("y=f(x)", "y=" + expr);

    // Crear eje x y calcular f(x)
    x = linspace(xmin, xmax, 2000);
    y = f(x);

    // Limpiar ventana de gráficos
    clf();

    // Graficar la función
    plot(x, y, 'b', 'LineWidth', 2);

    // Rejilla y ejes en el origen
    xgrid();
    a = gca();
    a.x_location = "origin";
    a.y_location = "origin";
    a.box = "off";
    a.foreground = color("gray70");

    // Buscar raíces aproximadas (cambio de signo)
    raiz_x = [];
    for i = 1:length(x)-1
        if y(i)*y(i+1) < 0 then
            xr = (x(i)+x(i+1))/2;
            raiz_x($+1) = xr;
        end
    end

    // Mostrar raíces aproximadas
    if length(raiz_x) > 0 then
        for i = 1:length(raiz_x)
            scatter(raiz_x(i), 0, 50, color("red"), "fill");
        end
        mprintf("\nRaíces aproximadas encontradas:\n");
        disp(raiz_x);
    else
        mprintf("\nNo se encontraron raíces en el intervalo dado.\n");
    end

    // Título automático
    xtitle("f(x) = " + expr, "x", "f(x)");

    // Ajuste automático del zoom vertical
    replot([xmin xmax min(y) max(y)]);
endfunction


// Ejemplo 1: la del texto que dijiste
graficar_texto("exp(-x) + (x.^2)/4", -5, 5);

// Ejemplo 2: trigonométrica compuesta
graficar_texto("cos(x).*cosh(x)+1", -10, 10);

// Ejemplo 3: polinómica
graficar_texto("x.^3 - 4.*x + 1", -4, 4);

// Ejemplo 4: racional
graficar_texto("(x.^2-4)/(x-2)", -5, 5); //DISCONTINUEDAD EN X=2!

graficar_texto("(exp(x) - x)/( 2)", -10, 10);



//---
function graficar_texto_dis(expr, xmin, xmax)
    // Vectorizar operadores
    expr_v = strsubst(expr, "^", ".^");
    expr_v = strsubst(expr_v, "*", ".*");
    expr_v = strsubst(expr_v, "/", "./");

    // Crear función f(x)
    deff('y = f(x)', 'y = ' + expr_v);

    // Dominio
    x = xmin:0.01:xmax;

    // Evaluar
    try
        y = f(x);
        // Filtrar valores extremos
        y(~isreal(y) | abs(y) > 1e6) = %nan;
    catch
        error("La expresión no se pudo evaluar correctamente.");
    end

    // Detectar discontinuidades por división por cero
    discontinuidades = [];
    for i = 2:length(x)
        if isnan(y(i)) & ~isnan(y(i-1)) & ~isnan(y(i+1)) then
            discontinuidades($+1) = x(i);
        end
    end

    // Graficar función
    clf();
    plot2d(x, y, style=2); // azul
    xtitle("f(x) = " + expr, "x", "f(x)");
    xgrid();

    // Marcar discontinuidades
    for i = 1:length(discontinuidades)
        x0 = discontinuidades(i);
        y0 = f(x0 - 0.001); // valor límite izquierdo
        plot2d(x0, y0, style=-9); // círculo abierto
    end
endfunction

graficar_texto_dis("(x^2 - 4)/(x - 2)", -5, 5);


//--------
function graficar_texto_dis_lim(expr, xmin, xmax)
    // Vectorizar operadores
    expr_v = strsubst(expr, "^", ".^");
    expr_v = strsubst(expr_v, "*", ".*");
    expr_v = strsubst(expr_v, "/", "./");

    // Crear función f(x)
    deff('y = f(x)', 'y = ' + expr_v);

    // Dominio
    x = xmin:0.01:xmax;

    // Evaluar
    try
        y = f(x);
        y(~isreal(y) | abs(y) > 1e6) = %nan;
    catch
        error("La expresión no se pudo evaluar correctamente.");
    end

    // Detectar discontinuidades
    discontinuidades = [];
    for i = 2:length(x)-1
        if isnan(y(i)) & ~isnan(y(i-1)) & ~isnan(y(i+1)) then
            discontinuidades($+1) = x(i);
        end
    end

    // Graficar función
    clf();
    plot2d(x, y, style=2); // azul
    xtitle("f(x) = " + expr, "x", "f(x)");
    xgrid();

    // Marcar discontinuidades y mostrar texto
    for i = 1:length(discontinuidades)
        x0 = discontinuidades(i);
        y0 = f(x0 - 0.001); // valor límite izquierdo
        plot2d(x0, y0, style=-9); // círculo abierto

        // Mostrar texto cerca del punto
        xstring(x0 + 0.2, y0, "Límite en x=" + string(x0) + ": " + string(y0));
    end
endfunction

graficar_texto_dis_lim("(x^2 - 4)/(x - 2)", -5, 5);


graficar_texto_dis_lim("(x^2 - 4)/(x - 2)", -5, 5);

graficar_texto_dis_lim("(exp(x) - x)/( 2)", -10, 10);


//---------
function graficar_texto_analisis(expr, xmin, xmax)
    // ===========================================================
    // Gráfica f(x) con detección de raíces, extremos y discontinuidades
    // expr: cadena de texto (por ejemplo "cos(x)*cosh(x)+1")
    // ===========================================================

    // --- Vectorizar operadores ---
    expr_v = strsubst(expr, "^", ".^");
    expr_v = strsubst(expr_v, "*", ".*");
    expr_v = strsubst(expr_v, "/", "./");

    // --- Crear función f(x) ---
    deff('y = f(x)', 'y = ' + expr_v);

    // --- Dominio ---
    x = xmin:0.01:xmax;
    n = length(x);

    // --- Evaluar f(x) ---
    try
        y = f(x);
        // Reemplazar valores complejos o muy grandes por NaN
        y(~isreal(y) | abs(y) > 1e6) = %nan;
    catch
        error("La expresión no se pudo evaluar correctamente.");
    end

    // --- Derivada numérica central ---
    dy = zeros(y);
    for i = 2:n-1
        dy(i) = (y(i+1) - y(i-1)) / (x(i+1) - x(i-1));
    end

    // --- Detectar raíces ---
    tolerancia = 1e-3;
    idx_zeros = find(abs(y) < tolerancia);

    // --- Detectar extremos locales ---
    idx_extremos = [];
    for i = 2:n-1
        if dy(i-1) * dy(i+1) < 0 & ~isnan(y(i)) then
            idx_extremos($+1) = i;
        end
    end

    // --- Detectar discontinuidades removibles ---
    idx_disc = []; // inicializar SIEMPRE
    for i = 2:n-1
        if isnan(y(i)) & ~isnan(y(i-1)) & ~isnan(y(i+1)) then
            idx_disc($+1) = i;
        end
    end

    // --- Graficar función ---
    clf();
    plot2d(x, y, style=2);
    xtitle("f(x) = " + expr, "x", "f(x)");
    xgrid();

    // --- Marcar raíces ---
    if ~isempty(idx_zeros) then
        for j = 1:length(idx_zeros)
            i = idx_zeros(j);
            plot2d(x(i), y(i), style=4);
            xstring(x(i)+0.2, y(i), "Raíz");
        end
    end

    // --- Marcar extremos ---
    if ~isempty(idx_extremos) then
        for j = 1:length(idx_extremos)
            i = idx_extremos(j);
            if dy(i-1) > 0 then
                tipo = "Mínimo";
            else
                tipo = "Máximo";
            end
            plot2d(x(i), y(i), style=5);
            xstring(x(i)+0.2, y(i), tipo);
        end
    end

    // --- Marcar discontinuidades ---
    if ~isempty(idx_disc) then
        for j = 1:length(idx_disc)
            i = idx_disc(j);
            x0 = x(i);
            y0 = f(x0 - 0.001);
            plot2d(x0, y0, style=-9);
            xstring(x0+0.2, y0, "Discontinuidad");
        end
    end
endfunction


graficar_texto_analisis("(x^2 - 4)/(x - 2)", -5, 5);
graficar_texto_analisis("x^3 - 4*x + 1", -4, 4);
graficar_texto_analisis("cos(x)*cosh(x)+1", -10, 10);
