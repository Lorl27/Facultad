	.file	"ejercicio7.c"
	.text
	.p2align 4
	.globl	molinete1
	.type	molinete1, @function
molinete1:
.LFB24:
	.cfi_startproc
	endbr64
	addl	$100000, contador(%rip)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE24:
	.size	molinete1, .-molinete1
	.p2align 4
	.globl	molinete2
	.type	molinete2, @function
molinete2:
.LFB28:
	.cfi_startproc
	endbr64
	addl	$100000, contador(%rip)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE28:
	.size	molinete2, .-molinete2
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"[Contador]: %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB26:
	.cfi_startproc
	endbr64
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	xorl	%ecx, %ecx
	leaq	molinete1(%rip), %rdx
	xorl	%esi, %esi
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	leaq	8(%rsp), %rdi
	call	pthread_create@PLT
	xorl	%ecx, %ecx
	leaq	molinete2(%rip), %rdx
	xorl	%esi, %esi
	leaq	16(%rsp), %rdi
	call	pthread_create@PLT
	movq	8(%rsp), %rdi
	xorl	%esi, %esi
	call	pthread_join@PLT
	movq	16(%rsp), %rdi
	xorl	%esi, %esi
	call	pthread_join@PLT
	movl	contador(%rip), %edx
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rsi
	movl	$2, %edi
	call	__printf_chk@PLT
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L7
	xorl	%eax, %eax
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L7:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE26:
	.size	main, .-main
	.globl	contador
	.bss
	.align 4
	.type	contador, @object
	.size	contador, 4
contador:
	.zero	4
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
