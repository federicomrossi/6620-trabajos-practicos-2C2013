#ifndef USE_MIPS_ASSEMBLY
#define USE_MIPS_ASSEMBLY
#include <mips/regdef.h>
#include <sys/syscall.h>


.text
.align 2
.globl heap
.extern strcmpi

heap: 
	subu sp, sp, 40 #creo el SRA 16 y LTA 8 y ABA 16 = 40
	sw ra, 32(sp)
	sw $fp, 28(sp)
	sw gp, 24(sp)
	move $fp, sp
	sw a0, 40(sp) #Guardo los parametros en el ABA
	sw a1, 44(sp)
	sw a2, 48(sp) 
	#t1, sp+16  = tmp
	#t2, sp+20  = hijo  
loop:	#comparacion de while. No hago la comp de finished, Break instead
	sll t3, a1, 1 #raiz*2
	addi t3, t3, 1 #+1
	bgt t3, a2, fin_loop  # > fin
	#comparaciones de if
	subu t4, t3, a2
	beq t4, 0, if
	#Guardo todos los tmp porque llamo una funcion. No hay nada!
	sll t3, t3, 2 # x 4 #cuentas de arrays
	addu t5, a0, t3
	addiu t6, t5, 4
	lw a0, 0(t5) #Cargo los parametros
	lw a1, 0(t6)
	#Llamo a la funcion el return value viene en v0
	jal strcmpi
	#recupero los temp necesarios
	lw a1, 44(sp)
	lw a0, 40(sp)
	bgt v0, 0, if
	#hago el else
	sll t2, a1, 1
	addiu t2, t2, 2
	j fi 	
if:	#hago el if
	sll t2, a1, 1
	addi t2, t2, 1	
fi:	#Guardo los tmp necesarios
	sw t2, 16(sp)
	#cargo los parametrosi
	sll t2, t2, 2
	sll a1, a1, 2
	addu t3, a0, t2
	addu t4, a0, a1
	lw a0, 0(t4)
	lw a1, 0(t3) 
	#llamo a strcmp
	jal strcmpi
	blt v0, 0, if2
	#recupero los tmp necesarios. No hay nada!
	#hago el else
	j fin_loop
if2:	#hago el if
	#Recupero los tmp necesarios.
	lw a0, 40(sp)
	lw a1, 44(sp)
	lw a2, 48(sp)
	lw t2, 16(sp)
	#hago los intercambios
	sll t3, a1, 2 #Index raiz x4 para array
	sll t4, t2, 2 #Index hijo x4 para array
	addu t3, a0, t3
	addu t4, a0, t4
	lw t1, 0(t3) # cargo el valor de words[raiz]
	lw t5, 0(t4) # cargo el valor de words[hijo]
	sw t5, 0(t3)	#guardo en words[raiz] = words[hijo]
	sw t1, 0(t4) #guardo en words[hijo] = tmp
	sw t2, 44(sp) # raiz = hijo
	move a1, t2
	j loop
fin_loop:
	#destruyo el stack
	lw a0, 40(sp)
	lw a1, 44(sp)
	lw a2, 48(sp)
	lw ra, 32(sp)
	lw $fp, 28(sp)
	lw gp, 24(sp)
	addiu sp, sp, 40
	j ra
	
#endif
