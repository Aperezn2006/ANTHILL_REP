# Nombre del ejecutable principal
EXEC = anthill
SDL_EXEC = anthill_sdl

# Ejecutables de los tests
TESTS = space_test link_test player_test set_test object_test character_test inventory_test

# Directorios
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
TEST_DIR = .
DOC_DIR = doc

# Archivos fuente
SRC = $(SRC_DIR)/game_loop.c \
      $(SRC_DIR)/command.c \
      $(SRC_DIR)/game_actions.c \
      $(SRC_DIR)/game.c \
      $(SRC_DIR)/graphic_engine.c \
      $(SRC_DIR)/space.c \
      $(SRC_DIR)/game_management.c \
      $(SRC_DIR)/player.c \
      $(SRC_DIR)/game_rules.c \
      $(SRC_DIR)/object.c \
      $(SRC_DIR)/character.c \
      $(SRC_DIR)/set.c \
      $(SRC_DIR)/link.c \
      $(SRC_DIR)/inventory.c \
			$(SRC_DIR)/gun.c \
			$(SRC_DIR)/obstacle.c \
			$(SRC_DIR)/physics.c \
			$(SRC_DIR)/ray.c \

SDL_SRC = $(SRC_DIR)/game_loop_sdl.c \
					$(SRC_DIR)/command.c \
					$(SRC_DIR)/game_actions_sdl.c \
					$(SRC_DIR)/game.c \
					$(SRC_DIR)/graphic_engine_sdl.c \
					$(SRC_DIR)/space.c \
					$(SRC_DIR)/game_management.c \
					$(SRC_DIR)/player.c \
					$(SRC_DIR)/game_rules.c \
					$(SRC_DIR)/object.c \
					$(SRC_DIR)/character.c \
					$(SRC_DIR)/set.c \
					$(SRC_DIR)/link.c \
					$(SRC_DIR)/inventory.c \
					$(SRC_DIR)/gun.c \
					$(SRC_DIR)/obstacle.c \
					$(SRC_DIR)/physics.c \
					$(SRC_DIR)/ray.c \
					$(SRC_DIR)/input.c \


# Archivos fuente de los tests
TEST_SRC = $(TEST_DIR)/space_test.c \
           $(TEST_DIR)/link_test.c \
           $(TEST_DIR)/player_test.c \
           $(TEST_DIR)/set_test.c \
           $(TEST_DIR)/object_test.c \
           $(TEST_DIR)/character_test.c \
           $(TEST_DIR)/inventory_test.c

