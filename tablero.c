#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tablero.h"
#include "piezas.h"
#include "armas.h"
#include "main.h"


struct Tablero* tablero_crear(int ancho, int alto){
    if (ancho <= 0 || alto <= 0) return NULL; // tamaño invalido
    
    Tablero* tablero = (Tablero*)malloc(sizeof(Tablero));
    if (!tablero) return NULL;

    tablero->W = ancho;
    tablero->H = alto;
    tablero->celdas = (void***)malloc(alto * sizeof(void**));

    if (!tablero->celdas) {
        free(tablero);
        return NULL;
    }

    for(int y = 0; y < alto; y++){
        tablero->celdas[y] = (void**)malloc((size_t)ancho * sizeof(void*));
        if (!tablero->celdas[y]){
            for (int i = 0; i< y; i++) free(tablero->celdas[i]);
            free(tablero->celdas);
            free(tablero);
            return NULL;
        }
        for (int x = 0; x<ancho; x++){
            Celda* c = (Celda*)malloc(sizeof(Celda));
            c->pieza = NULL; // vacia inicialmente
            tablero->celdas[y][x] = c;
        }
    }
    return tablero;
}
void tablero_imprimir(struct Juego *juego){
    if (!juego || !juego->t) return;

    Tablero *t = juego->t;
    
    printf("NIVEL: %d  |  Enemigos vivos: %d \nTurno: %d | Turno enemigos: %d\n",
            juego->nivel_actual,
            juego->enemigos_vivos,
            juego->turno_actual,
            juego->turno_enemigos
            );
    printf("Arsenal: [1] Escopeta (%d/%d) [2] Sniper (%d/%d)\n         [3] Granada (%d/%d) [4] Teletransportador Devastador (%d/%d)\n",
            juego->arsenal.municion_actual[0],
            juego->arsenal.municion_maxima[0],
            juego->arsenal.municion_actual[1],
            juego->arsenal.municion_maxima[1],
            juego->arsenal.municion_actual[2],
            juego->arsenal.municion_maxima[2],
            juego->arsenal.municion_actual[3],
            juego->arsenal.municion_maxima[3]
            );
    printf("=====================================================\n");
    for (int y = 0; y < t->H; y++){
        printf("%2d ", t->H - y); // num filas

        for (int x = 0; x < t->W; x++){
            // de void* a Celda* para acceder a la pieza
            Celda* c = (Celda*)t->celdas[y][x];
            if (c->pieza == NULL) {
                printf("[ ]");
            } else {
                printf("[%c]", c->pieza->tipo);
            }
        }
        printf("\n");
    }
    // eje X
    printf("   ");
    for (int x = 0; x < t->W; x++) printf(" %d ", x + 1);
    printf("\n");

};


void tablero_liberar(struct Tablero *tablero) {
    if (!tablero || !tablero->celdas) return;

    for (int y = 0; y < tablero->H; y++) {
        if (tablero->celdas[y]) {
            for (int x = 0; x < tablero->W; x++) {
                Celda* c = (Celda*)tablero->celdas[y][x];
                if (c) {
                    // liberamos pieza 1ro en caso de
                    if (c->pieza != NULL) {
                        free(c->pieza); 
                    }
                    free(c);
                }
            }
            // liberamos el arreglo de punteros de la fila (void **)
            free(tablero->celdas[y]);
        }
    }
    // liberamos el arreglo de filas (void ***) fuera del bucle
    free(tablero->celdas);
    
} /* debe limpiar la memoria heap */