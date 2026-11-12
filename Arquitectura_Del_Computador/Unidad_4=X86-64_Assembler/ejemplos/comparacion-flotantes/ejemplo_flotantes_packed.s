.data
.align 16
vec1:     .float 4.0, 2.0, 1.0, 5.0
vec2:     .float 2.0, 2.5, 1.5, 4.0
fmt:      .asciz "%f %f %f %f\n"            # formato para printf

.bss
result:   .space 16, 0                      # 4 floats = 16 bytes

.text
.global main
main:
    pushq   %rbp
    movq    %rsp, %rbp
    
    # Cargar los vectores
    movaps  vec1, %xmm0
    movaps  vec2, %xmm1
    
    # Sumar elemento a elemento
    addps   %xmm0, %xmm1
    
    # Guardar resultado en memoria
    movups  %xmm1, result
    
    # Preparar argumentos para printf
    leaq    fmt, %rdi               # 1er argumento: dirección del formato 
    movss   result, %xmm0           # cargar result[0]
    cvtss2sd %xmm0, %xmm0           # convertir a doble precisión
    movss   result+4, %xmm1         # result[1]
    cvtss2sd %xmm1, %xmm1           # convertir a doble precisión
    movss   result+8, %xmm2         # result[2]
    cvtss2sd %xmm2, %xmm2           # convertir a doble precisión
    movss   result+12, %xmm3        # result[3]
    cvtss2sd %xmm3, %xmm3           # convertir a doble precisión
    movl    $4, %eax                # número de argumentos de punto flotante 
    call    printf
    
    xorl    %eax, %eax
    leave
    ret