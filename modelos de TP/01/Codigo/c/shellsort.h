/* ****************************************************************************
 * ****************************************************************************
 *
 * LIBRERIA SHELLSORT
 *
 * ****************************************************************************
 * ***************************************************************************/



#ifndef SHELLSORT_H
#define SHELLSORT_H



// Funcion que aplica el algoritmo de ordenamiento Shellsort para ordenar un
// arreglo de palabras.
// PRE: 'words' es un puntero a un arreglo de punteros a caracter; 'arraysize'
// es el tamanio de dicho arreglo.
// POST: el arreglo 'words' queda ordenado.
void shellsort(char* words[], int arraysize);



#endif
