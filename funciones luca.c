

t_bool CargarPartidoJugado(tlista * listapendientes,tlista * listajugados ,int gol1,int gol2, tpartido * partido,tequipo * equipos, size_t sizeEquipos, tvectorposiciones * tablaPos)
{
    // miro si el partido esta en la lista de pendientes
    tnodo * aux= *listapendientes;

    while(aux)
    {
        if (aux->dato->idPartido == partido->idPartido)
        {
            if(intercambiarNodo(listapendientes,listajugados,equipos,sizeEquipos,partido)== TRUE) {
                fprintf(stderr, "no se pudo cambiar el partido");
                return TRUE;
            }
            partido->golesEq1=gol1;
            partido->golesEq2=gol2;
            ActualizarPuntosEquipos(tablaPos,partido);
            return FALSE;

        }
        else  aux=aux->sig;
    }
    // miro si el partido esta en la lista de jugados
    aux =  *listajugados;

    while (aux)
    {
        if (aux->dato->idPartido == partido->idPartido){

            fprintf(stderr, "este partido ya se juego") ;
            return TRUE;
        }
        aux=aux->sig;
    }
    // si no se encontro en ninguna lista el partido no existe
    fprintf(stderr,"no se encontro el partido %d en ninguna de las listas", partido->idPartido);
    return TRUE;
}


// modifica un partido q ya fue jugado y le carga denuevo los goles
t_bool ModificarPartidoJugado(tlista listajugados, tpartido * partido, int gol1,int gol2)
{
    tnodo * aux= listajugados;
     while (aux){
            if( aux ->dato->idPartido == partido->idPartido){

                partido->golesEq1=gol1;
                partido->golesEq2=gol2;
                // falta actualizar puntos!
                return FALSE;

            }
            aux=aux->sig;

     }

     fprintf(stderr," no se pudo modificar el partido %d", partido->idPartido);
     return TRUE;

}