# Archivos objeto generados a partir de los archivos fuente
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SDL_OBJ = = $(SDL_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Archivos objeto de los tests
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

# Librerias
LIBS = -Llib -lscreen
SDL_LIBS = -Llib -lscreen -lSDL2 -lSDL2_image

# Compilador y sus opciones
CC = gcc
CFLAGS = -Wall -g -Werror -Wpedantic -ansi -I$(INCLUDE_DIR)

# Reglas
all: $(EXEC) $(TESTS)
sdl: $(SDL_EXEC) $(TESTS)

# Regla para compilar el ejecutable principal
$(EXEC): $(OBJ_DIR)/game_loop.o $(OBJ_DIR)/command.o $(OBJ_DIR)/game_actions.o $(OBJ_DIR)/game.o $(OBJ_DIR)/graphic_engine.o $(OBJ_DIR)/space.o $(OBJ_DIR)/game_management.o $(OBJ_DIR)/player.o $(OBJ_DIR)/game_rules.o $(OBJ_DIR)/object.o $(OBJ_DIR)/character.o $(OBJ_DIR)/set.o $(OBJ_DIR)/link.o $(OBJ_DIR)/inventory.o $(SRC_DIR)/gun.c $(SRC_DIR)/obstacle.c $(SRC_DIR)/physics.c $(SRC_DIR)/ray.c 
	@echo "Compilando: $(EXEC)"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(SDL_EXEC): $(OBJ_DIR)/game_loop_sdl.o $(OBJ_DIR)/command.o $(OBJ_DIR)/game_actions_sdl.o $(OBJ_DIR)/game.o $(OBJ_DIR)/graphic_engine_sdl.o $(OBJ_DIR)/space.o $(OBJ_DIR)/game_management.o $(OBJ_DIR)/player.o $(OBJ_DIR)/game_rules.o $(OBJ_DIR)/object.o $(OBJ_DIR)/character.o $(OBJ_DIR)/set.o $(OBJ_DIR)/link.o $(OBJ_DIR)/inventory.o $(SRC_DIR)/gun.c $(SRC_DIR)/obstacle.c $(SRC_DIR)/physics.c $(SRC_DIR)/ray.c $(SRC_DIR)/input.c
	@echo "Compilando: $(SDL_EXEC)"
	@$(CC) $(CFLAGS) -o $@ $^ $(SDL_LIBS)

# Reglas para compilar cada archivo fuente con dependencias específicas
$(OBJ_DIR)/game_loop.o: $(SRC_DIR)/game_loop.c $(INCLUDE_DIR)/game.h $(INCLUDE_DIR)/command.h
	@echo "Compilando: $<"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_loop_sdl.o: $(SRC_DIR)/game_loop_sdl.c $(INCLUDE_DIR)/game.h $(INCLUDE_DIR)/command.h
	@echo "Compilando: $<"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/command.o: $(SRC_DIR)/command.c $(INCLUDE_DIR)/command.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_actions.o: $(SRC_DIR)/game_actions.c $(INCLUDE_DIR)/game.h $(INCLUDE_DIR)/command.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_actions_sdl.o: $(SRC_DIR)/game_actions_sdl.c $(INCLUDE_DIR)/game.h $(INCLUDE_DIR)/command.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game.o: $(SRC_DIR)/game.c $(INCLUDE_DIR)/game.h $(INCLUDE_DIR)/space.h $(INCLUDE_DIR)/player.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/graphic_engine.o: $(SRC_DIR)/graphic_engine.c $(INCLUDE_DIR)/graphic_engine.h $(INCLUDE_DIR)/game.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/graphic_engine_sdl.o: $(SRC_DIR)/graphic_engine_sdl.c $(INCLUDE_DIR)/graphic_engine_sdl.h $(INCLUDE_DIR)/game.h
	@echo "Compilando: $<"
	@$(CC) $(filter-out -Wpedantic -ansi, $(CFLAGS)) -c $< -o $@

$(OBJ_DIR)/space.o: $(SRC_DIR)/space.c $(INCLUDE_DIR)/space.h $(INCLUDE_DIR)/set.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_management.o: $(SRC_DIR)/game_management.c $(INCLUDE_DIR)/game.h $(INCLUDE_DIR)/game_management.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/player.o: $(SRC_DIR)/player.c $(INCLUDE_DIR)/player.h $(INCLUDE_DIR)/inventory.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_rules.o: $(SRC_DIR)/game_rules.c $(INCLUDE_DIR)/game_rules.h $(INCLUDE_DIR)/game.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/object.o: $(SRC_DIR)/object.c $(INCLUDE_DIR)/object.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/character.o: $(SRC_DIR)/character.c $(INCLUDE_DIR)/character.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/set.o: $(SRC_DIR)/set.c $(INCLUDE_DIR)/set.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/link.o: $(SRC_DIR)/link.c $(INCLUDE_DIR)/link.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/inventory.o: $(SRC_DIR)/inventory.c $(INCLUDE_DIR)/inventory.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/gun.o: $(SRC_DIR)/gun.c $(INCLUDE_DIR)/gun.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/input.o: $(SRC_DIR)/input.c $(INCLUDE_DIR)/input.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/obstacle.o: $(SRC_DIR)/obstacle.c $(INCLUDE_DIR)/obstacle.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/physics.o: $(SRC_DIR)/physics.c $(INCLUDE_DIR)/physics.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/ray.o: $(SRC_DIR)/ray.c $(INCLUDE_DIR)/ray.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Reglas para compilar cada test con dependencias específicas
space_test: $(OBJ_DIR)/space_test.o $(OBJ_DIR)/space.o $(OBJ_DIR)/set.o
	@echo "Compilando: space_test"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

link_test: $(OBJ_DIR)/link_test.o $(OBJ_DIR)/link.o
	@echo "Compilando: link_test"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

player_test: $(OBJ_DIR)/player_test.o $(OBJ_DIR)/player.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/set.o
	@echo "Compilando: player_test"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

set_test: $(OBJ_DIR)/set_test.o $(OBJ_DIR)/set.o
	@echo "Compilando: set_test"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

object_test: $(OBJ_DIR)/object_test.o $(OBJ_DIR)/object.o
	@echo "Compilando: object_test"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

character_test: $(OBJ_DIR)/character_test.o $(OBJ_DIR)/character.o
	@echo "Compilando: character_test"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

inventory_test: $(OBJ_DIR)/inventory_test.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/set.o
	@echo "Compilando: inventory_test"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Reglas para compilar los objetos de los tests
$(OBJ_DIR)/space_test.o: $(SRC_DIR)/space_test.c $(INCLUDE_DIR)/space.h $(INCLUDE_DIR)/set.h
	@echo "Compilando: $<"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/link_test.o: $(SRC_DIR)/link_test.c $(INCLUDE_DIR)/link.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/player_test.o: $(SRC_DIR)/player_test.c $(INCLUDE_DIR)/player.h $(INCLUDE_DIR)/inventory.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/set_test.o: $(SRC_DIR)/set_test.c $(INCLUDE_DIR)/set.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/object_test.o: $(SRC_DIR)/object_test.c $(INCLUDE_DIR)/object.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/character_test.o: $(SRC_DIR)/character_test.c $(INCLUDE_DIR)/character.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/inventory_test.o: $(SRC_DIR)/inventory_test.c $(INCLUDE_DIR)/inventory.h
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Limpiar los archivos generados
clean:
	@echo "Limpiando archivos generados..."
	@rm -f $(OBJ) $(SDL_OBJ) $(EXEC) $(TEST_OBJ) $(TESTS)

# Regla para recompilar completamente (limpiar y compilar de nuevo)
rebuild: clean all
	@echo "Recompilando todo..."

# Regla para generar documentación técnica
docs:
	cd $(DOC_DIR) && doxygen Doxyfile

# Regla para ejecutar el programa
run: $(EXEC)
	./$(EXEC) $(EXEC).dat

run_sdl: $(SDL_EXEC)
	export LD_LIBRARY_PATH=/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH
	./$(SDL_EXEC) $(SDL_EXEC)_sdl.dat

# Regla para ejecutar Valgrind
valgrind: $(EXEC)
	valgrind -s --show-leak-kinds=all --track-origins=yes --leak-check=full ./$(EXEC) $(EXEC).dat

valgrind_sdl: $(SDL_EXECEXEC)
	valgrind -s --show-leak-kinds=all --track-origins=yes --leak-check=full ./$(SDL_EXEC) $(SDL_EXEC)_sdl.dat

# Regla para organizar los archivos en sus carpetitas correspondientes
organize:
	@echo "Organizing source files into the src folder..."
	@if ls *.c >/dev/null 2>&1; then mv *.c src/; fi

	@echo "Organizing header files into the include folder..."
	@if ls *.h >/dev/null 2>&1; then mv *.h include/; fi

	@echo "Organizing lib files into the lib folder..."
	@if ls *.a >/dev/null 2>&1; then mv *.a lib/; fi
    
	@echo "Organizing object files into the obj folder..."
	@if ls *.o >/dev/null 2>&1; then mv *.o obj/; fi

# Regla para ejecutar el script con todos los tests sin Valgrind
run-tests:
	@echo "Ejecutando todos los tests..."
	@./script.sh 0

# Regla para ejecutar el script con todos los tests con Valgrind
run-tests-v:
	@echo "Ejecutando todos los tests con Valgrind..."
	@./script.sh 1

# Regla para ejecutar un test específico sin Valgrind
run-test:
	@echo "Ejecutando un test específico sin Valgrind..."
	@read -p "Introduce el nombre del test (sin extensión): " test_name; \
	./script.sh 0 $$test_name

# Regla para ejecutar un test específico con Valgrind
run-test-v:
	@echo "Ejecutando un test específico con Valgrind..."
	@read -p "Introduce el nombre del test (sin extensión): " test_name; \
	./script.sh 1 $$test_name
