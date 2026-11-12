.data
.bss
.text
.global main

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp


    movb $120,-1(%rbp)
    movb $-56,-2(%rbp)

    movb -1(%rbp),%ah
    subb -2(%rbp),%ah

    movq %rbp,%rsp
    popq %rbp
    ret

#  0xB0(176/-80)
# OF=1 | CF=1  | SF=1

