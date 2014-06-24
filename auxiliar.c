#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tareas.h"


void dump_line(FILE *fp) {
	int ch;
	while ((ch = fgetc(fp)) != EOF && ch != '\n');
}


typedef struct equipoPosicion
{
	char grupo;
	tequipo*equipo;
	int puntos;
	int partidosJugados;
	int partidosGanados;
	int partidosEmpatados;
	int partidosPerdidos;
	int golesFavor;
	int golesContra;

}tequipoPos;

typedef tequipoPos** tvectorPosiciones;

size_t TraerEquipos(tequipo **  equipos){

	if ((*equipos) != NULL) {
		fprintf(stderr, "Error, por favor ingrese un puntero equipo nulo");
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
		fprintf(stderr, "Error, no se pudo abrir grupos.txt, existe?");
		return 0;
	}

	/* pedimos memoria por primera vez antes de reallocar si es que necesitamos memoria.
	*/
	if (!(*equipos = (tequipo*)malloc(sizeof(tequipo)*init_chop))) {
		fprintf(stderr, "Error, could not find memory");
		return 0;
	}

	alloc_size = init_chop;

	while (fgets(str, M_ID + M + 1, fpequipos)){

		/* nos preguntamos si necesitamos memoria ... pedimos de a chops o de a pedazos
		*/
		if (used_size == alloc_size) {

			if (!(aux = (tequipo *)realloc(*equipos, sizeof(tequipo)*(alloc_size + chop_size)))) {
				fprintf(stderr, "Error, could not find memory");
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
	// para debug sacar despues de pasar las pruebas
	//printf("%s\n",equipos[1].nombre);
	//printf("%s\n",equipos[1].id);

	return used_size - 1;
}


void DestruirEquipos(tequipo * equipos){

	free(equipos);

}

// ########## ERIK ######################################


size_t TraerPartidos(tequipo * equipos, size_t sizeEquipos, tlista * lista)
{
	//aca hacemos que lo apuntado por lista que es un tnodo * sea null.
	(*lista) = NULL;
	FILE * fileReader;


	if (!(fileReader = fopen("partidos.txt", "r")))
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
		fscanf(fileReader, "%d;%2c;%2c;%d/%d/%d\n", &idPartido, (char *)&idEquipo1, (char *)&idEquipo2, &dia, &mes, &anio);

		idEquipo1[2] = '\0';
		idEquipo2[2] = '\0';
		/*Agrego,por linea, un nodo  a la lista */
		AgregarNodoEquipo(&(*lista), equipos, sizeEquipos, idPartido, idEquipo1, idEquipo2, dia, mes, anio);
	}

	/*Le asigno la cadena a la lista*/
	//(*lista) = aux;

	return 1;
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
		(*nodo)->dato->golesEq1 = -1;
		(*nodo)->dato->golesEq2 = -1;
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
	{	//FILA: id fecha equipo1-equipo2 (golEquipo1:golEquipo2)
		if (lista->dato->idPartido)
			printf("%d", lista->dato->idPartido);

		if (lista->dato->fecha.dd && lista->dato->fecha.mm && lista->dato->fecha.aaaa)
			printf(" (%d/%d/%d) ", lista->dato->fecha.dd, lista->dato->fecha.mm, lista->dato->fecha.aaaa);

		if (lista->dato->equipo1 && lista->dato->equipo2)
			printf("%s-%s ", lista->dato->equipo1->nombre, lista->dato->equipo2->nombre);

		if (lista->dato->golesEq1 >= 0)
			printf("(%d:%d)", lista->dato->golesEq1, lista->dato->golesEq2);

		puts("");
		lista = lista->sig;
	}
	printf("\n");
}

tequipo * BuscarEquipoPorId(tequipo * equipos, char * id, size_t size){

	size_t i;

	for (i = 0; i <= size; i++) {

		if (!strcmp(equipos[i].id, id))
		{
			return &equipos[i];
		}
	}
	return NULL;
}


void DestruirPartidos(tnodo * nodo){


	if (nodo->sig == NULL) {
		free(nodo->dato);
		nodo->dato = NULL;
		free(nodo);
		nodo = NULL;
	}
	else DestruirPartidos(nodo->sig);


}

size_t ValidarPartidos(tlista lista)
{
	int validado = 1, fila = 0, filaAux;
	tnodo* nodo = lista;

	while (nodo&&validado)
	{
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

			if (nodoEquipo1&&nodoEquipo2&&listaEquipo1&&listaEquipo2)
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

	if (validado)
	{
		printf("Validado \n");
		return 1;
	}
	else
	{
		printf("Error en la fila numero: %d \n", (fila + filaAux));
		return 0;
	}
}

// ########## GRABACION DE ARCHIVOS BINARIOS #################

t_bool GrabarPartidosJugados(tlista * lista_jugados){

	FILE * fpPartidosJugados;
	char NombreArchivo[M];
	strcpy(NombreArchivo, "partidosjugados.dat");

	int buffer[M_ID - 1];


	fpPartidosJugados = fopen(NombreArchivo, "wb");

	if (!fpPartidosJugados) {
		fprintf(stderr, "Error, no se pudo abrir %s", NombreArchivo);
		return TRUE;
	}

	while (!((*lista_jugados)->sig)) {

		buffer[0] = (*lista_jugados)->dato->idPartido;
		buffer[1] = (*lista_jugados)->dato->golesEq1;
		buffer[1] = (*lista_jugados)->dato->golesEq2;

		fwrite(buffer, sizeof(int), sizeof(buffer), fpPartidosJugados);

	}

	return FALSE;

}





// ############### LUCA ############################

tpartido * BuscarPartidoPorId(tlista lista, int id){

	tnodo * aux = lista;
	while (aux)
	{
		if (aux->dato->idPartido == id)
			return aux->dato;
		else  aux = aux->sig;
	}
	return NULL;
}



tpartido * BuscarPartidoPorEquipos(tlista lista, char * id1, char * id2){

	tnodo * aux = lista;

	while (aux){

		if (!(strcmp(aux->dato->equipo1->id, id1)) && !(strcmp(aux->dato->equipo2->id, id2)))  return aux->dato;
		else
		if (!(strcmp(aux->dato->equipo1->id, id2)) && !(strcmp(aux->dato->equipo2->id, id1)))  return aux->dato; // lo agregue por si se colocan al revez los ids, sino no va a encartrar el partido por el tema de la localia
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
			while (nodo->sig)
				nodo = nodo->sig;
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

	if (partido)
	{
		while (partidoAeliminar)  // obtencion del nodo a eliminar y nodo anterior
		{
			if (partidoAeliminar->dato->idPartido == partido->idPartido)
			{

				SwitchNodo(&partidoAnterior, &partidoAeliminar, listajugados);// pasa un nodo de una lista a la otra
				if (!partidoAnterior)
					(*listapendientes) = partidoAeliminar;
				return FALSE;
			}
			else
			{
				partidoAnterior = partidoAeliminar;
				partidoAeliminar = partidoAeliminar->sig;
			}
		}
	}
	else
	{
		return TRUE;
	}


}


t_bool PartidoJugadoNuevo(char opcion, tlista* partidosPendientes, tlista *partidosJugados, tequipo* equipos, int qEquipos, tvectorPosiciones *tablaPos)
{
	tpartido *partido;
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
	}
	ActualizarPuntosEquipos(tablaPos, partido);

	return error;
}

RecorrerTablaPos(tvectorPosiciones *tablaPos)
{
	int i = 0, gf, gc, dg;
	tequipoPos* equipoT = NULL;
	    printf("     EQUIPO  PTS PG PE PP GF GC DF\n");
	while ((*tablaPos)[i])
	{
		equipoT = (*tablaPos)[i];
		gf = equipoT->golesFavor;
		gc = equipoT->golesContra;
		dg = gf - gc;
		printf("%10s     %d  %d  %d  %d  %d  %d  %d\n", equipoT->equipo->nombre, equipoT->puntos,equipoT->partidosGanados,equipoT->partidosEmpatados,equipoT->partidosPerdidos,gf,gc,dg);
		i++;
	}
}

OrdenarTablaPos(tvectorPosiciones *tablaPos)
{



}

tequipoPos * BuscarEquipoPorIdEnTabla(tvectorPosiciones * equiposEnTabla, char * id){

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

t_bool AgregarEquipoPos(tvectorPosiciones *vec, tequipo*equipo)
{
	int i = 0;
	/*tvectorPosiciones* vec = NULL;
	vec = &(*(*tablaPos));*/
	
	if ((*vec))
	{

		while ((*vec)[i])
			i++;
		(*vec) = realloc((*vec), sizeof(tequipoPos*)*(i + 2)); //(mas el null mas el nuevo)
		(*vec)[i] = (tequipoPos*)malloc(sizeof(tequipoPos)* 1);
		(*vec)[i]->equipo = equipo;
		(*vec)[i]->grupo = equipo->id[0];
		(*vec)[i]->puntos = 0;
		(*vec)[i]->golesContra = 0;
		(*vec)[i]->golesFavor = 0;
		(*vec)[i]->partidosEmpatados = 0;
		(*vec)[i]->partidosGanados = 0;
		(*vec)[i]->partidosJugados = 0;
		(*vec)[i]->partidosPerdidos = 0;
		(*vec)[i + 1] = NULL;
	}
	else
	{
		(*vec) = (tequipoPos**)malloc(sizeof(tequipoPos*)* 1);
		(*vec)[0] = (tequipoPos*)malloc(sizeof(tequipoPos)* 2);
		(*vec)[0]->equipo = equipo;
		(*vec)[0]->grupo = equipo->id[0];
		(*vec)[0]->puntos = 0;
		(*vec)[0]->golesContra = 0;
		(*vec)[0]->golesFavor = 0;
		(*vec)[0]->partidosEmpatados = 0;
		(*vec)[0]->partidosGanados = 0;
		(*vec)[0]->partidosJugados = 0;
		(*vec)[0]->partidosPerdidos = 0;
		(*vec)[1] = NULL;
	}
	

}

t_bool ActualizarPuntosEquipos(tvectorPosiciones * tablaPos, tpartido*partido)
{
	tequipoPos * eqq = NULL;
	t_bool error = FALSE;
	tequipoPos* eq1, *eq2;
	eq1 = BuscarEquipoPorIdEnTabla(tablaPos, partido->equipo1->id);
	eq2 = BuscarEquipoPorIdEnTabla(tablaPos, partido->equipo2->id);

	if (!eq1)
		AgregarEquipoPos(tablaPos, partido->equipo1);	
	if (!eq2)
		AgregarEquipoPos(tablaPos, partido->equipo2);
	
	eq1 = BuscarEquipoPorIdEnTabla(tablaPos, partido->equipo1->id);
	eq2 = BuscarEquipoPorIdEnTabla(tablaPos, partido->equipo2->id);

	eqq=tablaPos[1];
	if (eq1&&eq2)
	{
		eq1->equipo = partido->equipo1;
		eq1->golesContra = partido->golesEq2;
		eq1->golesFavor = partido->golesEq1;
		eq1->partidosJugados++;

		eq2->equipo = partido->equipo2;
		eq2->golesContra = partido->golesEq1;
		eq2->golesFavor = partido->golesEq2;
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

		OrdenarTablaPos(tablaPos);

	}
	else
		error = TRUE;
		
	return error;
}

int main(int argc, const char * argv[])
{
	//TestEquipos();
	//TestTraerPartidos();
	tvectorPosiciones tablaPos = NULL;
	tequipo * equipos = NULL;
	size_t cantEquipos;
	tlista listaPartidos;
	tlista partidosJugados = NULL;
	cantEquipos = TraerEquipos(&equipos);

	TraerPartidos(equipos, cantEquipos, &listaPartidos);

	if (ValidarPartidos(listaPartidos))
		RecorrerPartidos(listaPartidos);

	//###TESTEO###
	/*tablaPos = (tequipoPos**)malloc(sizeof(tequipoPos*));
	tablaPos[0] = NULL;*/
	if (PartidoJugadoNuevo('i', &listaPartidos, &partidosJugados, equipos, cantEquipos, &tablaPos) == FALSE)
	{
		printf("Lista de partidos \n");
		RecorrerPartidos(listaPartidos);
		printf("Lista de partidos jugados \n");
		RecorrerPartidos(partidosJugados);
		printf("Lista de posiciones \n");
		RecorrerTablaPos(&tablaPos);
	}

	if (PartidoJugadoNuevo('i', &listaPartidos, &partidosJugados, equipos, cantEquipos, &tablaPos) == FALSE)
	{
		printf("Lista de partidos \n");
		RecorrerPartidos(listaPartidos);
		printf("Lista de partidos jugados \n");
		RecorrerPartidos(partidosJugados);
		printf("Lista de posiciones \n");
		RecorrerTablaPos(&tablaPos);
	}

	if (PartidoJugadoNuevo('i', &listaPartidos, &partidosJugados, equipos, cantEquipos, &tablaPos) == FALSE)
	{
		printf("Lista de partidos \n");
		RecorrerPartidos(listaPartidos);
		printf("Lista de partidos jugados \n");
		RecorrerPartidos(partidosJugados);
		printf("Lista de posiciones \n");
		RecorrerTablaPos(&tablaPos);
	}

	//###FIN TESTEO###

	DestruirPartidos(listaPartidos);
	DestruirEquipos(equipos);

	char c = 'A';
	scanf("%c", &c);

	return 0;
}
