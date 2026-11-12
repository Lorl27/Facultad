.global main
main:
        movq $10, %rdx
        movq $5, %rbx
        cmpq %rbx, %rdx
        jg mayor
        je igual
        movb $-1, %al	# Cuerpo del ELSE
        jmp fin
igual:
        movb $0, %al	# Cuerpo del ELSE IF
        jmp fin
mayor:
        movb $1, %al  	# Cuerpo del ELSE  
fin:        
        ret