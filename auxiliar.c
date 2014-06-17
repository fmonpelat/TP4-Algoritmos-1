#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tareas.h"


void AgregarNodoEquipo(tnodo* nodo, tequipo** equipos, int idPartido, char*idEquipo1, char*idEquipo2, int dia, int mes, int anio);
tequipo* BuscarEquipoPorId(tequipo**equipos, char*id);


void main()
{
	tlista listaEquipos;
	
	tequipo*equipos = NULL;
	TraerPartidos(equipos, &listaEquipos);
	int end = 0;
}

size_t TraerPartidos(tequipo* equipos, tlista* lista)
{

	tnodo* aux = NULL;

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
		char idEquipo1[2];
		char idEquipo2[2];
		int dia = 0, mes = 0, anio = 0;
		/*Parseo segun el formato de partidos.txt*/
		fscanf(fileReader, "%d;%2c;%2c;%d/%d/%d\n", &idPartido, &idEquipo1, &idEquipo2, &dia, &mes, &anio);
		/*Agrego,por linea, un nodo  a la lista */
		AgregarNodoEquipo(&aux, equipos, idPartido, idEquipo1, idEquipo2, dia, mes, anio);
	}

	/*Le asigno la cadena a la lista*/
	(*lista) = aux;

	return NULL;
}

void AgregarNodoEquipo(tnodo** nodo, tequipo* equipos, int idPartido, char*idEquipo1, char*idEquipo2, int dia, int mes, int anio)
{
	if (!(*nodo))
	{
		(*nodo)->dato = (tequipo*)malloc(sizeof(tequipo)* 1);
		(*nodo)->dato->equipo1 = BuscarEquipoPorId(equipos, idEquipo1);
		(*nodo)->dato->equipo2 = BuscarEquipoPorId(equipos, idEquipo2);
		(*nodo)->dato->fecha.dd = dia;
		(*nodo)->dato->fecha.mm = mes;
		(*nodo)->dato->fecha.aaaa = anio;
		(*nodo)->sig = NULL;
	}
	else
	{
		tnodo* aux = (*nodo);
		(*nodo) = (tnodo*)malloc(sizeof(tnodo)* 1);
		(*nodo)->dato = (tequipo*)malloc(sizeof(tequipo)* 1);
		(*nodo)->dato->equipo1 = BuscarEquipoPorId(equipos, idEquipo1);
		(*nodo)->dato->equipo2 = BuscarEquipoPorId(equipos, idEquipo2);
		(*nodo)->dato->fecha.dd = dia;
		(*nodo)->dato->fecha.mm = mes;
		(*nodo)->dato->fecha.aaaa = anio;
		(*nodo)->sig = aux;
	}

}

tequipo* BuscarEquipoPorId(tequipo*equipos, char*id)
{
	return NULL;
}