.data
.text
.global main
main:
    movb $0xFF, %al  # 11111111
    ret

 # el cdigo mueve 0xFF a al.
 # al es la parte de 8 bits baja de ax, por lo que es un nro
 # sin signo y devolvera 255
 # ax es la parte baja de rax, que es donde ret y echo $? se fijan para devolver el resultado correspondiente.