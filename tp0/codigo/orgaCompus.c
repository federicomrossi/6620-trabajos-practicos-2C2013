/*
 ============================================================================
 Name        : OrgaCompus.c
 Author      : Belen Beltran
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//#include "pgm.h"

#define MAX_NAME 256

//* Funciones Auxiliares *//

void displayHelp() {
	printf("%s", "Usage:\n \
	tp0 -h\n\
	tp0 -V\n\
	tp0 [options]\n\
	\nOptions:\n\
	-V, --version Print version and quit.\n\
	-h, --help Print this information. \n\
	-r, --resolution Set bitmap resolution to WxH pixels.\n\
	-o, --output Path to output file.\n\
	\nExamples:\n\
	tp0 -o output.pgm\n\
	tp0 -r 800x600 -o file.pgm \n");
}

void displayVersion() {
	printf("%s", "Programa de dibujo de tableros de Ajedrez en formato PGM \
	\nVersion: v1.0\n");
}

void getXY(char* optarg, unsigned* x, unsigned* y) {
	char* ocurr;
	if (((ocurr = strchr(optarg, 'x')) != 0) ||
			((ocurr = strchr(optarg, 'X')) != 0)) {
		*x = (unsigned)atoi(optarg);
		*y = (unsigned)atoi(ocurr + 1);
	}
}

void getFileName(char* optarg, char** fileName) {
	strcpy(*fileName, optarg);
}

int main(int argc, char* argv[]) {
	int opt, finished = 0;
	unsigned x = 8, y = 8; // Valores default

	while (((opt = getopt(argc, argv, "hVr:o:")) != -1) && finished == 0) {
		switch (opt) {
			// Help
			case 'h': 	displayHelp();
						finished = 1;
						break;
			// Version
			case 'V':	displayVersion();
						finished = 1;
						break;
			// Resolution
			case 'r':	getXY(optarg, &x, &y);
						break;
			// Output
			case 'o':	//pgm(x, y, optarg);
						printf("x: %d \ny: %d \nNombre Archivo: %s\n", x,
								y, optarg);
						finished = 1;
						break;
		}
	}

	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
