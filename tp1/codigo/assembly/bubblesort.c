/* ****************************************************************************
 * ****************************************************************************
 *
 * LIBRERIA BUBBLESORT
 *
 * ****************************************************************************
 * ***************************************************************************/


#include "bubblesort.h"
#include <stdbool.h>
#include <string.h>



// Funcion que aplica el algoritmo de ordenamiento Bubblesort para ordenar un
// arreglo de palabras.
// PRE: 'words' es un puntero a un arreglo de punteros a caracter; 'arraysize'
// es el tamanio de dicho arreglo.
// POST: el arreglo 'words' queda ordenado.
void bubblesort(char* words[], int arraysize)
{
	// Variables de procesamiento
	bool huboIntercambio;
	int i;
	int n = arraysize;
	char* sAux;

	// Recorremos el arreglo haciendo intercambios hasta que ya no se registre
	// ningun cambio realizado.
	do
	{
		huboIntercambio = false;

		for(i = 1; i < n; i++)
		{
			// Si el de indice menor es mayor que el de indice superior, los
			// intercambiamos
			if(strcasecmp(words[i-1], words[i]) > 0)
			{
				sAux = words[i-1];
				words[i-1] = words[i];
				words[i] = sAux;

				// Cambiamos el flag para registrar que hubo un cambio
				huboIntercambio = true;
			}
		}

		// Como el elemento del indice superior se encuentra ya ordenado una
		// vez finalizada la pasada, se reduce en uno la cantidad de indices
		// a iterar en la proxima pasada.
		n -= 1;

	} while(huboIntercambio);
}
