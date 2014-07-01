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
#include <ctype.h>
#include <string.h>
#include "tareas.h"


void dump_line(FILE *fp) {
	int ch;
	while ((ch = fgetc(fp)) != EOF && ch != '\n');
}


size_t TraerEquipos(tequipo **  equipos){

	if ((*equipos) != NULL) {
		fprintf(stderr, "Error, por favor ingrese un puntero equipo nulo\n");
		return 0;
	}

	tequipo * aux = NULL;
	size_t used_size = 0;
	size_t alloc_size = 0, init_chop = 2, chop_size = 4;
	FILE * fpequipos;
	size_t i = 0;
	char str[M_ID + M];
	char * pstr;
	char* pstr2;

	if (!(fpequipos = fopen("grupos.txt", "r"))){
		fprintf(stderr, "Error, no se pudo abrir grupos.txt, existe?\n");
		return 0;
	}

	/* pedimos memoria por primera vez antes de reallocar si es que necesitamos memoria.
	 */
	if (!(*equipos = (tequipo*)malloc(sizeof(tequipo)*init_chop))) {
		fprintf(stderr, "Error, could not find memory\n");
		return 0;
	}

	alloc_size = init_chop;

	while (fgets(str, M_ID + M + 1, fpequipos)){

		/* nos preguntamos si necesitamos memoria ... pedimos de a chops o de a pedazos
		 */
		if (used_size == alloc_size) {

			if (!(aux = (tequipo *)realloc(*equipos, sizeof(tequipo)*(alloc_size + chop_size)))) {
				fprintf(stderr, "Error, could not find memory\n");
				free(*equipos);
				*equipos = NULL;
				return 0;
			}
			*equipos = aux;
			alloc_size += chop_size;
			i++;
			/* debugging alloc size callouts
			printf("counter:%lu alloc:%lu chop_size:%lu\n",i,alloc_size,chop_size);
			*/
		}

		pstr = strtok(str, ";");
		if (pstr) strcpy((*equipos)[used_size].id, pstr);

		pstr = strtok(NULL, ";");
		pstr2 = strtok(pstr, "\r\n");

		if (pstr2) strcpy((*equipos)[used_size].nombre, pstr2);

		used_size++;

	}

	fclose(fpequipos);

	return used_size - 1;
}


void DestruirEquipos(tequipo * equipos){

	free(equipos);

}


t_bool GrabarPartidosJugados(tlista * lista_jugados){
    
	FILE * fpPartidosJugados;
	tlista aux;
	char NombreArchivo[M];
	strcpy(NombreArchivo, "partidosjugados.dat");
    
	int buffer[M_ID];
    
    
	fpPartidosJugados = fopen(NombreArchivo, "wb");
    
	if (!fpPartidosJugados) {
		fprintf(stderr, "Error, no se pudo abrir %s\n", NombreArchivo);
		return TRUE;
	}
    
    // prevenimos un sigsegv por si le pasamos null como lista.
    if (lista_jugados) {
        aux = (*lista_jugados);
        while (aux) {
        
            buffer[0] = aux->dato->idPartido;
            buffer[1] = aux->dato->golesEq1;
            buffer[2] = aux->dato->golesEq2;
        
            fwrite(buffer, sizeof(int), 3, fpPartidosJugados);
            fflush(fpPartidosJugados);
            aux = aux->sig;
        }
    }
	fclose(fpPartidosJugados);
	return FALSE;
    
}

t_bool leerPartidosJugados(tlista * listaJugados , tlista * listaPartidos, tequipo * equipos, size_t cantEquipos/*, tvectorPosiciones * tablaPos */){
    
	FILE * fpPartidosJugados;
	char NombreArchivo[M];
	strcpy(NombreArchivo, "partidosjugados.dat");
	int buffer[M_FILE];
    
    
    if (!*listaPartidos) {
        fprintf(stderr, "Error, lista de partidos no inicializada (estado nil).\n");
        fprintf(stderr, "Hint: Utilizo la funcion despues de cargar los partidos?...\n");
        return TRUE;
    }
    
    if (!equipos) {
        fprintf(stderr, "Error, array equipos no inicializada (estado nil).\n");
        fprintf(stderr, "Hint: Utilizo la funcion despues de cargar los equipos?...\n");
        return TRUE;
    }
    
	fpPartidosJugados = fopen(NombreArchivo, "rb");
    
	if (!fpPartidosJugados) {
		fprintf(stderr, "Error, no se pudo abrir %s\n", NombreArchivo);
        fprintf(stderr, "Si es la primera vez que corre el programa ejecute devuelta por favor\n");
        GrabarPartidosJugados(NULL);
		return TRUE;
	}
    
	while (fread(buffer, sizeof(int), 1, fpPartidosJugados)) {
		/*printf("%d ", buffer[0]);*/
		fread(buffer+1, sizeof(int), 1, fpPartidosJugados);
		/*printf("%d ", buffer[1]);*/
		fread(buffer+2, sizeof(int), 1, fpPartidosJugados);
		/*printf("%d \n", buffer[2]);*/
        
        newPartidoJugado(buffer[ID],buffer[GOL1],buffer[GOL2],listaPartidos,listaJugados, equipos, cantEquipos/*, tablaPos */);
        
	}
	return FALSE;
    
}

