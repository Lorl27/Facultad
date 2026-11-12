.data
.bss
.text
.global main

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movb $-63,-1(%rbp)
    movb $-56,-2(%rbp)

    movb -1(%rbp),%ah
    addb -2(%rbp),%ah

    movq %rbp,%rsp
    popq %rbp
    ret

#  0x189 -119
# OF=0 | CF=1  | SF=1

