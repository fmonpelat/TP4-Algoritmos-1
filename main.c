//
//  main.c
//  TP4 Algoritmos 1
//
//  Copyright (c) 2014 . All rights reserved.
//
//  Facundo Monpelat
//  Luca Mazzer
//  Erik Schatz
// POR FAVOR LEER conventions.h




#include <stdio.h>
#include "tareas.h"
#include <stdlib.h>
#include <string.h>


int main(int argc, const char * argv[])
{

    
    //TestEquipos();
    //TestTraerPartidos();
    

    tequipo * equipos=NULL;
    size_t cantEquipos;
    tlista listaEquipos;
    
    cantEquipos=TraerEquipos(&equipos);
    
    TraerPartidos(equipos,cantEquipos,&listaEquipos);
    //RecorrerPartidos(listaEquipos);
    
    
    //al salir guardamos la informacion antes de destruir la memoria
    if( GrabarPartidosJugados( lista_jugados )==TRUE ){
        return 1;
    };
    
    
    DestruirPartidos( listaEquipos );
    DestruirEquipos(equipos);
    
    
    
    
    return 0;
    
}

