.data

.text
.global main
main:
	movq $1, %rax
	movq $3, %rdx

	#quiero qintercambiar los valores de rax y rdx sin usar otros registros
	
	# Opción 1 
	movq %rax,-8(%rsp)
	movq %rdx,-16(%rsp)
	movq -8(%rsp), %rdx
	movq -16(%rsp), %rax
	
	# Opción 2
	pushq %rax 
	pushq %rdx 
    popq %rax
    popq %rdx

	ret