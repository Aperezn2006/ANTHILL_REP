/**
 * @brief It implements the character module
 *
 * @file character.c
 * @author Beatriz, Arturo, Rubén, Ana
 * @version 0
 * @date 18/02/2025
 * @copyright GNU Public License
 */

#include "character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief character
 *
 * This struct stores all the information of a character.
 */
struct _Character {
  Id id;                            /*!< Id number of the character, it must be unique */
  Id following;                     /*!< The id of the player the character's following*/
  Bool friendly;                    /*!< Indicates whether the character is hostile or not */
  long health;                      /*!< Health points the character has */
  char name[WORD_SIZE + 1];         /*!< Name of the character */
  char gdesc[7];                    /*!< Graphical description of the character */
  char message[MAX_MESSAGE];        /*!< It saves the message*/
  char current_image[3][MAX_IMAGE]; /*!< Path to the character's image (for SDL2)*/
  char north_image[3][MAX_MESSAGE]; /*!< Path to the character's image (for SDL2)*/
  char east_image[3][MAX_MESSAGE];  /*!< Path to the character's image (for SDL2)*/
  char south_image[3][MAX_MESSAGE]; /*!< Path to the character's image (for SDL2)*/
  char west_image[3][MAX_MESSAGE];  /*!< Path to the character's image (for SDL2)*/
  int curr_image_mode;              /*!< Identifies which sprite is being used (for SDL2)*/
  int sprite_slower;                /*!< It controls how often the sprites change (for SDL2)*/
  int x, y;                         /*!< The character's coordinates (for SDL2)*/
  int blink_timer;                  /*!< It controls the character's image blinking upon death (for SDL2)*/
};

/*Management of blink_timer*/
int character_get_blink_timer(Character *character) { return character ? character->blink_timer : 0; }

Status character_update_blink_timer(Character *character) {
  /*CdE*/
  if (!character) {
    return ERROR;
  }

  if (character->blink_timer > 0) {
    character->blink_timer--;
  }

  return OK;
}

/* Create y destroy */
/*character_create allocates memory for a new characte and initializes its members*/
Character *character_create(Id id) {
  Character *newcharacter = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  newcharacter = (Character *)malloc(sizeof(Character));

  if (newcharacter == NULL) {
    return NULL;
  }

  /* Initialization of an empty character*/
  newcharacter->id = id;
  newcharacter->name[0] = '\0';
  newcharacter->gdesc[0] = '\0';
  newcharacter->health = CHARACTER_HEALTH;
  newcharacter->friendly = TRUE;
  newcharacter->message[0] = '\0';
  newcharacter->following = NO_ID;
  newcharacter->current_image[0][0] = '\0';
  newcharacter->current_image[1][0] = '\0';
  newcharacter->north_image[0][0] = '\0';
  newcharacter->north_image[1][0] = '\0';
  newcharacter->east_image[0][0] = '\0';
  newcharacter->east_image[1][0] = '\0';
  newcharacter->south_image[0][0] = '\0';
  newcharacter->south_image[1][0] = '\0';
  newcharacter->west_image[0][0] = '\0';
  newcharacter->west_image[1][0] = '\0';
  newcharacter->x = 0;
  newcharacter->y = 0;
  newcharacter->blink_timer = 0;

  return newcharacter;
}

Status character_destroy(Character *character) {
  if (!character) {
    return ERROR;
  }

  free(character);
  character = NULL;
  return OK;
}

/* Manejo de id */
Id character_get_id(Character *character) {
  if (!character) {
    return NO_ID;
  }

  return character->id;
}

Status character_set_id(Character *character, Id id) {
  if (!character) {
    return ERROR;
  }

  character->id = id;

  return OK;
}

/*  Manejo de name */
char *character_get_name(Character *character) {
  if (!character) {
    return NULL;
  }

  return character->name;
}

Status character_set_name(Character *character, char *name) {
  if (!character || !name) {
    return ERROR;
  }

  strcpy(character->name, name);

  return OK;
}

