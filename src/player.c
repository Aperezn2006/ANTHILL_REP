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
  Id id;                         /*!< Id number of the player, it must be unique */
  Id player_location;            /*!< Id number of the space the player is in */
  char name[WORD_SIZE + 1];      /*!< Name of the player */
  long health;                   /*!< Health points the player has */
  char gdesc[4];                 /*!< Graphical description of the player*/
  Inventory *backpack;           /*!< Pointer to the player's inventory*/
  int max_turns;                 /*!< Default number of turns the player has in a row*/
  Direction direction;           /*SDL2*/
  char current_image[MAX_IMAGE]; /*!< Path to the player's image (for SDL2)*/
  char North_image[MAX_MESSAGE]; /*!< Path to the player's image (for SDL2)*/
  char East_image[MAX_MESSAGE];  /*!< Path to the player's image (for SDL2)*/
  char South_image[MAX_MESSAGE]; /*!< Path to the player's image (for SDL2)*/
  char West_image[MAX_MESSAGE];  /*!< Path to the player's image (for SDL2)*/
  int x, y;                      /*!< Player's position*/
  Gun *current_gun;              /*SDL2*/
};

/*Cosas de SDL2*/
Gun *player_get_gun(const Player *player) { return player ? player->current_gun : NULL; }

void player_set_gun(Player *player, Gun *gun) {
  if (player) {
    player->current_gun = gun;
  }
}

Direction player_get_direction(Player *player) { return player->direction; }

void player_set_direction(Player *player, Direction direction) {
  if (player) {
    player->direction = direction;
  }
}

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
  newPlayer->current_image[0] = '\0';
  newPlayer->East_image[0] = '\0';
  newPlayer->West_image[0] = '\0';
  newPlayer->x = 0;
  newPlayer->y = 0;

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

int player_get_inventory_cursor(Player *player) {
  Inventory *inv;

  if (!player) return -1;

  inv = player_get_inventory(player);
  if (!inv) return -1;

  return inventory_get_cursor(inv);
}

void player_set_inventory_cursor(Player *player, int cursor) {
  Inventory *inv;

  if (!player) return;

  inv = player_get_inventory(player);
  if (!inv) return;

  inventory_set_cursor(inv, cursor);
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

/*Management of image*/
/* Set player current_image */
Status player_set_image(Player *player, char *image) {
  if (!player || !image) return ERROR;
  printf("\nImage now is %s\n\n", image);
  strncpy(player->current_image, image, MAX_MESSAGE - 1);
  player->current_image[MAX_MESSAGE - 1] = '\0';
  return OK;
}

/* Get player image */
char *player_get_image(Player *player) {
  if (!player) return NULL;
  return player->current_image;
}

/* Set player North_image */
Status player_set_North_image(Player *player, const char *North_image) {
  if (!player || !North_image) return ERROR;
  strncpy(player->North_image, North_image, MAX_MESSAGE - 1);
  player->North_image[MAX_MESSAGE - 1] = '\0';
  return OK;
}

/* Get player North_image */
const char *player_get_North_image(const Player *player) {
  if (!player) return NULL;
  return player->North_image;
}

/* Set player East_image */
Status player_set_East_image(Player *player, const char *East_image) {
  if (!player || !East_image) return ERROR;
  strncpy(player->East_image, East_image, MAX_MESSAGE - 1);
  player->East_image[MAX_MESSAGE - 1] = '\0';
  return OK;
}

/* Get player East_image */
const char *player_get_East_image(const Player *player) {
  if (!player) return NULL;
  return player->East_image;
}

/* Get player South_image */
const char *player_get_South_image(const Player *player) {
  if (!player) return NULL;
  return player->South_image;
}

/* Set player South_image */
Status player_set_South_image(Player *player, const char *South_image) {
  if (!player || !South_image) return ERROR;
  strncpy(player->South_image, South_image, MAX_MESSAGE - 1);
  player->South_image[MAX_MESSAGE - 1] = '\0';
  return OK;
}

/* Get player West_image */
const char *player_get_West_image(const Player *player) {
  if (!player) return NULL;
  return player->West_image;
}

/* Set player West_image */
Status player_set_West_image(Player *player, const char *West_image) {
  if (!player || !West_image) return ERROR;
  strncpy(player->West_image, West_image, MAX_MESSAGE - 1);
  player->West_image[MAX_MESSAGE - 1] = '\0';
  return OK;
}

/*Management of position*/
/**
 * @brief It sets the player's position
 */
Status player_set_position(Player *player, int x, int y) {
  if (!player || (x < 0) || (y < 0)) {
    return ERROR;
  }

  player->x = x;
  player->y = y;

  return OK;
}

/**
 * @brief It gets the player's position
 */
Status player_get_position(Player *player, int *x, int *y) {
  if (!player) {
    return ERROR;
  }

  *x = player->x;
  *y = player->y;

  return OK;
}

int player_get_x(Player *player) {
  if (!player) {
    return ERROR;
  }

  return player->x;
}

int player_get_y(Player *player) {
  if (!player) {
    return ERROR;
  }

  return player->y;
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