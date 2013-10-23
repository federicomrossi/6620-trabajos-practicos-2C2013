/*
 ============================================================================
 Name         : tp1.c
 Authors      : Belen Beltran (91718)
 	 			Federico Martin Rossi (92086)
 	 			Pablo Rodriguez (93970)
 Version      : 1.0
 Description  : Programa de ordenamiento heapsort o bubblesort
 ============================================================================
 */

#include "heapsort.h"
#include "bubblesort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/** Funciones Auxiliares **/

// Devuelve la cantidad de palabras leidas
char** leerArchivo(char* sourceName, int* cant) {
    int size = 0;
	int tamano = 200;
	int tam;	
	char word[50];
	FILE* sourcefd;
	char** palabras;

	/* Cargo el archivo a memoria*/	
	palabras = (char**)malloc(tamano*sizeof(char*));

	// Se toma '-' como stdin
	if (sourceName[0] == '-')
		sourcefd = stdin;
	// Se abre el archvio correspondiente
	else
		sourcefd = fopen(sourceName,"r");

	fscanf(sourcefd, "%s", word);
	while (!feof(sourcefd)){
		if (size >= tamano){
			tamano += 200;
			palabras = (char**)realloc(palabras, tamano*sizeof(char*));
		}
		tam = strlen(word) + 1;
		if (palabras == NULL) {
			printf("%s ", word);
			printf("\n\nOhh ou\n\n");
		}
		palabras[size] = malloc(tam);
		memcpy(palabras[size], word, tam);
		size++;
		fscanf(sourcefd, "%s", word);
	}
	// Debug
	printf("Ultima pal: %s y cant de pal leidas: %d", word, size);
	// Se cierra el archivo si corresponde
	if (sourceName[0] != '-')
		fclose(sourcefd);

	*cant = size;

	return palabras;
}

void displayAyuda() {
	printf("%s", "Usage: ./tp1 [OPCION] [ARCHIVO]\n\
	\nOPCION:\n\
	-V, --version\tImprime la version del programa.\n\
	-h, --help\tImprime esta ayuda. \n\
	-b, --bubblesort\tEjecuta el algoritmo bubblesort en el ARCHIVO recibido por parametros.\n\
	-p, --heapsort\tEjecuta el algoritmo bubblesort en el ARCHIVO recibido por parametros.\n\
	NOTA: De no recibirse una OPCION, se podrán recibir nombres de ARCHIVO, resultando en la\
 concatenación e impresión por pantalla de estos.\
	\nEjemplos:\n\
	tp1 -b palabras.txt\n\
	tp1 -p palabras.txt\n");
}

void displayVersion() {
	printf("%s", "Esta aplicación ejecuta un ordenamiento sobre las palabras contenidas en un archivo.\
 Puede ejecutarse el algoritmo heapsort o bubblesort.\
	\nVersion: v1.0\n");
}

void ejecutarHeapsort(char* nombreArchivo) {
	int i, size;
	char** palabras = leerArchivo(nombreArchivo, &size);

	/*Ordeno*/
    heapsort_(palabras,size);
	
	/*Imprimo el resultado y libero memoria*/
    for(i=0;i<size;i++){
        printf("%s ",palabras[i]);
    	free(palabras[i]);
	}
	free(palabras);

	printf("\n");
}

void ejecutarBubblesort(char* nombreArchivo) {
	int i, size;
	char** palabras = leerArchivo(nombreArchivo, &size);

	/*Ordeno*/
    bubblesort_(palabras,size);
	
	/*Imprimo el resultado y libero memoria*/
    for(i=0;i<size;i++){
        printf("%s ",palabras[i]);
    	free(palabras[i]);
	}
	free(palabras);

	printf("\n");
}


int main (int argc, char* argv[]) {
	int c;

	if (argc < 2) {
		printf("Error: no se recibieron argumentos\n");
		return 1;
	}

	// while (1) {
	static struct option opciones[] = {
		// No setean flags
		{"help", no_argument, 0, 'h'},
		{"version", no_argument, 0, 'V'},
		{"bubble", required_argument, 0, 'b'},
		{"heap", required_argument, 0, 'p'},
		{0,0,0,0}
	};
	// getopt_long stores the option index here.
	int indice_opciones = -1;

	int hayOpciones = 0;

	while( (c = getopt_long (argc, argv, "hVb:p:", opciones, &indice_opciones)) != -1 ) {

		hayOpciones = 1;

		switch (c) {
			case 0:
				printf ("Estoy en 0. Option %s", opciones[indice_opciones].name);
				if (optarg)
					printf (" with arg %s", optarg);
				printf ("\n");
				break;

			case 'h':
				if (argc == 2)
					displayAyuda();
				break;

			case 'V':
				if (argc == 2)
					displayVersion();
				break;

			case 'p':
				if (argc == 3)
					ejecutarHeapsort(optarg);
				break;

			case 'b':
				if (argc == 3)
					ejecutarBubblesort(optarg);
				break;

			default:
				break;
		}
	 }
	 // Si hay argumentos que no son opciones, se buscan si nos nombres de archivo
	if (optind < argc && !hayOpciones) {
		printf ("No son opciones: ");
		while (optind < argc)
			printf ("%s ", argv[optind++]);
		putchar ('\n');
	}

	return 0;
 }
 
