# Para ejecutar el programa:
1. gcc archivo.c
2. ./a.exe

* Si quiero nombrarlo: 
1. gcc archivo.c -o nombre.exe 
2. ./nombre.exe

----
## LIBRERÍAS:
* stdio.h , math.h string.h , stdlib.h , ctype.h

---

''' strlen(c) != char c[10]='hi'; (2 vs 10-1) '''
El fin de cadena es el caracter ‘\0’
- ej uso: for(x=0;alfabeto[x]!='\0';x++){...}

**PARA LEER strings:**
1. scanf("%s", string);  **//no se pone el operador  & al leer un  array.**
2.  fgets(mensaje,sizeof(mensaje),stdin); //Utilizamos fgets para poder leer cadenas largas
    mensaje[strcspn(mensaje,"\n")]='\0'; //Eliminamos el salto de línea
3.  scanf(" %[^\n]",nam); //Eliminamos el salto de línea
---
### i++ vs ++i
- I++ : El operador tiene menos precedencia que cualquier 
otro. Por lo tanto, se incrementa la variable luego de usarla
- ++I: Se incrementará la variable ANTES de usarla


#### Punteros y arrays:

int a[0] == int a*
a[0]=0  == *a=0

---

char a[10];
a==&a==a[0];

int b[10];
int *p=b;
*p=5
p[1]=10;

printf("primer %d, sgundo %d",b[0],b[1]);  --> 5 , 10.

**modificando valores y dir. del puntero:**
    int *punt ,i;
    int x[5]={1 ,2 ,3 ,4 ,5};
    punt=&x[0]+3;   //el puntero apunta a x[3]
    *(punt -2) =9;  //comenzamos en x[3] 3-2=1 , x[1]=9 , x={4,9,3,4,5}  //! aca no cambiamos el puntero de lugar, solo modificamos el valor en esa dirrecion
    punt --; //retrocedemos 1 elemento  (estamos todavia en x[3],ahora estamos en x[2]) //!aca si lo cambiamos de lugar
    *(punt)=7 ; //x[2]=7 -->x={1,9,7,4,5}
    punt [1]=11 ; //como estamos en x[2]  , punt[1]==(*punt+1)==x[3] x={1,9,7,11,5}
    punt=x; // apuntamos de nuevo a x[0] para poder imprimir bien el array.


**A TENER EN CUENTA:**

char *ptr = "hola mundo"; → Apunta a memoria de solo lectura (modificarla causa un segmentation fault).
char ptr[] = "hola mundo"; → Almacena la cadena en memoria de escritura (se puede modificar).

---
### PUNTEROS:

**Básico:**
int i=5;
dirrección: printf("&p", %i);

*declaración puntero:* char* p; , int* p;
int* p=&i ; //Guardamos la dirección de memoria del entero, en un puntero.
printf("%d",*p) --> i --> 5

*uso de puntero, para cambiar valor*
    int* punt;  //crea un puntero de enteros
    int x=7;  
    punt=&x;  //le asigna al puntero, la direccion de la var x (x=7)
    *punt = 4; //ahora, x vale 4
    x=3 // puntero valdra 3 tmb!
    printf("%d",*punt) --> x --> 3.
    int y=2;
    *punt=&y //puntero valdra 2!
    printf("%d%d%d",*punt,x,y) --> 2,3,2
----
while(*p++ = *q++);  //while(...) se ejecuta hasta que *q==´\0´ - basicamente copia todo lo de *p en *q (va parte x parte- se incrmeentan al unísono) ===que strcopy(*p,*q)



**Ejemplo de USO (en funciones):**
void calcular_edades(float *edad_media) {
    int edad, pacientes_ingresados = 0,suma_Edad=0;
    suma_Edad+= edad;
    pacientes++;

    *edad_media=suma_Edad/pacientes;
}

int main(){
    float edad_media;
    calcular_edades(&edad_media);
}

**Para pedir memorias:**
int* puntero;
puntero= malloc(sizeof(int)*TAM);

for( int x=0; x<TAM;x++){
    puntero[x]=x;    ---> *(puntero+x) == puntero[x]
}

for(int x=0;x<TAM;x++){
    printf("valor: %d",puntero[x]);  --> &p[x] == p+x (dirreccion memoria)
}

free(puntero);

---
## Estructuras:

1. struct Persona{
    char* name;
    int edad;
}; 

2. typedef struct {
    char* name;
    int edad;
} Persona; 

*****
1. struct Persona.p1;   
p1.name="Something";

2. Persona p1;

## Estructuras  y punteros:

struct Persona* p1;
p1=malloc(sizeof(struct Persona));

Para acceder a sus campos: (*p1).nombre == p1->nombre;




-----

### RECETA:
#include <assert.h>

//descripcion fun
//fun:int->int
//ejemplos

int main(){
    assert(fun(a,b)==40);

    return 0;
}