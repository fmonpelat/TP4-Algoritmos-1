//
//  main.c
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
#include "menu.h"

int main(int argc, const char * argv[]){
    
    
    /*
    TestEquipos();
    TestTraerPartidos();
	// Test de modificacion de archivos
    if (TestFileDump()) {
        return EXIT_FAILURE;
    }
    // test de modificacion de un partido
    if ( TestModificarPartido() ) {
        return EXIT_FAILURE;
    }
    */
    
    /* ######################### VARIABLES ########################## */
    unsigned long id, gol1,gol2;
    tpartido * partidoAux;
    char NombreArchivoCSV[M];
    size_t counterEquipos;
    /* 
     ############################################################## */
    
    /*
     ####################### MUNDIAL DEFS ########################## */
    tmundial Brasil2014;
    Brasil2014.partidosJugados=NULL;
    Brasil2014.partidosPendientes=NULL;
    Brasil2014.q_equipos=0;
    Brasil2014.equipos=NULL;
    tvectorPosiciones * tablaPos= NULL;
    /* 
     ############################################################## */
    
    /* 
     traemos de archivo los equipos */
	Brasil2014.q_equipos = TraerEquipos(&(Brasil2014.equipos));
    if (Brasil2014.q_equipos==0) {
        fprintf(stderr, "Error, No hay equipos cargados.\n");
        return 1;
    }
    /* 
     traemos de archivo la lista de partidos */
	if(  TraerPartidos(Brasil2014.equipos, Brasil2014.q_equipos, &(Brasil2014.partidosPendientes))==TRUE  ){
        fprintf(stderr, "Error General de archivo.\n");
        return 1;
    }
	
    /* 
     validamos si los partidos estan bien definidos sino damos un error y decimos el porque... */
	if ( ValidarPartidos(Brasil2014.partidosPendientes) == TRUE ){
        fprintf(stderr, "La validacion de los partidos fue insatisfactoria, revise el archivo de partidos.\n");
        return EXIT_FAILURE;
    }
    
    tablaPos = CrearVecPos(Brasil2014.partidosJugados, Brasil2014.equipos, Brasil2014.q_equipos);
    
    if (  leerPartidosJugados(&(Brasil2014.partidosJugados),&(Brasil2014.partidosPendientes),Brasil2014.equipos,Brasil2014.q_equipos /*,tablaPos */ ) == TRUE ){
        return EXIT_FAILURE;
    }
    
    /* 
     actuaizamos la tabla de posiciones */
    ActualizarVecPos(Brasil2014.partidosJugados, tablaPos);
    
    
    
    /* 
     ############### BEGIN USER MENU ################################################# */
    
    opt_main state_menu=1;
    opt_subpartido state_submenu_partidos;
    opt_subsubpartidonuevo state_subsubmenu_partidonuevo;
    opt_subsubpartidojugado state_subsubmenu_partidojugado;
    opt_subreportes state_submenu_reportes;
    
    while ( state_menu != opt_exit ){
        
        PrintMainMenu();
        
        while ( state_menu != opt_exit ){
            
            state_menu=(opt_main)userInputUlong();
            //scanf("%ul",&state_menu);
            
            switch(state_menu){
                    
                case opt_partidos:
                    cls();
                    state_submenu_partidos=1;
                    while (state_submenu_partidos != opt_subpartidos_return) {
                        
                        PrintsubMenuPartidos();
                        state_submenu_partidos=(opt_subpartido)userInputUlong();
                        //scanf("%ul",&state_submenu_partidos);
                        
                        switch (state_submenu_partidos) {
                                
                            case opt_partidonuevojugado:
                                state_subsubmenu_partidonuevo=1;
                                while (state_subsubmenu_partidonuevo != opt_subpartidosnuevo_return) {
                                    cls();
                                    PrintsubsubMenuPartidos();
                                    state_subsubmenu_partidonuevo=(opt_subsubpartidonuevo)userInputUlong();
                                    //scanf("%ul",&state_subsubmenu_partidonuevo);
                                    switch (state_subsubmenu_partidonuevo) {
                                            
                                        case opt_id:
                                            // inicio de agregar partido por id
                                            printf("Ingrese el id del partido jugado: ");
                                            id=userInputUlong();
                                            if ( (partidoAux=BuscarPartidoPorId(Brasil2014.partidosPendientes, (int)id ) ) == NULL ){
                                                if(  (partidoAux=BuscarPartidoPorId(Brasil2014.partidosJugados, (int)id )) == NULL ){
                                                    fprintf(stderr,"No existe el id (%lu) de ese partido!\n",id);
                                                    getchar();
                                                    break;
                                                }
                                                printf("Ese partido ya se jugo.\n Por Favor utilize el submenu de partidos jugados opcion 1) Modificar.\n");
                                                getchar();
                                                break;
                                            }
                                            printf("\nIngrese los goles del equipo 1 ( %s ): \n",partidoAux->equipo1->nombre);
                                            gol1=userInputUlong();
                                            printf("Ingrese los goles del equipo 1 ( %s ): \n",partidoAux->equipo2->nombre);
                                            gol2=userInputUlong();
                                            if ( newPartidoJugadoXP(partidoAux,(int)gol1,(int)gol2,&Brasil2014.partidosPendientes,&Brasil2014.partidosJugados, Brasil2014.equipos, Brasil2014.q_equipos) == TRUE ){
                                                fprintf(stderr, "Error, al modificar el partido.\n");
                                                getchar();
                                                break;
                                            }
                                            ActualizarVecPos(Brasil2014.partidosJugados, tablaPos);
                                            // fin de agregar partido por id
                                            printf("Presione cualquier tecla para volver al menu ...\n");
                                            getchar();
                                            break;
                                            
                                        case opt_equipo:
                                            //se agrega un nuevo partido por equipo ...
                                            printf("agrego un nuevo partido por equipo\n");
                                            getchar();
                                            break;
                                            
                                        case opt_subpartidosnuevo_return:
                                            cls();
                                            break;
                                            
                                        default:
                                            printf("%s\n","Opcion Invalida");
                                            //dump_line(stdin);
                                            printf("Presione cualquier tecla para volver al subsubmenu de nuevos partidos ...\n");
                                            getchar();
                                            break;

                                    }
                                    //dump_line(stdin);
                                    
                                }
                                break;
                                
                            case opt_partidojugado:
                                state_subsubmenu_partidojugado=1;
                                while (state_subsubmenu_partidojugado != opt_subpartidosjugados_return) {
                                    cls();
                                    PrintsubsubMenuPartidosJugados();
                                    state_subsubmenu_partidojugado=(opt_subsubpartidojugado)userInputUlong();
                                    //scanf("%ul",&state_subsubmenu_partidojugado);
                                    switch (state_subsubmenu_partidojugado) {
                                            
                                        case opt_modificar:
                                            printf("Ingrese el id del partido jugado que quiere modificar: ");
                                            id=userInputUlong();
                                            if ( (partidoAux=BuscarPartidoPorId(Brasil2014.partidosJugados, (int)id ) ) == NULL ){
                                                if(  (partidoAux=BuscarPartidoPorId(Brasil2014.partidosPendientes, (int)id )) == NULL ){
                                                    fprintf(stderr,"No existe el id (%lu) de ese partido!\n",id);
                                                    getchar();
                                                    break;
                                                }
                                                printf("Ese partido no se jugo todavia.\n Para modificar ingrese uno que ya se haya jugado.\n");
                                                getchar();
                                                break;
                                            }
                                            printf("\nIngrese los goles del equipo 1 ( %s ): ",partidoAux->equipo1->nombre);
                                            gol1=userInputUlong();
                                            printf("\nIngrese los goles del equipo 1 ( %s ): ",partidoAux->equipo2->nombre);
                                            gol2=userInputUlong();
                                            ModificarPartidoJugado(Brasil2014.partidosJugados, partidoAux, (int)gol1, (int)gol2, tablaPos);
                                            printf("se modifico el partido:\n ");
                                            printf("%s  %d vs %s %d \n",partidoAux->equipo1->nombre,partidoAux->golesEq1,partidoAux->equipo2->nombre,partidoAux->golesEq2);
                                            
                                            getchar();
                                            break;
                                            
                                        case opt_eliminar:
                                            //eliminar un partido ya jugado ...
                                            printf("elimino un partido ya jugado de la lista de jugados\n");
                                            printf("Ingrese el id del partido jugado que quiere eliminar: ");
                                            id=userInputUlong();
                                            if ( (partidoAux=BuscarPartidoPorId(Brasil2014.partidosJugados, (int)id ) ) == NULL ){
                                                if(  (partidoAux=BuscarPartidoPorId(Brasil2014.partidosPendientes, (int)id )) == NULL ){
                                                    fprintf(stderr,"No existe el id (%lu) de ese partido!\n",id);
                                                    getchar();
                                                    break;
                                                }
                                                printf("Ese partido no se jugo todavia.\n Para eliminar ingrese uno que ya se haya jugado.\n");
                                                getchar();
                                                break;
                                            }
                                            gol1=0;
                                            gol2=0;
                                            newPartidoJugadoXP(partidoAux, (int)gol1, (int)gol2, &Brasil2014.partidosJugados, &Brasil2014.partidosPendientes, Brasil2014.equipos, Brasil2014.q_equipos);
                                            printf("se elimino el partido:\n ");
                                            printf("%s vs %s \n",partidoAux->equipo1->nombre,partidoAux->equipo2->nombre);
                                            printf("\nPresione cualquier tecla para volver al menu ...\n");
                                            getchar();
                                            break;
                                            
                                        case opt_subpartidosjugados_return:
                                            cls();
                                            break;
                                            
                                        default:
                                            printf("%s\n","Opcion Invalida");
                                            dump_line(stdin);
                                            printf("\nPresione cualquier tecla para volver al subsubmenu de partidos jugados ...\n");
                                            getchar();
                                            cls();
                                            break;

                                    }
                                    //dump_line(stdin);
                                }
                                cls();
                                break;
                                
                            case opt_subpartidos_return:
                                cls();
                                break;
                                
                            default:
                                printf("%s\n","Opcion Invalida");
                                dump_line(stdin);
                                printf("Presione cualquier tecla para volver al submenu de partidos ...\n");
                                getchar();
                                cls();
                                break;

                        }
                        
                    }
                    //dump_line(stdin);
                    //getchar();
                    cls();
                    break;
                    
                case opt_reportes:
                    state_submenu_reportes=1;
                    while ( state_submenu_reportes != opt_subreportes_return ) {
                        cls();
                        PrintsubMenuReportes();
                        state_submenu_reportes=(opt_subreportes)userInputUlong();
                        //scanf("%ul",&state_submenu_reportes);
                        
                        switch (state_submenu_reportes) {
                                
                            case opt_equipos:
                                printf("Lista de equipos del mundial\n");
                                for (counterEquipos=0; counterEquipos<Brasil2014.q_equipos; counterEquipos++) {
                                    printf("Grupo: %s Pais: %s\n",Brasil2014.equipos[counterEquipos].id,Brasil2014.equipos[counterEquipos].nombre);
                                }
                                printf("Presione cualquier tecla para volver al menu de reportes ...\n");
                                getchar();
                                break;
                                
                            case opt_partidospendientes:
                                printf("Lista de Partidos Pendientes: \n");
                                RecorrerPartidos(Brasil2014.partidosPendientes);
                                printf("Presione cualquier tecla para volver al menu de reportes ...\n");
                                getchar();
                                break;
                                
                            case opt_tablapos:
                                printf("Lista de Posiciones por grupos: \n");
                                RecorrerTablaPos(tablaPos);
                                printf("Presione cualquier tecla para volver al menu de reportes ...\n");
                                getchar();
                                break;
                                
                            case opt_subreportes_return:
                                cls();
                                break;
                                
                            default:
                                printf("%s\n","Opcion Invalida");
                                dump_line(stdin);
                                printf("Presione cualquier tecla para volver al menu de reportes ...\n");
                                getchar();
                                cls();
                                break;

                        }
                    //dump_line(stdin);
                    }
                    break;
                    
                case opt_csv:
                    printf("Opcion de carga avanzada mediante archivo de partidos en csv con sus goles\n");
                    printf("Se debe de ingresar en el siguiente formato:\n");
                    printf("1,A1,A2,12/06/2014,golA1,golA2\n");
                    printf("Ingrese el nombre del archivo: (para salir escriba salir) \n");
                    fgets(NombreArchivoCSV, M+1, stdin);
                    NombreArchivoCSV[strlen(NombreArchivoCSV)-1]='\0';
                    if ( !strcmp(NombreArchivoCSV, "salir") ) {
                        cls();
                        break;
                    }
                    if( leerPartidosCSV(&Brasil2014.partidosJugados, &Brasil2014.partidosPendientes, Brasil2014.equipos, Brasil2014.q_equipos,NombreArchivoCSV,tablaPos)==TRUE)break;
                    ActualizarVecPos(Brasil2014.partidosJugados, tablaPos);
                    printf("Se cargaron satisfactoriamente los partidos.\n");
                    printf("Presione cualquier tecla para volver al menu principal...\n");
                    getchar();
                    break;
                    
                case opt_exit:
                    cls();
                    break;
                
                default:
                    printf("%s\n","Opcion Invalida");
                    dump_line(stdin);
                    printf("Presione cualquier tecla para volver al menu principal ...\n");
                    getchar();
                    cls();
                    break;
            }
            cls();
            break;
        }

        
    }
    
    /* 
     ###################### END USER MENU ############################################## */
    
    if( GrabarPartidosJugados( &(Brasil2014.partidosJugados) ) == TRUE ){
        return 1;
    };
    
    DestruirPartidos( Brasil2014.partidosPendientes );
    DestruirPartidos( Brasil2014.partidosJugados );
    DestruirEquipos(Brasil2014.equipos);


    
    return EXIT_SUCCESS;
    
}

