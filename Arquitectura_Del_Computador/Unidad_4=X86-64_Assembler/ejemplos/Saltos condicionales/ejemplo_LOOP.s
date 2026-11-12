.global main
main:
        movb $0, %al
        movq $100, %rcx
for_1:
        incb %al        #Cuerpo del for
        loop for_1
fin:        
        ret