// Gráficos en 2d
function grafica_2D()
    x = [-2, -1.6, -1.2, -0.8, -0.4, 0, 0.4, 0.8, 1.2, 1.6, 2]
    y = [1.5, 0.99, 0.61, 0.27, 0.02, -0.0096, 0.065, 0.38, 0.63, 0.98, 1.5]
    
    p4_mod = poly([0, 0, 0.4475645, 0.0003142, -0.0188963], 'x', 'coeff') //Va de x^0 a x^n
    
    val_x = -2:0.01:2 // Va cada extremo del vector x
    val_y = horner(p4_mod, val_x)
    
    plot(x, y, 'b*'); // Los puntos son astericos azules
    plot(val_x, val_y, 'r-'); // El polinomio es una linea roja
    xlabel('x');
    ylabel('y');
    title('Aproximac`ón polinómica');
    legend('Puntos dados', 'Polinomio'); // El orden de las leyendas es de lo primero ploteado a lo último

endfunction



// Gráficos en 3d
function grafica_3D()
    // Datos
    x = [0; 0; 1; 1; 2; 2];
    v = [0; 1; 0; 1; 0; 2];
    y = [1.42; 1.85; 0.78; 0.18; 0.60; 1.05];
    
    // Coeficientes del modelo
    a = 1.4133;
    b = -0.6214;
    c = 0.4376;
    
    // Graficar los puntos en 3D
    plot3d1(x, v, y, flag=[1 2 3]); // Graficar los puntos
    set(gca(), "auto_clear", "off"); // Evita borrar al agregar el plano
    
    // Crear una rejilla para el plano ajustado
    [X, V] = meshgrid(0:0.1:2, 0:0.1:2);
    Z = a + b * X + c * V; // Evaluar el plano
    
    // Graficar el plano ajustado
    plot3d(X, V, Z);
endfunction


// .........................................................................
// ........................... MENÚ PRINCIPAL ..............................
// .........................................................................

while %t
    mprintf("\n==================================================================\n");
    mprintf("         GRAFICACION EN 2D Y 3D           \n");
    mprintf("==================================================================\n");
    mprintf("1. 2D\N");
    mprintf("2. 3D\n");
    mprintf("0. SALIR\n");
    mprintf("------------------------------------------------------------------\n");
    
    opcion = input("Elige una opción: ");
    
    select opcion
    case 1 then grafica_2D();
    case 2 then grafica_3D();
    case 0 then mprintf("\n¡Éxitos en el examen!\n"); break;
    else mprintf("\nOpción no válida.\n");
    end
end
