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
#define M_FILE 3

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
size_t q_equipos;
tequipo * equipos;
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
int golesDif;
} tequipoPos;

typedef tequipoPos ** tvectorPosiciones;

/* #### FACU #### */
size_t TraerEquipos( tequipo ** ); /*Lee el .txt, convierte los datos a un array de equipos */
void TestEquipos( void );
void DestruirEquipos(tequipo*); /*libera la memoria */

/* AUX compatibilidad macosx simil fflush. */
void dump_line(FILE *);

/* para agregar un nuevo partido a la lista de jugados. */
t_bool newPartidoJugado(int idPartido, int gol1, int gol2,tlista * partidosPendientes, tlista * partidosJugados, tequipo * equipos, size_t qEquipos/*, tvectorPosiciones *tablaPos*/); /* asigna un nuevo partido a la lista con los goles de los 2 equipos pasandole el id de partido */

t_bool newPartidoJugadoXP(tpartido * partido ,int gol1, int gol2,tlista * partidosPendientes, tlista * partidosJugados, tequipo * equipos, size_t qEquipos); /* asigna un nuevo partido a la lista con los goles de los 2 equipos pasandole el puntero al partido*/

/* funciones sobre el archivo binario. */
t_bool GrabarPartidosJugados( tlista * );
typedef enum bool_partido { ID , GOL1 , GOL2 } int_filepartido;
t_bool leerPartidosJugados(tlista * listaJugados , tlista * listaPartidos, tequipo * equipos, size_t cantEquipos/*, tvectorPosiciones * tablaPos */);
int TestFileDump(void);
int TestModificarPartido(void);
unsigned long userInputUlong(void);
//Carga CSV
t_bool leerPartidosCSV(tlista * listaJugados , tlista * listaPartidos, tequipo * equipos, size_t cantEquipos,char * NombreArchivo,tvectorPosiciones * tablaPos);
int TestALL(void);



//ERIK
t_bool TraerPartidos( tequipo * ,size_t , tlista * );
void TestTraerPartidos( void );
void DestruirPartidos( tnodo * nodo); /*libera la memoria */
void AgregarNodoEquipo( tnodo ** , tequipo* ,size_t , int , char * , char * , int , int , int );
tequipo * BuscarEquipoPorId( tequipo * , char * , size_t );
void RecorrerPartidos( tlista );
t_bool ValidarPartidos(tlista lista);

t_bool PartidoJugadoNuevo(char , tlista * , tlista * , tequipo * , size_t , tvectorPosiciones * );
tequipoPos * BuscarEquipoPorIdEnTablaPos(tvectorPosiciones * equiposEnTabla, char * id);
tvectorPosiciones * CrearVecPos(tlista partidosJugados, tequipo* equipos, size_t qEquipos);

//esta funcion si le pasas un 0 a int borrar
t_bool ModificarTablaPos(tvectorPosiciones * tablaPos, tpartido * partido, int borrar);

// esta crea toda la tabla de posiciones de todos los partidos jugados.
void ActualizarVecPos(tlista partidosJugados, tvectorPosiciones * vecPos);


void RecorrerTablaPos(tvectorPosiciones *tablaPos);
void OrdenarTablaPos(tvectorPosiciones *tablaPos);
void IntercambiarVecPos(tequipoPos** equipo1, tequipoPos** equipo2);





//LUCA
tpartido * BuscarPartidoPorId(tlista ,int );
tpartido * BuscarPartidoPorEquipos (tlista ,char * ,char * );
void TestBusquedaPartidos( tlista );

void  SwitchNodo(tlista  * , tlista * , tlista * );
t_bool intercambiarNodo(tlista  * listapendientes, tlista * listajugados, tequipo * equipos, size_t sizeEquipos, tpartido * partido);
t_bool ModificarPartidoJugado(tlista listajugados, tpartido * partido, int gol1,int gol2, tvectorPosiciones * tablaPos);

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