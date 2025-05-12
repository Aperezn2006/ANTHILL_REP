#include "physics.h"

#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "gun.h"
#include "link.h"
#include "player.h"
#include "ray.h"
#define MAX_RAYS 10

static Ray *rays[MAX_RAYS];
static int ray_count = 0;

#define COLLISION_MARGIN 2

Bool physics_check_object_collision(Game *game, Player *player, Object *obj) {
  int player_x, player_y;
  int obj_x, obj_y;
  Id player_space, obj_space;

  if (!game || !player || !obj) return FALSE;

  player_space = game_get_player_location(game);
  obj_space = game_get_object_location(game, object_get_id(obj));

  if (player_space == NO_ID || obj_space == NO_ID || player_space != obj_space) {
    return FALSE;
  }

  player_get_position(player, &player_x, &player_y);
  obj_x = object_get_x(obj);
  obj_y = object_get_y(obj);

  if (abs(player_x - obj_x) <= COLLISION_MARGIN && abs(player_y - obj_y) <= COLLISION_MARGIN) {
    return TRUE;
  }

  return FALSE;
}

/* Detects if the player has collided with a link and returns the link */
Link *physics_get_colliding_link(Game *game, Player *player) {
  Id current_space_id = game_get_player_location(game);
  Link *link = NULL;
  int link_x, link_y, player_x, player_y, i;
  if (current_space_id == NO_ID) {
    printf("[DEBUG] Player is not in a valid space.\n");
    return NULL;
  }

  printf("[DEBUG] Checking collision for player at space ID %ld\n", current_space_id);

  for (i = 0; i < 6; i++) {
    link = game_get_link_at_direction(game, current_space_id, i);
    if (link) {
      link_x = link_get_x(link);
      link_y = link_get_y(link);
      player_x = player_get_x(player);
      player_y = player_get_y(player);
      printf("[DEBUG] Checking link at (%d, %d) vs player at (%d, %d)\n", link_x, link_y, player_x, player_y);

      if (abs(player_x - link_x) <= COLLISION_MARGIN && abs(player_y - link_y) <= COLLISION_MARGIN) {
        printf("[DEBUG] Collision detected with link in direction %d\n", i);
        return link;
      }
    }
  }
  printf("[DEBUG] No collision detected.\n");
  return NULL;
}

Character *physics_get_colliding_character(Game *game, Player *player) {
  Id current_space_id = game_get_player_location(game);
  Character *character = NULL;
  Space *space = NULL;
  int character_x, character_y, player_x, player_y;
  int i, num_characters;
  Id char_id;

  if (current_space_id == NO_ID) {
    printf("[DEBUG] Player is not in a valid space.\n");
    return NULL;
  }

  space = game_get_space(game, current_space_id);
  if (!space) {
    printf("[DEBUG] Could not retrieve space.\n");
    return NULL;
  }

  player_x = player_get_x(player);
  player_y = player_get_y(player);

  num_characters = space_get_num_characters(space);

  for (i = 0; i < num_characters; i++) {
    char_id = space_get_character_from_index(space, i);
    character = game_get_character(game, char_id);

    if (!character) {
      printf("[DEBUG] Null character at index %d\n", i);
      continue;
    }

    character_x = character_get_x(character);
    character_y = character_get_y(character);

    printf("[DEBUG] Checking character %ld at (%d, %d) vs player at (%d, %d)\n", character_get_id(character), character_x, character_y, player_x,
           player_y);

    if (abs(player_x - character_x) <= COLLISION_MARGIN && abs(player_y - character_y) <= COLLISION_MARGIN) {
      printf("[DEBUG] Collision detected with character ID %ld\n", character_get_id(character));
      return character;
    }
  }

  printf("[DEBUG] No character collision detected.\n");
  return NULL;
}

