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




size_t TraerEquipos( tequipo **  equipos ){
    
    if ( (*equipos)!=NULL ) {
        fprintf(stderr, "Error, por favor ingrese un puntero equipo nulo");
        return 0;
    }
    
    tequipo * aux=NULL;
    size_t used_size=0;
    size_t alloc_size=0,init_chop=2,chop_size=2;
    FILE * fpequipos;
    char str[M_ID+M];
    char * pstr;
    char* pstr2;

    if (  !( fpequipos = fopen("grupos.txt", "r") )  ){
        fprintf(stderr, "Error, no se pudo abrir grupos.txt, existe?");
        return 0;
    }
    
    /* pedimos memoria por primera vez antes de reallocar si es que necesitamos memoria.
     */
    if (  !( *equipos = (tequipo*)malloc( sizeof(tequipo)*init_chop) )  ) {
        fprintf(stderr, "Error, could not find memory");
        return 0;
    }
    
    alloc_size=init_chop;
    
    while ( fgets(str, M_ID+M+1 , fpequipos) ){
        
        /* nos preguntamos si necesitamos memoria ... pedimos de a chops o de a pedazos
         */
        if ( used_size == alloc_size ) {
        
            if (  !( aux = (tequipo *)realloc(*equipos, sizeof(tequipo)*( alloc_size+chop_size) ))  ) {
                fprintf(stderr, "Error, could not find memory");
                free(*equipos);
                *equipos=NULL;
                return 0;
            }
            *equipos=aux;
            alloc_size+=chop_size;
        }
        
        pstr = strtok(str,";");
        if ( pstr ) strcpy ( (*equipos)[used_size].id , pstr);
        
        pstr = strtok(NULL,";");
        pstr2 = strtok(pstr,"\r\n");
       
        if( pstr2 ) strcpy( (*equipos)[used_size].nombre, pstr2);
        
        used_size++;
    
    }
    fclose(fpequipos);
    // para debug sacar despues de pasar las pruebas
    //printf("%s\n",equipos[1].nombre);
    //printf("%s\n",equipos[1].id);
    
    return used_size-1;
}


void DestruirEquipos( tequipo * equipos){
    
    free(equipos);

}









