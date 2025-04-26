/**
 * @brief It implements the object module
 *
 * @file object.c
 * @version 2
 * @date 23-03-2024
 */
#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief object
 *
 * This struct stores all the information of a object.
 */
struct _Object {
  Id id;                    /*!< Id number of the object, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the object */
  char desc[WORD_SIZE];     /*!< Description of the object */
  Bool inspected;           /*!< Whether the object has been inspected */
  int health;
  Bool movable;
  Id dependency;
  Id open;
  int turn_amplifier;
  char image[MAX_IMAGE]; /*!< Path to the object's image (for SDL2)*/
  int x, y;              /*!< Object's position*/
};

/*Create & destroy*/
/**
 * @brief It creates a new object, allocating memory and initializing its members
 */
Object *object_create(Id id, Id location) {
  Object *newobject = NULL;
  /*CdE*/
  if (id == NO_ID) {
    return NULL;
  }

  newobject = (Object *)malloc(sizeof(Object));
  if (newobject == NULL) {
    return NULL;
  }

  /* Initialization of an empty object */
  newobject->id = id;
  newobject->name[0] = '\0';
  newobject->desc[0] = '\0';
  newobject->inspected = 0;
  newobject->health = 0;
  newobject->movable = FALSE;
  newobject->dependency = NO_ID;
  newobject->open = NO_ID;
  newobject->image[0] = '\0';
  newobject->x = 0;
  newobject->y = 0;

  return newobject;
}

/**
 * @brief It destroys a object, freeing the allocated memory
 */
Status object_destroy(Object *object) {
  /*CdE*/
  if (!object) {
    return ERROR;
  }

  free(object);
  object = NULL;

  return OK;
}
Status object_set_health(Object *object, int health) {
  if (!object) return ERROR;
  object->health = health;
  return OK;
}

int object_get_health(const Object *object) {
  if (!object) return 0;
  return object->health;
}
Status object_set_movable(Object *object, Bool movable) {
  if (!object) return ERROR;
  object->movable = movable;
  return OK;
}

Bool object_is_movable(const Object *object) {
  if (!object) return FALSE;
  return object->movable;
}
Status object_set_dependency(Object *object, Id dependency) {
  if (!object) return ERROR;
  object->dependency = dependency;
  return OK;
}

Id object_get_dependency(const Object *object) {
  if (!object) return NO_ID;
  return object->dependency;
}
Status object_set_open(Object *object, Id link_id) {
  if (!object) return ERROR;
  object->open = link_id;
  return OK;
}

Id object_get_open(const Object *object) {
  if (!object) return NO_ID;
  return object->open;
}

/*Management of id*/
/**
 * @brief It sets the id of a object
 */
Status object_set_id(Object *object, Id id) {
  /*CdE*/
  if (!object || id == NO_ID) {
    return ERROR;
  }

  object->id = id;

  return OK;
}

/**
 * @brief It gets the id of a object
 */
Id object_get_id(Object *object) {
  /*CdE*/
  if (!object) {
    return NO_ID;
  }

  return object->id;
}

/*Management of name*/
/**
 * @brief It sets the name of a object
 */
Status object_set_name(Object *object, char *name) {
  /*CdE*/
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }

  return OK;
}

/**
 * @brief It gets the name of a object
 */
const char *object_get_name(Object *object) {
  /*CdE*/
  if (!object) {
    return NULL;
  }

  return object->name;
}

/*Management of desc*/
/**
 * @brief It sets the description of a object
 */
Status object_set_desc(Object *object, char *desc) {
  /*CdE*/
  if (!object || !desc) {
    return ERROR;
  }

  if (!strcpy(object->desc, desc)) {
    return ERROR;
  }

  return OK;
}

/**
 * @brief It gets the description of a object
 */
const char *object_get_desc(Object *object) {
  /*CdE*/
  if (!object) {
    return NULL;
  }

  return object->desc;
}

/*Management of inspected*/
/**
 * @brief It sets whether the object has been inspected or not
 */
Status object_set_inspected(Object *object, Bool inspected) {
  /*CdE*/
  if (!object) {
    return ERROR;
  }

  object->inspected = inspected;

  return OK;
}

/**
 * @brief It gets whether the object has been inspected or not
 */
Bool object_get_inspected(Object *object) {
  /*CdE*/
  if (!object) {
    return FALSE;
  }

  return object->inspected;
}

/*Management of image*/
/**
 * @brief It sets the object's image_path
 */
Status object_set_image(Object *object, char *image) {
  if (!object) {
    return ERROR;
  }

  strcpy(object->image, image);

  return OK;
}

/**
 * @brief It gets the object's image_path
 */
char *object_get_image(Object *object) {
  if (!object) {
    return NULL;
  }

  return object->image;
}

/*Management of position*/
/**
 * @brief It sets the object's position
 */
Status object_set_position(Object *object, int x, int y) {
  if (!object || (x < 0) || (y < 0)) {
    return ERROR;
  }

  object->x = x;
  object->y = y;

  return OK;
}

/**
 * @brief It gets the object's position
 */
Status object_get_position(Object *object, int *x, int *y) {
  if (!object) {
    return ERROR;
  }

  *x = object->x;
  *y = object->y;

  return OK;
}

int object_get_x(Object *object) {
  if (!object) {
    return ERROR;
  }

  return object->x;
}

int object_get_y(Object *object) {
  if (!object) {
    return ERROR;
  }

  return object->y;
}

/*Print*/
/**
 * @brief It prints the object information
 */
Status object_print(Object *object) {
  /*CdE*/
  if (!object) {
    return ERROR;
  }

  fprintf(stdout, "--> object (Id: %ld; Name: %s, Description: %s, Inspected: %d, Health: %d, Movable: %d, Dependency %ld, Open link: %ld)\n",
          object->id, object->name, object->desc, object->inspected, object->health, object->movable, object->dependency, object->open);

  return OK;
}