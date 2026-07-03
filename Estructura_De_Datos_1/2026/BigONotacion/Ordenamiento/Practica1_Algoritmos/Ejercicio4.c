// Tiempo : O(n^2)  (Se calcula strlen por cada for : O(n) * O(n))
// Memoria : O(1)
int buscarX(char *s){
    int i;
    for (i=0;i<strlen(s);i++){
        if(s[i] == 'X') return i;
    }

    return -1;
}

// Para mejorarla, calculamos strlen antes:
// Asi, TIempo: O(n).

int buscarX(char *s){
    int len=strlen(s);
    for (int x=0;x<len;x++){
        if(s[x]=='X') return x;
    }

    return -1;
}