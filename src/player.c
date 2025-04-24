/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Beatriz, Arturo, Rubén, Ana
 * @version 1
 * @date 05/02/2025
 * @copyright GNU Public License
 */

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventory.h"
#include "set.h"

/**
 * @brief player
 *
 * This struct stores all the information of a player.
 */
struct _Player {
  Id id;                    /*!< Id number of the player, it must be unique */
  Id player_location;       /*!< Id number of the space the player is in */
  char name[WORD_SIZE + 1]; /*!< Name of the player */
  long health;              /*!< Health points the player has */
  char gdesc[4];            /*!< Graphical description of the player*/
  Inventory *backpack;      /*!< Pointer to the player's inventory*/
  int max_turns;            /*!< Default number of turns the player has in a row*/
};

/*Create & destroy*/
Player *player_create(Id id) {
  Player *newPlayer = NULL;

  /* Error control */
  if (id == NO_ID) {
    return NULL;
  }

  newPlayer = (Player *)malloc(sizeof(Player));

  if (newPlayer == NULL) {
    return NULL;
  }

  /* Initialization of an empty player*/
  newPlayer->id = id;
  newPlayer->name[0] = '\0';
  newPlayer->backpack = inventory_create(1);
  if (!newPlayer->backpack) {
    free(newPlayer);
    return NULL;
  }
  newPlayer->player_location = NO_ID;
  newPlayer->health = PLAYER_HEALTH;
  newPlayer->max_turns = 1;

  return newPlayer;
}

Status player_destroy(Player *player) {
  if (!player) {
    return ERROR;
  }

  if (player->backpack) {
    inventory_destroy(player->backpack);
  }

  free(player);

  return OK;
}

/*Manejo de id*/
Id player_get_id(Player *player) {
  if (!player) {
    return NO_ID;
  }

  return player->id;
}

Status player_set_id(Player *player, Id id) {
  if (!player) {
    return ERROR;
  }

  player->id = id;

  return OK;
}

/*Manejo de player_location*/
Id player_get_location(Player *player) {
  Id player_location;

  if (!player) {
    return NO_ID;
  }

  player_location = player->player_location;

  return player_location;
}

Status player_set_location(Player *player, Id player_location) {
  if (!player) {
    return ERROR;
  }

  player->player_location = player_location;

  return OK;
}

/*Manejo de name*/
const char *player_get_name(Player *player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}

Status player_set_name(Player *player, char *name) {
  if (!player || !name) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }

  return OK;
}

/*Manejo de objects*/
Id player_get_object_from_index(Player *player, int n) {
  if (!player || !player->backpack) {
    return NO_ID;
  }

  return inventory_get_object_by_index(player->backpack, n);
}

int player_get_num_objects(Player *player) {
  if (!player || !player->backpack) {
    return -1;
  }

  return inventory_get_num_objects(player->backpack);
}

Status player_remove_object(Player *player, Id object_id) {
  if (!player || !player->backpack) {
    return ERROR;
  }

  return inventory_remove_object(player->backpack, object_id);
}

Bool player_has_object(Player *player, Id object_id) {
  if (!player || !player->backpack) {
    return WRONG;
  }

  return inventory_has_object(player->backpack, object_id);
}

Status player_add_object(Player *player, Id object_id) {
  if (!player || !player->backpack) {
    return ERROR;
  }

  return inventory_add_object(player->backpack, object_id);
}

/*Manejo de health*/
long player_get_health(Player *player) {
  if (!player) {
    return -1;
  }

  return player->health;
}

Status player_set_health(Player *player, long health) {
  if (!player) {
    return ERROR;
  }

  player->health = health;

  return OK;
}

Status player_decrease_health(Player *player, long damage) {
  if (!player || damage <= 0) {
    return ERROR;
  }

  player->health -= damage;

  return OK;
}

/*Manejo de gdesc*/
Status player_set_description(Player *player, char *gdesc) {
  if (!player) {
    return ERROR;
  }

  strcpy(player->gdesc, gdesc);

  return OK;
}

char *player_get_description(Player *player) {
  if (!player) {
    return NULL;
  }

  return player->gdesc;
}

/*Manejo de inventory*/
Status player_set_max_objs(Player *player, int max) {
  if (!player) {
    return ERROR;
  }
  inventory_set_max_objects(player->backpack, max);
  return OK;
}

Inventory *player_get_inventory(Player *player) {
  if (!player) {
    return NULL;
  }

  return player->backpack;
}

/*Management of max_turns*/
/**
 * @brief It sets the max number of turns the player has
 */
Status player_set_max_turns(Player *player, int max_turns) {
  /*CdE*/
  if (!player) {
    return ERROR;
  }

  player->max_turns = max_turns;

  return OK;
}

/**
 * @brief It gets the max number of turns the player has
 */
int player_get_max_turns(Player *player) {
  /*CdE*/
  if (!player) {
    return -1;
  }

  return player->max_turns;
}

/*Print*/
Status player_print(Player *player) {
  /* Error Control */
  if (!player) {
    return ERROR;
  }

  /* 1. Print the id and the name of the player */
  fprintf(stdout, "--> player (Id: %ld; Name: %s)\n", player->id, player->name);

  return OK;
}