unsigned long userInputUlong(void){
    
    char buff[M];
    unsigned long number;
    char ** ptr;
    
    //dump_line(stdin);
    fgets(buff, M, stdin);
    number=strtoul( buff, ptr, 10);
    
    return number;
}

//API CSV carga

t_bool leerPartidosAPI(tlista * listaJugados , tlista * listaPartidos, tequipo * equipos, size_t cantEquipos,char * NombreArchivo,tvectorPosiciones * tablaPos){
    
	FILE * fpPartidosAPI;
    tpartido * partidoAux;
    int idPartido = 0;
    char idEquipo1[M_ID];
    char idEquipo2[M_ID];
    int dia = 0, mes = 0, anio = 0;
    int gol1,gol2;
    
    
    if (!*listaPartidos) {
        fprintf(stderr, "Error, lista de partidos no inicializada (estado nil).\n");
        fprintf(stderr, "Hint: Utilizo la funcion despues de cargar los partidos?...\n");
        return TRUE;
    }
    
    if (!equipos) {
        fprintf(stderr, "Error, array equipos no inicializada (estado nil).\n");
        fprintf(stderr, "Hint: Utilizo la funcion despues de cargar los equipos?...\n");
        return TRUE;
    }
    
	fpPartidosAPI = fopen(NombreArchivo, "rb");
    
	if (!fpPartidosAPI) {
		fprintf(stderr, "Error, no se pudo abrir %s\n", NombreArchivo);
		return TRUE;
	}
    
    while (!feof(fpPartidosAPI)){
        
        fscanf(fpPartidosAPI, "%d,%2c,%2c,%d/%d/%d,%d,%d\n", &idPartido, (char *)&idEquipo1, (char *)&idEquipo2, &dia, &mes, &anio,&gol1,&gol2);
        
        if ( (partidoAux=BuscarPartidoPorId(*listaPartidos, (int)idPartido ) ) == NULL ){
            if(  (partidoAux=BuscarPartidoPorId(*listaJugados, (int)idPartido )) == NULL ){
                fprintf(stderr,"No existe el id (%d) de ese partido!\n",idPartido);
                fprintf(stderr, "Archivo de API CSV Malformado verifique y pruebe nuevamente.\n");
                return TRUE;
            }
            ModificarPartidoJugado(*listaJugados, partidoAux, gol1, gol2, tablaPos);
        }
        else newPartidoJugadoXP(partidoAux, gol1, gol2, listaPartidos, listaJugados, equipos, cantEquipos);
        
	}
	return FALSE;
    
}




// ########## ERIK ######################################


t_bool TraerPartidos(tequipo * equipos, size_t sizeEquipos, tlista * lista)
{
	//aca hacemos que lo apuntado por lista que es un tnodo * sea null.
	(*lista) = NULL;
	FILE * fileReader;


	if (!(fileReader = fopen("partidos.txt", "r")))
	{
		fprintf(stderr,"No existe el archivo partidos.txt\n");
		return TRUE;
	}

	while (!feof(fileReader))
	{


		int idPartido = 0;
		char idEquipo1[M_ID];
		char idEquipo2[M_ID];
		int dia = 0, mes = 0, anio = 0;
		/*Parseo segun el formato de partidos.txt*/
		fscanf(fileReader, "%d;%2c;%2c;%d/%d/%d\n", &idPartido, (char *)&idEquipo1, (char *)&idEquipo2, &dia, &mes, &anio);

		idEquipo1[2] = '\0';
		idEquipo2[2] = '\0';
		/*Agrego,por linea, un nodo  a la lista */
		AgregarNodoEquipo(&(*lista), equipos, sizeEquipos, idPartido, idEquipo1, idEquipo2, dia, mes, anio);
	}

	/*Le asigno la cadena a la lista*/
	//(*lista) = aux;

	return FALSE;
}

