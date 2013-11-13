/*
 ============================================================================
 Name         : tp1.c
 Authors      : Belen Beltran (91718)
 	 			Federico Martin Rossi (92086)
 	 			Pablo Rodriguez (93970)
 Version      : 1.0
 Description  : Programa de ordenamiento heapsort
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "bubblesort.h"

void* malloc(size_t);
void* realloc(void*,size_t);
void free(void*);
int system(const char* cadena);
extern heapsort(char**, int);

/** Funciones Auxiliares **/
void readWord(FILE* fd,char* word){
	int index=0;
	int c;
	while((c=getc(fd))!=EOF && c!=32 && c!='\n'  && index < 49){
		if((c>=48 && c<=57) || (c>=65 && c<=90) ||
			(c>=97 && c<=122) || (c>=130 && c<=165)){
			word[index++]=c;
		}
	}
	word[index]='\0';
}

// Devuelve la cantidad de palabras leidas
char** leerArchivo(char* sourceName, int* cant) {
    int size = 0;
	int tamano = 5000;
	int tam;	
	char word[50];
	FILE* sourcefd;
	char** palabras;

	
	// Se toma '-' como stdin
    if (sourceName[0] == '-')
        sourcefd = stdin;
    // Se abre el archvio correspondiente
    else {
        sourcefd = fopen(sourceName,"r");
        if (!sourcefd) {
        	fprintf(stderr, "El archivo no pudo ser abierto\n");
        	return 0;
        }
		// Si el archivo esta vacio
		fseek(sourcefd, 0, SEEK_END);
		if ( ftell(sourcefd) == 0 ) {
			fprintf(stderr, "El archivo esta vacio\n");
			return 0;
		}

		// Se vuelve al principio
		fseek(sourcefd, 0, SEEK_SET);
    }

	/* Cargo el archivo a memoria*/	
	palabras = (char**)malloc(tamano*sizeof(char*));

	// Se toma '-' como stdin
	if (sourceName[0] == '-')
		sourcefd = stdin;
	// Se abre el archvio correspondiente
	else
		sourcefd = fopen(sourceName,"r");

	readWord(sourcefd,word);
	while (!feof(sourcefd)){
		if (size >= tamano){
			tamano += 5000;
			palabras = (char**)realloc(palabras, tamano*sizeof(char*));
		}
		tam = strlen(word) + 1;
		if (palabras == NULL) {
			fprintf(stderr,"\n\nNo se pueden alocar mas palabras\n\n");
			break;
		}
		palabras[size] = malloc(tam);
		memcpy(palabras[size], word, tam);
		size++;
		readWord(sourcefd, word);
	}
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
	NOTA: De no recibirse una OPCION, se podran recibir nombres de ARCHIVO, resultando en la\
 concatenacion e impresion por pantalla de estos.\
	\nEjemplos:\n\
	tp1 -b palabras.txt\n\
	tp1 -p palabras.txt\n");
}

void displayVersion() {
	printf("%s", "Esta aplicacion ejecuta un ordenamiento sobre las palabras contenidas en un archivo.\
 Puede ejecutarse el algoritmo heapsort o bubblesort.\
	\nVersion: v1.0\n");
}

void ejecutarHeapsort(char* nombreArchivo) {
	int i, size;
	char** palabras = leerArchivo(nombreArchivo, &size);

	if (!palabras)
		return;

	/*Ordeno*/
    heapsort(palabras,size);
	
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

	if (!palabras)
		return;

	/*Ordeno*/
    bubblesort(palabras,size);
	
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

	// Si hay pocos argumentos
	if (argc < 2) {
		fprintf(stderr, "ERROR: No hay suficientes argumentos\n");
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
		char op[256];
		while (optind < argc) {
			sprintf(op, "cat %s", argv[optind++]);
			system(op);
		}
	}

	return 0;
 }