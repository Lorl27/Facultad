// ANTONELLA GRASSI
// PRACTICA 7 - INTERPOLACIÒN POLINOMIAL Y AJUSTE DE CURVAS

//============= FUNCIONES AUXILIARES
//funcprot(0);

//1. Método de Eliminación Gaussiana con pivoteo parcial
function [x,a] = gausselimPP(A,b)
[nA,mA] = size(A);
[nb,mb] = size(b);
a = [A b];
n = nA;

for k=1:n-1
    kpivot = k; amax = abs(a(k,k));
    for i=k+1:n
        if abs(a(i,k))>amax then
            kpivot = i; amax = a(i,k);
        end
    end
    temp = a(kpivot,:); a(kpivot,:) = a(k,:);
    a(k,:) = temp;
    
    for i=k+1:n
        for j=k+1:n+1
            a(i,j) = a(i,j) - a(k,j)*a(i,k)/a(k,k);
        end
        for j=1:k
            a(i,j) = 0;
        end
    end
end

x(n) = a(n,n+1)/a(n,n);

for i = n-1:-1:1
    sumk = 0;
    for k=i+1:n
        sumk = sumk + a(i,k)*x(k);
    end
    x(i) = (a(i,n+1)-sumk)/a(i,i);
end
endfunction


//2. Constructor de Matriz de Vandermonde A
// Crea columnas [1, x, x^2, ... x^n]
// n: grado del polinomio: p=[1,...,x^(grado)]
function A = ConstruirVandermonde(x, n)
    m = length(x);
    A = ones(m, 1);
    for j = 1:n
        A = [A, (x').^j];
    end
endfunction


// 3. Aproximación polinomial de mínimos cuadrados para matrices con rango completo
function [p, err, coefs]=MinCuad_poly(x, y, grado)
    // Construir sistema A
    A = ConstruirVandermonde(x, grado);
    b = y'; // Transpuesta para que sea vector columna
    
    // Resolver Sistema Normal: (A' * A) * x = (A' * b)
    MatrizNormal = A' * A;
    VectorIndep  = A' * b;
    
    [coefs, dump] = gausselimPP(MatrizNormal, VectorIndep);
    
    // Crear objeto polinomio
    p = poly(coefs, "x", "coeff");
    
    // Calcular Error (Norma 2 del residuo)
    y_aprox = horner(p, x);
    

    err = norm(y - y_aprox); 
endfunction

/// ============================ RESOLUCIÒN EJERCICIO =====
x_datos=[0.0,1.0,1.5,2.0,2.5,3.0,3.5,4.5];
y_datos=[0.0,2.3,3.0,3.4,3.2,2.7,2.0,0.0];

//objetivo: modelar la silueta de una "parabola suave" probando polinomios de pn(x) de distinto grados mediante MINIMOS CUADRADOS

//altura 0 en a=0 y b=4.5 , tenemos que usar uno que garantice las raices en x=0 y x=4.5
// pn(x)= x(x-4.5)*q(x) tal que q(x) polinomio de grado n-2 , obtenido por MINIMOS CUADRADOS

// a - Utilizar minimos cuadrados para encontrar los polinomios de grado n=4 y n=6 que mejor se ajusten a los datos y, que pasen por los puntos extremos

mprintf("\nitem a:\n")

grados = [4, 6];
errores = [];
polinomios = list();

xx = linspace(min(x_datos), max(x_datos), 200);
scf(0); clf();
plot(x_datos, y_datos, "ko", "MarkerSize", 4);  
colores = ["b-", "m--"]; // azul y magnenta(Irosa)

for i=1:2
        g = grados(i);
        [p, err,coefs] = MinCuad_poly(x_datos, y_datos, g);
        errores(i) = err;
        polinomios(i) = p;
        mprintf("\nGrado %d: Error = %.5f\nPolinomio: ", g, err); disp(p);
        plot(xx, horner(p, xx), colores(i));
end

    
// b - ¿Còmo se define la matriz A del problema de minimos cuadrados en cada caso?
mprintf("\n--- item b. Definiciòn de Matrices de diseño A : ---\n");

mprintf(" A1 (grado 4) =\n");
mprintf("[ 1  x1  x1^2 x1^3 x1^4  ]\n");
mprintf("[ 1  x2  x2^2 x2^3 x2^4  ]\n");
mprintf("[  .   .    .        .   ]\n");
mprintf("[ 1 x8 x8^2 x8^3 x8^4  ]\n\n");

mprintf(" A2 (grado 6) =\n");
mprintf("[ 1  x1  x1^2 x1^3 x1^4 x1^5 x1^6 ]\n");
mprintf("[ 1  x2  x2^2 x2^3 x2^4 x2^5 x2^6 ]\n");
mprintf("[  .   .    .        .    ... ...]\n");
mprintf("[ 1 x8 x8^2 x8^3 x8^4 x8^5 x8^6 ]\n\n");

mprintf("--- Aproximaciòn de Matrices de diseño A : ---\n\n");
x_rango=1:8; //rango de datos

for i = 1:length(grados)
    n = grados(i);
    A = ConstruirVandermonde(x_rango, n);
    mprintf("\nMatriz A%d:\n",i);
    disp(A);
end


// c - en una sola grafica , represente los puntos experimentales y los polinomios ajustados en el intervalo [0,4.5]

legend(["Datos"; "Grado 4"; "Grado 6"]);
title("grafica utilizando polinomios de grado 4 y grado 6, ajustado al intervalo [0,4.5]");


//d - observando la gràfica anterior , ¿Cuàl modelo eligirìa usted para fabricar la pieza y por què? 

mprintf("\n--- item d. MODELO ELEGIDO: ---\n");  

mprintf(" Para fabricar la pieza elegiria el modelo de grado 4.\n A pesar de tener un mayor error ya que se distancia de algunos puntos (especialmente en la captura adjuntada),\n vemos que visualmente sigue la tendencia de ser una paràbola suave ,\n mientras que el polinomio de grado 6 en los extermos presenta cierta curvatura que podrìa provocar una mala mediciòn en esos puntos (x,y) ")


disp("Podemos comprobarlo con el que tiene menor error es el polinomio de grado 6, utilizando scilab:")
[min_e, idx] = min(errores);
mprintf("\n>> MEJOR AJUSTE MATEMÁTICO: Grado %d (Menor error: %.5f)\n", grados(idx), min_e);

disp("Sin embargo, una tendencia parabolica parece màs apropiado para fabricar una estructura sin importar que tenga un error mayor")

valor_error=abs(errores(2)-errores(1));
mprintf("La diferencia entre errores es %.5f:\n",valor_error);
mprintf("Si se tendria fija una tolerancia maxima de error permitida,\n podrìamos utilizar el grado 6 que ajusta mejor, \npero al ser una diferencia relativamente reducida : eligiria el del grado 4.")
// ============ RESULTADOS OBTENIDOS ==============
//item a:
//
//Grado 4: Error = 0.10048
//Polinomio: 
//  -0.0027881 +2.6752057x -0.1572391x² -0.234717x³ +0.0305849x⁴
//
//Grado 6: Error = 0.04673
//Polinomio: 
//  0.0001517 +3.8611709x -3.3553964x² +2.8945204x³ -1.3744384x⁴ +0.2927543x⁵ 
//   -0.0228571x⁶
//
//--- item b. Definiciòn de Matrices de diseño A : ---
// A1 (grado 4) =
//[ 1  x1  x1^2 x1^3 x1^4  ]
//[ 1  x2  x2^2 x2^3 x2^4  ]
//[  .   .    .        .   ]
//[ 1 x8 x8^2 x8^3 x8^4  ]
//
// A2 (grado 6) =
//[ 1  x1  x1^2 x1^3 x1^4 x1^5 x1^6 ]
//[ 1  x2  x2^2 x2^3 x2^4 x2^5 x2^6 ]
//[  .   .    .        .    ... ...]
//[ 1 x8 x8^2 x8^3 x8^4 x8^5 x8^6 ]
//
//--- Aproximaciòn de Matrices de diseño A : ---
//
//
//Matriz A1:
//
//   1.   1.   1.    1.     1.   
//   1.   2.   4.    8.     16.  
//   1.   3.   9.    27.    81.  
//   1.   4.   16.   64.    256. 
//   1.   5.   25.   125.   625. 
//   1.   6.   36.   216.   1296.
//   1.   7.   49.   343.   2401.
//   1.   8.   64.   512.   4096.
//
//Matriz A2:
//
//   1.   1.   1.    1.     1.      1.       1.     
//   1.   2.   4.    8.     16.     32.      64.    
//   1.   3.   9.    27.    81.     243.     729.   
//   1.   4.   16.   64.    256.    1024.    4096.  
//   1.   5.   25.   125.   625.    3125.    15625. 
//   1.   6.   36.   216.   1296.   7776.    46656. 
//   1.   7.   49.   343.   2401.   16807.   117649.
//   1.   8.   64.   512.   4096.   32768.   262144.
//
//--- item d. MODELO ELEGIDO: ---
// Para fabricar la pieza elegiria el modelo de grado 4.
// A pesar de tener un mayor error ya que se distancia de algunos puntos (especialmente en la captura adjuntada),
// vemos que visualmente sigue la tendencia de ser una paràbola suave ,
// mientras que el polinomio de grado 6 en los extermos presenta cierta curvatura que podrìa provocar una mala mediciòn en esos puntos (x,y) 
//  "Podemos comprobarlo con el que tiene menor error es el polinomio de grado 6, utilizando scilab:"
//
//>> MEJOR AJUSTE MATEMÁTICO: Grado 6 (Menor error: 0.04673)
//
//  "Sin embargo, una tendencia parabolica parece màs apropiado para fabricar una estructura sin importar que tenga un error mayor"
//La diferencia entre errores es 0.05375:
//Si se tendria fija una tolerancia maxima de error permitida,
// podrìamos utilizar el grado 6 que ajusta mejor, 
//pero al ser una diferencia relativamente reducida : eligiria el del grado 4.
