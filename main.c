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
    tlista listaPartidos;
    tlista partidosJugados = NULL;
    tpartido * partidoNodoJugado;
    
    cantEquipos=TraerEquipos(&equipos);
    
    TraerPartidos(equipos,cantEquipos,&listaPartidos);
    
    if (ValidarPartidos(listaPartidos))
		//RecorrerPartidos(listaPartidos);
    
    
    //partidoNodoJugado = BuscarPartidoPorId( listaPartidos, 2 );
    //printf("%d\n",partidoNodoJugado->idPartido);
    //intercambiarNodo(&listaPartidos, &partidosJugados, equipos, cantEquipos, partidoNodoJugado);
    
    partidoNodoJugado = BuscarPartidoPorId( listaPartidos, 1 );
    intercambiarNodo(&listaPartidos, &partidosJugados, equipos, cantEquipos, partidoNodoJugado);

	printf("Lista de partidos");
	RecorrerPartidos(listaPartidos);
	printf("\nLista de partidos jugados");
	RecorrerPartidos(partidosJugados);

    
    
    
    //al salir guardamos la informacion antes de destruir la memoria
    //if( GrabarPartidosJugados( lista_jugados )==TRUE ){
    //    return 1;
    //};
    DestruirPartidos( listaPartidos );
    DestruirEquipos(equipos);
    
    
    
    
    return 0;
    
}

