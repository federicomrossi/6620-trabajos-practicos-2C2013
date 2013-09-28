#ifndef USE_MIPS_ASSEMBLY
#define USE_MIPS_ASSEMBLY
#include <mips/regdef.h>
#include <sys/syscall.h>

.text
.align 2
.globl swap



swap:
		subu sp,sp,48		# creo stack frame
		sw $fp,12(sp)
		sw gp,8(sp)
		move $fp,sp
		sw s0,16(sp)
		sw s1,20(sp)
		sw s2,24(sp)
		sw s3,28(sp)
		sw s4,32(sp)
		sw s5,36(sp)
		sw s6,40(sp)
		sw s7,44(sp)

		#Guardo los parametros recibidos en fp
		sw a0,48($fp)		
		sw a1,52($fp) 		
		sw a2,56($fp)

		##Guardo en variables auxiliares las direcciones de memoria a intercambiar
		lw t0, 48($fp)		#en 48 esta el words
		lw t1, 52($fp)		#en 52 esta el i
		lw t2, 56($fp)		#en 56 esta el j

		##Realizo el intercambio
		#t3 = direccion de fp+(i*4)
		#t4 = direccion de fp+(j+4)
		sll t1, t1, 2
		sll t2, t2, 2
		addu t1, t1, t0
		addu t2, t2, t0


		#Cargo los elementos a intercambiar en t3 y t4
		lw t3, 0(t1)
		lw t4, 0(t2)

		#Guardo los elementos de manera intercambiada
		sw t4, 0(t1)
		sw t3, 0(t2)


		lw v0, 0(t2) 

		##Comienzo retorno
		lw s7, 44(sp)
		lw s6, 40(sp)
		lw s5, 36(sp)
		lw s4, 32(sp)
		lw s3, 28(sp)
		lw s2, 24(sp)
		lw s1, 20(sp)
		lw s0, 16(sp)		

		move sp, $fp
		lw gp, 8(sp)
		lw $fp, 12(sp)
		addiu sp, sp, 48
		jr ra			#ra = return address es la direccion a la q quiero volver luego de llamar la funcion

#endif
