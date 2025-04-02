/**
 * @brief It implements the inventory module
 *
 * @file inventory.c
 * @author Beatriz
 * @version 1
 * @date 11-02-2024
 */
#include "inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

struct _Inventory {
  Set *objects;
  int max_objects;
};

/*Create & destroy*/
/**
 * @brief It creates a new player, allocating memory and initializing its members
 */
Inventory *inventory_create(int max_objects) {
  Inventory *inventory = NULL;
  /*CdE*/
  if (max_objects <= 0) {
    return NULL;
  }

  if (!(inventory = (Inventory *)malloc(sizeof(Inventory)))) {
    return NULL;
  }

  inventory->objects = set_create();
  if (!inventory->objects) {
    free(inventory);
    return NULL;
  }

  inventory->max_objects = max_objects;

  return inventory;
}

/**
 * @brief It destroys an inventory, freeing the allocated memory
 */
Status inventory_destroy(Inventory *inventory) {
  /*CdE*/
  if (!inventory) {
    return ERROR;
  }

  if (inventory->objects) {
    set_destroy(inventory->objects);
  }

  free(inventory);
  return OK;
}

/*Management of objects*/
/**
 * @brief It adds an object to the inventory
 */
Status inventory_add_object(Inventory *inventory, Id object_id) {
  /*CdE*/
  if (!inventory || object_id == NO_ID) {
    return ERROR;
  }

  /*comprobar que no se ha alcanzado el max_objects*/
  if (set_get_size(inventory->objects) >= inventory->max_objects) {
    return ERROR;
  }

  if (set_add(inventory->objects, object_id) == ERROR) {
    return ERROR;
  }

  return OK;
}

/**
 * @brief It gets a pointer to the set of objects of a certain inventory
 */
Set *inventory_get_objects(Inventory *inventory) {
  if (!inventory) {
    return NULL;
  }

  return inventory->objects;
}

/**
 * @brief It removes an object from the inventory
 */
Status inventory_remove_object(Inventory *inventory, Id object_id) {
  /*CdE*/
  if (!inventory || object_id == NO_ID) {
    return ERROR;
  }

  if (set_del(inventory->objects, object_id) == ERROR) {
    return ERROR;
  }

  return OK;
}

/**
 * @brief  It checks whether the inventory has a certain object
 */
Bool inventory_has_object(Inventory *inventory, Id object_id) {
  /*CdE*/
  if (!inventory || object_id == NO_ID) {
    return FALSE;
  }

  if (set_has(inventory->objects, object_id) == TRUE) {
    return TRUE;
  }

  return FALSE;
}

/**
 * @brief It gets the number of objects that the inventory has
 */
int inventory_get_num_objects(Inventory *inventory) {
  /*CdE*/
  if (!inventory) {
    return -1;
  }

  return (set_get_size(inventory->objects));
}

/**
 * @brief It gets a certain object using its index in the array of objects in the object set
 */
Id inventory_get_object_by_index(Inventory *inventory, int n) {
  /*CdE*/
  if (!inventory) {
    return NO_ID;
  }

  return set_get_n(inventory->objects, n);
}

/**
 * @brief It gets the index of a certain object in the array of objects in the object set
 */
int inventory_get_object_index(Inventory *inventory, Id object_id) {
  Set *objects = NULL;
  int size, pos = 0, i;
  Id aux_object_id;
  /*CdE*/
  if (!inventory || object_id == NO_ID) {
    return -1;
  }

  if (!(objects = inventory_get_objects(inventory))) {
    return -1;
  }

  if ((size = inventory_get_num_objects(inventory)) <= 0) {
    return -1;
  }

  for (i = 0; i < size; i++) {
    aux_object_id = set_get_n(objects, i);

    if (aux_object_id == object_id) {
      return pos;
    }

    pos++;
  }

  return -1;
}

/**
 * @brief It sets the maximun amount of objects the inventory can hold
 */
Status inventory_set_max_objects(Inventory *inventory, int max) {
  /*CdE*/
  if (!inventory) {
    return ERROR;
  }

  inventory->max_objects = max;

  return OK;
}

/**
 * @brief It gets the maximun amount of objects the inventory can hold
 */
int inventory_get_max_objects(Inventory *inventory) {
  /*CdE*/
  if (!inventory) {
    return -1;
  }

  return inventory->max_objects;
}

/**
 * @brief It prints the inventory's information
 */
Status inventory_print(Inventory *inventory) {
  /*CdE*/
  if (!inventory) {
    return ERROR;
  }

  fprintf(stdout, "--> Inventory objects: \n");
  set_print(inventory->objects);

  return OK;
}