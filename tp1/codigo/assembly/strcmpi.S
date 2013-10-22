#ifndef USE_MIPS_ASSEMBLY
#define USE_MIPS_ASSEMBLY
#include <mips/regdef.h>
#include <sys/syscall.h>

# strcmpi.s : 	Evalua dos strings para ver si son equivalentes o no.
# 				No toma en cuenta mayusculas y minusculas para la evaluacion.
#
# Variables: 
#				- a0 -> dir del primer array
#				- a1 -> dir del segundo array
#				- t1 -> int i (indice)
#				- t2 -> puntero para recorrer el array 'a'
#				- t3 -> puntero para recorrer el array 'b'
# Auxiliares:
#				- t4
#				- t5 
#				- t6

.text
.align 2
.globl strcmpi


strcmpi:		subu sp, sp, 8 # Se crea el SRA 8 y LTA 0 y ABA 0 = 8 bytes
		        sw $30, 4(sp)
		        sw gp, 0(sp)
		        move $30, sp
#		        lw a0, 8(sp) # Se guarda el primer argumento, el puntero al array 'a'
#		        lw a1, 12(sp) # Se guarda el segundo argumento, el puntero al array 'b'

		        addu t1, zero, zero # Se setea i = 0

recorrer: 		addu t5, t1, a0 # t5 <- direccion de a[i]
				lb t2, 0(t5) # t2 <- a[i]
				addu t5, t1, a1 # t5 <- direccion de b[i]
				lb t3, 0(t5) # t3 <- b[i]

				beq t2, zero, terminoA # Si 'a' termina, se analiza si 'b' tambien
				beq t3, zero, terminoB # Si 'b' termina, se analiza si 'a' tambien
				beq t2, t3, sonIguales # Si son iguales, sigo analizando otra letra. Sino veo mayusculas y minusculas

				addu t4, t2, zero # Se copia el valor de t2 en t4
				addu t6, t4, zero # Se copia el valor de t4 en t6

caseSensitive:	slti t5, t4, 90 # Se chequea si puede ser un char en mayusculas. (char < 90) -> 1
				beq t5, zero, continue # Si no esta la posibilidad, se continua
				slti t5, t4, 65 # Se chequea si es una letra mayuscula realmente. (char < 65) -> 1
				bne t5, zero, continue # Si no es mayuscula, se continua

				addu t6, t4, zero # Se guarda el valor de t4 para analizar corte
				addiu t4, t4, 32 # Se transforma en minusculas
				
continue:		beq t6, t3, stop # Si se analizo la 2da letra, se sale del ciclo

				addu t2, t4, zero # Sino, se guarda lo recien calculado en t2
				addu t4, t3, zero # Se copia el valor de t3 en t4	
				addu t6, t4, zero # Se copia el valor de t4 en t6		
				b caseSensitive # Y se analiza la 2da letra


stop:			addu t3, t4, zero # Se guarda lo calculado en t3
				bne t2, t3, salirDistintas # Son distintas

sonIguales:		addiu t1, t1, 1 # i += 1
				b recorrer # Se continua el loop

terminoA:		beq t3, zero, salirIguales # Si 'b' termina, se trata de dos cadenas iguales
				b salirDistintas # Sino, se trata de cadenas diferentes

terminoB:		beq t2, zero, salirIguales # Si 'a' termina, se trata de dos cadenas iguales
				b salirDistintas # Sino, se trata de cadenas diferentes

salirDistintas:	addiu v0, zero, 1 # Se devuelve un 1
				b salir

salirIguales:	addu v0, zero, zero # Se devuelve un 0
				b salir

salir:			lw $30, 4(sp)
		        lw gp, 0(sp)
		        addiu sp, sp, 8
		        j ra
#endif
