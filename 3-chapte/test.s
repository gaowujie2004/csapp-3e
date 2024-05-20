	.file	"test.c"
	.text
	.globl	store_prod
	.def	store_prod;	.scl	2;	.type	32;	.endef
	.seh_proc	store_prod
store_prod:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	%r8, 32(%rbp)
	movq	24(%rbp), %rax
	imulq	32(%rbp), %rax
	cqto
	movq	16(%rbp), %rcx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	nop
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$88, %rsp
	.seh_stackalloc	88
	leaq	80(%rsp), %rbp
	.seh_setframe	%rbp, 80
	.seh_endprologue
	call	__main
	movabsq	$68174490358557645, %rax
	movl	$0, %edx
	movq	%rax, -16(%rbp)
	movq	%rdx, -8(%rbp)
	movabsq	$69075210266725597, %rax
	movl	$0, %edx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rbx
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	addq	%rcx, %rax
	adcq	%rbx, %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$0, %eax
	addq	$88, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 13.2.0"
