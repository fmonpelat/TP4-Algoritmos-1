//
//  menu.h
//  TP4 Algoritmos 1
//
//  Created by fmonpelat on 6/29/14.
//  Copyright (c) 2014 ___FMONPELAT___. All rights reserved.
//

#ifndef TP4_Algoritmos_1_menu_h
#define TP4_Algoritmos_1_menu_h

// main menu
typedef enum opt{ opt_exit,opt_partidos,opt_reportes,opt_csv} opt_main;
    // submenu partidos
    typedef enum option_subpartidos{ opt_subpartidos_return,opt_partidonuevojugado,opt_partidojugado } opt_subpartido;
        // subsubmenu partidos
        typedef enum option_subsubpartidosnuevo { opt_subpartidosnuevo_return,opt_id,opt_equipo } opt_subsubpartidonuevo;
        typedef enum option_subsubpartidosjugados { opt_subpartidosjugados_return,opt_modificar,opt_eliminar } opt_subsubpartidojugado;

    // menu reportes
    typedef enum option_subreportes { opt_subreportes_return,opt_equipos,opt_partidospendientes,opt_tablapos } opt_subreportes;


// prototipos

void PrintMainMenu(void);
void PrintsubMenuPartidos(void);
void PrintsubsubMenuPartidos(void);
void PrintsubMenuReportes(void);
void PrintsubsubMenuPartidosJugados(void);
void cls(void);



#endif