void AgregarNodoEquipo(tnodo ** nodo, tequipo* equipos, size_t sizeEquipos, int idPartido, char * idEquipo1, char * idEquipo2, int dia, int mes, int anio)
{
	if (!(*nodo))
	{
		tnodo* aux = (*nodo);
		(*nodo) = (tnodo*)malloc(sizeof(tnodo)* 1);
		(*nodo)->dato = (tpartido*)malloc(sizeof(tpartido)* 1);
		(*nodo)->dato->idPartido = idPartido;
		(*nodo)->dato->equipo1 = BuscarEquipoPorId(equipos, idEquipo1, sizeEquipos);
		(*nodo)->dato->equipo2 = BuscarEquipoPorId(equipos, idEquipo2, sizeEquipos);
		(*nodo)->dato->golesEq1 = 0;
		(*nodo)->dato->golesEq2 = 0;
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
			printf("%s-%s (%d:%d)", lista->dato->equipo1->nombre, lista->dato->equipo2->nombre, lista->dato->golesEq1,lista->dato->golesEq2);
		puts("");

		lista = lista->sig;
	}

}

tequipo * BuscarEquipoPorId(tequipo * equipos, char * id, size_t size){

	size_t i;

	for (i = 0; i != size; i++) {

		if (!strcmp(equipos[i].id, id))
		{
			return &equipos[i];
		}


	}
	return NULL;
}


void DestruirPartidos(tnodo * nodo){

    //prevengo un super bug con el if(nodo)
    if (nodo) {
        if (nodo->sig == NULL) {
            free(nodo->dato);
            nodo->dato = NULL;
            free(nodo);
            nodo = NULL;
        }
        else DestruirPartidos(nodo->sig);
    }

}

t_bool ValidarPartidos(tlista lista){
    
	int validado = 1, fila = 0, filaAux = 0;
	tnodo* nodo = lista;


	while (nodo && validado){

		lista = nodo->sig;
		filaAux = 0;
		fila++;
		while (lista&&validado)
		{
			if (nodo->dato->idPartido == lista->dato->idPartido)
				validado = 0;
			char*nodoEquipo1 = nodo->dato->equipo1->id;
			char*nodoEquipo2 = nodo->dato->equipo2->id;
			char*listaEquipo1 = lista->dato->equipo1->id;
			char*listaEquipo2 = lista->dato->equipo2->id;

			if (nodoEquipo1 && nodoEquipo2 && listaEquipo1 && listaEquipo2)
			{
				if ((!strcmp(nodoEquipo1, listaEquipo1) && !strcmp(nodoEquipo2, listaEquipo2)) || (!strcmp(nodoEquipo1, listaEquipo2) && !strcmp(nodoEquipo2, listaEquipo1)))
					validado = 0;
			}
			if (validado)
				filaAux++;
			lista = lista->sig;
		}
		nodo = nodo->sig;
	}

	if (!validado){

		fprintf(stderr, "Error en la fila numero: %d \n", (fila + filaAux));
		return TRUE;

	}
	return FALSE;
}





// ############### LUCA ############################


tpartido * BuscarPartidoPorId(tlista lista, int id){

	tnodo * aux = lista;


	while (aux){

		if (aux->dato->idPartido == id)  return aux->dato;
		else  aux = aux->sig;

	}

	return NULL;

}



tpartido * BuscarPartidoPorEquipos(tlista lista, char * id1, char * id2){

	tnodo * aux = lista;

	while (aux){

		if (!(strcmp(aux->dato->equipo1->id, id1)) && !(strcmp(aux->dato->equipo2->id, id2)))  return aux->dato;
		if (!(strcmp(aux->dato->equipo1->id, id2)) && !(strcmp(aux->dato->equipo2->id, id1)))  return aux->dato;
		else  aux = aux->sig;

	}

	return NULL;

}


