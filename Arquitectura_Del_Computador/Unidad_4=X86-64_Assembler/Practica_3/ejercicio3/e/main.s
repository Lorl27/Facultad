.data
.bss
.text
.global main

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movb $-91,-1(%rbp)
    movb $120,-2(%rbp)

    movb -1(%rbp),%ah
    subb -2(%rbp),%ah

    movq %rbp,%rsp
    popq %rbp
    ret

# 0x2D (-211/45)
# OF=1 | CF=0  | SF=0

