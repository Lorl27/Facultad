.global main
main:
        movb $0, %al
        movq $1, %rcx
while_1:
        cmpq $100, %rcx
        jge fin
        incb %al		# Cuerpo del WHILE
        imul $2, %rcx		# Cuerpo del WHILE
        jmp while_1
fin:        
        ret