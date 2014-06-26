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
	tvectorPosiciones * tablaPos = NULL;
	tequipo * equipos = NULL;
	size_t cantEquipos;
	tlista listaPartidos;
	tlista partidosJugados = NULL;
	cantEquipos = TraerEquipos(&equipos);
    
	TraerPartidos(equipos, cantEquipos, &listaPartidos);
	tablaPos = CrearVecPosiciones(equipos, cantEquipos);
	if (ValidarPartidos(listaPartidos))
		RecorrerPartidos(listaPartidos);

    // En Desarrollo ...
    //leerPartidosJugados(&partidosJugados);

	/*tablaPos = (tequipoPos**)malloc(sizeof(tequipoPos*));
     tablaPos[0] = NULL;*/
	if ( PartidoJugadoNuevo('i', &listaPartidos, &partidosJugados, equipos, cantEquipos, tablaPos) == FALSE)
	{
		printf("Lista de partidos \n");
		RecorrerPartidos(listaPartidos);
		printf("Lista de partidos jugados \n");
		RecorrerPartidos(partidosJugados);
		printf("Lista de posiciones \n");
		RecorrerTablaPos(tablaPos);
	}
    
	if (PartidoJugadoNuevo('i', &listaPartidos, &partidosJugados, equipos, cantEquipos, tablaPos) == FALSE)
	{
		printf("Lista de partidos \n");
		RecorrerPartidos(listaPartidos);
		printf("Lista de partidos jugados \n");
		RecorrerPartidos(partidosJugados);
		printf("Lista de posiciones \n");
		RecorrerTablaPos(tablaPos);
	}
    
	if (PartidoJugadoNuevo('i', &listaPartidos, &partidosJugados, equipos, cantEquipos, tablaPos) == FALSE)
	{
		printf("Lista de partidos \n");
		RecorrerPartidos(listaPartidos);
		printf("Lista de partidos jugados \n");
		RecorrerPartidos(partidosJugados);
		printf("Lista de posiciones \n");
		RecorrerTablaPos(tablaPos);
	}


    //En Desarrollo falta verificar que esta guardando me esta guardando las cosas como:
    if( GrabarPartidosJugados( &partidosJugados )==TRUE ){
        return 1;
    };
 
    DestruirPartidos( listaPartidos );
    DestruirEquipos(equipos);
    
    
    
    
    return 0;
    
}

