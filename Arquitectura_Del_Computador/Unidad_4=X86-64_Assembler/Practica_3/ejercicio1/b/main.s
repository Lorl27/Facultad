.data
.text
.global main
main:
    movb $0xFE, %al  # movemos OxFE(254) a al
    movb $-1, %bl  # movemos -1 a bl
    addb %bl, %al  # sumamos bl con al, se guarda en al (254+-1)=253
    incb %bl # incrementamos bl a uno, bl=0
    ret 

# retorna el contenido de rax, es decir al:253