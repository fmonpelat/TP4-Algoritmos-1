//
//  tareas.c
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


void dump_line(FILE *fp) {
    int ch;
    while ( (ch = fgetc(fp)) != EOF && ch != '\n');
}




size_t TraerEquipos( tequipo **  equipos ){
    
    if ( (*equipos)!=NULL ) {
        fprintf(stderr, "Error, por favor ingrese un puntero equipo nulo");
        return 0;
    }
    
    tequipo * aux=NULL;
    size_t used_size=0;
    size_t alloc_size=0,init_chop=2,chop_size=4;
    FILE * fpequipos;
    size_t i=0;
    char str[M_ID+M];
    char * pstr;
    char* pstr2;

    if (  !( fpequipos = fopen("grupos.txt", "r") )  ){
        fprintf(stderr, "Error, no se pudo abrir grupos.txt, existe?");
        return 0;
    }
    
    /* pedimos memoria por primera vez antes de reallocar si es que necesitamos memoria.
     */
    if (  !( *equipos = (tequipo*)malloc( sizeof(tequipo)*init_chop) )  ) {
        fprintf(stderr, "Error, could not find memory");
        return 0;
    }
    
    alloc_size=init_chop;
    
    while ( fgets(str, M_ID+M+1 , fpequipos) ){
        
        /* nos preguntamos si necesitamos memoria ... pedimos de a chops o de a pedazos
         */
        if ( used_size == alloc_size ) {
        
            if (  !( aux = (tequipo *)realloc(*equipos, sizeof(tequipo)*( alloc_size+chop_size) ))  ) {
                fprintf(stderr, "Error, could not find memory");
                free(*equipos);
                *equipos=NULL;
                return 0;
            }
            *equipos=aux;
            alloc_size+=chop_size;
            i++;
            /* debugging alloc size callouts
            printf("counter:%lu alloc:%lu chop_size:%lu\n",i,alloc_size,chop_size);
            */
        }
        
        pstr = strtok(str,";");
        if ( pstr ) strcpy ( (*equipos)[used_size].id , pstr);
        
        pstr = strtok(NULL,";");
        pstr2 = strtok(pstr,"\r\n");
       
        if( pstr2 ) strcpy( (*equipos)[used_size].nombre, pstr2);
        
        used_size++;
        
    }
    
    fclose(fpequipos);
    // para debug sacar despues de pasar las pruebas
    //printf("%s\n",equipos[1].nombre);
    //printf("%s\n",equipos[1].id);
    
    return used_size-1;
}


void DestruirEquipos( tequipo * equipos){
    
    free(equipos);

}

// ########## ERIK ######################################


size_t TraerPartidos( tequipo * equipos,size_t sizeEquipos, tlista * lista)
{
    //aca hacemos que lo apuntado por lista que es un tnodo * sea null.
	(*lista) = NULL;
	FILE * fileReader;
    
    
	if (  !(fileReader = fopen("partidos.txt", "r"))  )
	{
		puts("No existe el archivo partidos.txt");
		return 1;
	}
    
	while (!feof(fileReader))
	{
        
        
		int idPartido = 0;
		char idEquipo1[M_ID];
		char idEquipo2[M_ID];
		int dia = 0, mes = 0, anio = 0;
		/*Parseo segun el formato de partidos.txt*/
		fscanf(fileReader, "%d;%2c;%2c;%d/%d/%d\n", &idPartido, (char * )&idEquipo1, (char *)&idEquipo2, &dia, &mes, &anio);
        
		idEquipo1[2] = '\0';
		idEquipo2[2] = '\0';
		/*Agrego,por linea, un nodo  a la lista */
		AgregarNodoEquipo(&(*lista), equipos, sizeEquipos, idPartido, idEquipo1, idEquipo2, dia, mes, anio);
	}
    
	/*Le asigno la cadena a la lista*/
	//(*lista) = aux;
    
	return 1;
}

