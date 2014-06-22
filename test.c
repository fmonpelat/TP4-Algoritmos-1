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

void TestEquipos(void){
    
    tequipo * eqaux=NULL;
    size_t i,cantEquipos;
    
    cantEquipos=TraerEquipos(&eqaux);
    
    for (i=0; i<cantEquipos; i++) {
        printf("Grupo: %s Pais: %s\n",eqaux[i].id,eqaux[i].nombre);
    }
    
    DestruirEquipos(eqaux);

}

void TestTraerPartidos(void){

    
    tequipo * equipos=NULL;
    size_t cantEquipos;
    tlista listaEquipos;
    
    cantEquipos=TraerEquipos(&equipos);
    
    TraerPartidos(equipos,cantEquipos,&listaEquipos);
    
    RecorrerPartidos(listaEquipos);

    DestruirPartidos( listaEquipos );
    
}

void TestBusquedaPartidos( tlista listaEquipos ){
    
    tpartido * auxprueba;
    
    auxprueba = BuscarPartidoPorId( listaEquipos, 48 );
    if (auxprueba) printf("eq1:%s eq2:%s\n",auxprueba->equipo1->nombre,auxprueba->equipo2->nombre);
    
    auxprueba = BuscarPartidoPorEquipos (listaEquipos ,"A1" , "A2" );
    if (auxprueba) printf("eq1:%s eq2:%s\n",auxprueba->equipo1->nombre,auxprueba->equipo2->nombre);
    


}





