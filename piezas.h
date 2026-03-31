#ifndef PIEZAS_H
#define PIEZAS_H

typedef struct {
    char tipo; /* ’P’=Peon, ’C’=Caballo, ’A’=Alfil, ’T’=Torre, ’Q’=Reina, ’R’=Rey */
    int hp;
    int x, y;
} Pieza;

typedef struct {
    Pieza *pieza; /* NULL si la celda esta vacia */
} Celda;

void spawn_nivel(struct Juego *juego, int nivel);
void mover_enemigos(struct Juego *juego);
bool verificar_estado_rey(struct Juego *juego); /* Revisa si el Rey esta en Jaque */

#endif