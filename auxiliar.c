#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tareas.h"

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
				if (!(strcmp(nodoEquipo1, listaEquipo1) && !strcmp(nodoEquipo2, listaEquipo2)) || !(strcmp(nodoEquipo1, listaEquipo2) && !strcmp(nodoEquipo2, listaEquipo1)))
					validado = 0;
			}
			if (validado)
				filaAux++;
			lista = lista->sig;
		}
		nodo = nodo->sig;			
	}

	if (validado)
		return 1;
	else
	{
		printf("Error en la fila numero: %d \n", (fila + filaAux));
		return 0;
	}
}
