/* ****************************************************************************
 * ****************************************************************************
 *
 * LIBRERIA HEAPSORT
 *
 * ****************************************************************************
 * ***************************************************************************/


#include "heapsort.h"
#include <string.h>


void heap(char* words[],int raiz, int fin){
    char finished = 0;
    char* tmp;
    int hijo;
    while (raiz*2+1 <= fin && !finished){
        //Elijo el hijo mayor
        if(raiz*2+1==fin || strcasecmp(words[raiz*2+1],words[raiz*2+2]) > 0 ){
            hijo=raiz*2+1;
        }else{
            hijo=raiz*2+2;
        }
        //Checkeo si es mayor e intercambio
        if(strcasecmp(words[raiz],words[hijo]) < 0){
            tmp=words[raiz];
            words[raiz]=words[hijo];
            words[hijo]=tmp;
            raiz=hijo;
        }else{
            finished=1;
        }
    }
}



// Funcion que aplica el algoritmo de ordenamiento Heapsort para ordenar un
// arreglo de palabras.
// PRE: 'words' es un puntero a un arreglo de punteros a caracter; 'arraysize'
// es el tamanio de dicho arreglo.
// POST: el arreglo 'words' queda ordenado.
void heapsort(char* words[], int arraysize){
    int i;
    char* tmp;
    //Armo Heap
    for (i=(arraysize/2)-1;i>=0;i--){
        heap(words,i,arraysize-1);
    }

    //Extraigo raiz y armo heap
    for(i=arraysize-1;i>0;i--){
        tmp=words[0];
        words[0]=words[i];
        words[i]=tmp;
        heap(words,0,i-1);
    }
}

