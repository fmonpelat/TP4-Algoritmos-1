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
    
    size_t i;
    tmundial mundialx;
    
    mundialx.equipos=NULL;
    mundialx.q_equipos=TraerEquipos(&(mundialx.equipos));
    
    for (i=0; i<mundialx.q_equipos; i++) {
        printf("Grupo: %s Pais: %s\n",mundialx.equipos[i].id,mundialx.equipos[i].nombre);
    }
    
    DestruirEquipos(mundialx.equipos);

}

void TestTraerPartidos(void){

    tmundial mundialx;
    mundialx.equipos=NULL;
    //tlista listaEquipos;
    
    
    mundialx.q_equipos=TraerEquipos(&(mundialx.equipos));
    
    TraerPartidos(mundialx.equipos,mundialx.q_equipos,&(mundialx.partidosPendientes));
    
    RecorrerPartidos( mundialx.partidosPendientes );

    DestruirPartidos( mundialx.partidosPendientes );
    
}

void TestBusquedaPartidos( tlista listaEquipos ){
    
    tpartido * auxprueba;
    
    auxprueba = BuscarPartidoPorId( listaEquipos, 48 );
    if (auxprueba) printf("eq1:%s eq2:%s\n",auxprueba->equipo1->nombre,auxprueba->equipo2->nombre);
    
    auxprueba = BuscarPartidoPorEquipos (listaEquipos ,"A1" , "A2" );
    if (auxprueba) printf("eq1:%s eq2:%s\n",auxprueba->equipo1->nombre,auxprueba->equipo2->nombre);
    


}


int TestFileDump(void){
    
    t_bool error=FALSE;
    tmundial mundialx;
    mundialx.equipos=NULL;
	tvectorPosiciones * tablaPos = NULL;
	//tequipo * equipos = NULL;
	//size_t cantEquipos;
	//tlista listaPartidos;
	//tlista partidosJugados = NULL;
    
    
	mundialx.q_equipos = TraerEquipos(&(mundialx.equipos));
    
	TraerPartidos(mundialx.equipos, mundialx.q_equipos, &(mundialx.partidosPendientes));
	
    // hacemos test si los partidos estan bien definidos sino damos un error y decimos el porque...
	if ( ValidarPartidos(mundialx.partidosPendientes) == TRUE ){
        fprintf(stderr, "La validacion de los partidos fue insatisfactoria, revise el archivo de partidos.\n");
        return EXIT_FAILURE;
        // para debug: RecorrerPartidos(listaPartidos);
    }
    
    tablaPos = CrearVecPos(mundialx.partidosJugados, mundialx.equipos, mundialx.q_equipos);
    
    if (  leerPartidosJugados(&(mundialx.partidosJugados),&(mundialx.partidosPendientes),mundialx.equipos,mundialx.q_equipos /*,tablaPos */ ) == TRUE ){
        fprintf(stderr, "No se pudo leer desde el archivo, salimos con error.");
        return EXIT_FAILURE;
    }
    
    
    /* if ( (error = newPartidoJugado(1,2,4,&listaPartidos,&partidosJugados, equipos, cantEquipos, tablaPos))==TRUE ){
     fprintf(stderr, "Error");
     }
     if ( (error = newPartidoJugado(2,1,1,&listaPartidos,&partidosJugados, equipos, cantEquipos, tablaPos))==TRUE ){
     fprintf(stderr, "Error");
     }
     */
    
	ActualizarVecPos(mundialx.partidosJugados, tablaPos);
    
	if (  error  )
	{
		ActualizarVecPos(mundialx.partidosJugados, tablaPos);
		printf("Lista de partidos \n");
		RecorrerPartidos(mundialx.partidosPendientes);
		printf("Lista de partidos jugados \n");
		RecorrerPartidos(mundialx.partidosJugados);
		printf("Lista de posiciones \n");
		RecorrerTablaPos(tablaPos);
	}
	
    
    if( GrabarPartidosJugados( &(mundialx.partidosJugados) ) == TRUE ){
        return 1;
    };
    
    DestruirPartidos( mundialx.partidosPendientes );
    DestruirPartidos( mundialx.partidosJugados );
    DestruirEquipos(mundialx.equipos);
    
    
    
    
    return 0;
}


