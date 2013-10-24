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

#include <stdio.h>
#include <string.h>

void* malloc(size_t);
void* realloc(void*,size_t);
void free(void*);
extern heapsort(char**, int);

int main(int argc, char* argv[]) {
    char** palabras;
    int size=0;
	int tamano=200;
    int i;
	int tam;
	char* sourceName=argv[1];	
	char word[50];
	FILE* sourcefd;

	// Si hay pocos argumentos
	if (argc < 2) {
		fprintf(stderr, "ERROR: No hay suficientes argumentos\n");
		return 1;
	}

	// Se toma '-' como stdin
    if (sourceName[0] == '-')
        sourcefd = stdin;
    // Se abre el archvio correspondiente
    else {
        sourcefd = fopen(sourceName,"r");
        if (!sourcefd) {
        	fprintf(stderr, "El archivo no pudo ser abierto\n");
        	return 1;
        }
		// Si el archivo esta vacio
		fseek(sourcefd, 0, SEEK_END);
		if ( ftell(sourcefd) == 0 ) {
			fprintf(stderr, "El archivo esta vacio\n");
			return 1;
		}

		// Se vuelve al principio
		fseek(sourcefd, 0, SEEK_SET);
    }

	/* Cargo el archivo a memoria*/	
	palabras = (char**)malloc(tamano*sizeof(char*));
	

	fscanf (sourcefd,"%s",word);
	while (!feof(sourcefd)) {
		if (size >= tamano) {
			tamano+=200;
			palabras=(char**)realloc(palabras, tamano*sizeof(char*));
		}
		tam = strlen(word) + 1;
        if (palabras == NULL) {
	        fprintf(stderr, "\n\nNo se pueden alocar mas palabras\n\n");
	        break;
		}
		palabras[size] = malloc(tam);
		memcpy(palabras[size], word, tam);
		size++;
		fscanf(sourcefd,"%s", word);
	}
	// Se cierra el archivo si corresponde
	if (sourceName[0] != '-')
		fclose(sourcefd);
	
	/*Ordeno*/
    heapsort(palabras, size);
	
	/*Imprimo el resultado y libero memoria*/
    for (i=0;i<size;i++) {
        printf("%s ", palabras[i]);
    	free(palabras[i]);
	}
	free(palabras);

    return 0;
}
