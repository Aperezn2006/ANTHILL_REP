/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG, Beatriz, Arturo, Rubén, Ana
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
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param none
 * @return a pointer to the graphic engine
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief It destroys a graphic engine
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param ge a pointer to the graphic engine
 * @return nothing
 */
void graphic_engine_destroy(Graphic_engine *ge);

void graphic_engine_toggle_fullscreen(Graphic_engine *ge);

void graphic_engine_init_game_areas(Graphic_engine *ge);

/**
 * @brief It paints the game's data on the user's screen
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param ge a pointer to the graphic engine
 * @param game a pointer to the game
 * @return nothing
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

void graphic_engine_paint_start(Graphic_engine *ge, Game *game);

/**
 * @brief It paints the end game screen
 * @author Rubén, Arturo, Bea, Ana
 *
 * @param ge a pointer to the graphic engine
 * @param game a pointer to the game
 * @return nothing
 */
void graphic_engine_paint_end(Graphic_engine *ge, Game *game);

/**
 * @brief It paints the inventory screen
 * @author Ana
 *
 * @param ge a pointer to the graphic engine
 * @param game a pointer to the game
 * @return nothing
 */
void graphic_engine_paint_inventory(Graphic_engine *ge, Game *game);
/**
 * @brief It paints the space screen
 * @author Ana
 *
 * @param ge a pointer to the graphic engine
 * @param game a pointer to the game
 * @return nothing
 */
void graphic_engine_paint_zoom(Graphic_engine *ge, Game *game);

#endif
