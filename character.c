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
  Id id;                     /*!< Id number of the character, it must be unique */
  char name[WORD_SIZE + 1];  /*!< Name of the character */
  char gdesc[7];             /*!< Graphical description of the character */
  long health;               /*!< Health points the character has */
  Bool friendly;             /*!< Indicates whether the character is hostile or not */
  char message[MAX_MESSAGE]; /*!< It saves the message*/
};

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

  character->health = health;

  return OK;
}

Status character_decrease_health(Character *character, long damage) {
  if (!character || !damage || damage < 0) {
    return ERROR;
  }
  character->health -= damage;
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

/*  Print */
Status character_print(Character *character) {
  /* Error Control */
  if (!character) {
    return ERROR;
  }

  /* 1. Print the id and the name of the character */
  fprintf(stdout, "--> Character (Id: %ld; Name: %s)\n", character->id, character->name);

  return OK;
}