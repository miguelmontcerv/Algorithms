	.file	"bb.c"
	.text
	.p2align 4,,15
	.globl	AgregarElemento
	.type	AgregarElemento, @function
AgregarElemento:
.LFB43:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	testq	%rdi, %rdi
	je	.L7
	cmpl	%esi, (%rdi)
	movq	%rdi, %rbx
	jg	.L8
	movq	16(%rdi), %rdi
	call	AgregarElemento
	movq	%rax, 16(%rbx)
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L8:
	.cfi_restore_state
	movq	8(%rdi), %rdi
	call	AgregarElemento
	movq	%rax, 8(%rbx)
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	.cfi_restore_state
	movl	$24, %edi
	movl	%esi, 12(%rsp)
	call	malloc@PLT
	movl	12(%rsp), %esi
	movq	$0, 8(%rax)
	movq	$0, 16(%rax)
	movl	%esi, (%rax)
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE43:
	.size	AgregarElemento, .-AgregarElemento
	.p2align 4,,15
	.globl	InOrden
	.type	InOrden, @function
InOrden:
.LFB44:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L17
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rsi, %rbp
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
.L11:
	movq	8(%rbx), %rdi
	movq	%rbp, %rsi
	call	InOrden
	movslq	count(%rip), %rax
	movl	(%rbx), %edx
	movq	16(%rbx), %rbx
	movl	%edx, 0(%rbp,%rax,4)
	addl	$1, count(%rip)
	testq	%rbx, %rbx
	jne	.L11
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L17:
	.cfi_restore 3
	.cfi_restore 6
	rep ret
	.cfi_endproc
.LFE44:
	.size	InOrden, .-InOrden
	.p2align 4,,15
	.globl	uswtime
	.type	uswtime, @function
