.data
alumnos:
    .space 4, 4      # Estudiante 0: legajo, nota
    .space 4, 4      # Estudiante 1: legajo, nota
    .space 4, 4      # Estudiante 2: legajo, nota

.text
.global main

main:
    leaq alumnos, %rbx   # Dirección base del arreglo
    
    movl $0, %ecx              # alumno 0
    movl $1000, (%rbx,%rcx,8) # Guardar legajo alumno 0
    movl $8, 4(%rbx,%rcx,8)    # Guardar nota alumno 0
    
    movl $1, %ecx              # alumno 1
    movl $1001, (%rbx,%rcx,8) # Guardar legajo alumno 1
    movl $10, 4(%rbx,%rcx,8)   # Guardar nota alumno 1
    
    movl $2, %ecx              # alumno 1
    movl $1002, (%rbx,%rcx,8) # Guardar legajo alumno 1
    movl $9, 4(%rbx,%rcx,8)    # Guardar nota alumno 1

    xorl %eax, %eax
    ret