.data
.text
.global main

main:
    pushq %rbp
    movq %rsp, %rbp

    movq $0, %rdx  # Inicializamos el contador
    movq $64, %rcx # establecemos las iteraciones

ciclo:
    rolq $1, %rax # Rota 1 bit a la izq. y lo saca hacia CF
    adcq $0, %rdx # rdx = rdx + 0 + CF (suma el bit que salió en CF)
    loop ciclo  # si llega a 0, no se ejecuta mas.

    movq %rdx, %rax

    movq %rbp, %rsp
    popq %rbp
    ret
