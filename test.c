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
#include <ctype.h>
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
    mundialx.partidosJugados=NULL;
    mundialx.partidosPendientes=NULL;
	tvectorPosiciones * tablaPos = NULL;
    
    // traemos de archivo los equipos
	mundialx.q_equipos = TraerEquipos(&(mundialx.equipos));
    
    // traemos de archivo la lista de partidos
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

int TestModificarPartido(void){
    
    t_bool error=FALSE;
    tmundial mundialx;
    mundialx.equipos=NULL;
    mundialx.partidosJugados=NULL;
    mundialx.partidosPendientes=NULL;
	tvectorPosiciones * tablaPos = NULL;
    tpartido * partidoaModificar;
    
    // traemos de archivo los equipos
	mundialx.q_equipos = TraerEquipos(&(mundialx.equipos));
    
    // traemos de archivo la lista de partidos
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
    
	if ( error ){
        
		printf("Lista de partidos jugados \n");
		RecorrerPartidos(mundialx.partidosJugados);
		printf("Lista de posiciones \n");
		RecorrerTablaPos(tablaPos);
	}
    
	partidoaModificar = BuscarPartidoPorId(mundialx.partidosJugados, 1);
    ModificarPartidoJugado(mundialx.partidosJugados, partidoaModificar, 8, 8, tablaPos);
    
    printf("Lista de partidos jugados despues de la modificacion \n");
    RecorrerPartidos(mundialx.partidosJugados);

    if( GrabarPartidosJugados( &(mundialx.partidosJugados) ) == TRUE ){
        return 1;
    };
    
    DestruirPartidos( mundialx.partidosPendientes );
    DestruirPartidos( mundialx.partidosJugados );
    DestruirEquipos(mundialx.equipos);
    
    return 0;
    
    
    
}

int TestALL(void){
    
    t_bool error=FALSE;
    size_t id,gol1,gol2,counterEquipos;
    tmundial mundialx;
    mundialx.equipos=NULL;
    mundialx.partidosJugados=NULL;
    mundialx.partidosPendientes=NULL;
	tvectorPosiciones * tablaPos = NULL;
    tpartido * partidoaModificar;
    tpartido * partidoAux;
    
    // traemos de archivo los equipos
	mundialx.q_equipos = TraerEquipos(&(mundialx.equipos));
    // verificamos que no sea 0 la cantidad de equipos.
    if (mundialx.q_equipos==0) {
        fprintf(stderr, "Error, No hay equipos cargados.\n");
        return 1;
    }
    // traemos de archivo la lista de partidos
    if(  TraerPartidos(mundialx.equipos, mundialx.q_equipos, &(mundialx.partidosPendientes))==TRUE  ){
        return 1;
    }
	
    // hacemos test si los partidos estan bien definidos sino damos un error y decimos el porque...
	if ( ValidarPartidos(mundialx.partidosPendientes) == TRUE ){
        fprintf(stderr, "La validacion de los partidos fue insatisfactoria, revise el archivo de partidos.\n");
        return EXIT_FAILURE;
        // para debug: RecorrerPartidos(listaPartidos);
    }
    
    // creamos la tabla de posiciones
    tablaPos = CrearVecPos(mundialx.partidosJugados, mundialx.equipos, mundialx.q_equipos);
    
    // leemos de archivo los partidos jugados y los agregamos al mundialx
    if (  leerPartidosJugados(&(mundialx.partidosJugados),&(mundialx.partidosPendientes),mundialx.equipos,mundialx.q_equipos /*,tablaPos */ ) == TRUE ){
        fprintf(stderr, "No se pudo leer desde el archivo, salimos con error.");
        return EXIT_FAILURE;
    }
    
    /*
    //podemos agregar un nuevo partido por id o por tpartido buscando el partido antes con las funciones especificas.
     if ( (error = newPartidoJugado(1,2,4,&mundialx.partidosPendientes,&mundialx.partidosJugados, mundialx.equipos, mundialx.q_equipos))==TRUE ){
     fprintf(stderr, "Error");
     }
    
     id=2;gol1=1;gol2=3;
     if ( (partidoAux=BuscarPartidoPorId(mundialx.partidosPendientes, (int)id ) ) == NULL ){
         if(  (partidoAux=BuscarPartidoPorId(mundialx.partidosJugados, (int)id )) == NULL ){
             fprintf(stderr,"No existe el id (%lu) de ese partido!\n",id);
             return 1;
         }
         printf("Ese partido ya se jugo.\n Por Favor utilize el submenu de partidos jugados opcion 1) Modificar.\n");
         return 1;
     }
     if ( newPartidoJugadoXP(partidoAux,(int)gol1,(int)gol2,&mundialx.partidosPendientes,&mundialx.partidosJugados,mundialx.equipos,mundialx.q_equipos) == TRUE ){
         fprintf(stderr, "Error, al modificar el partido.\n");
         return 1;
     }
     */
     
    
    // actualizamos la tabla de posiciones.
	ActualizarVecPos(mundialx.partidosJugados, tablaPos);
    
	if ( error ){
        printf("Lista de equipos del mundial\n");
        for (counterEquipos=0; counterEquipos<mundialx.q_equipos; counterEquipos++) {
            printf("Grupo: %s Pais: %s\n",mundialx.equipos[counterEquipos].id,mundialx.equipos[counterEquipos].nombre);
        }
		printf("Lista de partidos jugados \n");
		RecorrerPartidos(mundialx.partidosJugados);
		printf("Lista de posiciones \n");
		RecorrerTablaPos(tablaPos);
	}
    
	partidoaModificar = BuscarPartidoPorId(mundialx.partidosJugados, 1);
    ModificarPartidoJugado(mundialx.partidosJugados, partidoaModificar, 8, 8, tablaPos);
    
    printf("Lista de partidos jugados despues de la modificacion \n");
    RecorrerPartidos(mundialx.partidosJugados);
    
    if( GrabarPartidosJugados( &(mundialx.partidosJugados) ) == TRUE ){
        return 1;
    };
    
    DestruirPartidos( mundialx.partidosPendientes );
    DestruirPartidos( mundialx.partidosJugados );
    DestruirEquipos(mundialx.equipos);
    
    return 0;
    
    
    
    
}

