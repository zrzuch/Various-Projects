	.file	"SquareArea.c"
	.section	.rodata
.LC0:
	.string	"Feet for the length   ==> "
.LC1:
	.string	"%d"
.LC2:
	.string	"Inches for the length ==> "
.LC3:
	.string	"Feet for the width    ==> "
.LC4:
	.string	"Inches for the width  ==> "
	.align 4
.LC5:
	.string	"\nFor a room that is %d feet %d inches by %d feet %d inches,\n"
	.align 4
.LC6:
	.string	"  you will need %.1f square yards of carpet.\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x78,0x6
	.cfi_escape 0x10,0x3,0x2,0x75,0x7c
	subl	$16, %esp
	subl	$12, %esp
	# The next 2 lines print: Feet for the length   ==> 
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-12(%ebp), %eax
	pushl	%eax
	# The next 2 lines take an integer as input
	pushl	$.LC1
	call	__isoc99_scanf
	addl	$16, %esp
	subl	$12, %esp
	# The next 2 lines print: Inches for the length ==> 
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-16(%ebp), %eax
	pushl	%eax
	# The next 2 lines take an integer as input
	pushl	$.LC1
	call	__isoc99_scanf
	addl	$16, %esp
	subl	$12, %esp
	# The next 2 lines print: Feet for the width    ==> 
	pushl	$.LC3
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-20(%ebp), %eax
	pushl	%eax
	# The next 2 lines take an integer as input
	pushl	$.LC1
	call	__isoc99_scanf
	addl	$16, %esp
	subl	$12, %esp
	# The next 2 lines print: Inches for the width  ==> 
	pushl	$.LC4
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-24(%ebp), %eax
	pushl	%eax
	# The next 2 lines take an integer as input
	pushl	$.LC1
	call	__isoc99_scanf
	addl	$16, %esp
	movl	-24(%ebp), %ebx
	movl	-20(%ebp), %ecx
	movl	-16(%ebp), %edx
	movl	-12(%ebp), %eax
	subl	$12, %esp
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	pushl	%eax
	# The next 2 lines print: \nFor a room that is %d feet %d inches by %d feet %d inches,\n
	pushl	$.LC5
	call	printf
	addl	$32, %esp
	# The next 8 lines move and push the values for the findArea call 
	movl	-24(%ebp), %ebx
	movl	-20(%ebp), %ecx
	movl	-16(%ebp), %edx
	movl	-12(%ebp), %eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	pushl	%eax
	# calls findArea to be printed in the printf
	call	findArea
	addl	$16, %esp
	subl	$4, %esp
	leal	-8(%esp), %esp
	fstpl	(%esp)
	# The next 2 lines print:   you will need %.1f square yards of carpet.\n
	pushl	$.LC6
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leal	-8(%ebp), %esp
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.globl	convertFeetAndInchesToYards
	.type	convertFeetAndInchesToYards, @function
convertFeetAndInchesToYards:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	# Next 2 lines loads floating point values for the calculation
	fildl	8(%ebp)
	fildl	12(%ebp)
	fldl	.LC8
	# floating point division by 12 which is indicated in my code
	fdivrp	%st, %st(1)
	# floating point addition
	faddp	%st, %st(1)
	fldl	.LC9
	# floating point division by 3 which is indicated in my code
	fdivrp	%st, %st(1)
	fstps	-4(%ebp)
	flds	-4(%ebp)
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	convertFeetAndInchesToYards, .-convertFeetAndInchesToYards
	.globl	findArea
	.type	findArea, @function
findArea:
.LFB4:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	# Pushes the values to the call of convertFeetAndInchesToYards
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	convertFeetAndInchesToYards
	addl	$8, %esp
	fstps	-4(%ebp)
	# Pushes the values to the call of convertFeetAndInchesToYards
	pushl	20(%ebp)
	pushl	16(%ebp)
	call	convertFeetAndInchesToYards
	addl	$8, %esp
	# Multiplies the values for the final square yards answer
	fmuls	-4(%ebp)
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	findArea, .-findArea
	.section	.rodata
	.align 8
.LC8:
	.long	0
	.long	1076363264
	.align 8
.LC9:
	.long	0
	.long	1074266112
	.ident	"GCC: (GNU) 5.2.0"
	.section	.note.GNU-stack,"",@progbits