void  SwitchNodo(tlista * partidoAnterior, tlista * partidoAeliminar, tlista * listaJugados)
{
	tnodo * nodo = (*listaJugados);
	tnodo * aux = NULL;
	if (!(*partidoAnterior))//el nodo es el primero de la lista de pendientes
	{
		aux = (*partidoAeliminar);
		(*partidoAeliminar) = (*partidoAeliminar)->sig;
		if (nodo)
		{
			while (nodo->sig) nodo = nodo->sig;
			nodo->sig = aux;
			nodo->sig->sig = NULL;
		}
		else //el nodo no existe
		{
			(*listaJugados) = aux;
			(*listaJugados)->sig = NULL;
		}

		//aux->sig = NULL;
	}
	else
	{
		(*partidoAnterior)->sig = (*partidoAeliminar)->sig;
		if (nodo)
		{
			while (nodo->sig)
				nodo = nodo->sig;
			nodo->sig = (*partidoAeliminar);
			nodo->sig->sig = NULL;
		}
		else
			(*listaJugados) = (*partidoAeliminar);
		(*partidoAeliminar)->sig = NULL;
	}

}


t_bool intercambiarNodo(tlista  *listapendientes, tlista *listajugados, tequipo * equipos, size_t sizeEquipos, tpartido * partido) //
{
	tnodo * partidoAeliminar = (*listapendientes);
	tnodo * partidoAnterior = NULL;

	if (!partido) return TRUE;

	while (partidoAeliminar)  // obtencion del nodo a eliminar y nodo anterior
	{
		if (partidoAeliminar->dato->idPartido == partido->idPartido){

			SwitchNodo(&partidoAnterior, &partidoAeliminar, listajugados);// pasa un nodo de una lista a la otra
			if (!partidoAnterior){
				(*listapendientes) = partidoAeliminar;
				return FALSE;
			}			
		}
		partidoAnterior = partidoAeliminar;
		partidoAeliminar = partidoAeliminar->sig;
	}
	return TRUE;
}


t_bool PartidoJugadoNuevo(char opcion, tlista * partidosPendientes, tlista * partidosJugados, tequipo * equipos, size_t qEquipos, tvectorPosiciones *tablaPos){
    
	tpartido * partido=NULL;
	t_bool error = FALSE;
	char  id1[M_ID], id2[M_ID];
	int id;
	if (opcion == 'i')
	{
		puts("Introduzca el id del partido");
		scanf("%d", &id);
		fflush(stdin);
		partido = BuscarPartidoPorId((*partidosPendientes), id);
		if (!partido)
		{
			partido = BuscarPartidoPorId((*partidosJugados), id);
			if (partido)
				puts("Ese partido ya se jugo");
			else
				puts("Ese partido es invalido");
			error = TRUE;
		}
	}
	else if (opcion == 'e')
	{
		puts("Introduzca el id del equipo1");
		gets(id1);
		puts("Introduzca el id del equipo1");
		gets(id2);
		partido = BuscarPartidoPorEquipos((*partidosPendientes), id1, id2);
		if (!partido)
		{
			partido = BuscarPartidoPorEquipos((*partidosJugados), id1, id2);
			if (partido)
				puts("Esos equipos ya jugaron");
			else
				puts("Ese partido es invalido");
			error = TRUE;
		}

	}
	if (error == FALSE)
	{
		printf("Introduzca los goles de %s: \n", partido->equipo1->nombre);
		scanf("%d", &partido->golesEq1);
		printf("Introduzca los goles de %s: \n", partido->equipo2->nombre);
		scanf("%d", &partido->golesEq2);
		fflush(stdin);
		intercambiarNodo(&(*partidosPendientes), &(*partidosJugados), equipos, qEquipos, partido);
		//ModificarTablaPos(tablaPos, partido, 0);
	}


	return error;
}


t_bool newPartidoJugado(int idPartido, int gol1, int gol2,tlista * partidosPendientes, tlista * partidosJugados, tequipo * equipos, size_t qEquipos/*, tvectorPosiciones *tablaPos*/){
    
    
        tpartido * partido=NULL;
    
		partido = BuscarPartidoPorId((*partidosPendientes), idPartido);
        // si no lo encontramos el partido en partidos pendientes lo buscamos en el jugado.
		if (!partido)
		{
			partido = BuscarPartidoPorId((*partidosJugados), idPartido);
			if (!partido) fprintf(stderr,"Ese partido es invalido");
			else fprintf(stderr,"Ese partido ya se jugo");
            return TRUE;
		}
	
        partido->golesEq1=gol1;
		partido->golesEq2=gol2;
		intercambiarNodo(partidosPendientes, partidosJugados, equipos, qEquipos, partido);
		//ModificarTablaPos(tablaPos, partido, 0);

        return FALSE;
}

