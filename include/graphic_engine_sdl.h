#ifndef GRAPHIC_ENGINE2_H
#define GRAPHIC_ENGINE2_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game.h"
#include "input.h"
#include "obstacle.h"
#include "ray.h"

/**
 * @brief Graphic engine
 *
 * This struct stores all the information of a graphic engine.
 */
typedef struct _Graphic_engine_sdl Graphic_engine_sdl;

/**
 * @brief It creates a new graphic engine
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param none
 * @return a pointer to the graphic engine
 */
Graphic_engine_sdl *graphic_engine_create_sdl();

/**
 * @brief It destroys a graphic engine
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param ge a pointer to the graphic engine
 * @return nothing
 */
void graphic_engine_destroy_sdl(Graphic_engine_sdl *gengine);

/**
 * @brief It paints the game's data on the user's screen
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param ge a pointer to the graphic engine
 * @param game a pointer to the game
 * @return nothing
 */
void graphic_engine_render_sdl(Graphic_engine_sdl *gengine, Game *game);

#endif
