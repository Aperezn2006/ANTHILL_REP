#include "physics.h"

#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "gun.h"
#include "input.h"
#include "link.h"
#include "player.h"
#include "ray.h"
#include "space.h"

#define MAX_RAYS 10
#define COLLISION_MARGIN 10  // Adjust based on your game scale
#define MOVE_STEP 2
#define ACCELERATION 1
#define MAX_SPEED 3
#define FRICTION 1
#define GRAVITY 2
#define JUMP_VELOCITY -8

static Ray *rays[MAX_RAYS];
static int ray_count = 0;

Bool physics_check_object_collision(Game *game, Player *player, Object *obj) {
  int player_x, player_y;
  int obj_x, obj_y;

  if (!game || !player || !obj) return FALSE;

  Id player_space = game_get_player_location(game);
  Id obj_space = game_get_object_location(game, object_get_id(obj));

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
  if (current_space_id == NO_ID) {
    printf("[DEBUG] Player is not in a valid space.\n");
    return NULL;
  }

  printf("[DEBUG] Checking collision for player at space ID %ld\n", current_space_id);

  int player_x = 0;
  int player_y = 0;
  player_get_position(player, &player_x, &player_y);

  Direction directions[4] = {N, S, E, W};
  for (int i = 0; i < 4; i++) {
    Link *link = game_get_link_at_direction(game, current_space_id, directions[i]);
    if (link) {
      int link_x = link_get_x(link);
      int link_y = link_get_y(link);

      printf("[DEBUG] Checking link at (%d, %d) vs player at (%d, %d)\n", link_x, link_y, player_x, player_y);

      // Exclude character positions from collision detection
      Character *character = game_get_character(game, space_get_character(game_get_space(game, current_space_id)));
      if (character) {
        int character_x = character_get_x(character);
        int character_y = character_get_y(character);
        if (player_x == character_x && player_y == character_y) {
          printf("[DEBUG] Ignoring collision with character at (%d, %d)\n", character_x, character_y);
          continue;
        }
      }

      if (abs(10 * player_x - link_x) <= COLLISION_MARGIN && abs(10 * player_y - link_y) <= COLLISION_MARGIN) {
        printf("[DEBUG] Collision detected with link in direction %d\n", directions[i]);
        return link;
      }
    }
  }

  printf("[DEBUG] No collision detected.\n");
  return NULL;
}

/* Handles space transition when the player collides with an open link */
void physics_handle_space_transition(Game *game, Player *player) {
  printf("[DEBUG] Handling space transition...\n");
  Link *colliding_link = physics_get_colliding_link(game, player);

  if (colliding_link) {
    printf("[DEBUG] Colliding link found. Checking if open...\n");
    if (link_get_open(colliding_link)) {
      Id next_space_id = link_get_end(colliding_link);
      printf("[DEBUG] Link is open. Transitioning to space ID %ld\n", next_space_id);
      if (next_space_id != NO_ID) {
        game_set_player_location(game, next_space_id);
        player_set_position(player, 35, 30);
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
  if (ray_count >= MAX_RAYS) return;

  int player_x = 0;
  int player_y = 0;
  player_get_position(player, &player_x, &player_y);

  Ray *new_ray = ray_create(player_x, player_y, player_get_direction(player));
  if (new_ray) {
    rays[ray_count++] = new_ray;
  }
}

void physics_update_rays() {
  for (int i = 0; i < ray_count; i++) {
    if (rays[i]) {
      ray_update(rays[i]);
    }
  }
}

/* Placeholder for future chat system */
void physics_handle_chat(Game *game, Player *player) { printf("[DEBUG] Chat system not implemented yet.\n"); }
