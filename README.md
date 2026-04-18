Tarea 2 - Lenguajes de Programación
Nombre: Renato Padilla -- Rol: 202473641-8

(Alt+z)-->Recomendacion

El programa adjunto implementa una versión simplificada de Shotgun King (juegazo por cierto).

En este, el jugador controla al Rey, quien, debido a ser un tirano durante varios años, las piezas de su reino se revelan y lo destronan.
Sin mas opciones, el Rey se esconde en su boveda, donde posee varias armas. Decidido a retomar el control de su reino, toma su armamento y sale a recuperar su trono.

El juego es por turnos y consta de 3 niveles, una vez el jugador elimine a los enemigos en el tablero, avanzara de nivel.
Una vez llegado al nivel 3, el jugador debera eliminar a la reina para ganar el juego.
Si el jugador es eliminado por las piezas antes de cumplir el objetivo, perdera. 


Para el correcto funcionamiento del programa (compilación y ejecución), todos los archivos adjuntos (.h, .c y Makefile) a este README deben estar en la misma carpeta, además de ser operado en Linux Debian. 
Luego, abra la terminal dentro de la misma carpeta y ejecute lo siguiente:
    gcc --version
    make --versión

En caso que alguno de estos no muestre versión haga lo siguiente (caso contrario ignore esto):
    sudo apt update
    sudo apt install build-essential

Eso instalara lo necesario para ejecutar el programa.
Una vez eso listo, ejecute:
    make
    ./rey_destronado

------------------------------------------------------------------------------------------------------------
Consideraciones:

El Rey aparecera en una columna aleatoria del tablero, pero siempre aparecera en la 1ra fila inferior.
Los enemigos apareceran en las dos filas superiores, en columnas aleatorias (Peones 2da fila superior, las demas en la 1ra fila superior).
Los enemigos se moveran tal cual como lo hacen en ajedrez, se mueven maximo 3 enemigos por turno, y los enemigos que se mueven son completamente aleatorios.

La terminal mostrara solo un tablero a la vez, es decir, al ejecutar una accion se limpia la terminal y a su vez se imprimiran los datos del juego y el tablero inmediatamente con la accion realizada.
Cabe recalcar que se le pedira al jugador presionar otra vez Enter en caso de cualquiera de los siguientes casos:
    - Quiera moverse fuera del tablero
    - Quiera moverse a una casilla ocupada (movimiento normal, sin contar arma especial)
    - Haga daño a un enemigo
    - Elimine a un enemigo
    - Utilice un arma sin municion
    - Quiera moverse a una casilla riesgosa (riesgo de jauqe si la pieza se mueve)*
    - Complete el nivel actual

En caso que un enemigo quiera avanzar hacia el Rey por su ruta mas optima, y resulte que la casilla esta ocupada por otro enemigo, el enemigo pasara a usar otra ruta  con tal de alcanzar al Rey.

Una vez todos los enemigos del tablero hayan sido eliminado, el jugador avanzara de nivel. En caso de estar en el ultimo nivel y eliminar a la Reina, el jugador ganara automaticamente.

*Si el Rey quiere moverse a una casilla, y resulta que existe la posibilidad que un enemigo se mueva a esa misma casilla (haciendo jaque mate al jugador), se le notificara al jugador de esto y no hara el movimiento, diciendole que estara en riego de perder y pidiendole otra vez un input. Esto sucedera un total de dos veces, si el jugador aun asi insiste en ir a esa casilla, el juego lo permitira. (inspirado en el juego original). 
*Solo aplica si el Rey quiere hacer un movimiento

ARMA ESPECIAL:
