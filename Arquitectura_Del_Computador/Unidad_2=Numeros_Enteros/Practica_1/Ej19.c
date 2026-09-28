// 19) Algoritmo del campesino ruso.
//  La multiplicaci´on de enteros positivos puede implementarse con sumas, el operador AND y desplazamientos de bits usando las siguientes identidades:

//a*b={ 0 , b=0 ; 
//      a , b=1;
//      2a*k, b=2k (par)
//      2a*k+a , b=2k+1 (impar)
//  }


// Uselas para implementar una funci´on en lenguaje C: unsigned mult(unsigned a, unsigned b)

unsigned mult(unsigned a, unsigned b){
    if(b==0) return 0;
    if(b==1) return a;

    if((b&1)==0){// es par
        return mult(a<<1,b>>1); //2a*k (k=b/2) (2a= a*2)
    }else{ // es impar
        return mult(a<<1,b>>1)+a;
    }
}

/* version alternariva iterativa:

unsigned mult(unsigned a, unsigned b){
    unsigned resultado=0;

    if(b&1) resultado+=a; //si es impar...

    a<<=1;
    b>>=1;

    return resultado;
}

*/