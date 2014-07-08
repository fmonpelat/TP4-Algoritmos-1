//
//  conventions.h
//  TP4 Algoritmos 1
//
//  Copyright (c) 2014 . All rights reserved.
//
//  Facundo Monpelat
//  Luca Mazzer
//  Erik Schatz

#ifndef TP4_Algoritmos_1_conventions_h
#define TP4_Algoritmos_1_conventions_h

/* ----- CONVENTIONS FILE ---------
 
 este es un documento para anotar las convenciones de programacion para este tp.
 
 
 - convenciones de estilo:
 
    * Sentencias entre Parentesis y Asignaciones:
        En las sentencias entre parentesis dejar un espacio al estilo, asimismo tambien en las
        asignaciones:
 
            aux = ( i+1 );

    * Comentarios entre codigo:
        Al usar comentarios se deberan de abrir con la sintaxis ANSI C89 segun:

            /* algo este es un comentario
            */

/*
    * Funciones entre llaves:
 
        La convencion a seguir en este caso sera:
 
            funcion( arg1, arg2, arg3){
 
            // ALGO
 
            };
 
    * Sentencias IF:
 
        Para las sentencias condicionales if se debera de dejar un espacio despues del parentesis
        de apertura y otro antes de cerrarlo si es que dentro no hay parentesis.
        
            if( i==0 ){}; o tambien if (  ( i==1 ) && ( j==2 )  ){};
 
        Notar que en el segundo ejemplo se deja 2 espacios antes del if y demas si se
        anidan sucesivos parentesis.
 
    * Sentencias FOR:
        En las sentencias for dejaremos 1 espacio entre cada sentencia al estilo:
            
            for( i=0 ; i<MAX ; i++ ){};
 
    * Sentencias WHILE:
 
        En las sentencias while dejaremos como en las sentencias if al estilo:
 
            while(  ( c=getchar() )  ){};
 

    * Sentencias con punteros:
 
        Declaracion:
                    int * p;
        Desreferenciacion:
                    *p;
 

#endif









