// Ejercicio 3. Utilizando la definición de la estructura Point resuelva:

#include <math.h>
#include <stdio.h>
#include <assert.h>

struct point {
    double x;
    double y;
};

typedef struct point Point;

// 1. Definir la función POINTdist() que calcula la distancia Euclidiana entre dos puntos dados.
/*  DISEÑO DE DATOS:

    distancia: double

    Signatura:
    POINTdis Point Point -> double

    Próposito: Calcular la distancia Euclidiana entre dos puntos,
    ésta está bajo la fórmula: d = √((x2 - x1)² + (y2 - y1)²)

    EJEMPLOS:
        POINTdis({.25,.75},{.7,.90})==0.474342
        POINTdis({2,75},{7,.9})==74.2685
*/
double POINTdis(Point point1, Point point2){
    double distancia= sqrt(pow((point2.x - point1.x),2)+pow((point2.y - point1.y),2));
    return distancia;
}

void test_POINTdis(void){
    Point p1={.25,.75};
    Point p2={.7,.90};
    Point p3={2,75};
    Point p4={7,.9};
    assert(fabs(POINTdis(p1, p2) - 0.474342) < 0.000001);
    assert(fabs(POINTdis(p3, p4) - 74.2685) < 0.0001);
}

// 2. Definir la función POINTeq() la cual retorna 1 si dos puntos son iguales; y 0 en caso contrario.
// Recordar que entre números flotantes (reales) no tienen mucho sentido chequear exactitud, pero si
// podemos verificar que la diferencia en valor absoluto sea menor a 0,000001.

/*  DISEÑO DE DATOS:

    Signatura: 
    POINTeq: Point Point -> int

    Próposito: Se fija si 2 Points son iguales, en cuyo caso devuelve 1.
    Sino, devuelve 0.

    EJEMPLOS:
        POINTeq({.25,.75},{.7,.90})==0;
        POINTeq({0.5, 0.5}, {0.5, 0.5}) == 1;

*/

int POINTeq(Point p1, Point p2){
    return (fabs(p1.x - p2.x)<0.000001 && fabs(p1.y - p2.y)<0.000001);
    // 1 -> Iguales; 0-> No lo son.
}

void test_POINTeq(void){
    Point p1 = {0.25, 0.75};
    Point p2 = {0.7, 0.90};
    Point p3 = {0.5, 0.5};
    Point p4 = {0.5, 0.5};

    assert(POINTeq(p1,p2)==0); //NO son ==
    assert(POINTeq(p3,p4)==1); //Sí son ==
}

// 3. Definir el tipo Rectangulo para aquellos rectángulos paralelos a los ejes en un sistema de coordenas
// cartesianas. Representar a una rectángulo por sus vértices izquierdo inferior y derecho superior.
// Usar para estos últimos puntos, la estructura point definida anteriormente.

typedef struct rect{
    Point vertice_izq_inf;
    Point vertice_der_sup;
} Rectangulo;


// 4. Definir la función RECTarea() la cual calcula el área de un rectángulo.

/* DISEÑO DE DATOS:
    area: double
    base: double
    altura=double

    Signatura:
    RECTarea: Rectangulo -> double

    Próposito: Calcular el área de un rectángulo (FÓRMULA: BASE X ALTURA)

    EJEMPLOS:
        RRECTarea({{0, 0}, {1, 1}}) == 1.0;
        RECTarea({{2, 3}, {5, 7}}) == 12.0;
*/
double RECTarea(Rectangulo r){
    double base=r.vertice_der_sup.x - r.vertice_izq_inf.x;
    double altura=r.vertice_der_sup.y - r.vertice_izq_inf.y;
    double area =  base*altura;
    return area;
}

void test_RECTarea(void){
    Rectangulo r1 = {{0, 0}, {1, 1}};
    Rectangulo r2 = {{2, 3}, {5, 7}};

    assert(RECTarea(r1)==1.0);
    assert(RECTarea(r2) ==12.0);
}



// 5. Definir la función RECTin() la cual retorna 1 si un punto se encuentra dentro del rectangulo, y 0
// si esta a fuera. Utilizar los tipos Point y Rectangulo definidos anteriormente.

/* DISEÑO DE DATOS:

    Signatura:
    RECTint: Rectangulo Point -> int

    Próposito: Devuelve 1 si el Punto se encuentra en el rectángulo y, 0 en caso contrario.

    EJEMPLOS:
        RECTint({{0, 0}, {1, 1}},{0,1})==1;
        RECTint({{0, 0}, {1, 1}},{4,5})==0;

 */


int RECTint(Rectangulo r, Point p){
    return (p.x>=r.vertice_izq_inf.x && p.x<=r.vertice_der_sup.x && p.y>=r.vertice_izq_inf.y && p.y<=r.vertice_der_sup.y);
}

void test_RECTint(void){
    Rectangulo r = {{0, 0}, {1, 1}};
    Point p1 = {0, 1};
    Point p2={4,5};

    assert(RECTint(r,p1)==1);
    assert(RECTint(r,p2)==0);
}

//-----------------------

int main(void){
    //TESTS:
    test_POINTdis();
    test_POINTeq();
    test_RECTarea();
    test_RECTint();

    double distancia,area;
    int equidad,inside,inside_2;
    Point p1, p2;
    Rectangulo r;

    printf("Ingrese la coord 'x' para el punto P1: ");
    scanf("%lf",&p1.x);
    printf("Ingrese la coord 'y' para el punto P1: ");
    scanf("%lf",&p1.y);

    printf("Ingrese la coord 'x' para el punto P2: ");
    scanf("%lf",&p2.x);
    printf("Ingrese la coord 'y' para el punto P2: ");
    scanf("%lf",&p2.y);

    printf("Ingrese la coord 'x' del vertice izquierdo inferior del rectángulo r: ");
    scanf("%lf", &r.vertice_izq_inf.x);
    printf("Ingrese la coord 'y' del vertice izquierdo inferior del rectángulo r: ");
    scanf("%lf", &r.vertice_izq_inf.y);

    printf("Ingrese la coord 'x' del vertice derecho superior del rectángulo r: ");
    scanf("%lf", &r.vertice_der_sup.x);
    printf("Ingrese la coord 'y' del vertice derecho superior del rectángulo r: ");
    scanf("%lf", &r.vertice_der_sup.y);


    distancia=POINTdis(p1,p2);
    equidad=POINTeq(p1,p2);
    area=RECTarea(r);
    inside=RECTint(r,p1);
    inside_2=RECTint(r,p2);

    printf("La distancia entre p1 y p2 es: %lf \n", distancia);

    (equidad)?printf("P1 y p2 son iguales \n"):printf("NO son iguales \n");

    printf("El área de r es: %lf \n",area);

    (inside)?printf("P1 se encuentra dentro de r \n"):printf("P1 NO se encuentra dentro de r \n");
    (inside_2)?printf("P2 se encuentra dentro de r \n"):printf("P2 NO se encuentra dentro de r \n");

    return 0;
}

