CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 -g

# Todos los fuentes .c
SRCS = main.c tablero.c piezas.c armas.c
OBJS = $(SRCS:.c=.o)

# Nombre del ejecutable
BIN = rey_destronado

.PHONY: all clean run valgrind

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

valgrind: $(BIN)
	valgrind --leak-check=full --show-leak-kinds=all \
	         --track-origins=yes --error-exitcode=1 \
	         ./$(BIN)

clean:
	rm -f $(OBJS) $(BIN)