# 11111111 11111111 11111111 11111111 == 0 - 1

.data
.text
.global main

main:
    movl $0, %eax
    subl $1, %eax

    ret