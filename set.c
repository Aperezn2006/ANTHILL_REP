#include "set.h"

#include <stdio.h>
#include <stdlib.h>

struct _Set {
  Id *ids;   /*!< Ids in the game */
  int n_ids; /*!< Number of ids in the game */
};

/*Create & destroy*/
/**
 * @brief It creates a set
 */
Set *set_create() {
  Set *newSet = (Set *)calloc(1, sizeof(Set));
  /*CdE*/
  if (!newSet) {
    return NULL;
  }

  newSet->ids = NULL;

  return newSet;
}

/**
 * @brief It destroys a set
 */
Status set_destroy(Set *set) {
  /*CdE*/
  if (!set) {
    return ERROR;
  }

  if (set->ids) {
    free(set->ids);
  }

  free(set);
  return OK;
}

/*Management of ids*/
/**
 * @brief It adds an element to the set
 */
Status set_add_id(Set *set, Id id) {
  Id *new_ids = NULL;
  /*CdE*/
  if (!set || id == NO_ID) {
    return ERROR;
  }

  new_ids = (Id *)realloc(set->ids, (set->n_ids + 1) * sizeof(Id));
  if (!new_ids) {
    return ERROR; /*  Si realloc falla, no modificamos el array */
  }

  set->ids = new_ids;
  set->ids[set->n_ids] = id;
  set->n_ids++;

  return OK;
}

/**
 * @brief It deletes an element from the set
 */
Status set_remove_id(Set *set, Id id) {
  int i;
  /*CdE*/
  if (!set || set->n_ids == 0) {
    return ERROR;
  }

  for (i = 0; i < set->n_ids; i++) {
    if (set->ids[i] == id) {
      set->ids[i] = set->ids[set->n_ids - 1]; /*  Mover el último para evitar huecos */
      set->n_ids--;
      return OK;
    }
  }
  return ERROR;
}

/**
 * @brief It checks if the set contains an element
 */
Bool set_has_id(Set *set, Id id) {
  int i;
  /*CdE*/
  if (!set) {
    return WRONG;
  }

  for (i = 0; i < set->n_ids; i++) {
    if (set->ids[i] == id) return TRUE;
  }

  return FALSE;
}

/**
 * @brief It gets the element at a given position in the set
 */
Id set_get_id_from_index(Set *set, int n) {
  /*CdE*/
  if (!set || n < 0 || n >= set->n_ids) {
    return NO_ID;
  }
  return set->ids[n];
}

/*Management of n_ids*/
/**
 * @brief It gets the size of the set
 */
int set_get_num_ids(Set *set) {
  /*CdE*/
  if (!set) {
    return 0;
  }
  return set->n_ids;
}

/*Print*/
/**
 * @brief It prints the set
 */
void set_print(Set *set) {
  int i;
  /*CdE*/
  if (!set) {
    return;
  }

  printf("Set contains %d IDs:\n", set->n_ids);
  for (i = 0; i < set->n_ids; i++) {
    printf("%ld ", set->ids[i]); /*  Suponiendo que Id es un tipo numérico */
  }
  printf("\n");
}
