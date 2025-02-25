// 1. Entrada/Salida

#include <stdio.h>

// Ejercicio 1. ¿Cuál es la salida del siguiente programa?

// int main()
// {

//     int a, b, c, d = 6, e;
//     a = b = 3;
//     c = a * b + d;
//     e = (c + 5) / 4 - 3;
//     e += 5;
//     printf(" Los resultados son %d y %d ", c, e); // 15,7
//     return 0;
// }

/*----------------------------------------*/

// Ejercicio 2. ¿Cuál es la salida del siguiente programa?
// int main()
// {

//     int a, b, c, d = 6, e;
//     a = 3;
//     b = a - d / 3; //1
//     a *= b;
//     c = a + d / a - 3 / a * b; //4
//     e = c + 8 / 4 - b; //5
//     e += 5;//10
//     printf(" Los resultados son %d y %d ", c, e); // 4,10
//     return 0;
// }

// Ejercicio 3. Determine la salida del siguiente programa:

// int main()
// {

//     float x, y;
//     printf(" Introduzca 2 números :\n ");
//     scanf("%f %f", &x, &y);
//     printf(" La suma de %f y %f vale %f \n ", x, y, x + y);
//     printf(" La suma de %4f y %4.2f vale %10.3f \n ", x, y, x + y);
//     printf(" La suma de %e y %e vale %e \n ", x, y, x + y);
//     return 0;
// }

/*----------------------------------------*/

// 2. Selección

// Ejercicio 4. Escriba una función que determine en qué estado está el agua en función de su
// temperatura: si es negativa o 0 el estado será sólido, si positiva y menor que 100 será líquido y
// si es mayor que 100 será gaseoso. El valor de la temperatura deberá ingresarse por pantalla.

// int main() {
//     float temp;
//     printf("Ingresa la temp!!!!!:\n");
//     scanf("%f", &temp);
//     if (temp<=0){
//         printf("solido\n");
//     }
//     else if (temp>0 && temp<100){
//         printf("liquido\n");
//     }
//     else{
//         printf("gaseoso\n");
//     }
// }

/*----------------------------------------*/

// Ejercicio 5. Escriba una función que lea la nota de un alumno (entera) y muestre un mensaje
// diciendo si sacó insifuciente (2 a 5), aprobado (6), bueno (7), muy bueno (8), distinguido (9)
// o sobresaliente (10). Se debe mostrar un mensaje de error si la nota ingresada no es válida.
// Este programa debe hacerse de dos maneras diferentes: con if secuenciales y con if-else
// anidados.

// int main(){
//     int nota;
//     printf("Ingrese una notaaaaa:\n");
//     scanf("%i",&nota);
//     if (nota<2 || nota>10){
//         printf("ERROR. INUTIL\n");
//     }
//     else if(nota>=2 && nota<=5){
//         printf("DESAPROBASTE.BOBO\n");
//     }
//     else if(nota==6){
//         printf("REGULAR\n");
//     }
//     else if(nota==7){
//         printf("meh\n");
//     }
//     else if(nota==8){
//         printf("ojo\n");
//     }
//     else if(nota==9){
//         printf("quee\n");
//     }
//     else if(nota==10){
//         printf("WOPOOOWOWOWOWOWOWO\n");
//     }
// }


/*----------------------------------------*/

// Ejercicio 6. Construya un programa que lea por teclado el día y mes de nacimiento de una
// persona como números enteros y calcule su signo del zodíaco, mostrándolo por pantalla.

// Aries del 21 de marzo al 19 de abril
// Tauro del 20 de abril al 20 de mayo
// Géminis del 21 de mayo al 21 de junio
// Cáncer del 22 de junio al 21 de julio
// Leo del 22 de julio al 21 de agosto
// Virgo del 22 de agosto al 22 de septiembre
// Libra del 23 de septiembre al 22 de octubre
// Escorpio del 23 de octubre al 21 de noviembre
// Sagitario del 22 de noviembre al 21 de diciembre
// Capricornio del 22 de diciembre al 20 de enero
// Acuario del 21 de enero al 19 de febrero
// Piscis del 20 de febrero al 20 de marzo

