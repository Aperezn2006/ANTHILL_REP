# Nombre del ejecutable principal
EXEC = anthill

# Ejecutables de los tests
TESTS =  
#space_test character_test link_test player_test set_test 

# Archivos fuente
SRC = game_loop.c command.c game_actions.c game.c graphic_engine.c space.c game_reader.c player.c object.c character.c set.c link.c inventory.c 

# Archivos fuente de los tests
TEST_SRC = 
#space_test.c character_test.c link_test.c player_test.c set_test.c 

# Archivos fuente comunes (excluyendo game_loop.c)
COMMON_SRC = command.c game_actions.c game.c graphic_engine.c space.c game_reader.c player.c object.c character.c set.c link.c inventory.c

# Archivos objeto generados a partir de los archivos fuente
OBJ = $(SRC:.c=.o)

# Archivos objeto comunes (excluyendo game_loop.o)
COMMON_OBJ = $(COMMON_SRC:.c=.o)

# Archivos objeto de los tests
TEST_OBJ = $(TEST_SRC:.c=.o)

LIBS = -L. -lscreen

# Compilador y sus opciones
CC = gcc
CFLAGS = -Wall -g -Werror -Wpedantic -ansi

# Regla principal para compilar el ejecutable y los tests
all: $(EXEC) $(TESTS)

# Regla para compilar el ejecutable principal
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

# Regla para compilar los ejecutables de los tests
$(TESTS): %: %.o $(COMMON_OBJ)
	$(CC) $< $(COMMON_OBJ) -o $@ $(LIBS)

# Regla para compilar los archivos .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar los archivos generados
clean:
	rm -f $(OBJ) $(EXEC) $(TEST_OBJ) $(TESTS)

# Regla para recompilar completamente (limpiar y compilar de nuevo)
rebuild: clean all

# Regla para ejecutar el programa
run: $(EXEC)
	./$(EXEC) $(EXEC).dat

# Regla para ejecutar Valgrind
valgrind: $(EXEC)
	valgrind -s --show-leak-kinds=all --track-origins=yes --leak-check=full ./$(EXEC) $(EXEC).dat
