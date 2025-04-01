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
  Set *objs;
  int max_objs;
};

Inventory *inventory_create(int max_objs) {
  Inventory *inventory = NULL;

  if (max_objs <= 0) return NULL;

  if (!(inventory = (Inventory *)malloc(sizeof(Inventory)))) return NULL;

  inventory->objs = set_create();
  if (!inventory->objs) {
    free(inventory);
    return NULL;
  }

  inventory->max_objs = max_objs;

  return inventory;
}

Status inventory_destroy(Inventory *inventory) {
  if (!inventory) return ERROR;

  if (inventory->objs) {
    set_destroy(inventory->objs);
  }

  free(inventory);
  return OK;
}

Status inventory_add_object(Inventory *inventory, Id object_id) {
  if (!inventory) return ERROR;
  if (object_id == NO_ID) return ERROR;

  /*comprobar que no se ha alcanzado el max_objs*/
  if (set_get_size(inventory->objs) >= inventory->max_objs) return ERROR;

  if (set_add(inventory->objs, object_id) == ERROR) return ERROR;

  return OK;
}

Status inventory_remove_object(Inventory *inventory, Id object_id) {
  if (!inventory || object_id == NO_ID) return ERROR;

  if (set_del(inventory->objs, object_id) == ERROR) return ERROR;

  return OK;
}

Bool inventory_has_obj(Inventory *inventory, Id object_id) {
  if (!inventory) return FALSE;
  if (object_id == NO_ID) return FALSE;

  if (set_has(inventory->objs, object_id) == TRUE) {
    return TRUE;
  }

  return FALSE;
}

Set *inventory_get_objs(Inventory *inventory) {
  if (!inventory) return NULL;

  return inventory->objs;
}

Status inventory_set_max_objs(Inventory *inventory, int max) {
  if (!inventory) return ERROR;

  inventory->max_objs = max;

  return OK;
}

int inventory_get_max_objs(Inventory *inventory) {
  if (!inventory) return -1;

  return inventory->max_objs;
}

int inventory_get_num_objs(Inventory *inventory) {
  if (!inventory) return -1;

  return (set_get_size(inventory->objs));
}

Status inventory_print(Inventory *inventory) {
  if (!inventory) return ERROR;

  fprintf(stdout, "--> Inventory objects: \n");
  set_print(inventory->objs);

  return OK;
}

int get_obj_act_possition(Inventory *inventory, Id object_id) {
  Set *objs = NULL;
  int size, pos = 0, i;
  Id aux_object_id;

  if (!inventory) return -1;
  if (object_id == NO_ID) return -1;

  if (!(objs = inventory_get_objs(inventory))) return -1;

  if ((size = inventory_get_num_objs(inventory)) <= 0) return -1;

  for (i = 0; i < size; i++) {
    aux_object_id = set_get_n(objs, i);

    if (aux_object_id == object_id) {
      return pos;
    }

    pos++;
  }

  return -1;
}

Id inventory_get_obj_by_iteration(Inventory *inventory, int n) {
  if (!inventory) return NO_ID;

  return set_get_n(inventory->objs, n);
}

Status inventory_free(Inventory *inventory) {
  if (!inventory) return ERROR;
  inventory_destroy(inventory);
  return OK;
}