// int  main(){
//     int dia, mes;
//     printf("decime tu dia y mes:\n");
//     scanf("%i%i",&dia,&mes);
//     if (dia>=21 && mes==3 || dia<=19 && mes==4){
//         printf(" aries\n");
//     }
//     else if (dia>=20 && mes==4 || dia<=20 && mes==5){
//         printf("tauro\n");
//     }
//     else if (dia>=21 && mes==5 || dia<=21 && mes==6){
//         printf("geminis \n");
//     }
//     else if (dia>=22 && mes==6 || dia<=21 && mes==7){
//         printf(" cancer\n");
//     }
//     else if (dia>=21 && mes==7 || dia<=19 && mes==8){
//         printf(" leo\n");
//     }
//     else if (dia>=22 && mes==8 || dia<=22 && mes==9){
//         printf(" virgo\n");
//     }
//     else if (dia>=23 && mes==9 || dia<=22 && mes==10){
//         printf(" libra\n");
//     }
//     else if (dia>=23 && mes==10 || dia<=21 && mes==11){
//         printf(" escorpio\n");
//     }
//     else if (dia>=22 && mes==11 || dia<=21 && mes==12){
//         printf(" sagitario\n");
//     }
//     else if (dia>=22 && mes==12 || dia<=20 && mes==1){
//         printf(" capricornio\n");
//     }
//     else if (dia>=21 && mes==1 || dia<=19 && mes==2){
//         printf(" acuario\n");
//     }
//     else if (dia>=20 && mes==3 || dia<=20 && mes==3){
//         printf(" piscis\n");
//     }
//     else{
//         printf("has puesto un dato erroneo che");
//     }
    
    
// }

/*----------------------------------------*/

// Ejercicio 7. Un año es bisiesto si es divisible por 400, o bien si es divisible por 4 pero no por
// 100. Escriba un programa que lea por teclado un año y devuelva si es bisiesto o no.

// int main(){
//     int anio;
//     printf("ingrse año here:\n");
//     scanf("%i",&anio);
//     if((anio%400)==0 || (anio%4)==0 && (anio%100)!=0){
//         printf("BISIESTO\n");
//     }
//     else{
//         printf("no");
//     }
// }

/*----------------------------------------*/

// Ejercicio 8. Simplifique el siguiente código de forma que sean necesarias menos compara-
// // ciones.

// if ( Edad > 64) printf ( " Seguridad Social " ) ;
//  if ( Edad < 18) printf ( " Exento " ) ;
//  if (( Edad >= 18) && ( Edad < 65) ) printf ( " Imposible " ) ;

// int main(){

//     int edad;
//     printf("pone la edad");
//     scanf("%i",&edad);
//     if(edad>64){
//         printf ( " Seguridad Social " ) ;
//     }
//     else if(edad<18){
//         printf ( " Exento " ) ;
//     }
//     else
//         printf ( " Imposible " ) ;
    
// }

/*----------------------------------------*/

// 3. Bucle While

// Ejercicio 9. Escriba un programa que muestre los números enteros del 1 al 100.
// int main(){
//     int contador=1;
//     while(contador<=100){
//         printf("%i\n",contador);
//         contador+=1;
//     }
    
// }

/*----------------------------------------*/

// Ejercicio 10. Escriba un programa que muestre los números impares del 1 al 100.
// int main(){
//     int contador=1;
//     while(contador<=100){
//         if ((contador%2)!=0){
//             printf("%i\n",contador);
//             }
//     contador+=1;    
//     }
    
// }

/*----------------------------------------*/

// Ejercicio 11. Escriba un programa que pida dos números por teclado y muestre todos los
// números que van desde el primero hasta el segundo. Se debe controlar que los valores sean
// correctos, es decir, que el primero sea menor que el segundo. Si no lo son, se deben volver a
// pedir hasta que lo sean.
// int main(){
//     int num,num2,cont=0;
//     printf("inegrese 2 nuemropos:\n");
//     scanf("%i%i",&num,&num2);
//     printf("\n");
//     while (num>num2){
//     printf("inegrese 2 nuemropos:\n");
//     scanf("%i%i",&num,&num2);
//     }

//     while(cont<=num2){
//         printf("%i\n",cont);
//         cont+=1;
//     }
// }

/*----------------------------------------*/

// Ejercicio 12. Escriba un programa que, dado un número ingresado por teclado, determine si
// el mismo es primo o no, mostrándolo por pantalla.

// int main(){
//     int x=2,valor,primo=0,contador=0;
    
//     scanf("%i", &valor);

//     while(x<(valor/2) && primo != 1){
//         if(valor%x==0){
//             primo=1;
//         }
//         x++;
//     }
//     if (!primo){
//         printf("es primo");
//     }else {
//         printf("es divisible por %i", x-1);
//     }
    

