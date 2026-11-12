.data
a: .float 1.0, 2.0, 3.0, 4.0
b: .double 5.0
c: .space 4

.text
.global main
main:
    pushq %rbp

	# Copias de datos
	movss a, %xmm0          # cargar en xmm0 un valor escalar en simple precisión desde la dirección 'a'
	movss %xmm0, %xmm1      # copiar valor escalar en simple precisión (32 bits) de xmm0 a xmm1
    
    movss b, %xmm0          # cargar en xmm0 un valor escalar en doble precisión desde la dirección 'b'
    movsd %xmm0, %xmm1      # copiar valor escalar en doble precisión (64 bits) de xmm0 a xmm1
    
    leaq a, %rdi
    movss (%rdi), %xmm0     # carga 32 bits (float) desde memoria a %xmm0
    leaq c, %rdi
    movss %xmm0, (%rdi)     # almacena 32 bits (float) desde %xmm0 a memoria
    
    # Conversiones de datos
    movq $1, %rax               # Copiar un 1 entero a rax
    cvtsi2sdq %rax, %xmm0       # Convierte el 1 de rax al double 1.0 en xmm0
    movsd %xmm0, %xmm1          # Copia el valor escalar 1.0 en doble precisión del registro xmm0 al registro xmm1
    
    # Operaciones en punto flotante
    movq $0x41200000, %rax
    movq %rax,  %xmm0                   # xmm0 = 10.0
    leaq a, %rbx
    movq $0, %rcx
    addss (%rbx, %rcx,4), %xmm0         # Suma xmm0+1.0, resultado en xmm0
    incq %rcx
    subss (%rbx, %rcx,4), %xmm0         # Resta xmm0-2.0, resultado en xmm0
    incq %rcx
    mulss (%rbx, %rcx,4), %xmm0         # Multiplica a xmm0*(3.0), resultado en xmm0
    incq %rcx
    divss (%rbx, %rcx,4), %xmm0         # divide a xmm0/(4.0), resultado en xmm0
    
    popq %rbp
	xor	%eax, %eax
	ret