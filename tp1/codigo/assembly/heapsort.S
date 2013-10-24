#ifndef USE_MIPS_ASSEMBLY
#define USE_MIPS_ASSEMBLY
#include <mips/regdef.h>
#include <sys/syscall.h>


# Utilizacion de registros:
#
#	s0: words
#	s1:	arraysize
#	s2: variable local "i"
#	s3:	variable local "tmp"
#	t0:	variable local auxiliar
#	t1:	variable local auxiliar
#


.text
.align	2
.globl	heapsort
.extern	heap

			# ABA: 16; SRA: 16; LTA:24
heapsort:	subu	sp,sp,56				# Creamos stack frame. 
			sw		ra,52(sp)				# Return address	
			sw		$fp,48(sp)				# Frame pointer
			sw		gp,44(sp)				# Global pointer
			move	$fp,sp					# Establecemos la base

			# Almacenamos contenido de registros
			sw 		s0,40(sp)
			sw		s1,36(sp)
			sw		s2,32(sp)
			sw		s3,28(sp)			

			# Almacenamos los parametros recibidos
			sw		a0,56(sp)				# words
			sw		a1,60(sp)				# arraysize

			# Almacenamos los parametros guardados en fp en variables
			move	s0,a0					# words
			move	s1,a1 					# arraysize

			# Armamos el heap
			srl 	t0,s1,1 				# t0 = arraysize / 2
			subu	s2,t0,1 				# i = arraysize / 2 - 1			
FOR_1:		slt 	t0,s2,zero				# i es menor que 0
			bne		t0,zero,FOR_1_FIN		# Si t0 = 1 saltamos a FOR_1_FIN
			
			add 	a1,s2,zero				# Cargamos i en a1
			subu 	a2,s1,1 				# Cargamos arraysize-1 en a2
			jal		heap 					# Saltamos a funcion "heap"

			subu	s2,s2,1 				# i = i-1 (decrementamos i)
			j		FOR_1 					# Saltamos a etiqueta FOR_1

			# Iteramos sobre el heap intercambiando la raiz con el ultimo
			# elemento del arreglo, rearmando luego un heap desde los indices 
			# 0 al n-1
FOR_1_FIN:	subu 	s2,s1,1 				# i = arraysize-1
FOR_2:		beq		s2,zero,FOR_2_FIN		# Si i = 0 saltamos a FOR_2_FIN
			
			lw 		s3,0(s0)				# tmp = words[0]
			sll 	t1,s2,2 				# t1 = i * 4
			add 	t1,t1,s0				# t1 = words[i]
			lw		t2,0(t1)				# t2 = dato words[i]
			sw		t2,0(s0)				# words[0] = words[i]
			sw 		s3,0(t1)				# words[i] = tmp

			add 	a0,s0,zero				# Cargamos words en a0
			add 	a1,zero,zero			# Cargamos 0 en a1
			subu 	a2,s2,1 				# a2 = i -1
			jal		heap 					# Saltamos a funcion "heap"

			subu	s2,s2,1 				# i = i-1 (decrementamos i)
			j		FOR_2 					# Saltamos a etiqueta FOR_2

			# Reestablecemos valores iniciales
FOR_2_FIN:	lw		a0,56(sp)				# words
			lw		a1,60(sp)				# arraysize

			lw 		s0,40(sp)
			lw		s1,36(sp)
			lw		s2,32(sp)
			lw		s3,28(sp)
			
			move	sp,$fp
			lw		gp,44(sp)				# Global pointer
			lw		$fp,48(sp)				# Frame pointer
			lw		ra,52(sp)				# Return address
			addi	sp,sp,56

			jr		ra

#endif
