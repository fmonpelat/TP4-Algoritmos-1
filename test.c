//
//  test.c
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

/* definiciones de testing */

void TestEquipos(){
    
    tequipo * eqaux=NULL;
    size_t i,cantEquipos;
    
    cantEquipos=TraerEquipos(&eqaux);
    
    for (i=0; i<cantEquipos; i++) {
        printf("Grupo: %s Pais: %s\n",eqaux[i].id,eqaux[i].nombre);
    }
    
    DestruirEquipos(eqaux);

}