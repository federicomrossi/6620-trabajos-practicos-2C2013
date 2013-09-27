#include "pgm.h"
#include <string.h>

void escribirLinea(unsigned int x, FILE* file,char start){
    unsigned int i;
    unsigned int change = x >> 3;
    unsigned char resto = x & 0x00000007;
    unsigned int count = 0;
    for(i=0;i<x;i++){
        fprintf(file,"%d",start);
        count++;
        if(count == change + (resto ? 1 : 0)){
            start = !start;
            if(resto){
                resto--;
            }
            count=0;
        }
    }
    fprintf(file,"\n");
}

void pgm(unsigned x,unsigned y, char* fileName){
    FILE* file;
    int i;
    char start=1;
    unsigned int change = y >> 3;
    unsigned char resto = y & 0x00000007;
    unsigned int count = 0;
    if(!strcmp(fileName,"-")){
        file = stdout;
    }else{
        file = fopen(fileName,"w");
    }
    fprintf(file,"P2\n%d\n%d\n1\n",x,y);
    for(i=0;i<y;i++){
        escribirLinea(x,file,start);
        count++;
        if(count == change + (resto ? 1 : 0)){
            start = !start;
            if(resto)
                resto--;
            count=0;
        }
    }
    if(file != stdout)
        fclose(file);
}