// }

/*----------------------------------------*/

// Ejercicio 13. Escriba un programa que lea un número por teclado y muestre el factorial del
// mismo. Sugerencia: definir la variable que represente el factorial como double.


// double factorial(double n){
//     int contador=1;
//     double porqueria=1;

//     while(contador<=n){
//         porqueria*=contador;
//         contador++;
//     }
//     return porqueria;

// }



// double main(){
//     double numero,f;
//     printf("Pon un numero!!_: ");   
//     scanf("%lf",&numero);
//     f=factorial(numero);
//     printf("%lf",f);
// }

/*----------------------------------------*/

// Ejercicio 14. Los pacientes con síntomas de una cierta enfermedad son ingresados en el
// hospital si tienen un valor superior a 0,6 en la medición de un determinado índice, y son opera-
// dos si el valor es superior a 0,9. Escriba un programa en C que lea desde el teclado el número
// de pacientes a analizar seguido de la edad y el índice de cada paciente. El programa debe
// calcular y mostrar la edad media de los pacientes analizados, la edad media de los ingresados
// y la edad media de los operados.

// int main(){
//     float pacientes,edad,sumaAnalizados=0,SumaIngresados=0,sumaOPerados=0,totalOp=0,totalIngre=0;
//     float indices,promedioEDADA,promedioedadI,promedioEdadO,indiceoperado=0.9,indiceingresado=0.6;
//     printf("ingrese la cant de pacientes GAYS ");
//     scanf("%f",&pacientes);
//     for(int x=1;x<=pacientes;x++){
//         printf("INgrese la edad y el indice del paciente nro %i : ",x);
//         scanf("%f%f",&edad,&indices);
//         sumaAnalizados+=edad;
//         if(indices>indiceoperado){
//             totalOp+=1;
//             sumaOPerados+=edad;
//             printf("%f OP \n",indices);
//         }
//         else if(indices>indiceingresado){
//             totalIngre+=1;
//             SumaIngresados+=edad;
//             printf("%f \n",indices);
//         }
//     }
//     promedioEDADA=sumaAnalizados/pacientes;
//     promedioEdadO=sumaOPerados/totalOp;
//     promedioedadI=SumaIngresados/totalIngre;
//     printf("Los pacientes analizados fueron: %0.5f, en donde su promedio es de %f\n. Los pacientes ingresados fueron %0.3f, en donde su promedio de edad fue %f \n; Y pr ultimo, los operados fueron %0.3f y su promedio: %f" , pacientes,promedioEDADA,totalIngre,promedioedadI,totalOp,promedioEdadO );
//     return 0;
// }

/*----------------------------------------*/

// 4. Funciones

// Ejercicio 15. Escriba una función maximo que tome como parámetros dos enteros y devuelva
// el máximo entre ellos. Utilice esta función para calcular el máximo entre 4 enteros que se le
// soliciten al usuario por teclado.


int  maximo(int a, int b){
     if (a<b){
        return b;
    }
     return a;
 }

// int main(){
//     int a,b,c,d;
//     printf("INGRESA 4 NUMEROS ARFNHUDJGJRF: ");
//     scanf("%i%i%i%i",&a,&b,&c,&d);
//     int max=(maximo(maximo(a,b),(maximo(c,d))));
//     printf("tu num max es: %i\n",max);
//     return 0;
// }


/*----------------------------------------*/

// Ejercicio 16. Tres números positivos pueden ser la medida de los lados de un triángulo si y
// sólo si el mayor de ellos es menor que la suma de los otros dos. Escriba y pruebe una función
// ladosTriangulo que devuelva 1 si los tres números que se le pasan verifican esta condición o
// 0 en caso contrario.

//  int main()
//  {
//      unsigned int a, b, c, max, suma = 0;

//      printf("INGRESA 3 nums: ");
//      scanf("%i%i%i", &a, &b, &c);

//      max = maximo(maximo(a, b), maximo(b, c));
//      if (max == a)
//      {
//          printf("%i", max);
//          suma = c + b;
//          if (max > suma)
//          {
//              return 1;
//          }
//      }
//      else if (max == b)
//      {
//          printf("%i", max);
//          suma = c + a;
//          if (max > suma)
//          {
//              return 1;
//          }
//      }
//      else
//      {
         
