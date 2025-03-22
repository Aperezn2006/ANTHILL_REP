#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"
#include <SDL2/SDL.h>


typedef struct _Graphic_engine Graphic_engine;


Graphic_engine* graphic_engine_create(void);
void graphic_engine_destroy(Graphic_engine *gengine);


void graphic_engine_render(Graphic_engine *gengine, Game *game);

#endif 
