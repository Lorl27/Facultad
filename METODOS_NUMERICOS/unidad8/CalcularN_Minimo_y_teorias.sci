// ==========================================================
// CALCULADORA DE N (Para asegurar precisión)
// ==========================================================
// f: función a integrar
// a, b: límites
// tol: tolerancia deseada (ej: 10^-4)
// metodo: "trapecio" o "simpson"

function n_final = CalcularN_Minimo(f, a, b, tol, metodo)
    
    if metodo == "trapecio" then
        // 1. Hallar M2 = max |f''(x)|
        M2 = ObtenerCotaMaxima(f, a, b, 2); 
        
        // Fórmula Error Trapecio (Teorema 1 PDF): |E| <= ((b-a)^3 * M2) / (12 * n^2)
        // Despejando n: n >= sqrt( ((b-a)^3 * M2) / (12 * tol) )
        
        n_min = sqrt( ((b-a)^3 * M2) / (12 * tol) );
        n_final = ceil(n_min); // Redondear hacia arriba
        
        mprintf("Trapecio: M2=%.4f, n calculado=%.4f -> Usar n=%d\n", M2, n_min, n_final);
        
    elseif metodo == "simpson" then
        // 1. Hallar M4 = max |f''''(x)|
        M4 = ObtenerCotaMaxima(f, a, b, 4);
        
        // Fórmula Error Simpson (Teorema 2 PDF): |E| <= ((b-a)^5 * M4) / (180 * n^4)
        // Despejando n: n >= raiz4( ((b-a)^5 * M4) / (180 * tol) )
        
        numerador = (b - a)^5 * M4;
        denominador = 180 * tol;
        n_min = (numerador / denominador)^(0.25); // Raíz cuarta
        
        n_final = ceil(n_min);
        
        // Simpson OBLIGA a que n sea par
        if modulo(n_final, 2) <> 0 then
            n_final = n_final + 1;
        end
        
        mprintf("Simpson: M4=%.4f, n calculado=%.4f -> Usar n=%d (Par)\n", M4, n_min, n_final);
        
    else
        error("Método no reconocido. Use trapecio o simpson");
    end
endfunction


//-----------------
//Si te preguntan "¿Por qué Simpson dio exacto y Trapecio no?" o "Justifique el error", usa esto basado en tu PDF:
//
//Grado de Precisión:
//
//Trapecio: Es exacto para polinomios de grado 1 (rectas). Su error depende de f′′ (c).
// Si f(x) es una recta, f′′=0, error=0.
//
//Simpson: Es exacto para polinomios de grado 3. Su error depende de f^(4)(c).
//
//
//El Truco: Si integras f(x)=x^3 o f(x)=Ax^2+Bx+C, Simpson dará error cero (o casi cero por redondeo de máquina). Úsalo para justificar.
//
//Orden de Convergencia:
//
//Si duplicas n (haces los intervalos la mitad de pequeños):
//
//En Trapecio, el error se reduce aprox 4 veces (h^2 ).
//
//En Simpson, el error se reduce aprox 16 veces (h^4 ).
//
//Frase para el 10: "Simpson converge mucho más rápido hacia la solución real debido a su orden de error O(h ^4 )".
//
//3. La "Trampa" de la Derivada Infinita
//Ten cuidado con funciones como  raiz de x , o x^(1/3)   integradas desde 0.
//
//La derivada en 0 tiende a infinito.
//
//Tu función ObtenerCotaMaxima devolverá %inf o un número gigante.
//
//Respuesta de examen: "No se puede calcular una cota de error teórica a priori porque f ′(x) no está acotada en el intervalo, pero el método numérico igual arrojará una aproximación".
