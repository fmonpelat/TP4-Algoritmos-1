//
//  menu.c
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
#include <ctype.h>
#include "tareas.h"
#include "menu.h"

void cls(void){
    // para unix,bsd, linux solamente.
    system("clear");
    // para windows
     //system("cls");
}


void PrintMainMenu(void){

    printf("##########################################################################\n");
    printf("menu principal\n");
    printf("1) Partidos\n");
    printf("2) Reportes\n");
    printf("3) Carga Csv (Opcion Avanzada)\n\n");

    printf("Presione 0 para salir... \n");
    printf("##########################################################################\n");

}

void PrintsubMenuPartidos(void){

    printf("##########################################################################\n");
    printf("submenu partidos\n");
    printf("1) Nuevo Partido Jugado\n");
    printf("2) Partidos Jugados\n\n");

    printf("Presione 0 para volver al menu principal ... \n\n");
    printf("##########################################################################\n");

}

void PrintsubMenuReportes(void){

    printf("##########################################################################\n");
    printf("submenu reportes\n");
    printf("1) reportes por equipos\n");
    printf("2) reportes por partidos pendientes\n");
    printf("3) imprimir tablas de posiciones por grupos\n\n");

    printf("Presione 0 para volver al menu principal ... \n\n");
    printf("##########################################################################\n");

}

void PrintsubsubMenuPartidos(void){

    printf("##########################################################################\n");
    printf("submenu partidos nuevos jugados\n");
    printf("1) Nuevo partido jugado por id\n");
    printf("2) Nuevo partido jugado por equipos\n\n");

    printf("Presione 0 para volver al menu de partidos ... \n\n");
    printf("##########################################################################\n");

}

void PrintsubsubMenuPartidosJugados(void){

    printf("##########################################################################\n");
    printf("submenu partidos jugados\n");
    printf("1) Modificar partido jugado por id\n");
    printf("2) Eliminar partido jugado por id\n\n");

    printf("Presione 0 para volver al menu de partidos ... \n\n");
    printf("##########################################################################\n");

}
