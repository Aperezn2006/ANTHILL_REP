#include "graphic_engine.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

/* Definition of the opaque structure */
struct _Graphic_engine {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background_texture;
    SDL_Texture *ant_texture;
};

/* Function to load a texture from a file in the resources folder */
static SDL_Texture* load_texture(SDL_Renderer *renderer, const char *file_path) {
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = IMG_Load(file_path);
    if (surface == NULL) {
        printf("Error loading image: %s\n", IMG_GetError());
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

/* Create the graphic engine */
Graphic_engine* graphic_engine_create(void) {
    Graphic_engine *gengine;
    
    gengine = (Graphic_engine *)malloc(sizeof(Graphic_engine));
    if (gengine == NULL) {
        fprintf(stderr, "Error allocating memory for graphic engine\n");
        return NULL;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        free(gengine);
        return NULL;
    }

    gengine->window = SDL_CreateWindow("Ant Hill Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (gengine->window == NULL) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        free(gengine);
        SDL_Quit();
        return NULL;
    }

    gengine->renderer = SDL_CreateRenderer(gengine->window, -1, SDL_RENDERER_ACCELERATED);
    if (gengine->renderer == NULL) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(gengine->window);
        free(gengine);
        SDL_Quit();
        return NULL;
    }

    /* Load textures from the resources folder */
    gengine->background_texture = load_texture(gengine->renderer, "resources/background.jpg");
    gengine->ant_texture = load_texture(gengine->renderer, "resources/ant.jpg");

    if (gengine->background_texture == NULL || gengine->ant_texture == NULL) {
        SDL_DestroyRenderer(gengine->renderer);
        SDL_DestroyWindow(gengine->window);
        free(gengine);
        SDL_Quit();
        return NULL;
    }

    return gengine;
}

/* Free resources used by the graphic engine */
void graphic_engine_destroy(Graphic_engine *gengine) {
    if (gengine != NULL) {
        if (gengine->ant_texture != NULL) {
            SDL_DestroyTexture(gengine->ant_texture);
        }
        if (gengine->background_texture != NULL) {
            SDL_DestroyTexture(gengine->background_texture);
        }
        if (gengine->renderer != NULL) {
            SDL_DestroyRenderer(gengine->renderer);
        }
        if (gengine->window != NULL) {
            SDL_DestroyWindow(gengine->window);
        }
        free(gengine);
    }
    SDL_Quit();
}

/* Function to render the graphic engine */
void graphic_engine_render(Graphic_engine *gengine, Game *game) {
    SDL_Rect background_rect;
    SDL_Rect ant_rect;

    if (gengine == NULL || game == NULL) {
        return;
    }

    SDL_RenderClear(gengine->renderer);

    /* Render background */
    background_rect.x = 0;
    background_rect.y = 0;
    background_rect.w = WINDOW_WIDTH;
    background_rect.h = WINDOW_HEIGHT;
    SDL_RenderCopy(gengine->renderer, gengine->background_texture, NULL, &background_rect);

    /* Render ant (static location, you can change it based on the game state) */
    ant_rect.x = 350;
    ant_rect.y = 250;
    ant_rect.w = 50;
    ant_rect.h = 50; /* Adjust position and size as needed */
    SDL_RenderCopy(gengine->renderer, gengine->ant_texture, NULL, &ant_rect);

    /* Present the rendered content to the screen */
    SDL_RenderPresent(gengine->renderer);
}
