#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#include "armas.h"
#include "piezas.h"
#include "tablero.h"
#include "main.h"


/**
 * Funcion principal del programa. Inicializa la semilla aleatoria (permitiendo spawn aleatorio), crea el estado base del Juego y maneja el bucle principal de entrada (WASD/QEZC + 1234). Gestiona el avance de niveles, la destruccion y recreacion de tableros, y finaliza liberando toda la memoria cuando el jugador gana, pierde o sale.
 * * @return 0 indicando la salida exitosa del programa.
 */
int main(){
    srand((unsigned int)time(NULL)); // semilla para aleatoriedad
    Juego juego;
    juego.nivel_actual = 1;
    juego.turno_actual = 1;
    juego.turno_enemigos = 0;
    juego.advertencias_jaque = 0;
    
    juego.t = tablero_crear(12, 12);
    if (!juego.t){
        printf("Error: No se pudo crear el tablero");
        return 1;
    }
    
    juego.jugador = (Pieza *)malloc(sizeof(Pieza));
    spawn_rey(&juego);
    spawn_nivel(&juego, juego.nivel_actual);
    inicializar_armas(&juego);
    
    char input;
    bool turno_valido;

    while(true){

        system("clear"); // para tener un tablero y HUD a la vez (mayor fluidez)
        //printf("\033[H\033[J");
        tablero_imprimir(&juego);
        if (verificar_estado_rey(&juego)) {
            printf("\n¡PELIGRO! Tu casilla actual está bajo amenaza. ¡Estás en riesgo de Jaque!\n");
        }

        printf("En caso de querer salir: 0.\n");
        printf("Ingrese movimiento (WASD/QEZC) o arma (1234): ");
        scanf(" %c", &input);
        while (getchar() != '\n'); // limpiar buffer

        turno_valido = false;
        bool pausa = false; // si pasa a ser true = "evento" ocurrido u advertenciaa

        char dir;
        int dx = 0, dy = 0;

        switch (tolower(input)) { // pasamos el input a min
            case 'w': turno_valido = mover_rey(&juego,  0, -1); break;
            case 's': turno_valido = mover_rey(&juego,  0,  1); break;
            case 'a': turno_valido = mover_rey(&juego, -1,  0); break;
            case 'd': turno_valido = mover_rey(&juego,  1,  0); break;
            case 'q': turno_valido = mover_rey(&juego, -1, -1); break;
            case 'e': turno_valido = mover_rey(&juego,  1, -1); break;
            case 'z': turno_valido = mover_rey(&juego, -1,  1); break;
            case 'c': turno_valido = mover_rey(&juego,  1,  1); break;
            
            case '1': case '2': case '3': case '4':

                printf("Ingrese direccion de disparo (WASD/QEZC): ");
                scanf(" %c", &dir);
                while (getchar() != '\n'); // limpiar buffer

                dir = tolower(dir); // direccion a min
                
                // direccion a deltas (x, y)
                if (dir == 'w') { dy = -1; }
                else if (dir == 's') { dy = 1; }
                else if (dir == 'a') { dx = -1; }
                else if (dir == 'd') { dx = 1; }
                else if (dir == 'q') { dx = -1; dy = -1; }
                else if (dir == 'e') { dx = 1; dy = -1; }
                else if (dir == 'z') { dx = -1; dy = 1; }
                else if (dir == 'c') { dx = 1; dy = 1; }
                else { printf("Direccion invalida.\n"); break; }

                int indice_arma = input - '1'; 
                turno_valido = juego.arsenal.disparar[indice_arma](&juego, dx, dy);
                pausa = true;

                break;
            case '0':
                printf("¡Saliendo del juego!\n");
                tablero_liberar(juego.t);
                free(juego.jugador);
                return 0;
            default:
                printf("Accion no reconocida.\n");
                pausa = true;
                break;
        }
        if (turno_valido) {

            int enemigos_antes = juego.enemigos_vivos; //para poner pausa y mostrar evento de muerte de enemigo

            // limpiar muertos
            limpiar_enemigos_muertos(&juego);

            if (juego.enemigos_vivos < enemigos_antes) {
                pausa = true;
            }
            // mover enemigos
            mover_enemigos(&juego);
                       
            // actualizar contadores
            juego.turno_actual++;
            juego.turno_enemigos++;
        } else {
            printf("Turno no consumido. Intente de nuevo.\n");
            pausa = true;
        }
        
        if (juego.enemigos_vivos == 0) {
            if (juego.nivel_actual < 3) {
                printf("¡NIVEL %d COMPLETADO!\n", juego.nivel_actual);
                juego.nivel_actual++;
                
                // chao tablero viejo y piezas
                tablero_liberar(juego.t);
                
                // nuevas dim tablero
                int nuevo_ancho = (juego.nivel_actual == 2) ? 8 : 6;
                int nuevo_alto = (juego.nivel_actual == 2) ? 8 : 6;
                
                // nuevo tablero y spwan
                juego.t = tablero_crear(nuevo_ancho, nuevo_alto);
                juego.jugador = (Pieza *)malloc(sizeof(Pieza));

                spawn_rey(&juego);
                spawn_nivel(&juego, juego.nivel_actual);
                
                // recarga municion
                for(int i = 0; i < 4; i++) {
                    juego.arsenal.municion_actual[i] = juego.arsenal.municion_maxima[i];
                }
                
                printf("Entrando al Nivel %d...\n", juego.nivel_actual);
                printf("Presiona Enter para continuar...");
                getchar();
                continue; 
            } else {
                printf("¡HAS RECUPERADO TU TRONO! GANASTE EL JUEGO.\n");
                break; 
            }
        }
        if (pausa) { 
            printf("Presiona Enter para continuar...");
            getchar();
        }
    }
    tablero_liberar(juego.t);
    free(juego.jugador);
    return 0;
};