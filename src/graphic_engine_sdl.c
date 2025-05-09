#include "graphic_engine_sdl.h"

#define MY_FONT "fonts/04b_25__.ttf"
#define FONT_SIZE (25 * SDL_SCREEN_ZOOM)

/* Definition of the opaque structure */
struct _Graphic_engine_sdl {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *background_texture;
  SDL_Texture *info_texture;
  SDL_Texture *chat_texture;
  SDL_Texture *player_texture;
  SDL_Texture *character_textures[MAX_CHARACTERS];
  SDL_Texture *obstacle_texture;
  SDL_Texture *link_textures[4];
  SDL_Texture *object_textures[MAX_OBJECTS];
  SDL_Texture *inventory_textures[MAX_OBJECTS];
  SDL_Texture *ray_texture;
  SDL_Texture *inventory_not_selected;
  SDL_Texture *inventory_yes_selected;
  TTF_Font *font;
  TTF_Font *player_health[MAX_PLAYERS];
  SDL_Texture *player_health_textures[MAX_PLAYERS];
  TTF_Font *player_name[MAX_CHARACTERS];
  SDL_Texture *player_name_textures[MAX_PLAYERS];
  TTF_Font *character_health[MAX_CHARACTERS];
  SDL_Texture *character_health_textures[MAX_CHARACTERS];
  TTF_Font *character_name[MAX_CHARACTERS];
  SDL_Texture *character_name_textures[MAX_CHARACTERS];
  TTF_Font *character_message;
  SDL_Texture *character_message_texture;
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
Graphic_engine_sdl *graphic_engine_create_sdl() {
  int i;

  Graphic_engine_sdl *gengine = (Graphic_engine_sdl *)malloc(sizeof(Graphic_engine_sdl));
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

  if (TTF_Init() < 0) {
    printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
    SDL_Quit();
    return NULL;
  }

  gengine->font = TTF_OpenFont(MY_FONT, FONT_SIZE); /*specify the path to your font file and font size*/
  if (!gengine->font) {
    printf("Failed to load font: %s\n", TTF_GetError());
    return NULL;
  }

  gengine->character_message = TTF_OpenFont(MY_FONT, FONT_SIZE); /*specify the path to your font file and font size*/
  if (!gengine->character_message) {
    printf("Failed to load font: %s\n", TTF_GetError());
    return NULL;
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    gengine->player_health[i] = TTF_OpenFont(MY_FONT, FONT_SIZE / 2); /*specify the path to your font file and font size*/
    if (!gengine->player_health[i]) {
      printf("Failed to load font: %s\n", TTF_GetError());
      return NULL;
    }

    gengine->player_name[i] = TTF_OpenFont(MY_FONT, FONT_SIZE / 2); /*specify the path to your font file and font size*/
    if (!gengine->player_name[i]) {
      printf("Failed to load font: %s\n", TTF_GetError());
      return NULL;
    }
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    gengine->character_health[i] = TTF_OpenFont(MY_FONT, FONT_SIZE / 2); /*specify the path to your font file and font size*/
    if (!gengine->character_health[i]) {
      printf("Failed to load font: %s\n", TTF_GetError());
      return NULL;
    }

    gengine->character_name[i] = TTF_OpenFont(MY_FONT, FONT_SIZE / 2); /*specify the path to your font file and font size*/
    if (!gengine->character_name[i]) {
      printf("Failed to load font: %s\n", TTF_GetError());
      return NULL;
    }
  }

  gengine->window =
      SDL_CreateWindow("Ant Hill Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

  gengine->info_texture = NULL;
  gengine->chat_texture = NULL;

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

  /*gengine->obstacle_texture = load_texture(gengine->renderer, "resources/platform.png");
  if (!gengine->obstacle_texture) {
    printf("Error loading obstacle texture.\n");
  }*/

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

  for (i = 0; i < MAX_PLAYERS; i++) {
    gengine->player_health_textures[i] = NULL;
    gengine->player_name_textures[i] = NULL;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    gengine->character_health_textures[i] = NULL;
    gengine->character_name_textures[i] = NULL;
  }

  return gengine;
}

/* Free resources used by the graphic engine */
void graphic_engine_destroy_sdl(Graphic_engine_sdl *gengine) {
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

  if (gengine->info_texture) {
    SDL_DestroyTexture(gengine->info_texture);
    gengine->info_texture = NULL;
  }

  if (gengine->chat_texture) {
    SDL_DestroyTexture(gengine->chat_texture);
    gengine->chat_texture = NULL;
  }

  if (gengine->player_texture) {
    SDL_DestroyTexture(gengine->player_texture);
    gengine->player_texture = NULL;
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

  for (i = 0; i < MAX_PLAYERS; i++) {
    if (gengine->player_health_textures[i]) {
      SDL_DestroyTexture(gengine->player_health_textures[i]);
      gengine->player_health_textures[i] = NULL;
    }

    if (gengine->player_name_textures[i]) {
      SDL_DestroyTexture(gengine->player_name_textures[i]);
      gengine->player_name_textures[i] = NULL;
    }
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (gengine->character_health_textures[i]) {
      SDL_DestroyTexture(gengine->character_health_textures[i]);
      gengine->character_health_textures[i] = NULL;
    }

    if (gengine->character_name_textures[i]) {
      SDL_DestroyTexture(gengine->character_name_textures[i]);
      gengine->character_name_textures[i] = NULL;
    }
  }

  /* Now, safely free the structure */
  free(gengine);

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

/* Function to render the graphic engine */
void graphic_engine_render_sdl(Graphic_engine_sdl *gengine, Game *game) {
  int i = 0;
  Id id_act = NO_ID;
  Space *current_space = NULL;
  Player *player = NULL;
  Character *character = NULL;
  Link *link = NULL;
  Object *obj = NULL;
  Ray *ray = NULL;
  int player_x, player_y;
  int character_x, character_y;
  int link_x, link_y;
  int obj_x, obj_y;
  int inv_x, inv_y;
  const char *player_path = NULL;
  const char *background_path = NULL;
  SDL_Color black_text_color = {0, 0, 0, 255};
  SDL_Color red_text_color = {255, 0, 0, 0};
  SDL_Color white_text_color = {255, 255, 255, 0};
  char aux_string[WORD_SIZE];

  if (!gengine || !game) {
    return;
  }

  /* Get player position */
  player = game_get_current_player(game);
  player_x = 0;
  player_y = 0;
  player_get_position(player, &player_x, &player_y);

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
    SDL_Rect background_rect = {0, 0, SDL_WINDOW_WIDTH, SDL_MAP_HEIGHT};
    SDL_RenderCopy(gengine->renderer, gengine->background_texture, NULL, &background_rect);
  } else {
    printf("Warning: Background texture is NULL.\n");
  }

  gengine->info_texture = load_texture(gengine->renderer, "resources/Info.png");
  SDL_Rect info_rect = {0, SDL_MAP_HEIGHT, SDL_WINDOW_WIDTH, SDL_INFO_HEIGHT};
  SDL_RenderCopy(gengine->renderer, gengine->info_texture, NULL, &info_rect);

  /*Chat*/
  /*gengine->chat_texture = load_texture(gengine->renderer, "resources/bocadillo.png");*/

  SDL_Surface *message_textSurface = TTF_RenderText_Solid(
      gengine->character_message,
      ((game_get_message(game)[0] == '\0' || strcmp(game_get_message(game), ".") == 0) ? "Talk to someone" : game_get_message(game)),
      white_text_color);
  if (!message_textSurface) {
    printf("Failed to create text surface: %s\n", TTF_GetError());
    return;
  }

  gengine->character_message_texture = SDL_CreateTextureFromSurface(gengine->renderer, message_textSurface);
  if (!gengine->character_message_texture) {
    printf("Failed to create text texture: %s\n", SDL_GetError());
    return;
  }

  /*SDL_Rect message_rect = {10 * SDL_TILE_SIZE, SDL_MAP_HEIGHT + SDL_INFO_HEIGHT / 2 - message_textSurface->h, 2 * message_textSurface->w,
                           2 * message_textSurface->h};
  SDL_RenderCopy(gengine->renderer, gengine->chat_texture, NULL, &message_rect);*/

  SDL_Rect message_textRect = {SDL_WINDOW_WIDTH / 2 - message_textSurface->w / 2, SDL_MAP_HEIGHT + SDL_INFO_HEIGHT / 2 - message_textSurface->h / 2,
                               message_textSurface->w, message_textSurface->h};
  SDL_RenderCopy(gengine->renderer, gengine->character_message_texture, NULL, &message_textRect);
  /*Chat*/

  for (i = 0; i < MAX_OBJECTS; i++) {
    obj = game_get_object_from_index(game, i);
    if (obj && (game_get_object_location(game, object_get_id(obj)) == id_act)) {
      obj_x = object_get_x(obj);
      obj_y = object_get_y(obj);
      SDL_Rect obj_rect = {obj_x * SDL_TILE_SIZE, obj_y * SDL_TILE_SIZE, SDL_OBJECT_HW, SDL_OBJECT_HW};
      printf(":::::: About to load [%s]\n", object_get_image(obj));
      gengine->object_textures[i] = load_texture(gengine->renderer, object_get_image(obj));

      if (gengine->object_textures[i]) {
        SDL_RenderCopy(gengine->renderer, gengine->object_textures[i], NULL, &obj_rect);
      } else {
        printf("Warning: Object texture is NULL.\n");
      }
    }
  }

  /*TTF*/
  /*Health*/
  sprintf(aux_string, "|");
  for (i = 0; i < player_get_health(player) - 1; i++) {
    strcat(aux_string, "|");
  }
  SDL_Surface *textSurface = TTF_RenderText_Solid(gengine->player_health[0], aux_string, red_text_color);
  if (!textSurface) {
    printf("Failed to create text surface: %s\n", TTF_GetError());
    return;
  }

  gengine->player_health_textures[0] = SDL_CreateTextureFromSurface(gengine->renderer, textSurface);
  if (!gengine->player_health_textures[0]) {
    printf("Failed to create text texture: %s\n", SDL_GetError());
    return;
  }

  SDL_Rect textRect = {player_x * SDL_TILE_SIZE + SDL_PLAYER_HW / 2 - (textSurface->w / 2), player_y * SDL_TILE_SIZE, textSurface->w, textSurface->h};
  SDL_RenderCopy(gengine->renderer, gengine->player_health_textures[0], NULL, &textRect);

  /*Name*/
  SDL_Surface *name_textSurface = TTF_RenderText_Solid(gengine->player_name[0], player_get_name(player), black_text_color);
  if (!name_textSurface) {
    printf("Failed to create text surface: %s\n", TTF_GetError());
    return;
  }

  gengine->player_name_textures[0] = SDL_CreateTextureFromSurface(gengine->renderer, name_textSurface);
  if (!gengine->player_name_textures[0]) {
    printf("Failed to create text texture: %s\n", SDL_GetError());
    return;
  }

  SDL_Rect name_textRect = {player_x * SDL_TILE_SIZE + SDL_PLAYER_HW / 2 - (name_textSurface->w / 2), player_y * SDL_TILE_SIZE + SDL_PLAYER_HW,
                            name_textSurface->w, name_textSurface->h};
  SDL_RenderCopy(gengine->renderer, gengine->player_name_textures[0], NULL, &name_textRect);
  /*TTF*/

  /* Load player image dynamically */
  player_path = player_get_image(player);
  if (player_path) {
    if (gengine->player_texture) {
      SDL_DestroyTexture(gengine->player_texture);
    }
    gengine->player_texture = load_texture(gengine->renderer, player_path);
  }

  for (i = 0; i < space_get_num_characters(game_get_space(game, player_get_location(game_get_current_player(game)))); i++) {
    character = game_get_character(game, space_get_character_from_index(game_get_space(game, player_get_location(game_get_current_player(game))), i));
    if (character && (game_get_character_location(game, character_get_id(character)) == id_act)) {
      character_x = character_get_x(character);
      character_y = character_get_y(character);
      SDL_Rect character_rect = {character_x * SDL_TILE_SIZE, character_y * SDL_TILE_SIZE, SDL_CHARACTER_HW, SDL_CHARACTER_HW};

      /*TTF*/
      sprintf(aux_string, "|");
      for (i = 0; i < character_get_health(character) - 1; i++) {
        strcat(aux_string, "|");
      }
      SDL_Surface *textSurface = TTF_RenderText_Solid(gengine->character_health[i], aux_string, red_text_color);
      if (!textSurface) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
        return;
      }

      gengine->character_health_textures[i] = SDL_CreateTextureFromSurface(gengine->renderer, textSurface);
      if (!gengine->character_health_textures[i]) {
        printf("Failed to create text texture: %s\n", SDL_GetError());
        return;
      }

      SDL_Rect textRect = {character_x * SDL_TILE_SIZE + SDL_PLAYER_HW / 2 - (textSurface->w / 2), character_y * SDL_TILE_SIZE, textSurface->w,
                           textSurface->h};
      SDL_RenderCopy(gengine->renderer, gengine->character_health_textures[i], NULL, &textRect);

      /*Name*/
      SDL_Surface *name_textSurface = TTF_RenderText_Solid(gengine->character_name[i], character_get_name(character), black_text_color);
      if (!name_textSurface) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
        return;
      }

      gengine->character_name_textures[i] = SDL_CreateTextureFromSurface(gengine->renderer, name_textSurface);
      if (!gengine->character_name_textures[i]) {
        printf("Failed to create text texture: %s\n", SDL_GetError());
        return;
      }

      SDL_Rect name_textRect = {character_x * SDL_TILE_SIZE + SDL_PLAYER_HW / 2 - (name_textSurface->w / 2),
                                character_y * SDL_TILE_SIZE + SDL_PLAYER_HW, name_textSurface->w, name_textSurface->h};
      SDL_RenderCopy(gengine->renderer, gengine->character_name_textures[i], NULL, &name_textRect);
      /*TTF*/

      int blink_timer = character_get_blink_timer(character);

      /* Parpadeo: alterna visibilidad */
      if (character_get_health(character) == 0) {
        if (blink_timer == 0 || ((blink_timer / 5) % 2 == 0)) {
          gengine->character_textures[i] = load_texture(gengine->renderer, character_get_image(character));

          if (gengine->character_textures[i]) {
            SDL_RenderCopy(gengine->renderer, gengine->character_textures[i], NULL, &character_rect);
          } else {
            printf("Warning: Character texture is NULL.\n");
          }
        }

        character_update_blink_timer(character);
      } else {
        gengine->character_textures[i] = load_texture(gengine->renderer, character_get_image(character));

        if (gengine->character_textures[i]) {
          SDL_RenderCopy(gengine->renderer, gengine->character_textures[i], NULL, &character_rect);
        } else {
          printf("Warning: Character texture is NULL.\n");
        }
      }
    }
  }

  /* Render links */
  for (i = 0; i < 6; i++) {
    link = game_get_link_at_direction(game, id_act, i);
    if (link) {
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
        SDL_Rect link_rect = {link_x * SDL_TILE_SIZE, link_y * SDL_TILE_SIZE, SDL_LINK_HW, SDL_LINK_HW};
        SDL_RenderCopy(gengine->renderer, gengine->link_textures[i], NULL, &link_rect);
      }
    }
  }

