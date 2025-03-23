# Nombre del ejecutable
EXEC = anthill

# Archivos fuente
SRC = game_loop.c command.c game_actions.c game.c graphic_engine.c space.c game_reader.c player.c object.c character.c set.c link.c inventory.c

# Archivos objeto generados a partir de los archivos fuente
OBJ = $(SRC:.c=.o)

LIBS = -L. -lscreen

# Compilador y sus opciones
CC = gcc
CFLAGS = -Wall -g -Werror -Wpedantic -ansi

# Regla principal para compilar el ejecutable
all: $(EXEC)

# Regla para compilar el ejecutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

# Regla para compilar los archivos .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar los archivos generados
clean:
	rm -f $(OBJ) $(EXEC)

# Regla para recompilar completamente (limpiar y compilar de nuevo)
rebuild: clean all

# Regla para ejecutar el programa
run: $(EXEC)
	./$(EXEC) $(EXEC).dat

# Regla para ejecutar Valgrind
valgrind: $(EXEC)
	valgrind -s --show-leak-kinds=all --track-origins=yes --leak-check=full  ./$(EXEC) $(EXEC).dat