/*  Manejo de gdesc */
char *character_get_description(Character *character) {
  if (!character) {
    return NULL;
  }

  return character->gdesc;
}

Status character_set_description(Character *character, char *description) {
  if (!character || !description) {
    return ERROR;
  }

  strcpy(character->gdesc, description);

  return OK;
}

/*  Manejo de health */
long character_get_health(Character *character) {
  if (!character) {
    return -1;
  }

  return character->health;
}

Status character_set_health(Character *character, long health) {
  if (!character) {
    return ERROR;
  }
  if (character->health != health) {
    character->blink_timer = 30; /* Parpadear durante 30 frames (~0.5s si vas a 60fps) */
  }
  character->health = health;

  return OK;
}

Status character_decrease_health(Character *character, long damage) {
  if (!character || !damage || damage < 0) {
    return ERROR;
  }
  character->health -= damage;
  character->blink_timer = 30;
  return OK;
}

/*  Manejo de friendly */
Bool character_get_friendly(Character *character) {
  if (!character) {
    return FALSE;
  }

  return character->friendly;
}

Status character_set_friendly(Character *character, Bool friendly) {
  if (!character) {
    return ERROR;
  }

  character->friendly = friendly;

  return OK;
}

/*  Manejo de message */
char *character_get_message(Character *character) {
  if (!character) {
    return NULL;
  }

  return character->message;
}

Status character_set_message(Character *character, char *message) {
  if (!character || !message) {
    return ERROR;
  }

  strcpy(character->message, message);

  return OK;
}

/*  Manejo de following */
Id character_get_following(Character *character) {
  if (!character) return NO_ID;

  return character->following;
}

Status character_set_following(Character *character, Id id) {
  if (!character) return ERROR;

  character->following = id;
  return OK;
}

/*Management of image*/
/* Set character current_image */
Status character_set_image(Character *character, char *image1, char *image2, char *image3) {
  if (!character || !image1 || !image2 || !image3) {
    return ERROR;
  }
  strncpy(character->current_image[0], image1, MAX_MESSAGE - 1);
  strncpy(character->current_image[1], image2, MAX_MESSAGE - 1);
  strncpy(character->current_image[2], image3, MAX_MESSAGE - 1);

  character->current_image[0][MAX_MESSAGE - 1] = '\0';
  character->current_image[1][MAX_MESSAGE - 1] = '\0';
  character->current_image[2][MAX_MESSAGE - 1] = '\0';

  return OK;
}

/* Get character image */
Status character_toggle_curr_image_mode(Character *character) {
  if (!character) {
    return ERROR;
  }

  if (character->curr_image_mode < 2 && character->sprite_slower == 4) {
    character->curr_image_mode++;
    character->sprite_slower = 0;
  } else if (character->curr_image_mode == 2 && character->sprite_slower == 4) {
    character->curr_image_mode = 0;
    character->sprite_slower = 0;
  } else {
    character->sprite_slower++;
  }

  printf("CURRENT IMAGE MODE IS %i, SPRITE Nº %i\n", character->curr_image_mode, character->sprite_slower);

  return OK;
}

char *character_get_image(Character *character) {
  if (!character) {
    return NULL;
  }

  printf("IMAGE PATH IS %s\n", character->current_image[character->curr_image_mode]);

  return character->current_image[character->curr_image_mode];
}

/* Set character north_image */
Status character_set_north_image(Character *character, const char *north_image, int sprite) {
  if (!character || !north_image) {
    return ERROR;
  }
  strncpy(character->north_image[sprite], north_image, MAX_MESSAGE - 1);
  character->north_image[sprite][MAX_MESSAGE - 1] = '\0';
  return OK;
}

/* Get character north_image */
const char *character_get_north_image(const Character *character, int sprite) {
  if (!character) {
    return NULL;
  }
  return character->north_image[sprite];
}

/* Set character east_image */
Status character_set_east_image(Character *character, const char *east_image, int sprite) {
  if (!character || !east_image) return ERROR;
  strncpy(character->east_image[sprite], east_image, MAX_MESSAGE - 1);
  character->east_image[sprite][MAX_MESSAGE - 1] = '\0';
  return OK;
}

