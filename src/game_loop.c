/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG, Beatriz, Arturo, Rubén, Ana
 * @version 1
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "game_management.h"
#include "game_rules.h"
#include "graphic_engine.h"
#include "player.h"

/**
 * @brief Initializes the game loop by loading game data and creating the graphic engine.
 *
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 * @param gengine A double pointer to the graphic engine to be initialized.
 * @param file_name The name of the file containing game data.
 * @return 0 on success, 1 on failure.
 */
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);

/**
 * @brief Runs the main game loop, processing commands and updating the game state.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 * @param gengine A pointer to the graphic engine.
 * @param log_file A file pointer for logging commands (can be NULL).
 */
void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file);

/**
 * @brief Cleans up resources used during the game loop, including the game and graphic engine.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 * @param gengine A pointer to the graphic engine.
 * @param log_file A file pointer for logging commands (can be NULL).
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine, FILE *log_file);

/**
 * @brief Logs the details of a command to the specified log file.
 * @author Profesores PPROG
 *
 * @param log_file A file pointer to the log file.
 * @param cmd A pointer to the command to be logged.
 */
void log_command(Game *game, FILE *log_file, Command *cmd);

int main(int argc, char *argv[]) {
  Game *game;
  Graphic_engine *gengine;
  FILE *log_file = NULL;
  int deterministic_mode = 0;
  char *data_file = NULL;
  int i;

  if (argc < 2) {
    fprintf(stderr, "Uso: %s <game_data_file> [-l <log_file>] [-d]\n", argv[0]);
    return 1;
  }

  /* Analizar argumentos */
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-l") == 0 && i + 1 < argc) {
      log_file = fopen(argv[++i], "w");
      if (!log_file) {
        fprintf(stderr, "Error: No se pudo abrir el archivo de log %s\n", argv[i]);
        return 1;
      }
      fprintf(log_file, "-------- LOGFILE --------\n\n");
    } else if (strcmp(argv[i], "-d") == 0) {
      deterministic_mode = 1;
    } else if (!data_file) {
      data_file = argv[i]; /* El primer argumento sin prefijo es el archivo de datos */
    }
  }

  if (!data_file) {
    fprintf(stderr, "Error: No se proporcionó el archivo de datos del juego.\n");
    return 1;
  }
  if (deterministic_mode) {
    srand(1);
  } else {
    srand(time(NULL));
  }

  game = game_alloc();
  if (!game) {
    fprintf(stderr, "Error: No se pudo crear el juego\n");
    return 1;
  }

  if (!game_loop_init(game, &gengine, data_file)) {
    game_loop_run(game, gengine, log_file);
    graphic_engine_paint_end(gengine, game);
    game_loop_cleanup(game, gengine, log_file);
  }

  return 0;
}

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name) {
  if (game_init_from_file(game, file_name, FALSE) == ERROR) {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL) {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game, TRUE);
    return 1;
  }

  return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file) {
  Command *last_cmd;
  int i;

  if (!gengine) {
    return;
  }

  last_cmd = game_get_last_command(game);

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE)) {
    last_cmd = game_get_last_command(game);
    space_set_discovered(game_get_space(game, game_get_player_location(game)), TRUE);
    graphic_engine_paint_game(gengine, game);
    if (game_get_inventory_vis(game) == TRUE) {
      graphic_engine_paint_inventory(gengine, game);
    }
    if (game_get_zoom_vis(game) == TRUE) {
      graphic_engine_paint_zoom(gengine, game);
    }
    command_get_user_input(last_cmd);
    game_actions_update(game, last_cmd);
    update_game(game);
    last_cmd = game_get_last_command(game);

    if (log_file) {
      log_command(game, log_file, last_cmd);
    }

    if (command_get_code(last_cmd) != UNKNOWN && command_get_code(last_cmd) != NO_CMD) {
      /*Chequeo de following*/

      for (i = 0; i < game_get_num_characters(game); i++) {
        if (player_get_id(game_get_player(game, game_get_player_index_from_turn(game))) ==
            character_get_following(game_get_character_from_index(game, i))) {
          printf("[[DEBUG]] MOVED %s %li %li\n", character_get_name(game_get_character_from_index(game, i)),
                 player_get_id(game_get_player(game, game_get_player_index_from_turn(game))),
                 character_get_following(game_get_character_from_index(game, i)));
          game_set_character_location(game, game_get_player_location(game), character_get_id(game_get_character_from_index(game, i)));
        }
      }
    }

    for (i = 0; i < game_get_num_players(game); i++) {
      if (player_get_health(game_get_player_from_index(game, i)) == 0) {
        graphic_engine_paint_game(gengine, game);
        game_set_finished(game, TRUE);
      }
    }
  }
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine, FILE *log_file) {
  game_destroy(game, TRUE);
  graphic_engine_destroy(gengine);
  if (log_file) {
    fclose(log_file);
  }
}

void log_command(Game *game, FILE *log_file, Command *cmd) {
  CommandCode code = command_get_code(cmd);
  char result[WORD_SIZE];

  if (!log_file || !cmd) {
    return;
  }

  if (command_get_result(cmd) == OK) {
    strcpy(result, "OK");
  } else if (command_get_result(cmd) == ERROR) {
    strcpy(result, "ERROR");
  }

  fprintf(log_file, "Comando ejecutado: %s %s, %s (P%li)\n", command_to_str(code), command_get_word(cmd), result,
          player_get_id(game_get_current_player(game)));
  fflush(log_file);
}