void AgregarNodoEquipo(tnodo ** nodo, tequipo* equipos,size_t sizeEquipos, int idPartido, char * idEquipo1, char * idEquipo2, int dia, int mes, int anio)
{
	if (!(*nodo))
	{
		tnodo* aux = (*nodo);
		(*nodo) = (tnodo*)malloc(sizeof(tnodo)* 1);
		(*nodo)->dato = (tpartido*)malloc(sizeof(tpartido)* 1);
		(*nodo)->dato->idPartido = idPartido;
		(*nodo)->dato->equipo1 = BuscarEquipoPorId(equipos, idEquipo1, sizeEquipos);
		(*nodo)->dato->equipo2 = BuscarEquipoPorId(equipos, idEquipo2, sizeEquipos);
        (*nodo)->dato->golesEq1=0;
        (*nodo)->dato->golesEq2=0;
		(*nodo)->dato->fecha.dd = dia;
		(*nodo)->dato->fecha.mm = mes;
		(*nodo)->dato->fecha.aaaa = anio;
		(*nodo)->sig = aux;
	}
	else
	{
		AgregarNodoEquipo(&(*nodo)->sig, equipos, sizeEquipos, idPartido, idEquipo1, idEquipo2, dia, mes, anio);
	}
    
}

void RecorrerPartidos(tlista lista)
{
	while (lista)
	{
		if (lista->dato->idPartido)
			printf("%d", lista->dato->idPartido);
        
		if (lista->dato->fecha.dd && lista->dato->fecha.mm && lista->dato->fecha.aaaa)
			printf(" (%d/%d/%d) ", lista->dato->fecha.dd, lista->dato->fecha.mm, lista->dato->fecha.aaaa);
        
		if (lista->dato->equipo1 && lista->dato->equipo2)
			printf("Equipo1: %s, Equipo2: %s", lista->dato->equipo1->nombre, lista->dato->equipo2->nombre);
		puts("");
        
		lista = lista->sig;
	}
    
}

tequipo * BuscarEquipoPorId(tequipo * equipos, char * id , size_t size){
    
    size_t i;
    
    for (i=0; i!=size; i++) {
    
		if ( !strcmp(equipos[i].id, id) )
		{
			return &equipos[i];
		}
        

	}
	return NULL;
}


void DestruirPartidos( tnodo * nodo){
    
 
    if ( nodo->sig == NULL) {
        free(nodo->dato);
        nodo->dato=NULL;
        free(nodo);
        nodo=NULL;
    }
    else DestruirPartidos( nodo->sig );
    
    
}



// GRABACION DE ARCHIVOS BINARIOS

t_bool GrabarPartidosJugados( tlista * lista_jugados ){
    
    FILE * fpPartidosJugados;
    char NombreArchivo[M];
    strcpy(NombreArchivo, "partidosjugados.dat");
    
    int buffer[M_ID-1];
    
    
    fpPartidosJugados = fopen(NombreArchivo,"wb");
    
    if (!fpPartidosJugados) {
        fprintf(stderr, "Error, no se pudo abrir %s",NombreArchivo);
        return TRUE;
    }
    
    while ( !((*lista_jugados)->sig) ) {

        buffer[0] = (*lista_jugados)->dato->idPartido;
        buffer[1] = (*lista_jugados)->dato->golesEq1;
        buffer[1] = (*lista_jugados)->dato->golesEq2;
        
        fwrite(buffer, sizeof(int), sizeof(buffer), fpPartidosJugados);
        
    }
    
    return FALSE;
    
}





// ############### LUCA ############################


tpartido * BuscarPartidoPorId (tlista lista, int id){
    
    tnodo * aux = lista;
    
    
    while ( aux ){
        
        if( aux->dato->idPartido == id )  return aux->dato;
        else  aux = aux->sig;
        
    }
    
    return NULL;
    
}



tpartido * BuscarPartidoPorEquipos (tlista lista, char * id1, char * id2 ){
    
    tnodo * aux= lista;
    
    while ( aux ){
        
        if( !(strcmp(aux->dato->equipo1->id,id1)) && !(strcmp(aux->dato->equipo2->id,id2))  )  return aux->dato;
        if( !(strcmp(aux->dato->equipo1->id,id2)) && !(strcmp(aux->dato->equipo2->id,id1))  )  return aux->dato;
        else  aux= aux->sig;
        
    }
    
    return NULL;
    
}













