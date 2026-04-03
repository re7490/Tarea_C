Tarea 2 - Lenguajes de Programación
Nombre: Renato Padilla -- Rol: 202473641-8

El programa adjunto implementa una versión simplificada de Shotgun King (juegazo por cierto).

En este, el jugador controla al Rey, quien, debido a ser un tirano durante varios años, las piezas de su reino se revelan y lo destronan.
Sin mas opciones, el Rey se esconde en su boveda, donde posee varias armas. Decidido a retomar el control de su reino, toma su armamento y sale a recuperar su trono.

El juego es por turnos y consta de 3 niveles, una vez el jugador elimine a los enemigos en el tablero, avanzara de nivel.
Una vez llegado al nivel 3, el jugador debera eliminar a la reina para ganar el juego.
Si el jugador es eliminado por las piezas antes de cumplir el objetivo, perdera. 


Para el correcto funcionamiento del programa (compilación y ejecución), todos los archivos adjuntos (.h, .c y Makefile) 
a este README deben estar en la misma carpeta, además de ser operado en Linux Debian. 
Luego, abra la terminal dentro de la misma carpeta y ejecute lo siguiente:

gcc --version
make --versión

En caso que alguno de estos no muestre versión haga lo siguiente (caso contrario ignore esto):
sudo apt update
sudo apt install build-essential

Eso instalara lo necesario para ejecutar el programa.
Una vez eso listo, ejecute:
make
./space_defender

------------------------------------------------------------------------------------------------------------
Consideraciones, arma especial y manejo de colisiones