  ray = game_get_ray(game);             /*Get the current ray instance*/
  if (ray && ray_is_active(ray) == 1) { /*Render only if ray is active*/
    ray_update(ray);                    /*Update ray position dynamically*/

    if (gengine->ray_texture) {
      SDL_Rect ray_rect = {ray_get_x(ray), ray_get_y(ray), 50 * SDL_SCREEN_ZOOM, 50 * SDL_SCREEN_ZOOM}; /*Adjust size as needed*/
      SDL_RenderCopy(gengine->renderer, gengine->ray_texture, NULL, &ray_rect);
      printf("Rendering ray at (%d, %d)\n", ray_get_x(ray), ray_get_y(ray));
    } else {
      printf("Warning: Ray texture is NULL.\n");
    }
  }

  /* Render player */
  if (gengine->player_texture) {
    int blink_timer = player_get_blink_timer(player);

    /* Si está parpadeando, alterna entre mostrar y ocultar */
    if (blink_timer == 0 || ((blink_timer / 5) % 2 == 0)) {
      SDL_Rect player_rect = {player_x * SDL_TILE_SIZE, player_y * SDL_TILE_SIZE, SDL_PLAYER_HW, SDL_PLAYER_HW};
      SDL_RenderCopy(gengine->renderer, gengine->player_texture, NULL, &player_rect);
    }

    /* Actualiza el temporizador de parpadeo */
    player_update_blink_timer(player);
  } else {
    printf("Warning: Ant texture is NULL.\n");
  }

