.if 0
#include <stdio.h>

int suma(int a, int b, int c, int d, int e, int f, int g, int h){
    return a+b+c+d+e+f+g+h;
}

int main()
{
    printf("Suma = %d\n", suma(1,2,3,4,5,6,7,8));
    return 0;
}
.endif    

# El cógigo a continuación en Assembler es equivalente al código anterior en C

.data
str: .asciz "Suma = %d\n"

.text
.global main
main:
        pushq   %rbp            # Prólogo de main
        movq    %rsp, %rbp
        
        pushq   $8              # Octavo argumento de suma
        pushq   $7              # Séptimo argumento de suma
        movl    $6, %r9d        # Sexto argumento de suma
        movl    $5, %r8d        # Quinto argumento de suma
        movl    $4, %ecx        # Cuarto argumento de suma
        movl    $3, %edx        # Tercer argumento de suma
        movl    $2, %esi        # Segundo argumento de suma
        movl    $1, %edi        # Primer argumento de suma
        
        call    suma
        
        movl    %eax, %esi      # Primer argumento de printf
        movq    $str, %rdi      # Segundo argumento de printf
        movl    $0, %eax        # Cantidad de argumentos de punto flotante
        
        call    printf
        
        leave                   # Instrucción equivalente al epílogo
        movl    $0, %eax
        ret

suma:
        pushq   %rbp            # Prólogo de suma
        movq    %rsp, %rbp
        subq    $32, %rsp
        
        movl    %edi, -4(%rbp)      # Variable local 1
        movl    %esi, -8(%rbp)      # Variable local 2 
        movl    %edx, -12(%rbp)     # Variable local 3 
        movl    %ecx, -16(%rbp)     # Variable local 4
        movl    %r8d, -20(%rbp)     # Variable local 5
        movl    %r9d, -24(%rbp)     # Variable local 6
        movl    -4(%rbp), %edx
        movl    -8(%rbp), %eax
        addl    %eax, %edx          # Suma el primer y el segundo argumento
        movl    -12(%rbp), %eax
        addl    %eax, %edx          # Suma el tercer argumento
        movl    -16(%rbp), %eax
        addl    %eax, %edx          # Suma el cuarto argumento
        movl    -20(%rbp), %eax
        addl    %eax, %edx          # Suma el quinto argumento
        movl    -24(%rbp), %eax
        addl    %eax, %edx          # Suma el sexto argumento
        movl    16(%rbp), %eax      
        addl    %eax, %edx          # Suma el séptimo argumento 
        movl    24(%rbp), %eax      # Suma el octavo argumento
        addl    %edx, %eax          # Suma el séptimo argumento 
                                    # En eax está el valor de retorno
        
        movq    %rbp, %rsp          # Epílogo de suma      
        popq    %rbp            
        ret
        

