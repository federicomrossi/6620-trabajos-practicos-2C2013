/* ****************************************************************************
 * ****************************************************************************
 *
 * LIBRERIA DE CARGA DE ARCHIVO DE PALABRAS
 *
 * ****************************************************************************
 * ***************************************************************************/



#ifndef FILELOADER_H
#define FILELOADER_H

#define INITIAL_BUFFER_SIZE 100

#include <stdbool.h>


// Funcion que carga un archivo de texto a memoria
// PRE: 'fileUrl' es la url completa al archivo a ordenar.
// POST: devuelve la lista de palabras cargadas en memoria
char* file_loader(const char * fileUrl);

// Funcion que separa las palabras de un texto en unidades.
// PRE: 'text' es una cadena que contiene el texto; 'result' es un puntero en donde se
// insertan las palabras del texto.
// POST: en 'result' se almacenaron las palabras.
int to_words(char * text, char *** result);

// Funcion que verifica si un caracter es un fin de palabra o un separador.
// PRE: 'letter' es el caracter a procesar.
// POST: devuelve true si el caracter es un fin de palabra o separador, o
// false en su defecto.
bool isEndOfWord(char letter);

#endif
