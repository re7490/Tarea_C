#ifndef PIEZAS_H
#define PIEZAS_H

#include <stdbool.h>

struct Juego;

typedef struct Pieza{
    char tipo; /* ’P’=Peon, ’C’=Caballo, ’A’=Alfil, ’T’=Torre, ’Q’=Reina, ’R’=Rey */
    int hp;
    int x, y;
    bool movido; /* Para evitar que una pieza mueva varias veces en el mismo turno */   
} Pieza;

typedef struct Celda{
    Pieza *pieza; /* NULL si la celda esta vacia */
} Celda;

void spawn_nivel(struct Juego *juego, int nivel);
void mover_enemigos(struct Juego *juego);
bool verificar_estado_rey(struct Juego *juego); /* Revisa si el Rey esta en Jaque */
void spawn_rey(struct Juego *juego); /* Spawnea al Rey en el tablero */  
bool mover_rey(struct Juego *juego, int dir_x, int dir_y); /* Mueve al Rey en la direccion dada */   

#endif