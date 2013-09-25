#include "pgm.h"
#include <string.h>

void escribirLinea(unsigned int x, FILE* file,char start){
    int i;
    int change = x / 8;
    for(i=1;i<=x;i++){
        fprintf(file,"%d",start);
        if(!(i%change))
            start = !start;
    }
    fprintf(file,"\n");
}

void pgm(unsigned x,unsigned y, char* fileName){
    FILE* file;
    int i;
    char start=1;
    char change = y / 8;
    if(!strcmp(fileName,"-"))
        file = stdout;
    else
        file = fopen(fileName,"w");
    fprintf(file,"P2\n%d\n%d\n1\n",x,y);
    for(i=1;i<=y;i++){
        escribirLinea(x,file,start);
        if(!(i%change))
            start = !start;
    }
    if(file != stdout)
        fclose(file);
}
