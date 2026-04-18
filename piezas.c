#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "piezas.h"
#include "piezas.h"
#include "armas.h"
#include "main.h"

void spawn_nivel(struct Juego *juego, int nivel) {
    Tablero *t = juego->t;
    int peones = 0, caballos = 0, alfiles = 0, torres = 0, reinas = 0;

    // config nivel
    if (nivel == 1) { peones = 4; caballos = 2; alfiles = 2; }
    else if (nivel == 2) { peones = 4; caballos = 2; torres = 2; }
    else if (nivel == 3) { peones = 2; reinas = 1; alfiles = 1; torres = 1; }

    juego->enemigos_vivos = peones + caballos + alfiles + torres + reinas;

    char tipos[] = {'P', 'C', 'A', 'T', 'Q'};
    int cantidades[] = {peones, caballos, alfiles, torres, reinas};
    int hps[] = {1, 2, 2, 4, 3}; // vida

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < cantidades[i]; j++) {
            Pieza *p = (Pieza *)malloc(sizeof(Pieza));
            p->tipo = tipos[i];
            p->hp = hps[i];
            p->movido = false;
            
            int x, y;
            // Peones fila 2, Especiales fila 1
            y = (p->tipo == 'P') ? 1 : 0;
            
            // buscar casilla vacia random en fila
            do {
                x = rand() % t->W;
            } while (((Celda *)t->celdas[y][x])->pieza != NULL);

            p->x = x;
            p->y = y;
            ((Celda *)t->celdas[y][x])->pieza = p;
        }
    }
}


