# Nombre del ejecutable
EXEC = anthill

# Archivos fuente
SRC = game_loop.c command.c game_actions.c game.c graphic_engine2.c space.c game_reader.c player.c object.c character.c set.c link.c

# Archivos objeto generados a partir de los archivos fuente
OBJ = $(SRC:.c=.o)

# Bibliotecas necesarias para el proyecto
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lm

# Directorios donde se encuentran las bibliotecas (si es necesario especificarlos)
LIB_DIRS = -L/usr/lib

# Directorios donde se encuentran los archivos de cabecera (si es necesario especificarlos)
INC_DIRS = -I/usr/include/SDL2

# Compilador y sus opciones
CC = gcc
CFLAGS = -Wall -g -Werror -Wpedantic -ansi $(INC_DIRS)

# Regla principal para compilar el ejecutable
all: $(EXEC)

# Regla para compilar el ejecutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIB_DIRS) $(LIBS)

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
	valgrind --leak-check=full  ./$(EXEC) $(EXEC).dat

