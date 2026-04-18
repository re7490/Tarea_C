#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tablero.h"
#include "piezas.h"
#include "armas.h"
#include "main.h"

bool escopeta(struct Juego *j, int dir_x, int dir_y) {
    if (j->arsenal.municion_actual[0] <= 0){
        printf("¡Sin municion de escopeta!\n");
        return false;
    }

    int x_impacto = j->jugador->x + dir_x;
    int y_impacto = j->jugador->y + dir_y;

    // primer impacto (distancia 1)
    if (esta_en_rango(j, x_impacto, y_impacto)) {
        Celda *c1 = (Celda *)j->t->celdas[y_impacto][x_impacto];
        if (c1->pieza != NULL) {
            c1->pieza->hp -= 2; // daño 2 
            printf("Escopetazo directo! 2 HP a %c.\n", c1->pieza->tipo);
        }
    }

    // daño en area (cono)
    int x2_centro = x_impacto + dir_x;
    int y2_centro = y_impacto + dir_y;
    
    for (int i = -1; i <= 1; i++) {
        int target_x, target_y;
        
        if (dir_x != 0 && dir_y == 0) { // horinzontal <->
            target_x = x2_centro;
            target_y = y2_centro + i;
        } else if (dir_x == 0 && dir_y != 0) { // vertical |
            target_y = y2_centro;
        } else { // diagonal " / y \ "
            target_x = x2_centro + (i * (dir_x == 1 ? -1 : 1));
            target_y = y2_centro + (i * (dir_y == 1 ? 1 : -1));
        }

        if (esta_en_rango(j, target_x, target_y)) {
            Celda *c2 = (Celda *)j->t->celdas[target_y][target_x];
            if (c2->pieza != NULL) {
                c2->pieza->hp -= 1; // daño 1
            }
        }
    }

    j->arsenal.municion_actual[0]--;
    return true;
}

bool francotirador(struct Juego *j, int dir_x, int dir_y){
    // validamos municion
    if (j->arsenal.municion_actual[1] <= 0) {
        printf("Sin municion de Sniper!\n");
        return false;
    }

    // proyectil comienza donde esta el Rey
    int cur_x = j->jugador->x + dir_x;
    int cur_y = j->jugador->y + dir_y;

    // recorrer el tablero en direccion elegida
    while (esta_en_rango(j, cur_x, cur_y)) {
        Celda *c = (Celda *)j->t->celdas[cur_y][cur_x];

        // ¿hay una pieza en esta celda?
        if (c->pieza != NULL) {
            printf("IMPACTO!! 3 HP infligidos a %c.\n", c->pieza->tipo);
            c->pieza->hp -= 3; // inflige 3 de daño 
            
            // Si la pieza muere, se maneja en una funcion de limpieza
            break; 
        }

        // avanza a la siguiente casilla en la misma trayectoria
        cur_x += dir_x;
        cur_y += dir_y;
    }

    // consumir municion
    j->arsenal.municion_actual[1]--;
    return true;


};

bool granada(struct Juego *j, int dir_x, int dir_y) {
    // validamos municion
    if (j->arsenal.municion_actual[2] <= 0) {
        printf("¡Sin municion de granada!\n");
        return false; 
    }

    // calculo punto de impacto (exactamente a 3 casillas) 
    int target_x = j->jugador->x + (dir_x * 3);
    int target_y = j->jugador->y + (dir_y * 3);

    printf("¡Lanzando granada a (%d, %d)!\n", target_x + 1, j->t->H - (target_y));

    // procesar area de explosion 3x3 centrada en el impacto 
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int current_x = target_x + dx;
            int current_y = target_y + dy;

            // usar esta_en_rango para cada casilla de la explosion
            if (esta_en_rango(j, current_x, current_y)) {
                Celda *c = (Celda *)j->t->celdas[current_y][current_x];
                
                // 2 de daño a todo en el radio 
                if (c->pieza != NULL) {
                    c->pieza->hp -= 2;
                    printf("Explosion daño a %c en (%d, %d).\n", 
                            c->pieza->tipo, current_x + 1, j->t->H - (current_y));
                }
            }
        }
    }

    j->arsenal.municion_actual[2]--;
    return true;
}

