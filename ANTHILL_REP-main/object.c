/**
 * @brief It implements the object module
 *
 * @file object.c
 * @version 1
 * @date 11-02-2024
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
  char desc[WORD_SIZE];
  Bool inspected;
};

Object *object_create(Id id, Id location) {
  Object *newobject = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  newobject = (Object *)malloc(sizeof(Object));
  if (newobject == NULL) {
    return NULL;
  }

  /* Initialization of an empty object */
  newobject->id = id;
  newobject->name[0] = '\0';
  newobject->desc[0] = '\0';

  printf("Object created with ID: %ld, Location: %ld\n", id, location); /*  Debug statement */

  return newobject;
}

Status object_destroy(Object *object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  object = NULL;

  return OK;
}

/*  GET */

Id object_get_id(Object *object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

const char *object_get_name(Object *object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}

const char *object_get_desc(Object *object) {
  if (!object) {
    return NULL;
  }
  return object->desc;
}

/*  SET */

Status object_set_id(Object *object, Id id) {
  if (!object || id == NO_ID) {
    return ERROR;
  }
  object->id = id;
  return OK;
}

Status object_set_name(Object *object, char *name) {
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }

  return OK;
}

Status object_set_desc(Object *object, char *desc) {
  if (!object || !desc) {
    return ERROR;
  }

  if (!strcpy(object->desc, desc)) {
    return ERROR;
  }

  return OK;
}

/*Manejo de inspected*/
Status object_set_inspected(Object *object, Bool inspected) {
  if (!object) {
    return ERROR;
  }

  object->inspected = inspected;

  return OK;
}

Bool object_get_inspected(Object *object) {
  if (!object) {
    return FALSE;
  }

  return object->inspected;
}

Status object_print(Object *object) {
  /* Error Control */
  if (!object) {
    return ERROR;
  }

  /* Print the id, name, and location of the object */
  fprintf(stdout, "--> object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}