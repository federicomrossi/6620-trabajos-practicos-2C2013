/*
 ============================================================================
 Name         : tp1.c
 Authors      : Belen Beltran (91718)
 	 			Federico Martin Rossi (92086)
 	 			Pablo Rodriguez (93970)
 Version      : 1.0
 Description  : Programa de 
 ============================================================================
 */

#include "heapsort.h"
#include "bubblesort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char** palabras;
    int size=0;
	int tamano=200;
    int i;
	int tam;
	char* sourceName=argv[1];	
	char word[50];
	FILE* sourcefd;

	/* Cargo el archivo a memoria*/	
	palabras = malloc(tamano*sizeof(char*));
	sourcefd = fopen(sourceName,"r");
	fscanf(sourcefd,"%s",word);
	while(!feof(sourcefd)){
		tam=strlen(word)+1;
		palabras[size]=malloc(tam);
		memcpy(palabras[size],word,tam);
		size++;
		if(size > tamano){
			tamano+=200;
			palabras=realloc(palabras,tamano*sizeof(char*));
		}
		fscanf(sourcefd,"%s",word);
	}
	fclose(sourcefd);
	
	/*Ordeno*/
    heapsort(palabras,size);
	
	/*Imprimo el resultado y libero memoria*/
    for(i=0;i<size;i++){
        printf("%s ",palabras[i]);
    	free(palabras[i]);
	}
	free(palabras);

    return 0;
}
