#ifndef USE_MIPS_ASSEMBLY
#define USE_MIPS_ASSEMBLY
#include <mips/regdef.h>
#include <sys/syscall.h>

.text
.align 2
.globl shellsort
.extern swap
.extern compare


shellsort:	subu sp,sp,24		# creo stack frame, es de 24 porque necesito guardar ra
		sw ra,16(sp)		
		sw $fp,12(sp)
		sw gp,8(sp)
		move $fp,sp

		#Guardo los parametros recibidos en fp
		sw a0,24($fp)		# words = char **
		sw a1,28($fp) 		# size

		#Guardo los parametros cargados en fp a variables temporales
		lw s6, 24($fp)		#en 24 esta el words
		lw s7, 28($fp)		#en 28 esta el size

		#Iniciaizo variables locales
		srl s0, s7, 1		# intervalo = size/2
		li s1, 0		# k
		li s2, 0		# j
		li s3, 0		# i
		li s4, 0		# sAux


		#add v0, s0, zero	
		#j fin

		#while(intervalo > 0)
loop1:		bgt s0, zero, initloop2	#branch grater than, salta si s0 es mayor a 0
		j fin

		#for(i = intervalo-1; i < arraysize; i++)	
initloop2:	addi s3, s0, -1		# i = interlvalo - 1
loop2:		bge s3, s7, endloop2	# si i >= size fin de for, bge=branch greater than or equal
		sub s2, s3, s0		#j = i - intervalo;
	

		#while(j >= 0)
loop3:		bge s2, zero, loop3task
		addi s3, s3, 1
		j loop2

	


loop3task:	add s1, s2, s0		#k = j + intervalo;

		#Para comparar cadenas, la forma mas sencilla es iterar sobre cada caracter de cada cadena, y restarlos. Si el resultado es 0, son 
#iguales. Si no, a continuacion, si el resultado es> 0, entonces la primera cadena es mayor de que la otra cadena, de lo contrario la segunda cadena es inferior y #habria que intercambiarlas. Si te quedas sin alguna de las cadenas antes que el otro, y son iguales hasta llegar a ese punto, la cadena mas corta es menor que el que #mas.
		#CARGO LAS CADENAS A COMPARAR
		#words[j]
		##Guardo en variables auxiliares las direcciones de memoria a intercambiar
		#words = s6
		#Guardo i y j por q las voy a modificar y no las quiero perder
		sw s1, 0($fp)
		sw s2, 4($fp)



		sll s1, s1, 2
		sll s2, s2, 2
		addu s1, s1, s6
		addu s2, s2, s6

		#Cargo los strings a comparar en ax que luego compare utiliza para trabajar
		lw a0, 0(s1)		#OPTIMIZAR CODIGO PARA ISAR MENOS ti
		lw a1, 0(s2)			
		jal compare		#llamo a compare

		lw s1, 0($fp)		#Cargo el valor de k en stack
		lw s2, 4($fp)		#Cargo el valor de j en stack

		bltz v0, swapping	#swap si compare > 0
		add s2, zero, zero	#j=0		
		j endif

		# poner el valor a utilizar en los registros correctos y llamar a swap
swapping:	add a0, s6,0
		add a1, s1, 0
		add a2, s2, 0
		jal swap

endif:		sub s2, s2, s0		#j = j - intervalo;
		j loop3


endloop2:	srl s0, s0, 1		#intervalo = intervalo / 2;
		j loop1



		##Comienzo retorno
fin:		move sp, $fp
		lw gp, 8(sp)
		lw $fp, 12(sp)
		lw ra, 16(sp)
		addiu sp, sp, 24
		jr ra			#ra = return address es la direccion a la q quiero volver luego de llamar la funcion

#endif
