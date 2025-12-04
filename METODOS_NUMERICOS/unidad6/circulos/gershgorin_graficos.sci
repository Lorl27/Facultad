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
A = [4 1 -1; 2 3 0; 0 1 2];
[centros, radios, rho_cota,rho_min, solapados] = gershgorin_info_plot(A, %t);
disp("Centros:");
disp(centros);
disp("Radios:");
disp(radios);
///======== EJERCICIO 1. P6:
//(a) Usar el teorema de Gerschgorin para determinar cotas de los autovalores de las siguientes matrices:
//a)
//{
//1 0 0
//−1 0 1
//−1 −1 2
//}
//b)
//{
//1 0 0
//−0.1 0 0.1
//−0.1 −0.1 2
//}
// c)
//{
//1 0 0
//−0.25 0 0.25
//−0.25 −0.25 2
//}
//d)
//{
//4 −1 0
//−1 4 −1
//−1 −1 4
//}
// e)
//{
//3 2 1
//2 3 0
//1 0 3
//}
// f)
//{
//4.75 2.25 −0.25
//2.25 4.75 1.25
//−0.25 1.25 4.75
//}

A=[1 0 0;
-1 0 1;
-1 -1 2]

B=[1 0 0;
-0.1 0 0.1;
-0.1 -0.1 2]

C=[1 0 0;
-0.25 0 0.25;
-0.25 -0.25 2]

D=[4 -1 0;
-1 4 1;
-1 -1 4]

E=[3 2 1;
2 3 0;
1 0 3]

F=[4.75 2.25 -0.25;
2.25 4.75 1.25;
-0.25 1.25 4.75]

[centros, radios, rho_cota,rho_min, solapados] = gershgorin_info_plot(A, %t);
[centros, radios, rho_cota,rho_min, solapados] = gershgorin_info_plot(B, %t);
[centros, radios, rho_cota,rho_min, solapados] = gershgorin_info_plot(C, %t);
[centros, radios, rho_cota,rho_min, solapados] = gershgorin_info_plot(D, %t);
[centros, radios, rho_cota,rho_min, solapados] = gershgorin_info_plot(E, %t);
[centros, radios, rho_cota,rho_min, solapados] = gershgorin_info_plot(F, %t);


/////============= PARICAL 2024:
//3. consider ela matriz A= (10 1 1 ; 1 4 2 ; 1 2 1)
// a. grafique en scilab los criculos d egerhsogirn de A 
//b. explique porque el item anterior peude afirmar que A tiene un autovalor domiannte 
//c. aplique el metodo de la potencia a la matriz A para aproximar el autovalor dominante de A con una tolerancia de 10^-5 para los sig vectoress inciales:
// 1. z^(0)=[1,1,1]^t
//  2. z^(0)=[-0,462,-4,357,8,989]^t
//   3. z^(0)=[0,100,1000]^t
//    cuente la canitdad d eiteracions realizadas para cada vector inicial.

//A:
A = [10 1 1; 1 4 2; 1 2 1];
[centros, radios, rho_cota,rho_min, solapados] = gershgorin_info_plot(A, %t);

//B:
//Observaciones por Gershgorin:
//El disco 1 (con centro 10 y radio 2) corresponde al intervalo real [8,12].
//Los otros dos discos están contenidos en el intervalo real [−2,7].
//
//Por el teorema de Gershgorin, cada autovalor se encuentra en la unión de esos discos. Además, el disco 1 está separado (no intersecta los otros dos), porque[8,12] no intersecta [−2,7]. Cuando un disco está aislado, Gershgorin garantiza que exactamente un autovalor (contando multiplicidad) queda dentro de ese disco.
//
//Como ese autovalor está en [8,12] y los restantes están en [−2,7], su módulo es mayor que el de los demás (al menos ∣𝜆1∣≥8 y los otros ∣λi∣≤7). Por tanto existe un único autovalor con mayor módulo: un autovalor dominante real y simple. Eso explica por qué el método de la potencia tiene buen sentido aquí y converge a ese autovalor único.


//C otro lado

//D.
////Autovalor dominante (aprox.) — valor obtenido por el método (coincide con spec):λdom≈10.3554216
////
////Resultados por vector inicial (tolerancia 10^−5):
////
////Para z^(0)=[1,1,1]T
////
////autovalor aproximado: λ≈10.35542880
////
////autovector (normalizado por norma ∞): [1, 0.2047606, 0.1506642]T
////iteraciones realizadas: 16.
////
////Para z^(0)=[−0.462,−4.357, 8.989]T
////
////autovalor aproximado: λ≈10.35541495
////
////autovector (normalizado ∞): [1, 0.2047564, 0.1506621]T
////iteraciones realizadas: 18.
////
////Para z^(0)=[0.1, 100, 1000]T
////autovalor aproximado: λ≈10.35542711
////
////autovector (normalizado ∞): [1, 0.2047601, 0.1506639]T
////iteraciones realizadas: 18.
////
////Observaciones:
////Todas las inicializaciones convergen al mismo autovalor dominante real y al mismo autovector (salvo escala/signo), como corresponde.
////
////El número de iteraciones varía ligeramente con el vector inicial: aquí el vector equilibrado [1,1,1] converge algo más rápido (16 vs 18). Vectores con componente dominante en una dirección poco alineada con el autovector dominante tardan más en “descomponerse” en la dirección dominante.
