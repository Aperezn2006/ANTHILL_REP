#ifndef GRAPHIC_ENGINE2_H
#define GRAPHIC_ENGINE2_H

#include <SDL2/SDL.h>

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
Graphic_engine *graphic_engine_create(void);

/**
 * @brief It destroys a graphic engine
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param ge a pointer to the graphic engine
 * @return nothing
 */
void graphic_engine_destroy(Graphic_engine *gengine);

/**
 * @brief It paints the game's data on the user's screen
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param ge a pointer to the graphic engine
 * @param game a pointer to the game
 * @return nothing
 */
void graphic_engine_render(Graphic_engine *gengine, Game *game);

#endif
