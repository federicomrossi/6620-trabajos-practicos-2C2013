	.file	1 "orgaCompus.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.rdata
	.align	2
$LC0:
	.ascii	"%s\000"
	.align	2
$LC1:
	.ascii	"<- Help display ->\n"
	.ascii	"Usage:\n"
	.ascii	" \ttp0 -h\n"
	.ascii	"\ttp0 -V\n"
	.ascii	"\ttp0 [options]\n"
	.ascii	"\t\n"
	.ascii	"Options:\n"
	.ascii	"\t-V, --version Print version and quit.\n"
	.ascii	"\t-h, --help Print this information. \n"
	.ascii	"\t-r, --resolution Set bitmap resolution to WxH pixels.\n"
	.ascii	"\t-o, --output Path to output file.\n"
	.ascii	"\t\n"
	.ascii	"Examples:\n"
	.ascii	"\ttp0 -o output.pgm\n"
	.ascii	"\ttp0 -r 800x600 -o file.pgm \n"
	.ascii	"<- End of help display ->\n\000"
	.text
	.align	2
	.globl	displayHelp
	.ent	displayHelp
displayHelp:
	.frame	$fp,40,$31		# vars= 0, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,40
	.cprestore 16
	sw	$31,32($sp)
	sw	$fp,28($sp)
	sw	$28,24($sp)
	move	$fp,$sp
	la	$4,$LC0
	la	$5,$LC1
	la	$25,printf
	jal	$31,$25
	move	$sp,$fp
	lw	$31,32($sp)
	lw	$fp,28($sp)
	addu	$sp,$sp,40
	j	$31
	.end	displayHelp
	.size	displayHelp, .-displayHelp
	.rdata
	.align	2
$LC2:
	.ascii	"This program draws chess boards in PGM file format\t\n"
	.ascii	"Version: v1.0\n\000"
	.text
	.align	2
	.globl	displayVersion
	.ent	displayVersion
displayVersion:
	.frame	$fp,40,$31		# vars= 0, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,40
	.cprestore 16
	sw	$31,32($sp)
	sw	$fp,28($sp)
	sw	$28,24($sp)
	move	$fp,$sp
	la	$4,$LC0
	la	$5,$LC2
	la	$25,printf
	jal	$31,$25
	move	$sp,$fp
	lw	$31,32($sp)
	lw	$fp,28($sp)
	addu	$sp,$sp,40
	j	$31
	.end	displayVersion
	.size	displayVersion, .-displayVersion
	.align	2
	.globl	getXY
	.ent	getXY
getXY:
	.frame	$fp,48,$31		# vars= 8, regs= 4/0, args= 16, extra= 8
	.mask	0xd0010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,48
	.cprestore 16
	sw	$31,44($sp)
	sw	$fp,40($sp)
	sw	$28,36($sp)
	sw	$16,32($sp)
	move	$fp,$sp
	sw	$4,48($fp)
	sw	$5,52($fp)
	sw	$6,56($fp)
	lw	$4,48($fp)
	li	$5,120			# 0x78
	la	$25,strchr
	jal	$31,$25
	sw	$2,24($fp)
	lw	$2,24($fp)
	bne	$2,$0,$L21
	lw	$4,48($fp)
	li	$5,88			# 0x58
	la	$25,strchr
	jal	$31,$25
	sw	$2,24($fp)
	lw	$2,24($fp)
	bne	$2,$0,$L21
	b	$L19
$L21:
	lw	$16,52($fp)
	lw	$4,48($fp)
	la	$25,atoi
	jal	$31,$25
	sw	$2,0($16)
	lw	$16,56($fp)
	lw	$2,24($fp)
	addu	$2,$2,1
	move	$4,$2
	la	$25,atoi
	jal	$31,$25
	sw	$2,0($16)
$L19:
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	lw	$16,32($sp)
	addu	$sp,$sp,48
	j	$31
	.end	getXY
	.size	getXY, .-getXY
	.rdata
	.align	2
$LC3:
	.ascii	"hVr:o:\000"
	.align	2
$LC4:
	.ascii	"Error: Unknown option selected.\n\000"
	.text
	.align	2
	.globl	main
	.ent	main
main:
	.frame	$fp,72,$31		# vars= 32, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,72
	.cprestore 16
	sw	$31,64($sp)
	sw	$fp,60($sp)
	sw	$28,56($sp)
	move	$fp,$sp
	sw	$4,72($fp)
	sw	$5,76($fp)
	sw	$0,28($fp)
	li	$2,1			# 0x1
	sw	$2,32($fp)
	sw	$0,36($fp)
	li	$2,8			# 0x8
	sw	$2,40($fp)
	li	$2,8			# 0x8
	sw	$2,44($fp)
$L23:
	lw	$4,72($fp)
	lw	$5,76($fp)
	la	$6,$LC3
	la	$25,getopt
	jal	$31,$25
	sw	$2,24($fp)
	lw	$3,24($fp)
	li	$2,-1			# 0xffffffffffffffff
	beq	$3,$2,$L24
	lw	$2,28($fp)
	bne	$2,$0,$L24
	lw	$2,32($fp)
	sll	$3,$2,2
	lw	$2,76($fp)
	addu	$2,$3,$2
	lw	$2,0($2)
	addu	$2,$2,2
	lb	$2,0($2)
	bne	$2,$0,$L27
	lw	$2,32($fp)
	addu	$2,$2,2
	sw	$2,32($fp)
	lw	$2,24($fp)
	sw	$2,48($fp)
	li	$2,104			# 0x68
	lw	$3,48($fp)
	beq	$3,$2,$L29
	lw	$3,48($fp)
	slt	$2,$3,105
	beq	$2,$0,$L35
	li	$2,86			# 0x56
	lw	$3,48($fp)
	beq	$3,$2,$L30
	b	$L33
$L35:
	li	$2,111			# 0x6f
	lw	$3,48($fp)
	beq	$3,$2,$L32
	li	$2,114			# 0x72
	lw	$3,48($fp)
	beq	$3,$2,$L31
	b	$L33
$L29:
	la	$25,displayHelp
	jal	$31,$25
	li	$2,1			# 0x1
	sw	$2,28($fp)
	b	$L23
$L30:
	la	$25,displayVersion
	jal	$31,$25
	li	$2,1			# 0x1
	sw	$2,28($fp)
	b	$L23
$L31:
	addu	$2,$fp,40
	addu	$3,$fp,44
	lw	$4,optarg
	move	$5,$2
	move	$6,$3
	la	$25,getXY
	jal	$31,$25
	b	$L23
$L32:
	lw	$2,optarg
	sw	$2,36($fp)
	li	$2,1			# 0x1
	sw	$2,28($fp)
	b	$L23
$L33:
	li	$2,1			# 0x1
	sw	$2,28($fp)
	la	$4,$LC4
	la	$25,printf
	jal	$31,$25
	la	$25,displayHelp
	jal	$31,$25
	b	$L23
$L27:
	li	$2,1			# 0x1
	sw	$2,28($fp)
	la	$4,$LC4
	la	$25,printf
	jal	$31,$25
	la	$25,displayHelp
	jal	$31,$25
	b	$L23
$L24:
	lw	$2,36($fp)
	beq	$2,$0,$L37
	lw	$4,40($fp)
	lw	$5,44($fp)
	lw	$6,36($fp)
	la	$25,pgm
	jal	$31,$25
$L37:
	move	$2,$0
	move	$sp,$fp
	lw	$31,64($sp)
	lw	$fp,60($sp)
	addu	$sp,$sp,72
	j	$31
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"
