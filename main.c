//
//  main.c
//  TP4 Algoritmos 1
//
//  Copyright (c) 2014 . All rights reserved.
//
//  Facundo Monpelat
//  Luca Mazzer
//  Erik Schatz





#include <stdio.h>
#include "tareas.h"
#include <stdlib.h>
#include <string.h>


int main(int argc, const char * argv[]){
    
    
	/*TestEquipos();
    TestTraerPartidos();
	
    if (TestFileDump()) {
        return EXIT_FAILURE;
    }
    */
    
    
    while ( opt_statement != opt_exit ){
        
        PrintMainMenu();
        
        while ( opt_statement != opt_exit ){
            
            scanf("%ul",&opt_statement);
            
            switch(opt_statement){
                case opt_agregarPersona:
                    dump_line(stdin);
                    printf("Por favor ingrese los datos de cada persona \n");
                    agregarPersona( &Ciudad );
                    cargarPersona( &Ciudad , Ciudad.q_personas-1 );
                    printf("Presione cualquier tecla para volver al menu ...");
                    //dump_line(stdin);
                    getchar();
                    system("clear");
                    break;
                    
                case opt_agregarHijo:
                    
                    printf("Por favor ingrese el dni del padre: ");
                    scanf("%lu",&dniPadre);
                    putc('\n', stdout);
                    dump_line(stdin);
                    printf("Ingrese el dni del Hijo: ");
                    scanf("%lu",&dniHijo);
                    putc('\n', stdout);
                    linkHijos(&Ciudad, dniPadre, dniHijo);
                    padre=searchBydni(&Ciudad, dniPadre);
                    hijo=searchBydni(&Ciudad, dniHijo);
                    
                    if (hijo == NULL) {
                        fprintf(stderr, "No existen tales DNI\n");
                    }
                    else printf("Ahora %s es Hijo de %s\n",hijo->nombre,padre->nombre);
                    if (hijo==NULL && padre==NULL) {
                        if (Ciudad.q_personas==0) {
                            printf("No existe ningun Habitante en la ciudad, puede agregar uno optando por la opcion %d.\n",opt_agregarPersona);
                        }
                        else printf("Usted ingreso dos DNI que no se encontraron vuelva a intentar nuevamente.\n");
                    }
                    putc('\n', stdout);
                    printf("Presione cualquier tecla para volver al menu ...");
                    dump_line(stdin);
                    getchar();
                    system("clear");
                    break;
                    
                case opt_Habitantes:
                    
                    if (Ciudad.q_personas!=0) {
                        
                        for (i=0; i< Ciudad.q_personas; i++) {
                            printf("Nombre: %s Apellido: %s DNI: %lu\n",Ciudad.personas[i]->nombre,Ciudad.personas[i]->apellido,Ciudad.personas[i]->dni);
                        }
                    }
                    else printf("No existe ningun Habitante en la ciudad, puede agregar uno optando por la opcion %d.\n",opt_agregarPersona);
                    
                    putc('\n', stdout);
                    printf("Presione cualquier tecla para volver al menu ...");
                    dump_line(stdin);
                    getchar();
                    system("clear");
                    break;
                    
                case opt_Imprimir:
                    
                    if (Ciudad.q_personas!=0 ) {
                        
                        printf("Ingrese el DNI de la persona para imprimir su arbol: \n");
                        scanf("%lu",&dniPadre);
                        
                        /* No es necesario ordenarlo para imprimir el arbol..
                         */
                        bubblesort_tpersona( &Ciudad );
                        imprimirArbol(&Ciudad, searchBydni(&Ciudad, dniPadre) );
                    }
                    else printf("No existe ningun Habitante en la ciudad, puede agregar uno optando por la opcion %d.\n",opt_agregarPersona);
                    
                    printf("\nPresione cualquier tecla para volver al menu ...");
                    dump_line(stdin);
                    getchar();
                    system("clear");
                    break;
                    
                case opt_exit:
                    
                    break;
                    
                default:
                    
                    printf("%s\n","Opcion Invalida");
                    //dump_line(stdin);
                    printf("Presione cualquier tecla para volver al menu ...");
                    getchar();
                    system("clear");
                    break;
            }
            system("clear");
            break;
        }
    }
    
    
    
    return EXIT_SUCCESS;
    
}

