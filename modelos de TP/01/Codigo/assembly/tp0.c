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
 *		- Shellsort
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fileloader.h"

extern int shellsort(char **, size_t);

int main (int argc, char** argv)
{	
	char* texto;	
	char** words;
	size_t size;
	int i;	

	texto=file_loader(argv[1]);
	size=to_words(texto,&words);

	shellsort(words, size);
	i=0;
        while (i<size)
        {
                puts(words[i]);
                i++;
        }

	return 0;
}
