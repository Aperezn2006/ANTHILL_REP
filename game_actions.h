/**
 * @brief It defines the game update interface
 *
 * @file game_actions.h
 * @author Profesores PPROG, Rubén, Ana
 * @version 2
 * @date 16-03-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "character.h"
#include "command.h"
#include "game.h"
#include "object.h"
#include "player.h"
#include "space.h"
#include "types.h"

/**
 * @brief It updates the current command based on user input
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param cmd a pointer to the command
 * @return OK if everything goes well
 */
Status game_actions_update(Game *game, Command *cmd);

#endif