.data
a: .long 1, 2, 3, 4
g: .quad 0x1122334455667788
msg: .asciz "Imprime %c\n"
.text
.global main
main:
 # rsp inicial : 0x7fffffffebc8.
    subq $8, %rsp # rsp = 0x7fff ffffebc0
    movq $g, %rax # rax = 0x00000000  00404038 (dir memoria)
    movl g+4, %eax # rax = 0x000000000 11223344
    movq $3, %rbx # rbx =  0x000000000 00000003
    movb a(, %rbx,4), %al # rax = 0x000000000 11223304   ; al= a + %rbx*4 = 0x404028 + 3*4 = 0x404028*+12=0x404034 = 0x000000004
    leaq msg, %rdi # rdi = 0x00000000 00404040
    movb( %rdi, %rbx, 2), %sil # sil = %rdi+%rbx*2= 0x0000000000404040 + 3*2= 0x0000000000404040 + 6 = 0x0000000000404046 = 'E'
    xorl %eax, %eax # rax = 0x0
    call printf     # rax =0x00000000 0x0000000A ; printf retorna nro caracteres impresos. msg(10)="imprime e\n”
    addq $8, %rsp     # rsp = 0x7fffffffebc8
    ret
    
# d. Indicar lo que se imprimirıa en pantalla luego de ejecutarse la instruccion call printsf
# Imprime e