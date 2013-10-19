/*
 ============================================================================
 Name         : tp1.c
 Authors      : Belen Beltran (91718)
 	 			Federico Martin Rossi (92086)
 	 			Pablo Rodriguez (93970)
 Version      : 1.0
 Description  : Programa de dibujo de tableros de Ajedrez en formato PGM
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "heapsort.h"

int main(int argc, char* argv[]) {
    char* palabras[]={"hola","pablo","belu","fede"};
    int size=4;
    int i;
    heapsort(palabras,size);
    for(i=0;i<size;i++){
        printf("%s\n",palabras[i]);
    }
    return 0;
}
