/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Ana
 * @version 1
 * @date 05/02/2025
 * @copyright GNU Public License
 */

/*TAD vinculado al jugador de la aventura y que describe la
información relacionada con el estado del protagonista (ubicación, objetos que
tiene, puntos de vida, etc.).*/
#include "player.h"
#include "inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  Set *objects;             /*!< Set of object IDs */
  long health;              /*!< Health points the player has */
  char gdesc[4];
  Inventory *inventory;

};

/*Create & destroy*/
/** player_create allocates memory for a new player
 *  and initializes its members
 */
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
  newPlayer->objects = set_create();
  if (!newPlayer->objects) {
    free(newPlayer);
    return NULL;
  }
  newPlayer->player_location = NO_ID; /*  Añadir esta línea */
  newPlayer->health = PLAYER_HEALTH;

  return newPlayer;
}

Status player_destroy(Player *player) {
  if (!player) {
    return ERROR;
  }

  if (player->objects) {
    set_destroy(player->objects);
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
Id player_get_n_object(Player *player, int n) {
  if (!player || !player->objects) {
    return NO_ID;
  }

  return set_get_n(player->objects, n);
}

int player_get_num_objects(Player *player) {
  if (!player || !player->objects) {
    return 0;
  }

  return set_get_size(player->objects);
}

Status player_remove_object(Player *player, Id object_id) {
  if (!player || !player->objects) {
    return ERROR;
  }

  return set_del(player->objects, object_id);
}

Bool player_has_object(Player *player, Id object_id) {
  if (!player || !player->objects) {
    return FALSE;
  }

  return set_has(player->objects, object_id);
}

Status player_add_object(Player *player, Id object_id) {
  if (!player || !player->objects) {
    return ERROR;
  }

  return set_add(player->objects, object_id);
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
  if (!player) {
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

Status player_set_max_objs (Player *player, int max){
  if (!player){
    return ERROR;
  }
  inventory_set_max_objs (player->inventory, max);
  return OK;
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