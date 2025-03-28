#include "graphic_engine.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TILE_SIZE 10

/* Definition of the opaque structure */
struct _Graphic_engine {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background_texture;
    SDL_Texture *ant_texture;
};

/* Function to load a texture from a file */
static SDL_Texture* load_texture(SDL_Renderer *renderer, const char *file_path) {
    if (!file_path) {
        printf("Error: file path is NULL.\n");
        return NULL;
    }
    
    SDL_Surface *surface = IMG_Load(file_path);
    if (!surface) {
        printf("Error loading image: %s\n", IMG_GetError());
        return NULL;
    }
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    if (!texture) {
        printf("Error creating texture from surface: %s\n", SDL_GetError());
    }
    
    return texture;
}

/* Create the graphic engine */
Graphic_engine* graphic_engine_create(void) {
    Graphic_engine *gengine = (Graphic_engine *)malloc(sizeof(Graphic_engine));
    if (!gengine) {
        fprintf(stderr, "Error allocating memory for graphic engine\n");
        return NULL;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        free(gengine);
        return NULL;
    }

    if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG))) {
        printf("IMG_Init failed: %s\n", IMG_GetError());
        free(gengine);
        SDL_Quit();
        return NULL;
    }

    gengine->window = SDL_CreateWindow("Ant Hill Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!gengine->window) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        free(gengine);
        SDL_Quit();
        return NULL;
    }

    gengine->renderer = SDL_CreateRenderer(gengine->window, -1, SDL_RENDERER_ACCELERATED);
    if (!gengine->renderer) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(gengine->window);
        free(gengine);
        SDL_Quit();
        return NULL;
    }

    return gengine;
}

/* Free resources used by the graphic engine */
void graphic_engine_destroy(Graphic_engine *gengine) {
    if (gengine) {
        if (gengine->background_texture) {
            SDL_DestroyTexture(gengine->background_texture);
        }
        if (gengine->ant_texture) {
            SDL_DestroyTexture(gengine->ant_texture);
        }
        if (gengine->renderer) {
            SDL_DestroyRenderer(gengine->renderer);
        }
        if (gengine->window) {
            SDL_DestroyWindow(gengine->window);
        }
        free(gengine);
    }
    IMG_Quit();
    SDL_Quit();
}

/* Function to render the graphic engine */
void graphic_engine_render(Graphic_engine *gengine, Game *game) {
    if (!gengine || !game) {
        return;
    }

    SDL_RenderClear(gengine->renderer);

    /* Get player location and corresponding space */
    Id id_act = game_get_player_location(game);
    Space *current_space = game_get_space(game, id_act);
    if (!current_space) {
        printf("Error: Could not get current space for player.\n");
        return;
    }

    /* Load background dynamically */
    const char *background_path = space_get_image(current_space);
    if (background_path) {
        if (gengine->background_texture) {
            SDL_DestroyTexture(gengine->background_texture);
        }
        gengine->background_texture = load_texture(gengine->renderer, background_path);
    }

    /* Render background */
    if (gengine->background_texture) {
        SDL_Rect background_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_RenderCopy(gengine->renderer, gengine->background_texture, NULL, &background_rect);
    } else {
        printf("Warning: Background texture is NULL.\n");
    }

    /* Get player position */
    Player *player = game_get_player(game);
    int player_x = player_get_x(player);
    int player_y = player_get_y(player);

    /* Load ant image dynamically */
    const char *ant_path = player_get_image(player);
    if (ant_path) {
        if (gengine->ant_texture) {
            SDL_DestroyTexture(gengine->ant_texture);
        }
        gengine->ant_texture = load_texture(gengine->renderer, ant_path);
    }

    /* Render ant */
    if (gengine->ant_texture) {
        SDL_Rect ant_rect = {player_x * TILE_SIZE, player_y * TILE_SIZE, 50, 50};
        SDL_RenderCopy(gengine->renderer, gengine->ant_texture, NULL, &ant_rect);
    } else {
        printf("Warning: Ant texture is NULL.\n");
    }

    /* Present the rendered content to the screen */
    SDL_RenderPresent(gengine->renderer);
}
