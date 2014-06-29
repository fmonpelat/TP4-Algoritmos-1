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
    tequipo * eqaux=NULL;
    tmundial mundialx;
    
    mundialx.equipos=NULL;
    mundialx.q_equipos=TraerEquipos(&(mundialx.equipos));
    
    //mundialx.equipos=eqaux;
    //mundialx.q_equipos=cantEquipos;
    
    for (i=0; i<mundialx.q_equipos; i++) {
        printf("Grupo: %s Pais: %s\n",mundialx.equipos[i].id,mundialx.equipos[i].nombre);
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


int TestFileDump(void){
    
    t_bool error=FALSE;
	tvectorPosiciones * tablaPos = NULL;
	tequipo * equipos = NULL;
	size_t cantEquipos;
	tlista listaPartidos;
	tlista partidosJugados = NULL;
    
    
	cantEquipos = TraerEquipos(&equipos);
    
	TraerPartidos(equipos, cantEquipos, &listaPartidos);
	
    // hacemos test si los partidos estan bien definidos sino damos un error y decimos el porque...
	if ( ValidarPartidos(listaPartidos) == TRUE ){
        fprintf(stderr, "La validacion de los partidos fue insatisfactoria, revise el archivo de partidos.\n");
        return EXIT_FAILURE;
        // para debug: RecorrerPartidos(listaPartidos);
    }
    
    tablaPos = CrearVecPos(partidosJugados, equipos, cantEquipos);
    
    if (  leerPartidosJugados(&partidosJugados,&listaPartidos,equipos,cantEquipos /*,tablaPos */ ) == TRUE ){
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
    
	ActualizarVecPos(partidosJugados, tablaPos);
    
	if (  error  )
	{
		ActualizarVecPos(partidosJugados, tablaPos);
		printf("Lista de partidos \n");
		RecorrerPartidos(listaPartidos);
		printf("Lista de partidos jugados \n");
		RecorrerPartidos(partidosJugados);
		printf("Lista de posiciones \n");
		RecorrerTablaPos(tablaPos);
	}
	
    
    if( GrabarPartidosJugados( &partidosJugados ) == TRUE ){
        return 1;
    };
    
    DestruirPartidos( listaPartidos );
    DestruirEquipos(equipos);
    
    
    
    
    return 0;
}


