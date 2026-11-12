.global main
main:
        movb $0, %al
        movq $100, %rcx
for_1:
        cmpq $0, %rcx
        je fin
        incb %al        #Cuerpo del for
        decq %rcx
        jmp for_1
fin:        
        ret