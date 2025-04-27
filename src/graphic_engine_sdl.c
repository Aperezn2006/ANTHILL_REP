#include "graphic_engine_sdl.h"

#include <SDL2/SDL_image.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "input.h"
#include "obstacle.h"
#include "ray.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TILE_SIZE 10

/* Definition of the opaque structure */
struct _Graphic_engine {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *background_texture;
  SDL_Texture *ant_texture;
  SDL_Texture *character_textures[MAX_CHARACTERS];
  SDL_Texture *obstacle_texture;
  SDL_Texture *link_textures[4];
  SDL_Texture *object_textures[MAX_OBJECTS];
  SDL_Texture *inventory_textures[MAX_OBJECTS];
  SDL_Texture *ray_texture;
  SDL_Texture *inventory_not_selected;
  SDL_Texture *inventory_yes_selected;
};

/* Function to load a texture from a file */
SDL_Texture *load_texture(SDL_Renderer *renderer, const char *file_path) {
  SDL_Surface *surface = NULL;
  SDL_Texture *texture = NULL;
  if (!file_path) {
    printf("Error: file path is NULL.\n");
    return NULL;
  }

  surface = IMG_Load(file_path);
  if (!surface) {
    printf("Error loading image: %s\n", IMG_GetError());
    return NULL;
  }

  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (!texture) {
    printf("Error creating texture from surface: %s\n", SDL_GetError());
  }

  return texture;
}

