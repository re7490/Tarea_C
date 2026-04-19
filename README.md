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
    make --version

En caso que alguno de estos no muestre versión haga lo siguiente (caso contrario ignore esto):
    sudo apt update
    sudo apt install build-essential

Eso instalara lo necesario para ejecutar el programa.
Una vez eso listo, ejecute:
    make
    ./rey_destronado

------------------------------------------------------------------------------------------------------------
Al iniciar el juego se generara el primer nivel automaticamente.
El Rey aparece en una columna aleatoria del tablero, pero siempre en la 1ra fila inferior.
Los enemigos aparecen en las dos filas superiores, en columnas aleatorias (Peones 2da fila superior, las demas en la 1ra fila superior).

Las acciones son las siguientes:
    A,a (Izquierda) - D,d (Derecha) - W,w (Arriba) - S,s (Abajo) 
    Q,q (Arriba izquierda)- E,e (Arriba derecha) - Z,z (Abajo izquierda) - C,c (Abajo derecha)
    1 (Escopeta) - 2 (Sniper) - 3 (Granada) - 4 (Teletransportador devastador)
    0 (Salir del juego)

Reglas:
El jugador aparece en el tablero con la maxima municion de todas las armas (Escopeta=2, Sniper=1, Granada=2, Especial=2), al usar las armas disminuiran sus municiones y no se podran recargar, a excepcion de la Escopeta, que recarga 1 municion cada vez que se mueve el jugador.
Al momento de seleccionar el arma a usar, se le pedira al jugador una direccion en la que disparar.

Los enemigos se moveran tal cual como lo hacen en ajedrez:
    Peon: avanza 1 casilla verticalmente hacia el extremo opuesto del tablero, puede atacar al rey si se encuentra en sus diagonales inferiores o si se encuentra en su casilla inferior
    Alfil: se mueve solo en las diagonales con un maximo de 3 casillas por turno.
    Torre: se mueve solo en las ortogonales con un maximo de 3 casillas por turno, ademas solo podra moverse cada 2 turnos.
    Caballo: se mueve en forma de L.
    Reina: se mueve como un alfil y una torre, teniendo un maximo de 4 casillas por turno.

Ademas, para que no sea casi imposible el juego, en cada turno de los enemigos solo puden moverse como maximo 3 enemigos, y los que se mueven son completamente aleatorios.

El HUD del juego muestra lo siguiente:
    -Turno actual y de los enemigos
    -Enemigos vivos
    -Munición de todas las armas
    -Tablero
    -Solicitacion de Input
    -Mensajes de eventos

Para ganar, el jugador debera avanzar eliminando a todos los enemigos de los niveles y eliminar a la Reina en el ultimo Nivel.
Si es eliminado por alguna pieza antes de lo anterior, perdera.

Consideraciones:

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

El arma especial (Teletransportador devastador), consiste en un teletransportador que poseia el Rey en su boveda, el cual le permite al Rey teletransportarse a 2 casillas en cualquier direccion, inflingiendo 5 de daño en la casilla donde aparece e inflingiendo 2 de daño a los enemigos que esten adyacentes (arriba, abajo, a la izquierda o derecha).