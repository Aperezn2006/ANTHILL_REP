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
  Set *characters;
  char gdesc[5][10];
  Bool discovered;
  Obstacle *obstacle[10];  /*SDL2*/
  int num_obstacles;       /*SDL2*/
  char image[MAX_MESSAGE]; /*SDL2*/
};

/*Cosas de SDL2*/

Status space_add_obstacle(Space *space, Obstacle *p) {
  if (!space) {
    fprintf(stderr, "Debug: space is NULL\n");
    return ERROR;
  }
  if (!p) {
    fprintf(stderr, "Debug: obstacle is NULL\n");
    return ERROR;
  }

  if (space->num_obstacles >= 10) {
    fprintf(stderr, "Debug: Maximum obstacles reached in space (num_obstacles = %d)\n", space->num_obstacles);
    return ERROR;
  }

  fprintf(stderr, "Debug: Adding obstacle. Current num_obstacles = %d\n", space->num_obstacles);

  space->obstacle[space->num_obstacles++] = p;

  fprintf(stderr, "Debug: Obstacle added. Updated num_obstacles = %d\n", space->num_obstacles);

  return OK;
}

int space_get_num_obstacles(Space *space) {
  if (!space) {
    return -1;
  }
  return space->num_obstacles;
}

Obstacle *space_get_obstacle(Space *space, int index) {
  if (!space || index < 0 || index >= space->num_obstacles) {
    return NULL;
  }
  return space->obstacle[index];
}

/* Set space image */
Status space_set_image(Space *space, const char *image) {
  if (!space || !image) return ERROR;
  strncpy(space->image, image, MAX_MESSAGE - 1);
  space->image[MAX_MESSAGE - 1] = '\0';
  return OK;
}

/* Get space image */
const char *space_get_image(const Space *space) {
  if (!space) return NULL;
  return space->image;
}

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
  newSpace->characters = set_create();
  if (!newSpace->characters) {
    free(newSpace);
    return NULL;
  }
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
  if (space->characters) {
    set_destroy(space->characters);
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
/* Manejo de characters */

Status space_add_character(Space *space, Id character_id) {
  if (!space || !space->characters) {
    return ERROR;
  }
  return set_add_id(space->characters, character_id);
}

Status space_remove_character(Space *space, Id character_id) {
  if (!space || !space->characters) {
    return ERROR;
  }
  return set_remove_id(space->characters, character_id);
}

Bool space_has_character(Space *space, Id character_id) {
  if (!space || !space->characters) {
    return FALSE;
  }
  return set_has_id(space->characters, character_id);
}

int space_get_num_characters(Space *space) {
  if (!space || !space->characters) {
    return -1;
  }
  return set_get_num_ids(space->characters);
}

Id space_get_character_from_index(Space *space, int index) {
  if (!space || !space->characters) {
    return NO_ID;
  }
  return set_get_id_from_index(space->characters, index);
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
