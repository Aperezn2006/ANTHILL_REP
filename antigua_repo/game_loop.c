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
#include "game_reader.h"
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
void log_command(FILE *log_file, Command *cmd);

int main(int argc, char *argv[]) {
  Game *game;
  Graphic_engine *gengine;
  FILE *log_file = NULL;

  if (argc < 2) {
    fprintf(stderr, "Use: %s <game_data_file> [-l <log_file>]\n", argv[0]);
    return 1;
  }

  game = game_alloc();
  if (!game) {
    fprintf(stderr, "Error: No se pudo crear el juego\n");
    return 1;
  }

  if (argc == 4 && strcmp(argv[2], "-l") == 0) {
    log_file = fopen(argv[3], "w");
    if (!log_file) {
      fprintf(stderr, "Error: No se pudo abrir el archivo de log %s\n", argv[3]);
      game_destroy(game);
      return 1;
    }
  }

  if (!game_loop_init(game, &gengine, argv[1])) {
    game_loop_run(game, gengine, log_file);
    graphic_engine_paint_end(gengine, game);
    game_loop_cleanup(game, gengine, log_file);
  }

  return 0;
}

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name) {
  if (game_init_from_file(game, file_name) == ERROR) {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL) {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
  }

  return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file) {
  Command *last_cmd;

  if (!gengine) {
    return;
  }

  last_cmd = game_get_last_command(game);

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE)) {
    space_set_discovered(game_get_space(game, game_get_player_location(game)), TRUE);
    graphic_engine_paint_inventory(gengine, game);
    graphic_engine_paint_game(gengine, game);
    command_get_user_input(last_cmd);
    game_actions_update(game, last_cmd);

    if (log_file) {
      log_command(log_file, last_cmd);
    }

    if (command_get_code(last_cmd) != UNKNOWN && command_get_code(last_cmd) != NO_CMD) {
      if (game_get_num_players(game) > 1) {
        graphic_engine_paint_game(gengine, game);
        sleep(1);
      }

      if (game_get_turn(game) == (game_get_num_players(game) - 1)) {
        game_set_turn(game, 0);
      } else {
        game_set_turn(game, game_get_turn(game) + 1);
      }
    }

    if (player_get_health(game_get_player_from_index(game, game_get_turn(game) - 1)) == 0) {
      game_set_finished(game, TRUE);
    }
  }
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine, FILE *log_file) {
  game_destroy(game);
  graphic_engine_destroy(gengine);
  if (log_file) {
    fclose(log_file);
  }
}

void log_command(FILE *log_file, Command *cmd) {
  CommandCode code = command_get_code(cmd);
  if (!log_file || !cmd) {
    return;
  }

  fprintf(log_file, "Comando ejecutado: %s, %s, %d\n", command_to_str(code), command_get_word(cmd), command_get_result(cmd));
  fflush(log_file);
}
