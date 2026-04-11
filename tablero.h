#ifndef TABLERO_H
#define TABLERO_H

struct Juego;

typedef struct Tablero{
    int W, H;
    void ***celdas; /* celdas[y][x] apunta a Celda* */
} Tablero;
/* Es completamente imperativo que el Tablero se maneje de la manera entregada */

Tablero* tablero_crear(int ancho, int alto);
void tablero_imprimir(struct Juego *juego);
void tablero_liberar(struct Tablero *tablero); /* debe limpiar la memoria heap */

#endif