/* Handles space transition when the player collides with an open link */
void physics_handle_space_transition(Game *game, Player *player) {
  Link *colliding_link = NULL;
  Id next_space_id;
  Direction direction;
  int player_x, player_y = 0;
  colliding_link = physics_get_colliding_link(game, player);

  if (colliding_link) {
    printf("[DEBUG] Colliding link found. Checking if open...\n");
    if (link_get_open(colliding_link)) {
      direction = link_get_direction(colliding_link);
      next_space_id = link_get_end(colliding_link);
      printf("[DEBUG] Link is open. Transitioning to space ID %ld\n", next_space_id);
      if (next_space_id != NO_ID) {
        game_set_player_location(game, next_space_id);
        switch (direction) {
          case 0:
            player_x = (SDL_WINDOW_WIDTH / 2 - SDL_LINK_HW / 2) / (SDL_TILE_SIZE);
            player_y = ((SDL_WALL_HEIGHT - SDL_LINK_HW / 2 - SDL_SCREEN_ZOOM) + SDL_PLAYER_HW) / (SDL_TILE_SIZE);
            break;

          case 1:
            player_x = ((SDL_WINDOW_WIDTH / 2 - SDL_LINK_HW / 2) - SDL_PLAYER_HW) / (SDL_TILE_SIZE);
            player_y = (2 * SDL_MAP_BORDER + SDL_MAP_HEIGHT - SDL_LINK_HW / 2 - SDL_WALL_HEIGHT) / (SDL_TILE_SIZE);
            break;

          case 2:
            player_x = (SDL_WINDOW_WIDTH - SDL_LINK_HW + SDL_SCREEN_ZOOM) / (SDL_TILE_SIZE);
            player_y = ((SDL_WALL_HEIGHT / 2 + SDL_MAP_HEIGHT / 2 - SDL_LINK_HW / 2) - SDL_PLAYER_HW) / (SDL_TILE_SIZE);
            break;

          case 3:
            player_x = (SDL_SCREEN_ZOOM + SDL_PLAYER_HW) / SDL_TILE_SIZE;
            player_y = (SDL_WALL_HEIGHT / 2 + SDL_MAP_HEIGHT / 2 - SDL_LINK_HW / 2) / (SDL_TILE_SIZE);
            break;

          case 4:
            player_x = (SDL_MAP_BORDER + SDL_WINDOW_WIDTH / 3 - SDL_LINK_HW / 2 - SDL_SCREEN_ZOOM) / (SDL_TILE_SIZE);
            player_y = ((SDL_WALL_HEIGHT - SDL_LINK_HW / 2 - SDL_SCREEN_ZOOM) + SDL_PLAYER_HW) / (SDL_TILE_SIZE);
            break;

          case 5:
            player_x = (SDL_WINDOW_WIDTH / 3 - SDL_LINK_HW / 2 - SDL_SCREEN_ZOOM) / (SDL_TILE_SIZE);
            player_y = ((SDL_WALL_HEIGHT - SDL_LINK_HW / 2 - SDL_SCREEN_ZOOM) + SDL_PLAYER_HW) / (SDL_TILE_SIZE);
            break;
        }
        player_set_position(player, player_x, player_y);
      }
    } else {
      printf("[DEBUG] Link is closed. Cannot transition.\n");
    }
  } else {
    printf("[DEBUG] No valid link to transition through.\n");
  }
}

/* Placeholder for future attack system */
void physics_handle_attack(Player *player) {
  Ray *new_ray = NULL;
  if (ray_count >= MAX_RAYS) return;
  new_ray = ray_create(player_get_x(player), player_get_y(player), player_get_direction(player));
  if (new_ray) {
    rays[ray_count++] = new_ray;
  }
}

void physics_update_rays() {
  int i = 0;
  for (i = 0; i < ray_count; i++) {
    if (rays[i]) {
      ray_update(rays[i]);
    }
  }
}

/* Placeholder for future chat system */
void physics_handle_chat(Game *game, Player *player) { printf("[DEBUG] Chat system not implemented yet.\n"); }
