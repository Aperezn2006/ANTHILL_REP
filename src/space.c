/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Profesores PPROG, Beatriz, Arturo, Rubén, Ana
 * @version 1
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space {
  Id id;
  char name[WORD_SIZE + 1];
  Set *objects;
  Id character_id;
  char gdesc[5][10];
  Bool discovered;
};

/*Create & destroy*/
Space *space_create(Id id) {
  Space *newSpace = NULL;
  int i = 0;
  if (id == NO_ID) return NULL;

  newSpace = (Space *)malloc(sizeof(Space));
  if (!newSpace) return NULL;

  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->objects = set_create();
  if (!newSpace->objects) {
    free(newSpace);
    return NULL;
  }
  newSpace->character_id = NO_ID;
  for (i = 0; i < 5; i++) {
    newSpace->gdesc[i][0] = '\0';
  }
  newSpace->discovered = FALSE;

  return newSpace;
}

Status space_destroy(Space *space) {
  if (!space) {
    return ERROR;
  }

  if (space->objects) {
    set_destroy(space->objects);
  }

  free(space);
  return OK;
}

/*Manejo del id*/
Id space_get_id(Space *space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

Status space_set_id(Space *space, Id id) {
  if (!space || !id || id < 0) {
    return ERROR;
  }
  space->id = id;
  return OK;
}

/*Manejo de name*/
const char *space_get_name(Space *space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

Status space_set_name(Space *space, char *name) {
  if (!space || !name) {
    return ERROR;
  }
  strcpy(space->name, name);
  return OK;
}

/*Manejo de objects*/
Id space_get_object_from_index(Space *space, int n) {
  if (!space || !space->objects) {
    return NO_ID;
  }
  return set_get_id_from_index(space->objects, n);
}

int space_get_num_objects(Space *space) {
  if (!space || !space->objects) {
    return 0;
  }
  return set_get_num_ids(space->objects);
}

Status space_remove_object(Space *space, Id object_id) {
  if (!space || !space->objects) {
    return ERROR;
  }
  return set_remove_id(space->objects, object_id);
}

Bool space_has_object(Space *space, Id object_id) {
  if (!space || !space->objects) {
    return WRONG;
  }
  return set_has_id(space->objects, object_id);
}

Status space_add_object(Space *space, Id object_id) {
  if (!space || !space->objects) {
    return ERROR;
  }
  return set_add_id(space->objects, object_id);
}

/*Manejo de character_id*/
Id space_get_character(Space *space) {
  if (!space) {
    return NO_ID;
  }

  return space->character_id;
}

Status space_set_character(Space *space, Id character_id) {
  if (!space) {
    return ERROR;
  }

  space->character_id = character_id;

  return OK;
}

Bool space_has_character(Space *space, Id character_id) {
  if (!space || space->character_id == NO_ID) {
    return WRONG;
  }

  if (space->character_id == character_id) {
    return TRUE;
  }

  return FALSE;
}

Status space_remove_character(Space *space) {
  if (!space) {
    return ERROR;
  }

  space->character_id = -1;

  return OK;
}

/*Manejo de la descripción*/
char **space_get_description(Space *space) {
  if (!space) {
    return NULL;
  }

  return (char **)space->gdesc;
}

/**
 * @brief It gets the graphical description of the space located in the n position of the array, whether its hidden or not
 */
char *space_get_i_static_description(Space *space, int n) {
  if (!space) {
    return NULL;
  }

  return space->gdesc[n];
}

char *space_get_i_dynamic_description(Space *space, int n) {
  if (!space) {
    return NULL;
  }

  if (space_get_discovered(space) == TRUE) {
    return space->gdesc[n];
  } else if (n == 2) {
    return "  HID    ";
  }

  return "         ";
}

Status space_set_description(Space *space, char description[5][10]) {
  int i = 0;

  if (!space || !description) {
    return ERROR;
  }

  for (i = 0; i < 5; i++) {
    strcpy(space->gdesc[i], description[i]);
  }

  return OK;
}

/*Manejo de discovered*/
Bool space_get_discovered(Space *space) {
  if (!space) {
    return WRONG;
  }

  return space->discovered;
}

Status space_set_discovered(Space *space, Bool discovered) {
  if (!space) {
    return ERROR;
  }

  space->discovered = discovered;

  return OK;
}

/*Print*/
Status space_print(Space *space) {
  int i = 0;
  char *gdesc[10];
  if (!space) {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  fprintf(stdout, "---> %i object's in the space.\n", space_get_num_objects(space));

  for (i = 0; i < 5; i++) {
    strcpy(gdesc[i], space_get_description(space)[i]);
    fprintf(stdout, "%s\n", gdesc[i]);
  }

  return OK;
}
