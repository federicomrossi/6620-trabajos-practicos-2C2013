/* ****************************************************************************
 * ****************************************************************************
 *
 * LIBRERIA SHELLSORT
 *
 * ****************************************************************************
 * ***************************************************************************/


#include "shellsort.h"
#include <string.h>



// Funcion que aplica el algoritmo de ordenamiento Shellsort para ordenar un
// arreglo de palabras.
// PRE: 'words' es un puntero a un arreglo de punteros a caracter; 'arraysize'
// es el tamanio de dicho arreglo.
// POST: el arreglo 'words' queda ordenado.
void shellsort(char* words[], int arraysize)
{
	int intervalo, k, j, i;
	char* sAux;

	// Tomamos como intervalo el modulo de la mitad del arreglo
	intervalo = arraysize / 2;

	// Iteramos hasta que el intervalo sea nulo
	while(intervalo > 0)
	{
		for(i = intervalo-1; i < arraysize; i++)
		{
			j = i - intervalo;

			// Procesamos hasta caer en un indice fuera de rango del arreglo
			while(j >= 0)
			{
				k = j + intervalo;

				// Si el de indice menor es mayor que el de indice superior, los
				// intercambiamos
				if(strcasecmp(words[j], words[k]) > 0)
				{
					sAux = words[j];
					words[j] = words[k];
					words[k] = sAux;
				}
				else
					j = 0;

				j -= intervalo;
			}
		}

		// Tomamos como nuevo intervalo el modulo de la mitad del intervalo
		// anterior
		intervalo = intervalo / 2;
	}
}
