.data
.text
.global main

main:
    #prologo:
    pushq %rbp
    movq %rsp,%rbp
    subq $16,%rsp

    movb $100,-1(%rbp)
    movb $120,-2(%rbp)

    movb -1(%rbp),%ah
    addb -2(%rbp), %ah

    movq %rbp ,%rsp
    popq %rbp
    ret


# 0XDC (220/-36)
# OF=1 | CF=0  | SF=1