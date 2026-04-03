#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tablero.h"
#include "piezas.h"
#include "main.h"
#include "armas.h"


struct Tablero* tablero_crear(int ancho, int alto){
    if (ancho <= 0 || alto <= 0) return NULL; //Tamaño inválido
    Tablero* tabla = (Tablero*)malloc(sizeof(Tablero));
    if (!tabla) return NULL;

    tabla->W = ancho;
    tabla->H = alto;
    tabla->celdas = (void***)malloc(alto*sizeof(void**));
    if (!tabla->celdas) {
        free(tabla);
        return NULL;
    }

    for(int y = 0; y < alto; y++){
        tabla->celdas[y] = (void**)malloc((size_t)ancho * sizeof(void*));
        if (!tabla->celdas[y]){
            for (int i = 0; i< y; i++) free(tabla->celdas[i]);
            free(tabla->celdas);
            free(tabla);
            return NULL;
        }
        for (int x = 0; x<ancho; x++){
            tabla->celdas[y][x] = NULL;
        }
    }
    return tabla;
}
void tablero_imprimir(struct Juego *juego){
    if (!juego || !juego->t) return;

    Tablero *t = juego->t;
    
    printf("NIVEL: %d   | Enemigos vivos: %d \n Turno: %d | Turno enemigos: %d",
            juego->nivel_actual,
            juego->enemigos_vivos,
            juego->turno_actual,
            juego->turno_enemigos
            );
    printf("Arsenal: [1] Escopeta (%d/2) [2] Sniper (%d/1)\n [3] Granada (%d/2) [4] Arma Especial (%d/4)\n",
            juego->arsenal.municion_actual[0],
            juego->arsenal.municion_actual[1],
            juego->arsenal.municion_actual[2],
            juego->arsenal.municion_actual[3]
            );
    printf("=====================================================\n");
    for (int y = 0; y < t->H; y++){
        
    }



};


void tablero_liberar(struct Tablero *tablero){


}; /* debe limpiar la memoria heap */