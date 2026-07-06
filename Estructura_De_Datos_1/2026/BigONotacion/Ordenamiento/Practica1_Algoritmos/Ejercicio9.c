
// Tiempo : O(len²) en el peor caso.
// Memoria : O(1)
int buscar_repetido(int arr[], int len){
    int i, j;
    for(i =0;i<len;i++){
        for(j=0;j<len;j++){
            if (arr[i] == arr[j] && i != j)
                return i;
        }
    }
    return -1;
}

// Si, se puede mejorar con tabla Hash.


// Tiempo : O(len) 
// Memoria : O(len) en el peor caso.
int buscar_repetido_hash(int arr[], int len){
    int vistos[len];
    for(int i=0; i<len; i++) vistos[i] = 0; // inicializar

    for(int i =0;i<len-1;i++){
        if(vistos[arr[i]]) return i; //ya lo vimos
        else vistos[arr[i]]=1;
    }

    return -1;
}

// Si los enteros entran entre 0 y 100: solo existen 101 valores posibles...:

// Tiempo : O(len) 
// Memoria : O(1).
int buscar_repetido_hash(int arr[], int len){
    int vistos[101];
    for(int i=0; i<101; i++) vistos[i] = 0; // inicializar

    for(int i =0;i<len-1;i++){
        if(vistos[arr[i]]) return i; //ya lo vimos
        else vistos[arr[i]]=1;
    }

    return -1;
}