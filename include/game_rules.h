#ifndef UPDATE_GAME_H
#define UPDATE_GAME_H

#include "game.h"

/**
 * @brief It updates the game according to its rules
 * @author Bea, Rubén
 *
 * @param game a pointer to the game
 * @param cmd a pointer to the last command
 * @return OK if everything went well, ERROR otherwise
 */
Status update_game(Game *game, Command *cmd);

/**
 * @brief It updates the game according to its rules
 * @author Bea, Rubén
 *
 * @param game a pointer to the game
 * @param cmd a pointer to the last command
 * @return OK if everything went well, ERROR otherwise
 */
Status update_game_sdl(Game *game, Id *object_used);

#endif /* UPDATE_GAME_H */