t_bool newPartidoJugadoXP(tpartido * partido, int gol1, int gol2,tlista * partidosPendientes, tlista * partidosJugados, tequipo * equipos, size_t qEquipos){
	
    partido->golesEq1=gol1;
    partido->golesEq2=gol2;
    intercambiarNodo(partidosPendientes, partidosJugados, equipos, qEquipos, partido);
    return FALSE;
}



void RecorrerTablaPos(tvectorPosiciones *tablaPos)
{
	int i = 0, gf, gc, dg;
	tequipoPos* equipoT = NULL;
	char grupoText[6] = "GRUPO";
	char equipoText[7] = "EQUIPO";
	char grupo = 'A';

	while (grupo != 'I')
	{
		i = 0;
		printf("%8s %c --------------------------------\n", grupoText, grupo);
		printf("%15s    PTS PJ PG PE PP GF GC DF\n", equipoText);
		while ((*tablaPos)[i])
		{
			if ((*tablaPos)[i]->equipo->id[0] == grupo)
			{
				equipoT = (*tablaPos)[i];
				gf = equipoT->golesFavor;
				gc = equipoT->golesContra;
				dg = equipoT->golesDif;
				printf("%15s     %d  %d  %d  %d  %d  %d  %d  %d\n", equipoT->equipo->nombre, equipoT->puntos, equipoT->partidosJugados, equipoT->partidosGanados, equipoT->partidosEmpatados, equipoT->partidosPerdidos, gf, gc, dg);

			}
			i++;
		}
		printf("\n");
		grupo++;
	}

}

void IntercambiarVecPos(tequipoPos** equipo1, tequipoPos** equipo2)
{
	tequipoPos* aux = NULL;
	aux = (*equipo1);
	(*equipo1) = (*equipo2);
	(*equipo2) = aux;
}

void OrdenarTablaPos(tvectorPosiciones *tablaPos)
{

	int i = 1, j ;
	int ordenado = 0;
	while ((*tablaPos)[i] && ordenado == 0)
	{
		ordenado = 1;
		j = 0;
		while ((*tablaPos)[j + i])
		{
			if ((*tablaPos)[j + 1]->puntos > (*tablaPos)[j]->puntos)
				IntercambiarVecPos(&(*tablaPos)[j], &(*tablaPos)[j + 1]);

			if ((*tablaPos)[j + 1]->partidosJugados == (*tablaPos)[j]->partidosJugados)
			{

				if (((*tablaPos)[j + 1]->puntos == (*tablaPos)[j]->puntos) && ((*tablaPos)[j + 1]->golesDif > (*tablaPos)[j]->golesDif))
					IntercambiarVecPos(&(*tablaPos)[j], &(*tablaPos)[j + 1]);
			}

			ordenado = 0;
			j++;
		}
		i++;
	}
}

tequipoPos * BuscarEquipoPorIdEnTablaPos(tvectorPosiciones * equiposEnTabla, char * id)
{

	size_t i = 0;
	if ((*equiposEnTabla))
	{
		while ((*equiposEnTabla)[i])
		{
			if (id == (*equiposEnTabla)[i]->equipo->id)
				return (*equiposEnTabla)[i];
			i++;
		}
	}

	return NULL;
}

void ActualizarVecPos(tlista partidosJugados,tvectorPosiciones * vecPos)
{
	int i = 0;
	while ((*vecPos)[i])
	{
		(*vecPos)[i]->puntos = 0;
		(*vecPos)[i]->golesContra = 0;
		(*vecPos)[i]->golesFavor = 0;
		(*vecPos)[i]->golesDif = 0;
		(*vecPos)[i]->partidosEmpatados = 0;
		(*vecPos)[i]->partidosGanados = 0;
		(*vecPos)[i]->partidosJugados = 0;
		(*vecPos)[i]->partidosPerdidos = 0;
		i++;
	}
	while (partidosJugados)
	{
		ModificarTablaPos(vecPos, partidosJugados->dato, 0);
		partidosJugados = partidosJugados->sig;
	}
}

