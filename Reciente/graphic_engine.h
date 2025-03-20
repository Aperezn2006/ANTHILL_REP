/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG, Rubén
 * @version 1
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

/**
 * @brief Graphic engine
 *
 * This struct stores all the information of a graphic engine.
 */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief It creates a new graphic engine
 * @author Profesores PPROG
 *
 * @param none
 * @return a pointer to the graphic engine
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief It destroys a graphic engine
 * @author Profesores PPROG
 *
 * @param ge a pointer to the graphic engine
 * @return nothing
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief It paints the game's data on the user's screen
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param ge a pointer to the graphic engine
 * @return nothing
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif
