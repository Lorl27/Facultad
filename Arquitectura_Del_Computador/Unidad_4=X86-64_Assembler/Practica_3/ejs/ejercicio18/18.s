calculo:
    pushq %rbp
    movq %rsp, %rbp

    # 1. Calcular (a + c + d) en %eax
    movsbl %dil, %eax       # %eax = (int) a
    movsbl %dl, %edx        # %edx = (int) c
    addl %edx, %eax         # %eax = a + c
    addl %ecx, %eax         # %eax = (a + c) + d

    # 2. Calcular (i + j) en %ecx
    movl 16(%rbp), %ecx     # %ecx = i (7)
    addl 24(%rbp), %ecx     # %ecx = i + j (7 + 8 = 15)

    # 3. Multiplicar (a + c + d) * (i + j)
    imull %ecx, %eax        # %eax = %eax * %ecx

    movq %rbp, %rsp
    popq %rbp
    ret