bool especial(struct Juego *j, int dir_x, int dir_y) {
    // validacion municion
    if (j->arsenal.municion_actual[3] <= 0) {
        printf("¡Sin municion del Enroque Ofensivo!\n");
        return false;
    }

    // calculo casilla destino
    int target_x = j->jugador->x + (dir_x * 2);
    int target_y = j->jugador->y + (dir_y * 2);

    // destino dentro tablero?
    if (!esta_en_rango(j, target_x, target_y)) {
        printf("Movimiento invalido: El destino del Enroque está fuera del tablero.\n");
        return false;
    }

    // celdas origen y destino
    Celda *celda_origen = (Celda *)j->t->celdas[j->jugador->y][j->jugador->x];
    Celda *celda_destino = (Celda *)j->t->celdas[target_y][target_x];

    // casilla de aterrizaje vacia
    if (celda_destino->pieza != NULL) {
        printf("¡IMPACTO DIRECTO! El Rey aplasta a '%c' haciendole 5 de daño.\n", celda_destino->pieza->tipo);
        free(celda_destino->pieza);
        celda_destino->pieza = NULL;
        j->enemigos_vivos--;
    }

    // confirmar tp del Rey
    celda_origen->pieza = NULL;
    celda_destino->pieza = j->jugador;
    j->jugador->x = target_x;
    j->jugador->y = target_y;
    
    printf("\n¡TELETRANSPORTADOR DEVASTADOR! El Rey se teletransporta a la casilla (%d, %d).\n", target_x + 1, target_y + 1);

    // onda expansiva: Daño 4 casillas adyacentes (Arriba, Abajo, Izquierda, Derecha)
    int adj_dx[] = {0, 0, -1, 1};
    int adj_dy[] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; i++) {
        int wave_x = target_x + adj_dx[i];
        int wave_y = target_y + adj_dy[i];
        
        // casilla onda expansiva valida y tiene un enemigo
        if (esta_en_rango(j, wave_x, wave_y)) {
            Celda *c = (Celda *)j->t->celdas[wave_y][wave_x];
            if (c->pieza != NULL  && c->pieza->tipo != 'R') {
                printf("La onda expansiva alcanza a '%c' en (%d, %d). -2 HP\n", 
                       c->pieza->tipo, wave_x + 1, wave_y + 1);
                
                aplicar_daño(j, wave_x, wave_y, 2);
            }
        }
    }

    // municion -1
    j->arsenal.municion_actual[3]--;
    return true; // turno consumido
}

void inicializar_armas(Juego *j) {
    // Escopeta
    j->arsenal.municion_maxima[0] = 2;
    j->arsenal.municion_actual[0] = 2;
    j->arsenal.disparar[0] = escopeta;

    // Sniper
    j->arsenal.municion_maxima[1] = 1;
    j->arsenal.municion_actual[1] = 1;
    j->arsenal.disparar[1] = francotirador;

    // Granada
    j->arsenal.municion_maxima[2] = 2;
    j->arsenal.municion_actual[2] = 2;
    j->arsenal.disparar[2] = granada;

    // Especial
    j->arsenal.municion_maxima[3] = 2;
    j->arsenal.municion_actual[3] = 2;
    j->arsenal.disparar[3] = especial;
}

bool esta_en_rango(Juego *j, int x, int y) {
    return (x >= 0 && x < j->t->W && y >= 0 && y < j->t->H);
}

void aplicar_daño(struct Juego *j, int x, int y, int puntos_daño) {
    if (esta_en_rango(j, x, y)) {
        Celda *c = (Celda *)j->t->celdas[y][x];
        if (c->pieza != NULL) {
            c->pieza->hp -= puntos_daño;
            // agregar logica eliminar pieza si HP <= 0
            // de manera q decremente enemigos_vivos en el juego
        }
    }
}

void limpiar_enemigos_muertos(struct Juego *j) {
    for (int y = 0; y < j->t->H; y++) {
        for (int x = 0; x < j->t->W; x++) {
            Celda *c = (Celda *)j->t->celdas[y][x];
            
            // si hay una pieza y no es el Rey
            if (c->pieza != NULL && c->pieza->tipo != 'R') {
                if (c->pieza->hp <= 0) {
                    printf("¡%c ha sido eliminado!\n", c->pieza->tipo);
                    
                    free(c->pieza); 
                    c->pieza = NULL;
                    j->enemigos_vivos--;
                }
            }
        }
    }
}