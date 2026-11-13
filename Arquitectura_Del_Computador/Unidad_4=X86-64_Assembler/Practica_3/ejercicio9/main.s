.data
a: .word -1
b: .byte 0xaa, 99
c: .float 1.5
str: .asciz "Hola mundo\n"
.text
.global main
main:
    leaq a, %rdx
    leaw (%rdx),%ax # ax = 0xffff
    leab 3(%rdx),%al  # al = 0x63
    leal  8(%rdx),%esi # esi = "aloH" - leemos solo 4 bytes (l)
    leal 4(%rdx), %esi # edi = 0x3fc00000
    movl %esi, ( %rdx)  # escribe "aloH" en a
    ret

