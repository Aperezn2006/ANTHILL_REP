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
#include <unistd.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "game_reader.h"
#include "graphic_engine.h"
#include "player.h"

/**
 * @brief It initializes the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param gengine a pointer to the grpahic engine
 * @param file_name a pointer to the name of the file where the game's data is
 * stored
 * @return 1 if everything goes well, 0 otherwise
 */
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);

/**
 * @brief It runs the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param gengine a pointer to the grpahic engine
 * @return nothing
 */
void game_loop_run(Game *game, Graphic_engine *gengine);

/**
 * @brief It finalizes the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param gengine a pointer to the grpahic engine
 * @return nothing
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

int main(int argc, char *argv[]) {
  Game *game;
  Graphic_engine *gengine;

  game = game_init();
  if (!game) {
    fprintf(stderr, "Error: No se pudo crear el juego\n");
    return 1;
  }

  if (argc < 2) {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    game_destroy(game);
    return 1;
  }

  if (!game_loop_init(game, &gengine, argv[1])) {
    game_loop_run(game, gengine);
    graphic_engine_paint_end(gengine, game);
    game_loop_cleanup(game, gengine);
  }

  return 0;
}

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name) {
  if (game_create_from_file(game, file_name) == ERROR) {
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

void game_loop_run(Game *game, Graphic_engine *gengine) {
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

    /*Manejo de los turnos*/
    if (command_get_code(last_cmd) != UNKNOWN && command_get_code(last_cmd) != NO_CMD) {
      if (game_get_turn(game) == (game_get_num_players(game) - 1)) {
        game_set_turn(game, 0);
      } else {
        game_set_turn(game, game_get_turn(game) + 1);
      }
    }

    /*El juego acaba cuando uno de los jugadores muera*/
    if (player_get_health(game_get_n_player(game, game_get_turn(game) - 1)) == 0) {
      game_set_finished(game, TRUE);
    }
  }
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine) {
  game_destroy(game);
  graphic_engine_destroy(gengine);
}
