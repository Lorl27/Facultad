.text
.global main
main:
movq $-1, %rax
movb $0, %al
movw $0, %ax
movl $0, %eax
ret

# conclusiones:
# b:1 byte - l:4 bytes - w:2 bytes, q:8 bytes 
# rax: 11111111 11111111 11111111 11111111 | 11111111 11111111 11111111 11111111
# al: 11111111 11111111 11111111 11111111 | 11111111 11111111  | 11111111 00000000
# ax: 11111111 11111111 11111111 11111111 | 11111111 11111111  | 00000000 00000000
# eax: 00000000 00000000 00000000 00000000 | 00000000 00000000  | 00000000 00000000

# Las escrituras sobre subregistros de 8 o 16 bits preservan el valor de los bits superiores del registro de 64 bits. No los limpian ni los modifican
# pero, en 32 bits: los superiores se vuelven 0.