void mover_enemigos(struct Juego *juego) {
    Tablero *t = juego->t;

    // flags mov a falso y ver quiene se pueden mover
    Pieza *enemigos_disponibles[100];
    int contador_enemigos = 0;

    for (int y = 0; y < t->H; y++) {
        for (int x = 0; x < t->W; x++) {
            Celda *c = (Celda *)t->celdas[y][x];
            if (c->pieza && c->pieza->tipo != 'R') {
                c->pieza->movido = false;
                enemigos_disponibles[contador_enemigos++] = c->pieza;
            }
        }
    }
    
    int limite = (contador_enemigos < 3) ? contador_enemigos : 3; // maximo 3 mov por turno
    int movidos_este_turno = 0;

    for (int i = 0; i < contador_enemigos && movidos_este_turno < limite; i++) {
        Pieza *p = enemigos_disponibles[i];

        Celda *c = (Celda *)t->celdas[p->y][p->x];

        if (p && p->tipo != 'R' && !p->movido) {
            
            if (p->tipo == 'P') {
                // Peon avanza 1 casilla (recto)
                int nx = p->x; // misma columna
                int ny = p->y + ((juego->jugador->y > p->y) ? 1 : (juego->jugador->y < p->y ? -1 : 0));

                if (nx >= 0 && nx < t->W && ny >= 0 && ny < t->H) {
                    Celda *dest = (Celda *)t->celdas[ny][nx];
                    if (dest->pieza != NULL && dest->pieza->tipo == 'R') {
                        printf("¡El Peón ha capturado al Rey! GAME OVER\n");
                        exit(0);
                    }
                    if (dest->pieza == NULL) {
                        dest->pieza = p;
                        c->pieza = NULL;
                        p->x = nx; p->y = ny;
                        p->movido = true;
                        movidos_este_turno++;
                    }
                }
            } 
            else if (p->tipo == 'T' && (juego->turno_enemigos % 2 == 0)) {
                // Torre hasta 3 casillas ortogonales
                int dx = 0, dy = 0;
                if (abs(juego->jugador->x - p->x) > abs(juego->jugador->y - p->y)) 
                    dx = (juego->jugador->x > p->x) ? 1 : -1;
                else 
                    dy = (juego->jugador->y > p->y) ? 1 : -1;

                int nx = p->x, ny = p->y, pasos = 0;
                while (pasos < 3) {
                    int tx = nx + dx, ty = ny + dy;
                    if (tx < 0 || tx >= t->W || ty < 0 || ty >= t->H) break;
                    Celda *sig_c = (Celda *)t->celdas[ty][tx];
                    if (sig_c->pieza != NULL) {
                        if (sig_c->pieza->tipo == 'R') {
                            printf("¡La Torre ha capturado al Rey! GAME OVER.\n");
                            exit(0); 
                        }
                        break; 
                    }
                    nx = tx; ny = ty; pasos++;
                }
                if (nx != p->x || ny != p->y) {
                    ((Celda *)t->celdas[ny][nx])->pieza = p;
                    c->pieza = NULL;
                    p->x = nx; p->y = ny;
                    p->movido = true;
                    movidos_este_turno++;
                }
            }
            else if (p->tipo == 'A') {
                // Alfil hasta 3 casillas diagonales
                int dx = (juego->jugador->x > p->x) ? 1 : -1;
                int dy = (juego->jugador->y > p->y) ? 1 : -1;
                int nx = p->x, ny = p->y, pasos = 0;

                while (pasos < 3) {
                    int tx = nx + dx, ty = ny + dy;
                    if (tx < 0 || tx >= t->W || ty < 0 || ty >= t->H) break;
                    Celda *sig_c = (Celda *)t->celdas[ty][tx];
                    if (sig_c->pieza != NULL) {
                        if (sig_c->pieza->tipo == 'R') {
                            printf("¡El Alfil ha capturado al Rey! GAME OVER.\n");
                            exit(0); 
                        }
                        break; 
                    }
                    nx = tx; ny = ty; pasos++;
                }
                if (nx != p->x || ny != p->y) {
                    ((Celda *)t->celdas[ny][nx])->pieza = p;
                    c->pieza = NULL;
                    p->x = nx; p->y = ny;
                    p->movido = true;
                    movidos_este_turno++;
                }
            }
            else if (p->tipo == 'C') {
                // Caballo mov en L minimizando distancia
                int saltos_x[] = {1, 2, 2, 1, -1, -2, -2, -1};
                int saltos_y[] = {-2, -1, 1, 2, 2, 1, -1, -2};
                int mejor_x = p->x, mejor_y = p->y;
                double dist_minima = -1.0; 

                for (int i = 0; i < 8; i++) {
                    int nx = p->x + saltos_x[i], ny = p->y + saltos_y[i];
                    if (nx >= 0 && nx < t->W && ny >= 0 && ny < t->H) {
                        Celda *c_dest = (Celda *)t->celdas[ny][nx];
                        if (c_dest->pieza != NULL && c_dest->pieza->tipo == 'R') {
                            printf("¡El Caballo ha capturado al Rey! GAME OVER.\n");
                            exit(0);
                        }
                        if (c_dest->pieza == NULL) {
                            double dist = sqrt(pow(juego->jugador->x - nx, 2) + pow(juego->jugador->y - ny, 2));
                            if (dist_minima < 0 || dist < dist_minima) {
                                dist_minima = dist; mejor_x = nx; mejor_y = ny;
                            }
                        }
                    }
                }
                if (mejor_x != p->x || mejor_y != p->y) {
                    ((Celda *)t->celdas[mejor_y][mejor_x])->pieza = p;
                    c->pieza = NULL;
                    p->x = mejor_x; p->y = mejor_y;
                    p->movido = true;
                    movidos_este_turno++;
                }
            }
            else if (p->tipo == 'Q') {
                // Reina hasta 4 casillas en cualquier direccion
                int dx = (juego->jugador->x > p->x) ? 1 : (juego->jugador->x < p->x ? -1 : 0);
                int dy = (juego->jugador->y > p->y) ? 1 : (juego->jugador->y < p->y ? -1 : 0);
                int nx = p->x, ny = p->y, pasos = 0;

                while (pasos < 4) {
                    int tx = nx + dx, ty = ny + dy;
                    if (tx < 0 || tx >= t->W || ty < 0 || ty >= t->H) break;
                    Celda *sig_c = (Celda *)t->celdas[ty][tx];
                    if (sig_c->pieza != NULL) {
                        if (sig_c->pieza->tipo == 'R') {
                            printf("¡LA REINA HA CAPTURADO AL REY! GAME OVER.\n");
                            exit(0); 
                        }
                        break; 
                    }
                    nx = tx; ny = ty; pasos++;
                }
                if (nx != p->x || ny != p->y) {
                    ((Celda *)t->celdas[ny][nx])->pieza = p;
                    c->pieza = NULL;
                    p->x = nx; p->y = ny;
                    p->movido = true;
                    movidos_este_turno++;
                }
            }
        }
    }
}

bool verificar_estado_rey(struct Juego *juego){
    return false;}; /* Revisa si el Rey esta en Jaque */

void spawn_rey(struct Juego *juego) {
    Tablero *t = juego->t;
    
    // rango x es de 1 hasta (W - 2) para evitar esquinas
    int x_random = 1 + (rand() % (t->W - 2));
    int y_rey = t->H - 1; // ultima fila
    
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