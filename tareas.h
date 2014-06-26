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


typedef enum bool{ TRUE, FALSE } t_bool;

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
} tfecha;

typedef struct partido{
int idPartido;
tequipo* equipo1;
tequipo* equipo2;
int golesEq1;
int golesEq2;
tfecha fecha;
} tpartido;

typedef struct nodo{
tpartido* dato;
struct nodo* sig;
} tnodo;

typedef tnodo* tlista;

typedef struct mundial{
int q_equipos;
tequipo ** equipos;
tlista partidosJugados;
tlista partidosPendientes;
} tmundial;

// estructura creadas

typedef struct equipoPosicion{
char grupo;
tequipo * equipo;
int puntos;
int partidosJugados;
int partidosGanados;
int partidosEmpatados;
int partidosPerdidos;
int golesFavor;
int golesContra;
} tequipoPos;

typedef tequipoPos ** tvectorPosiciones;

//FACU
//EQUIPOS DONE
size_t TraerEquipos( tequipo ** ); /*Lee el .txt, convierte los datos a un array de equipos */
void TestEquipos( void );
void DestruirEquipos(tequipo*); /*libera la memoria */

/* AUX compatibilidad macosx simil fflush. */
void dump_line(FILE *);




//ERIK
size_t TraerPartidos( tequipo * ,size_t , tlista * );
void TestTraerPartidos( void );
void DestruirPartidos( tnodo * nodo); /*libera la memoria */
void AgregarNodoEquipo( tnodo ** , tequipo* ,size_t , int , char * , char * , int , int , int );
tequipo * BuscarEquipoPorId( tequipo * , char * , size_t );
void RecorrerPartidos( tlista );
t_bool ValidarPartidos(tlista lista);

// validar unicos ids de partidos de la lista.


// funciones sobre el archivo binario

// la funcion devuelve estados de error TRUE o FALSE
t_bool GrabarPartidosJugados( tlista * );


// leer partidos
t_bool leerPartidosJugados( tlista * );






//LUCA
tpartido * BuscarPartidoPorId(tlista ,int );
tpartido * BuscarPartidoPorEquipos (tlista ,char * ,char * );
void TestBusquedaPartidos( tlista );

void  SwitchNodo(tlista  * , tlista * , tlista * );
t_bool intercambiarNodo(tlista  * listapendientes, tlista * listajugados, tequipo * equipos, size_t sizeEquipos, tpartido * partido);
t_bool PartidoJugadoNuevo(char , tlista * , tlista * , tequipo * , size_t , tvectorPosiciones * );
tequipoPos * BuscarEquipoPorIdEnTabla(tvectorPosiciones * , char * );
t_bool AgregarEquipoPos(tvectorPosiciones * vec, tequipo * equipo);
t_bool ActualizarPuntosEquipos(tvectorPosiciones * tablaPos, tpartido * partido);
void RecorrerTablaPos(tvectorPosiciones *tablaPos);

/*
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