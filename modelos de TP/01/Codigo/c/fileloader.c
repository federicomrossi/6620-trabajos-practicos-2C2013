/* ****************************************************************************
 * ****************************************************************************
 *
 * LIBRERIA DE CARGA DE ARCHIVO DE PALABRAS
 *
 * ****************************************************************************
 * ***************************************************************************/


#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "fileloader.h"




// Funcion que carga un archivo de texto a memoria
// PRE: 'fileUrl' es la url completa al archivo a ordenar.
// POST: devuelve la lista de palabras cargadas en memoria
char * file_loader(const char * fileUrl)
{
	 FILE * file;
	 long fileSize;
	 char * buffer;
	 size_t result;

	 file = fopen (fileUrl, "r");

	 if (file==NULL) 
	 {
	 	//Fail to load file
	 	fputs ("The file can not be open or not exist \n", stderr); 
		return NULL;
	 }

	 //Get file size
	 fseek (file , 0 , SEEK_END);
	 fileSize = ftell (file);
	 rewind (file);

	 //Allocate memory for the whole file
	 buffer = (char *) malloc ((sizeof(char) * fileSize) + 1);
	
	 if (buffer == NULL) 
	 {
	 	fputs ("There is no enoght memory to allocate the file in memory \n", stderr); 
		return NULL;
	}

	 //Copy the file to the buffer
	 result = fread (buffer, 1, fileSize, file);
         buffer[(sizeof(char) * fileSize)] = '\0';
	
	 if (result != fileSize) 
	 {
	 	fputs ("Fail to read the whole file \n", stderr); 
		return NULL;
	 }

	 /* the whole file is now loaded in the memory buffer. */

	 fclose (file);

	 return buffer;
}


// Funcion que separa las palabras de un texto en unidades.
// PRE: 'text' es una cadena que contiene el texto; 'result' es un puntero en donde se
// insertan las palabras del texto.
// POST: en 'result' se almacenaron las palabras.
int to_words(char * text, char *** result)
{
 	char ** words;
 	char ** reallocatedWords = NULL;
 	bool isNewWord = true;
	size_t textSize = strlen(text);
	int wordsIndex = 0;
	size_t bufferSize = INITIAL_BUFFER_SIZE * sizeof(char*);
	size_t spaceForWords = INITIAL_BUFFER_SIZE;

	//initialy allocate memory for 100 words
	words = (char **) malloc ( INITIAL_BUFFER_SIZE * sizeof(char*) );

	if(words == NULL)
	{
		fputs ("Not enough memory to allocate the words \n", stderr); 
		return -1;
	}

	for (int i = 0; i < textSize; i++)
	{
		if ( !isEndOfWord (text[i]) )
		{
			if(isNewWord)
			{
				words[wordsIndex] = &text[i];
				isNewWord = false;

				if(wordsIndex >= spaceForWords-1)
				{
					//Reallocate for more space and copy the old array to the new one
					bufferSize *= 2;
					spaceForWords *= 2;
					reallocatedWords = realloc(words, bufferSize);
				
					if(reallocatedWords != NULL) 
					{
						words = reallocatedWords;
						reallocatedWords = NULL;
					}
					else 
					{ 
						fputs ("Not enough memory to allocate the words \n", stderr); 
						return -1;
					}
				}

				wordsIndex++;
			}
		}
		else
		{
			text[i] = '\0';
			isNewWord = true;
		}
	}

	*result = words;

	return wordsIndex;
}


// Funcion que verifica si un caracter es un fin de palabra o un separador.
// PRE: 'letter' es el caracter a procesar.
// POST: devuelve true si el caracter es un fin de palabra o separador, o
// false en su defecto.
bool isEndOfWord(char letter)
{
	//A-Z es de 65 a 90
	//a-z es de 97 a 122
	//0-9 es de 48 a 57
	return !( (letter > 64 && letter < 91) || (letter > 96 && letter < 123) || (letter > 47 && letter < 58));
}
