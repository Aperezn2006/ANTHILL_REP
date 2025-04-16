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
#include "game_actions.h"
#include "game_management.h"
#include "graphic_engine.h"
#include "object.h"
#include "player.h"
#include "space.h"
#include "types.h"

/**
 * @brief It creates the game with the info from the filename
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param filename a pointer to the file where the spaces are defined
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_init_from_file(Game *game, char *filename);

/**
 * @brief It saves the current game's info in a specified file
 * @author Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_management_save(Game *game, char *file_name);

/**
 * @brief It loads a player's game from a certain file
 * @author Ana
 *
 * @param game a pointer to the game
 * @param file_name the name of the desired folder
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_management_load(Game *game, char *file_name, Graphic_engine *gengine, Bool new);

#endif