#ifndef USE_MIPS_ASSEMBLY
#define USE_MIPS_ASSEMBLY
#include <mips/regdef.h>
#include <sys/syscall.h>


# Utilizacion de registros:
#
#	s0:	parametro WORDS		
#	s1: parametro ARRAYSIZE
#
#	t0: variable local "i"
#	t1:	variable local "tmp"
#	t2:	variable local auxiliar
#	t3:	variable local auxiliar
#	t4:	variable local auxiliar
#


			.text
			.align	2
			.globl	heapsort
			.extern	heap

heapsort:	subu	$sp,$sp,32				# Creamos stack frame. 
			sw		$ra,24($sp)				# Return address	
			sw		$fp,20($sp)				# Frame pointer
			sw		$gp,16($sp)				# Global pointer
			move	$fp,$sp					# Establecemos la base

			# Almacenamos los parámetros recibidos
			sw		$a0,32($sp)				# words
			sw		$a1,36($sp)				# arraysize

			# Almacenamos los parametros guardados en fp en variables
			lw		$s0,32($sp)				# words
			lw		$s1,36($sp)				# arraysize

			# Armamos el heap
			sll 	$t0,$s1,2 				# t0 = arraysize / 2
			subu	$t0,$t0,1 				# i = arraysize / 2 - 1			
FOR_1:		slt 	$t2,$t0,$zero			# ¿t0 es menor que 0?
			bne		$t2,$zero,FOR_1_FIN		# Si t2 = 1 saltamos a FOR_1_FIN
			
			add 	$a0,$s0,$zero			# Cargamos words en a0
			add 	$a1,$t0,$zero			# Cargamos i en a1
			add 	$a2,$s1,$zero			# Cargamos arraysize en a2
			jal		heap 					# Saltamos a funcion "heap"

			subu	$t0,$t0,1 				# i = i-1 (decrementamos i)
			j		FOR_1 					# Saltamos a etiqueta FOR_1

			# Iteramos sobre el heap intercambiando la raiz con el último
			# elemento del arreglo, rearmando luego un heap desde los indices 
			# 0 al n-1
FOR_1_FIN:	subu 	$t0,$s1,1 				# i = arraysize-1
FOR_2:		slti	$t2,$t0,1 				# ¿t0 es menor que 1?
			bne		$t2,$zero,FOR_2_FIN		# Si t2 = 0 saltamos a FOR_2_FIN
			
			lw 		$t1,0($a0)				# tmp = words[0]

			addu 	$t3,0($a0)
			addu 	$t4,$a0,$t0
			sw		$t3,0($t4)				# words[0] = words[i]
			
			sw 		$t4,$t1					# words[i] = tmp

			add 	$a0,$a0,$zero			# Cargamos words en a0
			add 	$a1,$zero,$zero			# Cargamos 0 en a1
			subi 	$a2,$t0,1 				# a2 = i -1
			jal		heap 					# Saltamos a funcion "heap"

			subu	$t0,$t0,1 				# i = i-1 (decrementamos i)
			j		FOR_2 					# Saltamos a etiqueta FOR_2

			# Reestablecemos valores iniciales
FOR_2_FIN:	move	$sp,$fp
			lw		$gp,16($sp)				# Global pointer
			lw		$fp,20($sp)				# Frame pointer
			lw		$ra,24($sp)				# Return address
			addi	$sp,$sp,32

			jr		$ra

#endif
