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
  Id id;                            /*!< Id number of the player, it must be unique */
  Id player_location;               /*!< Id number of the space the player is in */
  char name[WORD_SIZE + 1];         /*!< Name of the player */
  long health;                      /*!< Health points the player has */
  char gdesc[4];                    /*!< Graphical description of the player*/
  Inventory *backpack;              /*!< Pointer to the player's inventory*/
  int max_turns;                    /*!< Default number of turns the player has in a row*/
  Direction direction;              /*SDL2*/
  char current_image[3][MAX_IMAGE]; /*!< Path to the player's image (for SDL2)*/
  char north_image[3][MAX_MESSAGE]; /*!< Path to the player's image (for SDL2)*/
  char east_image[3][MAX_MESSAGE];  /*!< Path to the player's image (for SDL2)*/
  char south_image[3][MAX_MESSAGE]; /*!< Path to the player's image (for SDL2)*/
  char west_image[3][MAX_MESSAGE];  /*!< Path to the player's image (for SDL2)*/
  int curr_image_mode;              /*!< Identifies which image is being used*/
  int x, y;                         /*!< Player's position*/
  Gun *current_gun;                 /*SDL2*/
  int sprite_slowed;
  int blink_timer;
};
int player_get_blink_timer(Player *player) { return player ? player->blink_timer : 0; }

void player_update_blink_timer(Player *player) {
  if (player && player->blink_timer > 0) {
    player->blink_timer--;
  }
}

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
  newPlayer->current_image[0][0] = '\0';
  newPlayer->current_image[1][0] = '\0';
  newPlayer->north_image[0][0] = '\0';
  newPlayer->north_image[1][0] = '\0';
  newPlayer->east_image[0][0] = '\0';
  newPlayer->east_image[1][0] = '\0';
  newPlayer->south_image[0][0] = '\0';
  newPlayer->south_image[1][0] = '\0';
  newPlayer->west_image[0][0] = '\0';
  newPlayer->west_image[1][0] = '\0';
  newPlayer->x = 0;
  newPlayer->y = 0;
  newPlayer->blink_timer = 0;

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
  if (!player) return ERROR;

  if (player->health != health) {
    player->blink_timer = 30; /* Parpadear durante 30 frames (~0.5s si vas a 60fps) */
  }

  player->health = health;
  return OK;
}

Status player_decrease_health(Player *player, long damage) {
  if (!player || damage <= 0) {
    return ERROR;
  }

  player->health -= damage;
  player->blink_timer = 30;

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
Status player_set_image(Player *player, char *image1, char *image2, char *image3) {
  if (!player || !image1 || !image2 || !image3) {
    return ERROR;
  }
  strncpy(player->current_image[0], image1, MAX_MESSAGE - 1);
  strncpy(player->current_image[1], image2, MAX_MESSAGE - 1);
  strncpy(player->current_image[2], image3, MAX_MESSAGE - 1);

  player->current_image[0][MAX_MESSAGE - 1] = '\0';
  player->current_image[1][MAX_MESSAGE - 1] = '\0';
  player->current_image[2][MAX_MESSAGE - 1] = '\0';

  return OK;
}

/* Get player image */
Status player_toggle_curr_image_mode(Player *player) {
  if (!player) {
    return ERROR;
  }

  if (player->curr_image_mode < 2 && player->sprite_slowed == 4) {
    player->curr_image_mode++;
    player->sprite_slowed = 0;
  } else if (player->curr_image_mode == 2 && player->sprite_slowed == 4) {
    player->curr_image_mode = 0;
    player->sprite_slowed = 0;
  } else {
    player->sprite_slowed++;
  }

  printf("CURRENT IMAGE MODE IS %i, SPRITE Nº %i\n", player->curr_image_mode, player->sprite_slowed);

  return OK;
}

char *player_get_image(Player *player) {
  if (!player) {
    return NULL;
  }

  printf("IMAGE PATH IS %s\n", player->current_image[player->curr_image_mode]);

  return player->current_image[player->curr_image_mode];
}

/* Set player north_image */
Status player_set_north_image(Player *player, const char *north_image, int sprite) {
  if (!player || !north_image) {
    return ERROR;
  }
  strncpy(player->north_image[sprite], north_image, MAX_MESSAGE - 1);
  player->north_image[sprite][MAX_MESSAGE - 1] = '\0';
  return OK;
}

/* Get player north_image */
const char *player_get_north_image(const Player *player, int sprite) {
  if (!player) {
    return NULL;
  }
  return player->north_image[sprite];
}

/* Set player east_image */
Status player_set_east_image(Player *player, const char *east_image, int sprite) {
  if (!player || !east_image) return ERROR;
  strncpy(player->east_image[sprite], east_image, MAX_MESSAGE - 1);
  player->east_image[sprite][MAX_MESSAGE - 1] = '\0';
  return OK;
}

/* Get player east_image */
const char *player_get_east_image(const Player *player, int sprite) {
  if (!player) return NULL;
  return player->east_image[sprite];
}

/* Get player south_image */
const char *player_get_south_image(const Player *player, int sprite) {
  if (!player) return NULL;
  return player->south_image[sprite];
}

/* Set player south_image */
Status player_set_south_image(Player *player, const char *south_image, int sprite) {
  if (!player || !south_image) return ERROR;
  strncpy(player->south_image[sprite], south_image, MAX_MESSAGE - 1);
  player->south_image[sprite][MAX_MESSAGE - 1] = '\0';
  return OK;
}

/* Get player west_image */
const char *player_get_west_image(const Player *player, int sprite) {
  if (!player) return NULL;
  return player->west_image[sprite];
}

/* Set player west_image */
Status player_set_west_image(Player *player, const char *west_image, int sprite) {
  if (!player || !west_image) return ERROR;
  strncpy(player->west_image[sprite], west_image, MAX_MESSAGE - 1);
  player->west_image[sprite][MAX_MESSAGE - 1] = '\0';
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
