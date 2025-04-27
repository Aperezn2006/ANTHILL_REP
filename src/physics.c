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

#define COLLISION_MARGIN 1

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

/* Handles space transition when the player collides with an open link */
void physics_handle_space_transition(Game *game, Player *player) {
  Link *colliding_link = NULL;
  Id next_space_id;
  printf("[DEBUG] Handling space transition...\n");
  colliding_link = physics_get_colliding_link(game, player);

  if (colliding_link) {
    printf("[DEBUG] Colliding link found. Checking if open...\n");
    if (link_get_open(colliding_link)) {
      next_space_id = link_get_end(colliding_link);
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
