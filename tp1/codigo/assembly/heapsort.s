#ifndef USE_MIPS_ASSEMBLY
#define USE_MIPS_ASSEMBLY
#include <mips/regdef.h>
#include <sys/syscall.h>


# Utilizacion de registros:
#
#	s1:	parametro WORDS		
#	s2: parametro ARRAYSIZE
#
#


			.text
			.align	2
			.globl	heapsort
			.extern	heap

heapsort:	subu	sp, sp, 0			# Creamos stack frame. 
			sw		ra, 16(sp)				
			sw		$fp, 12(sp)
			sw		gp, 8(sp)
			move	$fp, sp

			# Almacenamos los parámetros recibidos en fp
			sw		a0, 24($fp)		# words
			sw		a1, 28($fp)		# arraysize

			# Almacenamos los parametros guardados en fp en variables temp
			lw		

for_01:		

end_for_01:	


for_02:		

end_for_02:	