/* Get character east_image */
const char *character_get_east_image(const Character *character, int sprite) {
  if (!character) return NULL;
  return character->east_image[sprite];
}

/* Get character south_image */
const char *character_get_south_image(const Character *character, int sprite) {
  if (!character) return NULL;
  return character->south_image[sprite];
}

/* Set character south_image */
Status character_set_south_image(Character *character, const char *south_image, int sprite) {
  if (!character || !south_image) return ERROR;
  strncpy(character->south_image[sprite], south_image, MAX_MESSAGE - 1);
  character->south_image[sprite][MAX_MESSAGE - 1] = '\0';
  return OK;
}

/* Get character west_image */
const char *character_get_west_image(const Character *character, int sprite) {
  if (!character) return NULL;
  return character->west_image[sprite];
}

/* Set character west_image */
Status character_set_west_image(Character *character, const char *west_image, int sprite) {
  if (!character || !west_image) return ERROR;
  strncpy(character->west_image[sprite], west_image, MAX_MESSAGE - 1);
  character->west_image[sprite][MAX_MESSAGE - 1] = '\0';
  return OK;
}

/*Management of position*/
/**
 * @brief It sets the character's position
 */
Status character_set_position(Character *character, int x, int y) {
  if (!character || (x < 0) || (y < 0)) {
    return ERROR;
  }

  if ((x > ((SDL_MAP_BORDER - SDL_CHARACTER_HW) / SDL_TILE_SIZE)) &&
      (x < ((SDL_WINDOW_WIDTH - 2 * SDL_MAP_BORDER - SDL_CHARACTER_HW / 2) / SDL_TILE_SIZE))) {
    character->x = x;
  } else if ((character->x <= ((SDL_MAP_BORDER - SDL_CHARACTER_HW) / SDL_TILE_SIZE)) ||
             (character->x >= ((SDL_WINDOW_WIDTH - 2 * SDL_MAP_BORDER - SDL_CHARACTER_HW / 2) / SDL_TILE_SIZE))) {
    character->x = (SDL_MAP_BORDER + SDL_CHARACTER_HW + 1) / SDL_TILE_SIZE;
  }

  if ((y > ((SDL_MAP_BORDER + SDL_WALL_HEIGHT - SDL_CHARACTER_HW) / SDL_TILE_SIZE)) &&
      (y < ((SDL_MAP_HEIGHT - 2 * SDL_MAP_BORDER - SDL_CHARACTER_HW / 2) / SDL_TILE_SIZE))) {
    character->y = y;
  } else if ((character->y <= ((SDL_MAP_BORDER + SDL_WALL_HEIGHT - SDL_CHARACTER_HW) / SDL_TILE_SIZE)) ||
             (character->y >= ((SDL_MAP_HEIGHT - 2 * SDL_MAP_BORDER - SDL_CHARACTER_HW / 2) / SDL_TILE_SIZE))) {
    character->y = (SDL_MAP_BORDER + SDL_WALL_HEIGHT - SDL_CHARACTER_HW + 1) / SDL_TILE_SIZE;
  }

  return OK;
}

/**
 * @brief It gets the character's position
 */
Status character_get_position(Character *character, int *x, int *y) {
  if (!character) {
    return ERROR;
  }

  *x = character->x;
  *y = character->y;

  return OK;
}

int character_get_x(Character *character) {
  if (!character) {
    return -1;
  }

  return character->x;
}

int character_get_y(Character *character) {
  if (!character) {
    return -1;
  }

  return character->y;
}

/*  Print */
Status character_print(Character *character) {
  /* Error Control */
  if (!character) {
    return ERROR;
  }

  /* 1. Print the id and the name of the character */
  fprintf(stdout, "--> Character (Id: %ld; Name: %s; Graphical Description: %s; Health: %ld; Friendly: %s; Message: %s; Following: %ld;)\n",
          character->id, character->name, character->gdesc, character->health, character->friendly ? "Yes" : "No", character->message,
          character->following);
  return OK;
}