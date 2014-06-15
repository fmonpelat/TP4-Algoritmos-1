//
//  tareas.h
//  TP4 Algoritmos 1
//
//  Facundo Monpelat
//  Luca Mazzer
//  Erik Schatz

#ifndef TP4_Algoritmos_1_tareas_h
#define TP4_Algoritmos_1_tareas_h

//M_ID debe ser mayor a 0 si es que guardaremos los grupos y el numero ej: A1 sino no hay lugar para el '\0'
#define M_ID 3
#define M 64

/* PROTOTYPES 
 */

typedef struct equipo{
char id[M_ID];
char nombre[M];
} tequipo;

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

//FACU
//EQUIPOS DONE
size_t TraerEquipos( tequipo ** ); /*Lee el .txt, convierte los datos a un array de equipos */
void TestEquipos( void );
void DestruirEquipos(tequipo*); /*libera la memoria */

/* AUX compatibilidad macosx simil fflush. */
void dump_line(FILE *);


//ERIK
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
*/

#endif