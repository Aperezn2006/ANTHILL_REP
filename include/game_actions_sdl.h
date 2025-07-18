/**
 * @brief It defines the game update interface
 * @file game_actions.h
 * @author Profesores PPROG
 * @version 1
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "character.h"
#include "command.h"
#include "game.h"
#include "game_management.h"
#include "object.h"
#include "player.h"
#include "space.h"
#include "types.h"

/**
 * @brief It updates the current command based on user input
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param command a pointer to the command
 * @return OK if everything goes well, ERROR otherwise
 */
void game_actions_update_sdl(Game *game, int seed, Id *object_used);

#endif
