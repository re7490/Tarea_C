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
    srand((unsigned int)time(NULL)); // Semilla para aleatoriedad
    Juego juego;
    juego.nivel_actual = 1;
    juego.turno_actual = 1;
    juego.turno_enemigos = 0;
    
    juego.t = tablero_crear(12, 12);
    if (!juego.t){
        printf("Error: No se pudo crear el tablero");
        return 1;
    }
    
    juego.jugador = (Pieza *)malloc(sizeof(Pieza));
    spawn_rey(&juego);
    inicializar_armas(&juego);
    
    char input;
    bool turno_valido;

    while(true){
        tablero_imprimir(&juego);
        printf("Ingrese movimiento (WASD/QEZC) o arma (1234): ");
        scanf(" %c", &input);
        turno_valido = false;
        switch (tolower(input)) { //pasamos el input a min
            case 'w': turno_valido = mover_rey(&juego,  0, -1); break;
            case 's': turno_valido = mover_rey(&juego,  0,  1); break;
            case 'a': turno_valido = mover_rey(&juego, -1,  0); break;
            case 'd': turno_valido = mover_rey(&juego,  1,  0); break;
            case 'q': turno_valido = mover_rey(&juego, -1, -1); break;
            case 'e': turno_valido = mover_rey(&juego,  1, -1); break;
            case 'z': turno_valido = mover_rey(&juego, -1,  1); break;
            case 'c': turno_valido = mover_rey(&juego,  1,  1); break;
            
            // Aquí irán las llamadas a las armas (1, 2, 3, 4) más adelante
            default:
                printf("Accion no reconocida.\n");
                break;
        }
        if (turno_valido) {
            // 1. Verificar si el Rey entró en una casilla enemiga (opcional según tu lógica)
            // 2. Mover enemigos
            mover_enemigos(&juego);
            
            // 3. Limpiar muertos por si hubo trampas o efectos
            limpiar_enemigos_muertos(&juego);
            
            // 4. Actualizar contadores
            juego.turno_actual++;
            juego.turno_enemigos++;
        } else {
            printf("Turno no consumido. Intente de nuevo.\n");
        }
    }
    tablero_liberar(juego.t);
    free(juego.jugador);
    return 0;
};