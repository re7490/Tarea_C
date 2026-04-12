#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "piezas.h"
#include "piezas.h"
#include "armas.h"
#include "main.h"

void spawn_nivel(struct Juego *juego, int nivel){return;};


void mover_enemigos(struct Juego *juego){return;};


bool verificar_estado_rey(struct Juego *juego){return false;}; /* Revisa si el Rey esta en Jaque */

void spawn_rey(struct Juego *juego) {
    Tablero *t = juego->t;
    
    // rango x es de 1 hasta (W - 2) para evitar esquinas
    int x_random = 1 + (rand() % (t->W - 2));
    int y_rey = t->H - 1; // Última fila
    
    juego->jugador->tipo = 'R';
    juego->jugador->hp = 1; 
    juego->jugador->x = x_random;
    juego->jugador->y = y_rey;

    // puntero en la celda del tablero
    Celda *c = (Celda *)t->celdas[y_rey][x_random];
    c->pieza = juego->jugador; 
}

bool mover_rey(struct Juego *juego, int delta_x, int delta_y) {
    // calcular nueva posicion
    int nuevo_x = juego->jugador->x + delta_x;
    int nuevo_y = juego->jugador->y + delta_y;

    // validamos limites del tablero 
    if (nuevo_x < 0 || nuevo_x >= juego->t->W || nuevo_y < 0 || nuevo_y >= juego->t->H) {
        printf("Movimiento invalido: fuera del tablero.\n");
        return false; // no consume turno 
    }

    // obtener celdas (origen y destino)
    Celda *celda_origen = (Celda *)juego->t->celdas[juego->jugador->y][juego->jugador->x];
    Celda *celda_destino = (Celda *)juego->t->celdas[nuevo_y][nuevo_x];

    // ver si hay pieza enemiga, si es asi, el mov no se realiza y se indica al jugador
    if (celda_destino->pieza != NULL) {
        printf("Movimiento invalido: casilla ocupada.\n");
        return false;
    }

    // hacer mov
    celda_origen->pieza = NULL;      // vaciar celda actual
    celda_destino->pieza = juego->jugador; // poner Rey en la nueva celda
    juego->jugador->x = nuevo_x;
    juego->jugador->y = nuevo_y;

    // recargamos Escopeta
    if (juego->arsenal.municion_actual[0] < juego->arsenal.municion_maxima[0]) {
        juego->arsenal.municion_actual[0]++;
    }

    return true; // mov exitoso, consume turno 
}