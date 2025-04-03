/**
 * @brief It defines the creation of the game with the data from a file
 *
 * @file game_reader.h
 * @author Rubén, Ana
 * @version 2
 * @date 11-03-2025
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "command.h"
#include "game.h"
#include "object.h"
#include "player.h"
#include "space.h"
#include "types.h"

/**
 * @brief It loads the spaces that are adyacent to the current one
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param filename a pointer to the file where the spaces are defined
 * @return ERROR if anything goes wrong
 */
Status game_load_everything(Game *game, char *filename);

/**
 * @brief It creates the game with the info from the filename
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param filename a pointer to the file where the spaces are defined
 * @return OK if everything goes well
 */
Status game_create_from_file(Game *game, char *filename);

#endif