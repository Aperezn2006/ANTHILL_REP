/**
 * @brief It implements the creation of the game with the data from a file
 *
 * @file game_management.h
 * @author
 * @version 0
 * @date 10-04-2025
 * @copyright GNU Public License
 */

#ifndef GAME_MANAGEMENT_H
#define GAME_MANAGEMENT_H

#include "command.h"
#include "game.h"
#include "object.h"
#include "player.h"
#include "space.h"
#include "types.h"

/**
 * @brief It loads the spaces that are adjacent to the current one
 * @author Profesores PPROG, Arturo
 *
 * @param game a pointer to the game
 * @param filename a pointer to the file where the spaces are defined
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_load_everything(Game *game, char *filename);

/**
 * @brief It creates the game with the info from the filename
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param filename a pointer to the file where the spaces are defined
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_init_from_file(Game *game, char *filename);

#endif