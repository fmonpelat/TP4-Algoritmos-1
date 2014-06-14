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
#include "tareas.h"

tequipo * TraerEquipos( void ){
    
    FILE * fpEquipo;
    
    if (  !( fpEquipo = fopen("grupos.txt", "r") )  ){
        fprintf(stderr, "Error, no se pudo abrir grupos.txt, existe?");
        return NULL;
    }
    
    
    
    return NULL;
}

