/*
 ============================================================================
 Name         : OrgaCompus.c
 Authors      : Belen Beltran (91718)
 	 	 	 	Federico Martin Rossi ()
 	 	 	 	Pablo Rodriguez ()
 Version      : 1.0
 Description  : Programa de dibujo de tableros de Ajedrez en formato PGM
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "pgm.h"


//* Funciones Auxiliares *//

void displayHelp() {
	printf("%s", "<- Help display ->\nUsage:\n \
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
	tp0 -r 800x600 -o file.pgm \n<- End of help display ->\n");
}

void displayVersion() {
	printf("%s", "This program draws chess boards in PGM file format\
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

int main(int argc, char* argv[]) {
	int opt, finished = 0, i = 1;
	char* file = NULL;
	unsigned x = 8, y = 8; // Valores default

	while (((opt = getopt(argc, argv, "hVr:o:")) != -1) && !finished) {
		// Solo ejecuta opcion si esta es de una sola letra
		// Ej: ejecuta '-h', pero no '-help'
		if (argv[i][2] == 0) {
			i += 2;
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
				case 'o':   file = optarg;
							finished = 1;
							break;
				// Ninguna de las anteriores
				default:	finished = 1;
							printf("Error: Unknown option selected.\n");
							displayHelp();
							break;
			}
		}
		else {
			finished = 1;
			printf("Error: Unknown option selected.\n");
			displayHelp();
		}
	}
	if (file)
        pgm(x, y, file);

	return EXIT_SUCCESS;
}
