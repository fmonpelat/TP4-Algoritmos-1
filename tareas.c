//
//  tareas.c
//  TP4 Algoritmos 1
//
//  Copyright (c) 2014 . All rights reserved.
//
//  Facundo Monpelat
//  Luca Mazzer
//  Erik Schatz



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tareas.h"


void dump_line(FILE *fp) {
    int ch;
    while ( (ch = fgetc(fp)) != EOF && ch != '\n');
}




tequipo * TraerEquipos( void ){
    
    tequipo * equipos=NULL;
    tequipo * aux=NULL;
    size_t used_size=0;
    size_t alloc_size=0,init_chop=2,chop_size=2;
    size_t i=0;

    FILE * fpequipos;
    char str[M_ID+M];
    char grupo[M_ID+1];
    char pais[M+1];
    char * pstr;
    


    if (  !( fpequipos = fopen("grupos.txt", "r") )  ){
        fprintf(stderr, "Error, no se pudo abrir grupos.txt, existe?");
        return NULL;
    }
    
    
    if (  !( equipos = (tequipo*)malloc( sizeof(tequipo)*init_chop) )  ) {
        fprintf(stderr, "Error, could not find memory");
        return NULL;
    }
    alloc_size=init_chop;
    
    while ( fgets(str, M_ID+M+1 , fpequipos) ){
        
        if ( used_size == alloc_size ) {
        
            if (  !( aux = (tequipo *)realloc(equipos, sizeof(tequipo)*( alloc_size+chop_size) ))  ) {
                fprintf(stderr, "Error, could not find memory");
                free(equipos);
                equipos=NULL;
                return NULL;
            }
            equipos=aux;
            alloc_size+=chop_size;
        }
        
 
        pstr = strtok(str,";");
        strcpy(equipos[used_size].id,pstr);
        //printf("%s\n",pstr);
        while (  (pstr = strtok (NULL, ";"))!=NULL  ) {

        
                printf("%s",pstr);
                strcpy(equipos[used_size].nombre,pstr);
                
            
        }
        used_size++;
    
    }
    for (i=0; i<used_size; i++) {
    //printf("Grupo: %s Pais: %s",equipos[i].id,equipos[i].nombre);
    }
    
    return NULL;
}














