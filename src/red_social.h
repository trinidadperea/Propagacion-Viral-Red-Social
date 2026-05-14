// Header del proyecto
// definicion de estructuras

#ifndef RED_SOCIAL_H
#define RED_SOCIAL_H

#include <stdio.h>
#include <stdlib.h>

// variables globales
#define NUM_USUARIOS 10000   // nodos del grafo
#define PROB_BASE 0.3        // Probabilidad por defecto
#define MAX_ITERACIONES 50   // Límite de la simulación

// estados: visto, ignorado, compartido
typedef enum{
    NO_ALCANZADO,   // el usuario aun no me el contenido
    VISUALIZADO,    // el usuario vio el contenido
    COMPARTIDO,     // el usuario lo compartio
    IGNORO          // el usuarioo lo vio y no hizo nada
} Estado;

// usuarios: id, estado, seguidores, propabilidad
typedef struct{
    int id;
    Estado estado_actual;
    Estado estado_siguiente; // estado actualizado luego de ver el contenido
    int *seguidores; // lista con los usuarios que lo siguen
    int cant_seguidores // tamaño de la lista de los seguidores
    float probabilidad_compartir // un valor entre (0 y 1)
} Usuario;

// constantes: nro total de usuarios, probabilidad base 
// esto nos va a servir para luego sacar los valores para evaluar
typedef struct{
    int total_alcanzados;
    int total_compartieron;
    int total_ignoraron;
    double tiempo_ejecucion;
} Estadisticas;

// metodos  autilizar desde secuencial.c y desde paralelo.c
void generar_red(Usuario*red, int n)
void liberar_red(Usuario*red, int n)

#endif
