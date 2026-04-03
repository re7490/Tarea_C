#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#include "armas.h"
#include "piezas.h"
#include "tablero.h"
#include "main.h"

int main(){
    Juego juego;
    printf("¡Bienvenido al juego!\n Desea iniciar el juego?");
    printf("0 - NO | 1 - SI\n Ingrese opcion: ");
    int iniciar;
    while (scanf("%d", &iniciar) != 0 && scanf("%d", &iniciar) != 1)
    {
        printf("Opcion invalida. Intente de nuevo: ");
    }
    if (scanf("%d", &iniciar) == 0) {
        printf("Juego no ejecutado....(por que elegirias esta opcion?)");
        return 1; }
    juego.nivel_actual = 1;
    juego.turno_actual = 1;
    juego.turno_enemigos = 0;
    juego.enemigos_vivos = 0;

    juego.t = tablero_crear(12, 12);
    if (!juego.t){
        printf("Error: No se pudo crear el tablero");
        return 1;
    }
    juego.t->celdas[5][5] = malloc(sizeof(Celda));
    Celda* c = (Celda*)juego.t->celdas[5][5];
    c->pieza = malloc(sizeof(Pieza));
    c->pieza->tipo = 'R'; // El Rey
    c->pieza->x = 5;
    c->pieza->y = 5;

    
    tablero_imprimir(&juego);


    


    return 0;
};