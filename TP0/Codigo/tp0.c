/* ****************************************************************************
 * PROGRAMA DE ORDENAMIENTO DE PALABRAS
 * ****************************************************************************
 * 
 * Facultad de Ingenieria - UBA
 * 66.20 Organizacion de computadoras
 * Trabajo Practico: Conjunto de instrucciones MIPS
 * 
 * ALUMNOS: 
 * 
 * Facundo Rossi (86707) - frossi85@gmail.com
 * Federico Colangelo (89869) - federico.colangelo@semperti.com
 * Federico Martin Rossi (92086) - federicomrossi@gmail.com
 *
 * ****************************************************************************
 *
 * Programa que permite aplicar metodos de ordenamiento a un texto o textos 
 * especificados por el usuario. Estos textos pueden ser ingresados a traves de
 * la entrada estandar o bien a traves de la especificacion de los nombres de
 * archivo que se desean procesar. Cabe resaltar que al especificar varios
 * nombres de archivos, los metodos seran aplicados al conjunto total de los
 * textos contenidos en estos. Es decir, el resultado del ordenamiento sera 
 * unico ya que contendra la mezcla de palabras de todos los archivos.
 * Los metodos de ordenamiento soportados por la presente version del programa
 * son: 
 *	
 *		- Bubblesort
 *		- Shellsort
 *
 *
 *
 * FORMA DE USO
 * ============
 *
 * El programa debera ser ejecutado por consola mediante el siguiente comando:
 *
 *  	# ./tp0 [OPCION] [archivos...]
 *	
 * donde, la opcion puede ser:
 *
 *	-h,		Muestra la ayuda
 *	-V,		Muestra la informacion de la version
 *	-b,		Indica la utilizacion del algoritmo Bubblesort
 *	-s,		Indica la utilizacion del algoritmo Shellsort
 *
 * y en archivos se debe especificar los nombres de archivo (incluyendo su
 * extension) separados uno del otro por un espacio.
 * En caso de desear ingresar el texto a traves de la entrada estandar, debe
 * utilizarse la siguiente variacion del comando anterior:
 *
 *  	# ./tp0 [OPCION]
 *
 *
 */



#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bubblesort.h"
#include "shellsort.h"
#include "fileloader.h"





/* ****************************************************************************
 * CONSTANTES
 * ***************************************************************************/


// Maximo de caracteres permitidos por texto de entrada estandar
#define MAX_CHARS 1000



/* ****************************************************************************
 * FUNCIONES AUXILIARES
 * ***************************************************************************/


// Funcion que imprime por pantalla el mensaje de ayuda del programa.
void ayudaImprimirSalidaEstandar()
{
	printf("tp0 [OPTIONS] [files...]\n");
	printf("-h, \t\t\t display this help and exit.\n");
	printf("-V, \t\t\t display version information and exit.\n");
	printf("-b, \t\t\t use the bubblesort algorithm.\n");
	printf("-s, \t\t\t use the shellsort algorithm.\n\n");
	printf("$echo -n echo 'El tractorcito rojo que silbo y bufo' > entrada.txt\n");
	printf("$tp0 -b entrada.txt\n");
	printf("bufo El que rojo silbo tractorcito y\n\n");
	printf("cat letters.txt\n");
	printf("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ$\n\n");
	printf("$tp0 letters.txt\n");
	printf("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ\n$\n\n");
	printf("$tp0 letters.txt entrada.txt\n");
	printf("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ bufo El que rojo silbo tractorcito y\n$\n");
}


// Funcion que imprime por pantalla la version del programa.
void versionImprimirSalidaEstandar()
{
	printf("Programa de ordenamiento de palabras\nVersion: v0.1\n");
}


// Funcion que imprime los resultados del ordenamiento a traves de la salida
// estandar.
// PRE: 'palabras' es un arreglo de palabras; 'arraysize' es el tamanio del
// arreglo
void ordenamientoImprimirSalidaEstandar(char* palabras[], int arraysize)
{
	int i;
	for(i = 0; i < arraysize; printf("%s ", palabras[i++]));
	printf("\n");
}