  /*Render inventory*/
  inv_x = 22, inv_y = 2;
  SDL_Texture *dynamic_inventory = NULL;
  if (game_get_inventory_vis(game) == TRUE) {
    printf("\n------------RENDERING INVENTORYYY---------------\n\n");
    for (i = 0; i < inventory_get_max_objects(player_get_inventory(player)); i++) {
      obj = game_get_object_from_id(game, inventory_get_object_by_index(player_get_inventory(player), i));
      gengine->inventory_textures[i] = load_texture(gengine->renderer, object_get_image(obj));
      SDL_Rect inv_rect = {inv_x * SDL_TILE_SIZE, inv_y * SDL_TILE_SIZE, 50 * SDL_SCREEN_ZOOM, 50 * SDL_SCREEN_ZOOM};
      SDL_Rect obj_rect = {(inv_x * SDL_TILE_SIZE) + (5 * SDL_SCREEN_ZOOM), (inv_y * SDL_TILE_SIZE) + (5 * SDL_SCREEN_ZOOM), 40 * SDL_SCREEN_ZOOM,
                           40 * SDL_SCREEN_ZOOM};

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

      inv_x += 6;
      if (inv_x >= 44) {
        inv_x = 22;
        inv_y += 6;
      }
    }
  }

  SDL_RenderPresent(gengine->renderer);
}
