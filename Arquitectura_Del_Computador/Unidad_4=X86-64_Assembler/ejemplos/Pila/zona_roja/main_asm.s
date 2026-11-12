.data
msg: .asciz "Suma: %d\n"

.text            
.global main
main:
   # Prólogo
   pushq %rbp
   movq %rsp, %rbp
   subq $16, %rsp
   # Construcción de argumentos
   movl $10, %edi      # arg. 1
   movl $20, %esi      # arg. 2
   movl $30, %edx      # arg. 3
   # Llamada a la función suma
   call suma
   movl %eax, -4(%rbp)
   leaq msg, %rdi
   movl -4(%rbp), %esi
   xorl %eax, %eax
   # Llamada a printf
   call printf
   # Epílogo
   movq %rbp, %rsp
   popq %rbp
   ret