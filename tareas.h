//
//  tareas.h
//  TP4 Algoritmos 1
//
//  Facundo Monpelat
//  Luca Mazzer
//  Erik Schatz

#ifndef TP4_Algoritmos_1_tareas_h
#define TP4_Algoritmos_1_tareas_h
#define M_ID 2
#define M 64

/* PROTOTYPES 
 */

typedef struct equipo{
char id[M_ID];
char nombre[M];
}tequipo;

typedef struct fecha{
int dd;
int mm;
int aaaa;
}tfecha;

typedef struct partido{
int idPartido;
tequipo* equipo1;
tequipo* equipo2;
int golesEq1;
int golesEq2;
tfecha fecha;
}tpartido;

typedef struct nodo{
tpartido* dato;
struct nodo* sig;
}tnodo;

typedef tnodo* tlista;

typedef struct mundial{
int q_equipos;
tequipo ** equipos;
tlista partidosJugados;
tlista partidosPendientes;
}tmundial;


tequipo * TraerEquipos(); /*Lee el .txt, convierte los datos a un array de equipos */
	/*funciones especificas, auxiliares, bleble*/
size_t CantEquipos(tequipo*);
void DestruirEquipos(tequipo*); /*libera la memoria */

tlista TraerPartidos(); /*Lee el .txt, convierte los datos a nodos de una tlista */
void DestruirPartidos(tlista); /*libera la memoria */
/*

PARTIDOS:
BuscarPartidoPorId
BuscarPartidoPorEquipos
ModificarPartidosJugado
(no especificada) ModifcarFechaPorPartido
CrearPartidosJugado (lo crea ordenado por puntos de mayor a menor)
EliminarPartidoJugado

REPORTES:
ListarPartidosPendientes
ListarEquipos
VerPosiciones

Test
*/

#endif