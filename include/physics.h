#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdbool.h>

#include "game.h"
#include "link.h"
#include "player.h"
#include "space.h"

/* Detects if the player has collided with a link */
Bool physics_check_link_collision(Game *game, Player *player);

Bool physics_check_object_collision(Game *game, Player *player, Object *obj);

/* Handles space transition when the player collides with a link */
void physics_handle_space_transition(Game *game, Player *player);

/* Placeholder for future attack system */
void physics_handle_attack(Player *player);
void physics_update_rays();
void physics_update_player_movement(Player *player, Space *space);

/* Placeholder for future chat system */
void physics_handle_chat(Game *game, Player *player);

Link *physics_get_colliding_link(Game *game, Player *player);

Character *physics_get_colliding_character(Game *game, Player *player);

#endif