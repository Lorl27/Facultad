# 00000000 00000000 00000000 00000000 == 0x80000000 + 0x80000000

.data
.text
.global main

main:
    addl $0x80000000, %eax
    addl $0x80000000, %eax

    ret


