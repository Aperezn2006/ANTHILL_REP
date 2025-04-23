# Nombre del ejecutable principal
EXEC = anthill

# Ejecutables de los tests
TESTS = space_test link_test player_test set_test object_test character_test inventory_test
# character_test 

# Directorios
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
TEST_DIR = .
DOC_DIR = doc

# Archivos fuente
SRC = $(SRC_DIR)/game_loop.c $(SRC_DIR)/command.c $(SRC_DIR)/game_actions.c $(SRC_DIR)/game.c \
      $(SRC_DIR)/graphic_engine.c $(SRC_DIR)/space.c $(SRC_DIR)/game_management.c $(SRC_DIR)/player.c \
      $(SRC_DIR)/game_rules.c $(SRC_DIR)/object.c $(SRC_DIR)/character.c $(SRC_DIR)/set.c $(SRC_DIR)/link.c $(SRC_DIR)/inventory.c

# Archivos fuente de los tests
TEST_SRC = $(TEST_DIR)/space_test.c $(TEST_DIR)/link_test.c $(TEST_DIR)/player_test.c $(TEST_DIR)/set_test.c \
					 $(TEST_DIR)/object_test.c $(TEST_DIR)/character_test.c $(TEST_DIR)/inventory_test.c
# $(TEST_DIR)/character_test.c

# Archivos objeto generados a partir de los archivos fuente
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Archivos objeto comunes (excluyendo game_loop.o)
COMMON_SRC = $(filter-out $(SRC_DIR)/game_loop.c, $(SRC))
COMMON_OBJ = $(COMMON_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Archivos objeto de los tests
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBS = -Llib -lscreen

# Compilador y sus opciones
CC = gcc
CFLAGS = -Wall -g -Werror -Wpedantic -ansi -I$(INCLUDE_DIR)

# Regla principal para compilar el ejecutable y los tests
all: $(EXEC) $(TESTS)

# Regla para compilar el ejecutable principal
$(EXEC): $(OBJ)
	@echo "Compilando el ejecutable principal: $(EXEC)"
	@$(CC) $(OBJ) -o $(EXEC) $(LIBS)

# Regla para compilar los ejecutables de los tests
$(TESTS): %: $(OBJ_DIR)/%.o $(COMMON_OBJ)
	@echo "Compilando el test: $@"
	@$(CC) $< $(COMMON_OBJ) -o $@ $(LIBS)

# Regla para compilar los archivos .c en .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Limpiar los archivos generados
clean:
	@echo "Limpiando archivos generados..."
	@rm -f $(OBJ) $(EXEC) $(TEST_OBJ) $(TESTS)
	@rm -rf $(OBJ_DIR)

# Regla para recompilar completamente (limpiar y compilar de nuevo)
rebuild: clean all

# Regla para generar documentación técnica
docs:
	cd $(DOC_DIR) && doxygen Doxyfile

# Regla para ejecutar el programa
run: $(EXEC)
	./$(EXEC) $(EXEC).dat

# Regla para ejecutar Valgrind
valgrind: $(EXEC)
	valgrind -s --show-leak-kinds=all --track-origins=yes --leak-check=full ./$(EXEC) $(EXEC).dat

# Regla para organizar los archivos en sus carpetitas correspondientes
organize:
	@echo "Organizing source files into the src folder..."
	@mv *.c src/

	@echo "Organizing header files into the include folder..."
	@mv *.h include/

	@echo "Organizing lib files into the lib folder..."
	@mv *.a lib/
	
	@echo "Organizing object files into the obj folder..."
	@mv *.o obj/