uswtime:
.LFB45:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %r12
	xorl	%edi, %edi
	movq	%rdx, %rbx
	subq	$192, %rsp
	.cfi_def_cfa_offset 224
	leaq	32(%rsp), %rsi
	movq	%fs:40, %rax
	movq	%rax, 184(%rsp)
	xorl	%eax, %eax
	call	getrusage@PLT
	leaq	8(%rsp), %rsi
	leaq	16(%rsp), %rdi
	call	gettimeofday@PLT
	pxor	%xmm1, %xmm1
	movsd	.LC0(%rip), %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdq	40(%rsp), %xmm1
	mulsd	%xmm2, %xmm1
	movq	184(%rsp), %rax
	xorq	%fs:40, %rax
	cvtsi2sdq	32(%rsp), %xmm0
	addsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	48(%rsp), %xmm0
	movsd	%xmm1, (%r12)
	pxor	%xmm1, %xmm1
	cvtsi2sdq	56(%rsp), %xmm1
	mulsd	%xmm2, %xmm1
	addsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	24(%rsp), %xmm0
	mulsd	%xmm2, %xmm0
	movsd	%xmm1, 0(%rbp)
	pxor	%xmm1, %xmm1
	cvtsi2sdq	16(%rsp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, (%rbx)
	jne	.L23
	addq	$192, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L23:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE45:
	.size	uswtime, .-uswtime
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"%d"
.LC2:
	.string	"Error"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC3:
	.string	"\nBusqueda Binaria con %d numeros, buscando el %d\n"
	.section	.rodata.str1.1
.LC4:
	.string	"Tiempo: %.10f\n"
	.section	.rodata.str1.8
	.align 8
.LC5:
	.string	"------------------------------------------------------"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB42:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movl	$10, %edx
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$104, %rsp
	.cfi_def_cfa_offset 160
	movq	8(%rsi), %rdi
	xorl	%esi, %esi
	movq	%fs:40, %rax
	movq	%rax, 88(%rsp)
	xorl	%eax, %eax
	call	strtol@PLT
	movl	%eax, n(%rip)
	cltq
	leaq	0(,%rax,4), %rdi
	call	malloc@PLT
	movq	16(%rbx), %rdi
	xorl	%esi, %esi
	movl	$10, %edx
	movq	%rax, %r13
	call	strtol@PLT
	movl	%eax, bus(%rip)
	movl	n(%rip), %eax
	movl	%eax, %r12d
	shrl	$31, %r12d
	addl	%eax, %r12d
	sarl	%r12d
	testl	%eax, %eax
	js	.L35
	leaq	20(%rsp), %r15
	leaq	.LC1(%rip), %r14
	xorl	%ebx, %ebx
	xorl	%ebp, %ebp
	.p2align 4,,10
	.p2align 3
.L26:
	movq	%r15, %rsi
	movq	%r14, %rdi
	xorl	%eax, %eax
	call	__isoc99_scanf@PLT
	movl	20(%rsp), %esi
	movq	%rbp, %rdi
	addl	$1, %ebx
	call	AgregarElemento
	cmpl	%ebx, n(%rip)
	movq	%rax, %rbp
	jge	.L26
.L25:
	movq	%r13, %rsi
	movq	%rbp, %rdi
	call	InOrden
	movslq	n(%rip), %rbp
	movq	%rbp, %r14
	salq	$2, %rbp
	movq	%rbp, %rdi
	call	malloc@PLT
	movq	%rbp, %rdi
	movq	%rax, %rbx
	call	malloc@PLT
	testl	%r12d, %r12d
	movq	%rax, %rbp
	js	.L27
	movslq	%r12d, %rax
	leaq	4(,%rax,4), %rcx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L28:
	movl	0(%r13,%rax), %edx
	movl	%edx, (%rbx,%rax)
	addq	$4, %rax
	cmpq	%rax, %rcx
	jne	.L28
.L27:
	leal	1(%r12), %eax
	cmpl	%eax, %r14d
	jl	.L29
	subl	$1, %r14d
	cltq
	subl	%r12d, %r14d
	leaq	0(%r13,%rax,4), %rcx
	xorl	%eax, %eax
	leaq	4(,%r14,4), %rsi
	.p2align 4,,10
	.p2align 3
.L30:
	movl	(%rcx,%rax), %edx
	movl	%edx, 0(%rbp,%rax)
	addq	$4, %rax
	cmpq	%rax, %rsi
	jne	.L30
.L29:
	leaq	40(%rsp), %rdx
	leaq	32(%rsp), %rsi
	leaq	24(%rsp), %rdi
	call	uswtime
	leaq	72(%rsp), %rdi
	leaq	funcion(%rip), %rdx
	xorl	%esi, %esi
	movq	%rbx, %rcx
	call	pthread_create@PLT
	testl	%eax, %eax
	jne	.L33
	leaq	80(%rsp), %rdi
	leaq	funcion(%rip), %rdx
	xorl	%esi, %esi
	movq	%rbp, %rcx
	call	pthread_create@PLT
	testl	%eax, %eax
	movl	%eax, %ebx
	jne	.L33
	movq	72(%rsp), %rdi
	xorl	%esi, %esi
	call	pthread_join@PLT
	movq	80(%rsp), %rdi
	xorl	%esi, %esi
	call	pthread_join@PLT
	leaq	64(%rsp), %rdx
	leaq	56(%rsp), %rsi
	leaq	48(%rsp), %rdi
	call	uswtime
	movl	bus(%rip), %ecx
	movl	n(%rip), %edx
	leaq	.LC3(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movsd	64(%rsp), %xmm0
	movl	$10, %edi
	movsd	40(%rsp), %xmm1
	movsd	%xmm0, 8(%rsp)
	movsd	%xmm1, (%rsp)
	call	putchar@PLT
	movsd	8(%rsp), %xmm0
	leaq	.LC4(%rip), %rsi
	movl	$1, %edi
	movl	$1, %eax
	subsd	(%rsp), %xmm0
	call	__printf_chk@PLT
	leaq	.LC5(%rip), %rdi
	call	puts@PLT
.L24:
	movq	88(%rsp), %rcx
	xorq	%fs:40, %rcx
	movl	%ebx, %eax
	jne	.L40
	addq	$104, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L35:
	.cfi_restore_state
	xorl	%ebp, %ebp
	jmp	.L25
.L33:
	leaq	.LC2(%rip), %rdi
	orl	$-1, %ebx
	call	puts@PLT
	jmp	.L24
.L40:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE42:
	.size	main, .-main
	.text
	.p2align 4,,15
	.globl	ImprimirTiempos
	.type	ImprimirTiempos, @function
ImprimirTiempos:
.LFB46:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$10, %edi
	movsd	%xmm2, 8(%rsp)
	movsd	%xmm5, (%rsp)
	call	putchar@PLT
	movsd	(%rsp), %xmm5
	leaq	.LC4(%rip), %rsi
	movsd	8(%rsp), %xmm2
	movl	$1, %edi
	movapd	%xmm5, %xmm0
	movl	$1, %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	subsd	%xmm2, %xmm0
	jmp	__printf_chk@PLT
	.cfi_endproc
.LFE46:
	.size	ImprimirTiempos, .-ImprimirTiempos
	.p2align 4,,15
	.globl	buscar
	.type	buscar, @function
buscar:
.LFB47:
	.cfi_startproc
	movslq	%ecx, %rax
	movl	$1, cuenta(%rip)
	cmpl	%esi, (%rdi,%rax,4)
	je	.L43
	movl	%edx, %r8d
	subl	%ecx, %r8d
	movl	%r8d, %eax
	shrl	$31, %eax
	addl	%r8d, %eax
	sarl	%eax
	addl	%ecx, %eax
	movslq	%eax, %r8
	movl	(%rdi,%r8,4), %r8d
	cmpl	%esi, %r8d
	je	.L43
	movslq	%edx, %r9
	cmpl	%esi, (%rdi,%r9,4)
	je	.L43
	cmpl	%esi, %r8d
	jg	.L52
	leal	1(%rax), %ecx
.L47:
	cmpl	%ecx, %edx
	jl	.L43
	movl	%edx, %eax
	movslq	%ecx, %r8
	movl	$2, cuenta(%rip)
	subl	%ecx, %eax
	sarl	%eax
	addl	%ecx, %eax
	cmpl	(%rdi,%r8,4), %esi
	je	.L43
	movslq	%eax, %r8
	movl	(%rdi,%r8,4), %r8d
	cmpl	%r8d, %esi
	jne	.L48
	jmp	.L53
	.p2align 4,,10
	.p2align 3
.L54:
	leal	-1(%rax), %edx
.L50:
	cmpl	%edx, %ecx
	jg	.L43
	movl	%edx, %eax
	addl	$1, cuenta(%rip)
	movslq	%ecx, %r8
	subl	%ecx, %eax
	sarl	%eax
	addl	%ecx, %eax
	cmpl	%esi, (%rdi,%r8,4)
	je	.L43
	movslq	%eax, %r8
	movl	(%rdi,%r8,4), %r8d
	cmpl	%esi, %r8d
	je	.L43
.L48:
	movslq	%edx, %r9
	cmpl	%esi, (%rdi,%r9,4)
	je	.L43
	cmpl	%r8d, %esi
	jl	.L54
	leal	1(%rax), %ecx
	jmp	.L50
	.p2align 4,,10
	.p2align 3
.L43:
	rep ret
	.p2align 4,,10
	.p2align 3
.L52:
	leal	-1(%rax), %edx
	jmp	.L47
.L53:
	rep ret
	.cfi_endproc
.LFE47:
	.size	buscar, .-buscar
	.p2align 4,,15
	.globl	funcion
	.type	funcion, @function
funcion:
.LFB48:
	.cfi_startproc
	movl	n(%rip), %edx
	movl	bus(%rip), %esi
	xorl	%ecx, %ecx
	call	buscar
	rep ret
	.cfi_endproc
.LFE48:
	.size	funcion, .-funcion
	.comm	n,4,4
	.comm	bus,4,4
	.globl	cuenta
	.bss
	.align 4
	.type	cuenta, @object
	.size	cuenta, 4
cuenta:
	.zero	4
	.globl	count
	.align 4
	.type	count, @object
	.size	count, 4
count:
	.zero	4
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	2696277389
	.long	1051772663
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