//          suma = b + a;
//          printf("max:%i, suma %i\n", max, suma);
//          if (max > suma)
//          {
//              return 1;
//          }
//      }
//      printf("ño >:(");
//      return 0;
//  }

/*----------------------------------------*/
// Ejercicio 17. Defina una función esRectangulo que tome tres enteros y devuelva 1 si los
// números que se le pasan pueden ser los lados de un triángulo rectángulo, o 0 en caso contrario.
// Sugerencia: una manera sería verificar si el cuadrado del mayor es igual la suma de los
// cuadrados de los otros dos. a2 + b2 = c2 Sin embargo, existe otra manera utilizando sólo una vez una fun-
// ción max3 que devuelve el máximo entre tres enteros dados. Defina ambas funciones y pruebe
// esRectangulo con las entradas (3, 5, 4), (5, 13, 12) y (7, 3, 5).


// int maximum(int a, int b, int c){
//     return (a<b&&c<b) ? b :  (a>c ? a : c);}

// int esRectangulo(int a,int b,int c,int m){
//     return ((m==a)? (((m*m)==((b*b)+(c*c)))? 1 : 0) : ((m==b) ? (((m*m)==(a*a)+(c*c))? 1 : 0) : ((m==c) ?  (((m*m)==(a*a)+(b*b))? 1 : 0) : 0)) );
// }

// int main(){
//     int a,b,c,r;
//     printf("INGRESA 3 nums: ");
//     scanf("%i%i%i", &a, &b, &c);
//     int m=maximum(a,b,c);
//     printf("el maximo entre los 3 es: %i\n",m);
//     r=esRectangulo(a,b,c,m);
//     printf("es r?: %i\n", r);
// }


/*----------------------------------------*/

// Ejercicio 18. La fecha del domingo de Pascua corresponde al primer domingo después de
// la primera luna llena que sigue al equinoccio de primavera. Dado un año, los cálculos que
// permiten conocer esta fecha son:
// A = año % 19
// B = año % 4
// C = año % 7
// D = (19 * A + 24) % 30
// E = (2 * B + 4 * C + 6 * D + 5) % 7
// N = (22 + D + E)

// Donde N indica el número del día del mes de marzo (o abril si N es superior a 31) correspondiente
// al domingo de Pascua. Escriba un programa que lea un año y muestre el día y el mes en el
// que se celebró o se celebrará el domingo de Pascua ese año. Utilice una función a la que se
// le pase como parámetro el año y retorne el valor de N. El programa principal realiza el resto del
// proceso.

/*----------------------------------------*/

#include <string.h>

int fun(int anio){
    int a,b,c,d,e,n;
    a = anio % 19;
    b = anio % 4;
    c = anio % 7;
    d = (19 * a + 24) % 30;
    e = (2 * b + 4 * c + 6 * d + 5) % 7;
    return n = (22 + d + e);
}

int main(){
    int year,n;
    char mes[]="marzo";
    printf("Igresa el año del q qrés saber pascuaç!!\n :");
    scanf("%i",&year);
    n=fun(year);
    
    if (n>31){
        strcpy(mes,"abril");
        n-=31;
        
    }

    printf("Pascua en %i se celebro el dia %i de %s\n:",year,n,mes);

    return 0;
}


/*----------------------------------------*/


// Ejercicio 19. La sucesión de Fibonacci se define de la siguiente manera:
// f (n) =
// 
// 
// 
// 0 si n = 0
// 1 si n = 1
// f (n − 1) + f (n − 2) si n > 2
// Escriba una función recursiva f que tome un entero n y devuelva el correspondiente valor
// según la sucesión de Fibonacci.

// int main(){
//     int numero;
//     printf("pone algo, loco\n");
//     scanf("%i",&numero);
//     if(numero==0){
//         printf("0");

//     }
//     else if(numero==1){
//         printf("1");
//     }
//     else{
//         int primero=0,segundo=1;
//         for(int x=2;x<numero;x++){
//             segundo=primero+segundo;
//             primero=segundo-primero;
//         }
//         printf("tu numero de fibonacci: %i\n",segundo);

//     }
// }

// int algo(int num)
// {
//     if (num == 0)
//     {
//         return 0;
//     }
//     else if (num == 1)
//     {
//         return 1;
//     }
//     else
//     {
//         return ((algo(num - 1)) + (algo(num - 2)));
//     }
// }

// int main(){
//     int num,result;
//     printf("num:\n");
//     scanf("%i",&num);
//     result=algo(num);
//     printf("%i",result);

// }
