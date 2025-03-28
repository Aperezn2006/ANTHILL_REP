/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Profesores PPROG, Rubén, Ana
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
  Id id;                    /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the space */
  Id north;                 /*!< Id of the space at the north */
  Id south;                 /*!< Id of the space at the south */
  Id east;                  /*!< Id of the space at the east */
  Id west;                  /*!< Id of the space at the west */
  Set *objects;             /*!< Set of object IDs */
  Id character_id;          /*Cada espacio solo puede tener un charcter*/
  char gdesc[5][10];
  char image[MAX_MESSAGE];
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
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->objects = set_create();
  if (!newSpace->objects) {
    free(newSpace);
    return NULL;
  }
  newSpace->character_id = NO_ID;
  for (i = 0; i < 5; i++) {
    newSpace->gdesc[i][0] = '\0';
  }
  newSpace->image[0] = '\0';
  newSpace->discovered = FALSE;

  return newSpace;
}

Status space_destroy(Space *space) {
  if (!space) return ERROR;

  if (space->objects) {
    set_destroy(space->objects);
  }

  free(space);
  return OK;
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

/*Manejo del id*/
Id space_get_id(Space *space) {
  if (!space) return NO_ID;
  return space->id;
}

/*Manejo de name*/
const char *space_get_name(Space *space) {
  if (!space) return NULL;
  return space->name;
}

Status space_set_name(Space *space, char *name) {
  if (!space || !name) return ERROR;
  strcpy(space->name, name);
  return OK;
}

/*Manejo de north*/
Id space_get_north(Space *space) {
  if (!space) return NO_ID;
  return space->north;
}

Status space_set_north(Space *space, Id id) {
  if (!space || id == NO_ID) return ERROR;
  space->north = id;
  return OK;
}

/*Manejo de south*/
Id space_get_south(Space *space) {
  if (!space) return NO_ID;
  return space->south;
}
Status space_set_south(Space *space, Id id) {
  if (!space || id == NO_ID) return ERROR;
  space->south = id;
  return OK;
}

/*Manejo de east*/
Id space_get_east(Space *space) {
  if (!space) return NO_ID;
  return space->east;
}
Status space_set_east(Space *space, Id id) {
  if (!space || id == NO_ID) return ERROR;
  space->east = id;
  return OK;
}

/*Manejo de west*/
Id space_get_west(Space *space) {
  if (!space) return NO_ID;
  return space->west;
}
Status space_set_west(Space *space, Id id) {
  if (!space || id == NO_ID) return ERROR;
  space->west = id;
  return OK;
}

/*Manejo de objects*/
Id space_get_n_object(Space *space, int n) {
  if (!space || !space->objects) {
    return NO_ID;
  }
  return set_get_n(space->objects, n);
}

int space_get_num_objects(Space *space) {
  if (!space || !space->objects) return 0;
  return set_get_size(space->objects);
}

Status space_set_object(Space *space, Id object_id) {
  if (!space || !space->objects) return ERROR;
  return set_add(space->objects, object_id);
}

Status space_remove_object(Space *space, Id object_id) {
  if (!space || !space->objects) return ERROR;
  return set_del(space->objects, object_id);
}

Bool space_has_object(Space *space, Id object_id) {
  if (!space || !space->objects) return FALSE;
  return set_has(space->objects, object_id);
}

Status space_add_object(Space *space, Id object_id) {
  if (!space || !space->objects) return ERROR;
  return set_add(space->objects, object_id);
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
    return FALSE;
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

char *space_get_n_description(Space *space, int n) {
  if (!space) {
    return NULL;
  }

  if (space_get_discovered(space) == TRUE) {
    return space->gdesc[n];
  } else if (n == 2) {
    return "  HID    ";
  } else {
    return "         ";
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
    return FALSE;
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
  Id idaux = NO_ID;
  int i = 0;
  char *gdesc[10];

  /* Error Control */
  if (!space) {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* 2. For each direction, print its link */
  idaux = space_get_north(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  /* 3. Print if there is an object in the space or not */
  fprintf(stdout, "---> %i object's in the space.\n", space_get_num_objects(space));

  /*
  if (space_get_object(space, object_get_id(space->objects_id[i]))) {
    fprintf(stdout, "---> Object in the space.\n");
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }*/

  /* 4. Print its descrption */
  for (i = 0; i < 5; i++) {
    strcpy(gdesc[i], space_get_description(space)[i]);
    fprintf(stdout, "%s\n", gdesc[i]);
  }

  return OK;
}