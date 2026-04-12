#ifndef ARMAS_H
#define ARMAS_H

#include <stdbool.h>

struct Juego; /* Forward declaration */
typedef struct Juego Juego;

typedef bool (*FuncArma)(struct Juego *j, int dir_x, int dir_y); /* Puntero a funcion */

typedef struct Armas{
    int municion_actual[4]; /* Se puede cambiar */
    int municion_maxima[4]; /* Se puede cambiar */
    FuncArma disparar[4]; /* Arreglo de punteros a funcion con las 4 armas */
} Armas;


bool escopeta(struct Juego *j, int dir_x, int dir_y);
bool francotirador(struct Juego *j, int dir_x, int dir_y); /* Ej (x,y) = (1,0), (0,-1)... */
bool granada(struct Juego *j, int target_x, int target_y);
bool especial(struct Juego *j, int dir_x, int dir_y); /* Se puede modificar */
/* Es imperativo el uso del arreglo FuncArma para utilizar las funciones de disparo */
/* Ej de uso en main : juego->arsenal.disparar[3](juego, input_x, input_y); */

void inicializar_armas(Juego *j); /* Inicializa el arreglo de punteros a funcion con las funciones de disparo correspondientes */
bool esta_en_rango(Juego *j, int x, int y);
void aplicar_daño(struct Juego *j, int x, int y, int puntos_daño);
void limpiar_enemigos_muertos(struct Juego *j);

#endif