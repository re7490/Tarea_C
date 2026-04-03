#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tablero.h"
#include "piezas.h"
#include "armas.h"
#include "main.h"


Tablero* tablero_crear(int ancho, int alto){
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
        printf("%2d ", t->H - y); // num filas
        for (int x = 0; x < t->W; x++){
            // void* a Celda* para acceder a la pieza
            Celda* c = (Celda*)t->celdas[y][x];
            if (c && c->pieza) {
                printf("[%c]", c->pieza->tipo);
            } else {
                printf("[ ]");
            }
        }
        printf("\n");
    }
    // Eje X
    printf("   ");
    for (int x = 1; x <= t->W; x++) printf(" %d ", x);
    printf("\n");

};


void tablero_liberar(struct Tablero *tablero){
    if (!tablero) return;

    if (tablero->celdas) {
        for (int y = 0; y < tablero->H; y++) {
            if (!tablero->celdas[y]) continue;

            for (int x = 0; x < tablero->W; x++) {
                Celda* c = (Celda*)tablero->celdas[y][x];
                if (c){
                    free(c);
                    tablero->celdas[y][x] = NULL;
                }
            }
            free(tablero->celdas[y]);
            tablero->celdas = NULL;
        }
    }
    free(tablero);
}; /* debe limpiar la memoria heap */