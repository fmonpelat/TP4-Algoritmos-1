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
#include "tareas.h"
#include <stdlib.h>
#include <string.h>
#include "menu.h"

int main(int argc, const char * argv[]){
    
    
	/*TestEquipos();
    TestTraerPartidos();
	
    if (TestFileDump()) {
        return EXIT_FAILURE;
    }
    */
    
    opt_main state_menu=1;
    opt_subpartido state_submenu_partidos;
    opt_subsubpartidonuevo state_subsubmenu_partidonuevo;
    opt_subsubpartidojugado state_subsubmenu_partidojugado;
    opt_subreportes state_submenu_reportes;
    
    while ( state_menu != opt_exit ){
        
        PrintMainMenu();
        
        while ( state_menu != opt_exit ){
            
            scanf("%ul",&state_menu);
            
            switch(state_menu){
                    
                case opt_partidos:
                    cls();
                    state_submenu_partidos=1;
                    while (state_submenu_partidos != opt_subpartidos_return) {
                        
                        PrintsubMenuPartidos();
                        scanf("%ul",&state_submenu_partidos);
                        
                        switch (state_submenu_partidos) {
                                
                            case opt_partidonuevojugado:
                                state_subsubmenu_partidonuevo=1;
                                while (state_subsubmenu_partidonuevo != opt_subpartidosnuevo_return) {
                                    cls();
                                    PrintsubsubMenuPartidos();
                                    scanf("%ul",&state_subsubmenu_partidonuevo);
                                    switch (state_subsubmenu_partidonuevo) {
                                        case opt_id:
                                            //se agrega un nuevo partido por id...
                                            printf("agrego un nuevo partido por id\n");
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
                                            dump_line(stdin);
                                            printf("Presione cualquier tecla para volver al subsubmenu de nuevos partidos ...\n");
                                            getchar();

                                            break;

                                    }
                                    dump_line(stdin);
                                    
                                }
                                break;
                                
                            case opt_partidojugado:
                                state_subsubmenu_partidojugado=1;
                                while (state_subsubmenu_partidojugado != opt_subpartidosjugados_return) {
                                    cls();
                                    PrintsubsubMenuPartidosJugados();
                                    scanf("%ul",&state_subsubmenu_partidojugado);
                                    switch (state_subsubmenu_partidojugado) {
                                        case opt_modificar:
                                            // modificar un partido ya jugado ...
                                            printf("modifico un partido ya jugado de la lista de jugados\n");
                                            getchar();
                                            break;
                                        case opt_eliminar:
                                            //eliminar un partido ya jugado ...
                                            printf("elimino un partido ya jugado de la lista de jugados\n");
                                            getchar();
                                            break;
                                        case opt_subpartidosjugados_return:
                                            cls();
                                            break;
                                        default:
                                            printf("%s\n","Opcion Invalida");
                                            dump_line(stdin);
                                            printf("Presione cualquier tecla para volver al subsubmenu de partidos jugados ...\n");
                                            getchar();
                                            cls();
                                            break;

                                    }
                                    dump_line(stdin);
                                }
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
                    getchar();
                    cls();
                    break;
                    
                case opt_reportes:
                    state_submenu_reportes=1;
                    while ( state_submenu_reportes != opt_subreportes_return ) {
                        cls();
                        PrintsubMenuReportes();
                        scanf("%ul",&state_submenu_reportes);
                        
                        switch (state_submenu_reportes) {
                            case opt_equipos:
                                //reportes por equipos ...
                                printf("imprimo los reportes por eqipos\n");
                                getchar();
                                break;
                            case opt_partidospendientes:
                                // reportes de los partidos pendientes ...
                                printf("imprimo los resportes de la lista de partidos pendientes\n");
                                getchar();
                                break;
                            case opt_tablapos:
                                // imprimimos la tabla de posicicones por grupos ...
                                printf("imprimo la taba de posciiones \n");
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
                    dump_line(stdin);
                    }
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
    
    
    
    return EXIT_SUCCESS;
    
}