tvectorPosiciones * CrearVecPos(tlista partidosJugados, tequipo* equipos, size_t qEquipos)
{
	int i;

	tequipoPos** vec = NULL;
	tvectorPosiciones * vecPos = (tvectorPosiciones *)malloc(sizeof(tvectorPosiciones)* 1);
	vec = (tequipoPos**)malloc(sizeof(tequipoPos*)* (qEquipos + 1));


	for (i = 0; i < qEquipos + 1; i++)
	{
		vec[i] = (tequipoPos*)malloc(sizeof(tequipoPos)* 1);
		vec[i]->equipo = equipos + i;
		strcpy( &vec[i]->grupo , equipos[i].id );
		vec[i]->puntos = 0;
		vec[i]->golesContra = 0;
		vec[i]->golesFavor = 0;
		vec[i]->golesDif = 0;
		vec[i]->partidosEmpatados = 0;
		vec[i]->partidosGanados = 0;
		vec[i]->partidosJugados = 0;
		vec[i]->partidosPerdidos = 0;
	}
	vec[i] = NULL;
	(*vecPos) = vec;	

	return vecPos;
}


t_bool ModificarTablaPos(tvectorPosiciones * tablaPos, tpartido * partido, int borrar)
{
	t_bool error = FALSE;
	tequipoPos* eq1, *eq2;

	eq1 = BuscarEquipoPorIdEnTablaPos(tablaPos, partido->equipo1->id);
	eq2 = BuscarEquipoPorIdEnTablaPos(tablaPos, partido->equipo2->id);

	if ( eq1 && eq2 )
	{
		
			if (!borrar)
			{
				eq1->golesContra = eq1->golesContra + partido->golesEq2;
				eq1->golesFavor = eq1->golesFavor + partido->golesEq1;
				eq1->golesDif = eq1->golesFavor - eq1->golesContra;
				eq1->partidosJugados++;

				eq2->golesContra = eq2->golesContra + partido->golesEq1;
				eq2->golesFavor = eq2->golesFavor + partido->golesEq2;
				eq2->golesDif = eq2->golesFavor - eq2->golesContra;
				eq2->partidosJugados++;

				if (partido->golesEq1 == partido->golesEq2)
				{
					eq1->partidosEmpatados++;
					eq2->partidosEmpatados++;
					eq1->puntos++;
					eq2->puntos++;
				}
				else if (partido->golesEq1 > partido->golesEq2)
				{
					eq1->partidosGanados++;
					eq2->partidosPerdidos++;
					eq1->puntos = eq1->puntos + 3;
				}
				else
				{
					eq1->partidosPerdidos++;
					eq2->partidosGanados++;
					eq2->puntos = eq1->puntos + 3;
				}
			}
			else
			{
				eq1->golesContra = eq1->golesContra - partido->golesEq2;
				eq1->golesFavor = eq1->golesFavor - partido->golesEq1;
				eq1->golesDif = eq1->golesFavor - eq1->golesContra;
				eq1->partidosJugados++;

				eq2->golesContra = eq2->golesContra - partido->golesEq1;
				eq2->golesFavor = eq2->golesFavor - partido->golesEq2;
				eq2->golesDif = eq2->golesFavor - eq2->golesContra;
				eq2->partidosJugados++;

				if (partido->golesEq1 == partido->golesEq2)
				{
					eq1->partidosEmpatados--;
					eq2->partidosEmpatados--;
					eq1->puntos--;
					eq2->puntos--;
				}
				else if (partido->golesEq1 > partido->golesEq2)
				{
					eq1->partidosGanados--;
					eq2->partidosPerdidos--;
					eq1->puntos = eq1->puntos - 3;
				}
				else
				{
					eq1->partidosPerdidos--;
					eq2->partidosGanados--;
					eq2->puntos = eq1->puntos - 3;
				}
			}
		

		OrdenarTablaPos(tablaPos);

	}
	else
		error = TRUE;

	return error;
}


t_bool ModificarPartidoJugado(tlista listajugados, tpartido * partido, int gol1,int gol2, tvectorPosiciones * tablaPos){
    
    tnodo * aux = listajugados;
    
    while (aux){
        
        if( aux ->dato->idPartido == partido->idPartido){
            
            partido->golesEq1=gol1;
            partido->golesEq2=gol2;
            ActualizarVecPos(listajugados,tablaPos); // actualuiza puntos
            return FALSE;
        }
        aux=aux->sig;
    }
    
    fprintf(stderr,"No se pudo modificar el partido %d", partido->idPartido);
    return TRUE;
    
}






