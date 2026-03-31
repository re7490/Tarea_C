#ifndef MAIN_H
#define MAIN_H

typedef struct {
    Tablero *t;
    Armas arsenal;
    Pieza *jugador; /* El Rey */
    int nivel_actual; /* 1, 2 o 3 */
    int turno_enemigos; /* Contador para gestionar piezas lentas como la Torre */
} Juego;
// Rol: Inicia el ciclo de juego, maneja el bucle principal de entrada (WASD+QEZC / 1234),
//gestiona el avance de niveles y libera la memoria general al terminar o perder.

#endif