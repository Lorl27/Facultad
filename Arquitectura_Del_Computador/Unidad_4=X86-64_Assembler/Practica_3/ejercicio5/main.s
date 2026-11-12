.data
.text
.global main
main:
movq $0x1122334455667788, %rax
addq $0x1122334455667788, %rax  # ERROR ACA
ret

# Error de tipo.
# a instrucción MOV es la ÚNICA instrucción que admite un operando inmediato de 64 bits completo,
#  los demas deben pasarse a uuno intermedio.