// Funcion que se encarga leer archivos de texto devolviendo una cadena con
// el contenido de estos.
// PRE: 'iniArchivos' es el indice inicial desde donde 'argv' posee nombres
// de archivo; 'argc' y 'argv' son los parametros de entrada de la funcion
// main.
// POST: se devuelve una unica cadena con el contenido completo de archivos.
char* cargarTextosDeArchivos(int iniArchivos, int argc, char **argv) 
{
	int i;
	char * texto = "";

	// Sensamos cada archivo ingresado y concatenamos su contenido
	for(i = iniArchivos; i < argc; i++)
	{
		// Cargamos contenido de archivo
		char * texto_tmp = file_loader(argv[i]);
		
		// Recalculamos el tamanio del arreglo
		int len = strlen(texto) + strlen(texto_tmp) + 2;
		
		// Solicitamos espacio de memoria nuevo
		char * texto_alloc = (char *) malloc(len * sizeof(char));
		
		// Copiamos contenido antigui y concatenamos el nuevo
		strcpy(texto_alloc, texto);
		if(i > iniArchivos) strcat(texto_alloc, " ");
		strcat(texto_alloc, texto_tmp);
		free(texto_tmp);
		
		// Liberamos espacio de memoria antiguio
		if(i > iniArchivos) free(texto);
		
		// Asociamos al nuevo arreglo
		texto = texto_alloc;
	}

	return texto;
}


// Funcion que se encarga de leer el texto ingresado por entrada estandar.
// POST: se devuelve una unica cadena con el texto ingresado.
char* cargarTextosDeEntradaEstandar()
{
	char * texto = (char *) malloc(MAX_CHARS * sizeof(char) + 1);
	if(fgets(texto, MAX_CHARS + 1, stdin) == NULL) return "";

	return texto;
}


void testFileLoader(const char * url)
{
	char * text;
	char ** words = NULL;
	int wordsSize = 0;

	text = file_loader(url);
	
	if (text != NULL)
	{
		//fputs(text, stdout);
	}

	wordsSize = to_words(text, &words);

	for(int i = 0; i < wordsSize; i++)
	{
		fputs("\n", stdout);
		fputs(words[i], stdout);
		fputs("\n", stdout);
	}	
}




/* ****************************************************************************
 * PROGRAMA PRINCIPAL
 * ***************************************************************************/


int main(int argc, char **argv) 
{
	int c;

	//File loader variables
	char * text;
	char ** words = NULL;
	int wordsSize = 0;

	opterr = 0;

	while ((c = getopt(argc, argv, "hVb:s:")) != -1)
	{
		switch (c)
		{
			// Ayuda
			case 'h':
				ayudaImprimirSalidaEstandar();
				break;

			// Version
			case 'V':
				versionImprimirSalidaEstandar();
				break;

			// Ejecucion de bubblesort
			case 'b':

				// Cargamos contenidos de archivos
				text = cargarTextosDeArchivos(2, argc, argv);

				// Si el/los archivos esta/n vacio/s, salimos
				if (text == NULL) break;
	
				wordsSize = to_words(text, &words);

				if (wordsSize == -1) break;
				
				// Ejecutamos bubblesort
				bubblesort(words, wordsSize);

				// Enviamos a salida estandar
				ordenamientoImprimirSalidaEstandar(words, wordsSize);
				
				free(words);
				free(text);
				break;

			// Ejecucion de shellsort
			case 's':

				// Cargamos contenidos de archivos
				text = cargarTextosDeArchivos(2, argc, argv);

				// Si el/los archivos esta/n vacio/s, salimos
				if (text == NULL) break;

				wordsSize = to_words(text, &words);

				if (wordsSize == -1) break;

				// Ejecutamos shellsort
				shellsort(words, wordsSize);

				// Enviamos a salida estandar
				ordenamientoImprimirSalidaEstandar(words, wordsSize);

				free(words);
				free(text);
				break;
			
			// No se especifica nombre de archivo
			case '?':

				// Ejecutar bubblesort con texto desde entrada estandar
				if(optopt == 'b')
				{
					// Cargamos texto
					text = cargarTextosDeEntradaEstandar();
					
					// Si no se ingreso texto, salimos
					if (text == NULL) break;
					wordsSize = to_words(text, &words);

					if (wordsSize == -1) break;
					
					// Ejecutamos bubblesort
					bubblesort(words, wordsSize);

					// Enviamos a salida estandar
					ordenamientoImprimirSalidaEstandar(words, wordsSize);

					free(words);
					free(text);
					break;
				}

				// Ejecutar shellsort con texto desde entrada
				// estandar
				else if(optopt == 's')
				{
					// Cargamos texto
					text = cargarTextosDeEntradaEstandar();
					
					// Si no se ingreso texto, salimos
					if (text == NULL) break;
					wordsSize = to_words(text, &words);

					if (wordsSize == -1) break;
					
					// Ejecutamos shellsort
					shellsort(words, wordsSize);

					// Enviamos a salida estandar
					ordenamientoImprimirSalidaEstandar(words, wordsSize);

					free(words);
					free(text);
					break;
				}

			default:
				opterr = 1;
				break;
		}
	}

	// Manejo de casos en que no se ingresan argumentos validos
	if(opterr || argc <= 1)
	{
		fprintf (stderr, "Los argumentos no son validos.\n");
		printf("Tipee 'tp0 -h' para ver el modo de uso.\n");
	}


	return 0;
}

