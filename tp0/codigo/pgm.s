	.file	1 "pgm.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.rdata
	.align	2
$LC0:
	.ascii	"%d\000"
	.align	2
$LC1:
	.ascii	"\n\000"
	.text
	.align	2
	.globl	escribirLinea
	.ent	escribirLinea
escribirLinea:
	.frame	$fp,64,$31		# vars= 24, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,64
	.cprestore 16
	sw	$31,56($sp)
	sw	$fp,52($sp)
	sw	$28,48($sp)
	move	$fp,$sp
	sw	$4,64($fp)
	sw	$5,68($fp)
	move	$2,$6
	sb	$2,24($fp)
	lw	$2,64($fp)
	srl	$2,$2,3
	sw	$2,32($fp)
	lbu	$2,64($fp)
	andi	$2,$2,0x7
	sb	$2,36($fp)
	sw	$0,40($fp)
	sw	$0,28($fp)
$L6:
	lw	$2,28($fp)
	lw	$3,64($fp)
	sltu	$2,$2,$3
	bne	$2,$0,$L9
	b	$L7
$L9:
	lb	$2,24($fp)
	lw	$4,68($fp)
	la	$5,$LC0
	move	$6,$2
	la	$25,fprintf
	jal	$31,$25
	lw	$2,40($fp)
	addu	$2,$2,1
	sw	$2,40($fp)
	lbu	$2,36($fp)
	beq	$2,$0,$L11
	lw	$2,32($fp)
	addu	$3,$2,1
	lw	$2,40($fp)
	beq	$2,$3,$L12
	b	$L8
$L11:
	lw	$3,40($fp)
	lw	$2,32($fp)
	beq	$3,$2,$L12
	b	$L8
$L12:
	lb	$2,24($fp)
	xori	$2,$2,0x0
	sltu	$2,$2,1
	sb	$2,24($fp)
	lbu	$2,36($fp)
	beq	$2,$0,$L13
	lbu	$2,36($fp)
	addu	$2,$2,-1
	sb	$2,36($fp)
$L13:
	sw	$0,40($fp)
$L8:
	lw	$2,28($fp)
	addu	$2,$2,1
	sw	$2,28($fp)
	b	$L6
$L7:
	lw	$4,68($fp)
	la	$5,$LC1
	la	$25,fprintf
	jal	$31,$25
	move	$sp,$fp
	lw	$31,56($sp)
	lw	$fp,52($sp)
	addu	$sp,$sp,64
	j	$31
	.end	escribirLinea
	.size	escribirLinea, .-escribirLinea
	.rdata
	.align	2
$LC2:
	.ascii	"-\000"
	.align	2
$LC3:
	.ascii	"w\000"
	.align	2
$LC4:
	.ascii	"P2\n"
	.ascii	"%d\n"
	.ascii	"%d\n"
	.ascii	"1\n\000"
	.text
	.align	2
	.globl	pgm
	.ent	pgm
pgm:
	.frame	$fp,64,$31		# vars= 24, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,64
	.cprestore 16
	sw	$31,56($sp)
	sw	$fp,52($sp)
	sw	$28,48($sp)
	move	$fp,$sp
	sw	$4,64($fp)
	sw	$5,68($fp)
	sw	$6,72($fp)
	li	$2,1			# 0x1
	sb	$2,32($fp)
	lw	$2,68($fp)
	srl	$2,$2,3
	sw	$2,36($fp)
	lbu	$2,68($fp)
	andi	$2,$2,0x7
	sb	$2,40($fp)
	sw	$0,44($fp)
	lw	$4,72($fp)
	la	$5,$LC2
	la	$25,strcmp
	jal	$31,$25
	bne	$2,$0,$L15
	la	$2,__sF+88
	sw	$2,24($fp)
	b	$L16
$L15:
	lw	$4,72($fp)
	la	$5,$LC3
	la	$25,fopen
	jal	$31,$25
	sw	$2,24($fp)
$L16:
	lw	$4,24($fp)
	la	$5,$LC4
	lw	$6,64($fp)
	lw	$7,68($fp)
	la	$25,fprintf
	jal	$31,$25
	sw	$0,28($fp)
$L17:
	lw	$2,28($fp)
	lw	$3,68($fp)
	sltu	$2,$2,$3
	bne	$2,$0,$L20
	b	$L18
$L20:
	lb	$2,32($fp)
	lw	$4,64($fp)
	lw	$5,24($fp)
	move	$6,$2
	la	$25,escribirLinea
	jal	$31,$25
	lw	$2,44($fp)
	addu	$2,$2,1
	sw	$2,44($fp)
	lbu	$2,40($fp)
	beq	$2,$0,$L22
	lw	$2,36($fp)
	addu	$3,$2,1
	lw	$2,44($fp)
	beq	$2,$3,$L23
	b	$L19
$L22:
	lw	$3,44($fp)
	lw	$2,36($fp)
	beq	$3,$2,$L23
	b	$L19
$L23:
	lb	$2,32($fp)
	xori	$2,$2,0x0
	sltu	$2,$2,1
	sb	$2,32($fp)
	lbu	$2,40($fp)
	beq	$2,$0,$L24
	lbu	$2,40($fp)
	addu	$2,$2,-1
	sb	$2,40($fp)
$L24:
	sw	$0,44($fp)
$L19:
	lw	$2,28($fp)
	addu	$2,$2,1
	sw	$2,28($fp)
	b	$L17
$L18:
	lw	$3,24($fp)
	la	$2,__sF+88
	beq	$3,$2,$L14
	lw	$4,24($fp)
	la	$25,fclose
	jal	$31,$25
$L14:
	move	$sp,$fp
	lw	$31,56($sp)
	lw	$fp,52($sp)
	addu	$sp,$sp,64
	j	$31
	.end	pgm
	.size	pgm, .-pgm
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"