/* Create the graphic engine */
Graphic_engine *graphic_engine_create(void) {
  int i;
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

  gengine->window =
      SDL_CreateWindow("Ant Hill Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

  for (i = 0; i < 4; i++) {
    gengine->link_textures[i] = NULL;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    gengine->character_textures[i] = NULL;
  }

  gengine->ray_texture = load_texture(gengine->renderer, "resources/ray.jpeg");
  if (!gengine->ray_texture) {
    printf("Error loading ray texture.\n");
  }

  gengine->obstacle_texture = load_texture(gengine->renderer, "resources/platform.png");
  if (!gengine->obstacle_texture) {
    printf("Error loading obstacle texture.\n");
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    gengine->object_textures[i] = NULL;
    gengine->inventory_textures[i] = NULL;
  }

  gengine->inventory_not_selected = load_texture(gengine->renderer, "resources/inventario_no.png");
  if (!gengine->inventory_not_selected) {
    printf("Error loading inventory texture 1.\n");
  }

  gengine->inventory_yes_selected = load_texture(gengine->renderer, "resources/inventario_si.png");
  if (!gengine->inventory_yes_selected) {
    printf("Error loading inventory texture 2.\n");
  }

  return gengine;
}

/* Free resources used by the graphic engine */
void graphic_engine_destroy(Graphic_engine *gengine) {
  int i;
  if (!gengine) {
    return;
  }

  /* Free link textures */
  for (i = 0; i < 4; i++) {
    if (gengine->link_textures[i]) {
      SDL_DestroyTexture(gengine->link_textures[i]);
      gengine->link_textures[i] = NULL;
    }
  }

  /* Free other textures */
  if (gengine->background_texture) {
    SDL_DestroyTexture(gengine->background_texture);
    gengine->background_texture = NULL;
  }

  if (gengine->ant_texture) {
    SDL_DestroyTexture(gengine->ant_texture);
    gengine->ant_texture = NULL;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (gengine->character_textures[i]) {
      SDL_DestroyTexture(gengine->character_textures[i]);
      gengine->character_textures[i] = NULL;
    }
  }

  if (gengine->ray_texture) {
    SDL_DestroyTexture(gengine->ray_texture);
    gengine->ray_texture = NULL;
  }

  if (gengine->obstacle_texture) {
    SDL_DestroyTexture(gengine->obstacle_texture);
    gengine->obstacle_texture = NULL;
  }

  /* Free SDL renderer and window */
  if (gengine->renderer) {
    SDL_DestroyRenderer(gengine->renderer);
    gengine->renderer = NULL;
  }

  if (gengine->window) {
    SDL_DestroyWindow(gengine->window);
    gengine->window = NULL;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    if (gengine->object_textures[i]) {
      SDL_DestroyTexture(gengine->object_textures[i]);
      gengine->object_textures[i] = NULL;
    }

    if (gengine->inventory_textures[i]) {
      SDL_DestroyTexture(gengine->inventory_textures[i]);
      gengine->inventory_textures[i] = NULL;
    }
  }

  if (gengine->inventory_not_selected) {
    SDL_DestroyTexture(gengine->inventory_not_selected);
    gengine->inventory_not_selected = NULL;
  }

  if (gengine->inventory_yes_selected) {
    SDL_DestroyTexture(gengine->inventory_yes_selected);
    gengine->inventory_yes_selected = NULL;
  }

  /* Now, safely free the structure */
  free(gengine);

  IMG_Quit();
  SDL_Quit();
}

/* Function to render the graphic engine */
void graphic_engine_render(Graphic_engine *gengine, Game *game) {
  Id id_act = NO_ID;
  Space *current_space = NULL;
  Player *player = NULL;
  int player_x, player_y;
  const char *ant_path = NULL;
  const char *background_path = NULL;
  Character *character = NULL;
  int character_x, character_y;
  int i = 0;
  Link *link = NULL;
  int link_x, link_y;
  Object *obj = NULL;
  int obj_x, obj_y;
  int inv_x, inv_y;
  Ray *ray = NULL;

  if (!gengine || !game) {
    return;
  }

  SDL_RenderClear(gengine->renderer);

  /* Get player location and corresponding space */
  id_act = game_get_player_location(game);
  if (id_act == NO_ID) {
    printf("\nSomething went wrong when changing player's location\n\n");
  }

  current_space = game_get_space(game, id_act);
  if (!current_space) {
    printf("Error: Could not get current space for player.\n");
    return;
  }

  /* Load background dynamically */
  background_path = space_get_image(current_space);
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
  player = game_get_current_player(game);
  player_x = 0;
  player_y = 0;
  player_get_position(player, &player_x, &player_y);

  /* Load ant image dynamically */
  ant_path = player_get_image(player);
  if (ant_path) {
    if (gengine->ant_texture) {
      SDL_DestroyTexture(gengine->ant_texture);
    }
    gengine->ant_texture = load_texture(gengine->renderer, ant_path);
  }

  for (i = 0; i < space_get_num_characters(game_get_space(game, player_get_location(game_get_current_player(game)))); i++) {
    character = game_get_character_from_index(game, i);
    if (character && (game_get_character_location(game, character_get_id(character)) == id_act)) {
      character_x = character_get_x(character);
      character_y = character_get_y(character);
      SDL_Rect character_rect = {character_x * TILE_SIZE, character_y * TILE_SIZE, 40, 40};
      gengine->character_textures[i] = load_texture(gengine->renderer, character_get_image(character));

      if (gengine->character_textures[i]) {
        SDL_RenderCopy(gengine->renderer, gengine->character_textures[i], NULL, &character_rect);
      } else {
        printf("Warning: Object texture is NULL.\n");
      }
    }
  }

  /* Render links */
  for (i = 0; i < 6; i++) {
    link = game_get_link_at_direction(game, id_act, i);
    if (link && game_connection_is_open(game, id_act, i)) {
      const char *link_path = link_get_image(link);
      if (link_path) {
        if (gengine->link_textures[i]) {
          SDL_DestroyTexture(gengine->link_textures[i]);
        }
        gengine->link_textures[i] = load_texture(gengine->renderer, link_path);
      }

      /* Get fixed link position */
      link_x = link_get_x(link);
      link_y = link_get_y(link);
      if (gengine->link_textures[i]) {
        SDL_Rect link_rect = {link_x * TILE_SIZE, link_y * TILE_SIZE, 60, 60};
        SDL_RenderCopy(gengine->renderer, gengine->link_textures[i], NULL, &link_rect);
      }
    }
  }

  ray = game_get_ray(game);             /*Get the current ray instance*/
  if (ray && ray_is_active(ray) == 1) { /*Render only if ray is active*/
    ray_update(ray);                    /*Update ray position dynamically*/

    if (gengine->ray_texture) {
      SDL_Rect ray_rect = {ray_get_x(ray), ray_get_y(ray), 50, 50}; /*Adjust size as needed*/
      SDL_RenderCopy(gengine->renderer, gengine->ray_texture, NULL, &ray_rect);
      printf("Rendering ray at (%d, %d)\n", ray_get_x(ray), ray_get_y(ray));
    } else {
      printf("Warning: Ray texture is NULL.\n");
    }
  }

  /* Render ant */
  if (gengine->ant_texture) {
    SDL_Rect ant_rect = {player_x * TILE_SIZE, player_y * TILE_SIZE, 50, 50};
    SDL_RenderCopy(gengine->renderer, gengine->ant_texture, NULL, &ant_rect);
  } else {
    printf("Warning: Ant texture is NULL.\n");
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    obj = game_get_object_from_index(game, i);
    if (obj && (game_get_object_location(game, object_get_id(obj)) == id_act)) {
      obj_x = object_get_x(obj);
      obj_y = object_get_y(obj);
      SDL_Rect obj_rect = {obj_x * TILE_SIZE, obj_y * TILE_SIZE, 40, 40};
      printf(":::::: About to load [%s]\n", object_get_image(obj));
      gengine->object_textures[i] = load_texture(gengine->renderer, object_get_image(obj));

      if (gengine->object_textures[i]) {
        SDL_RenderCopy(gengine->renderer, gengine->object_textures[i], NULL, &obj_rect);
      } else {
        printf("Warning: Object texture is NULL.\n");
      }
    }
  }

  /*Render inventory*/
  inv_x = 220, inv_y = 20;
  SDL_Texture *dynamic_inventory = NULL;
  if (game_get_inventory_vis(game) == TRUE) {
    printf("\n------------RENDERING INVENTORYYY---------------\n\n");
    for (i = 0; i < inventory_get_max_objects(player_get_inventory(player)); i++) {
      obj = game_get_object_from_id(game, inventory_get_object_by_index(player_get_inventory(player), i));
      gengine->inventory_textures[i] = load_texture(gengine->renderer, object_get_image(obj));
      SDL_Rect inv_rect = {inv_x, inv_y, 50, 50};
      SDL_Rect obj_rect = {inv_x + 5, inv_y + 5, 40, 40};

      if (inventory_get_cursor(player_get_inventory(player)) == i) {
        dynamic_inventory = gengine->inventory_yes_selected;
      } else {
        dynamic_inventory = gengine->inventory_not_selected;
      }

      if (dynamic_inventory) {
        SDL_RenderCopy(gengine->renderer, dynamic_inventory, NULL, &inv_rect);

        if (gengine->inventory_textures[i]) {
          SDL_RenderCopy(gengine->renderer, gengine->inventory_textures[i], NULL, &obj_rect);
        }
      }

      inv_x += 60;
      if (inv_x >= 440) {
        inv_x = 220;
        inv_y += 60;
      }
    }
  }

  SDL_RenderPresent(gengine->renderer);
}
