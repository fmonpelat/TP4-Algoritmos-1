#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tareas.h"

void AgregarNodoEquipo(tnodo* nodo, tequipo** equipos, int idPartido, char*idEquipo1, char*idEquipo2, int dia, int mes, int anio);
tequipo* BuscarEquipoPorId(tequipo**equipos, char*id);
void RecorrerPartidos(tlista);

void main()
{
	char c;
	tlista listaEquipos;

	tequipo**equipos = (tequipo**)malloc(sizeof(tequipo*)* 3);	
	equipos[0] = (tequipo*)malloc(sizeof(tequipo)*1);
	strcpy(equipos[0]->id, "A1");
	strcpy(equipos[0]->nombre, "Brasil");
	equipos[1] = (tequipo*)malloc(sizeof(tequipo)* 1);
	strcpy(equipos[1]->id, "A2");
	strcpy(equipos[1]->nombre, "Croacia");
	equipos[2] = NULL;
	 
	TraerPartidos(equipos, &listaEquipos);
	RecorrerPartidos(listaEquipos);

	scanf("%c", &c);
}

size_t TraerPartidos(tequipo** equipos, tlista* lista)
{
	(*lista) = NULL;

	FILE * fileReader;
	fileReader = fopen("partidos.txt", "r");
	if (!fileReader)
	{
		puts("No existe el archivo partidos.txt");
		return NULL;
	}

	while (!feof(fileReader))
	{


		int idPartido = 0;
		char idEquipo1[M_ID];
		char idEquipo2[M_ID];
		int dia = 0, mes = 0, anio = 0;
		/*Parseo segun el formato de partidos.txt*/
		fscanf(fileReader, "%d;%2c;%2c;%d/%d/%d\n", &idPartido, &idEquipo1, &idEquipo2, &dia, &mes, &anio);

		idEquipo1[2] = '\0';
		idEquipo2[2] = '\0';
		/*Agrego,por linea, un nodo  a la lista */
		AgregarNodoEquipo(&(*lista), equipos, idPartido, idEquipo1, idEquipo2, dia, mes, anio);
	}

	/*Le asigno la cadena a la lista*/
	//(*lista) = aux;

	return NULL;
}

void AgregarNodoEquipo(tnodo** nodo, tequipo** equipos, int idPartido, char idEquipo1[M_ID], char idEquipo2[M_ID], int dia, int mes, int anio)
{
	if (!(*nodo))
	{
		tnodo* aux = (*nodo);
		(*nodo) = (tnodo*)malloc(sizeof(tnodo)* 1);
		(*nodo)->dato = (tequipo*)malloc(sizeof(tequipo)* 1);
		(*nodo)->dato->idPartido = idPartido;
		(*nodo)->dato->equipo1 = BuscarEquipoPorId(equipos, idEquipo1);
		(*nodo)->dato->equipo2 = BuscarEquipoPorId(equipos, idEquipo2);
		(*nodo)->dato->fecha.dd = dia;
		(*nodo)->dato->fecha.mm = mes;
		(*nodo)->dato->fecha.aaaa = anio;
		(*nodo)->sig = aux;
	}
	else
	{
		AgregarNodoEquipo(&(*nodo)->sig, equipos, idPartido, idEquipo1, idEquipo2, dia, mes, anio);
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

tequipo* BuscarEquipoPorId(tequipo**equipos, char*id)
{
	char aux1[M_ID];
	strcpy(aux1, id);

	int i = 0;

	while (equipos[i])
	{
		if (!strcmp(equipos[i]->id, aux1))
		{
			return equipos[i];
		}

		i++;
	}


	return NULL;
}