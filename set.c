#include "set.h"

#include <stdio.h>
#include <stdlib.h>

struct _Set {
  Id *ids;
  int n_ids;
};

Set *set_create() {
  Set *newSet = (Set *)calloc(1, sizeof(Set));
  if (!newSet) {
    return NULL;
  }

  newSet->ids = NULL; /*Corrección*/

  /*newSet->ids = (Id *)malloc(1 * sizeof(Id));
  if (!newSet->ids) {
    free(newSet);
    return NULL;
  }
  newSet->n_ids = 0;*/

  return newSet;
}

Status set_destroy(Set *set) {
  if (!set) return ERROR;

  if (set->ids) {
    free(set->ids);
  }

  free(set);
  return OK;
}

Status set_add(Set *set, Id id) {
  Id *new_ids = NULL;

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

Status set_del(Set *set, Id id) {
  int i;

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

Bool set_has(Set *set, Id id) {
  int i;

  if (!set) {
    return FALSE;
  }

  for (i = 0; i < set->n_ids; i++) {
    if (set->ids[i] == id) return TRUE;
  }
  return FALSE;
}

int set_get_size(Set *set) {
  if (!set) return 0;
  return set->n_ids;
}

Id set_get_n(Set *set, int n) {
  if (!set || n < 0 || n >= set->n_ids) return NO_ID;
  return set->ids[n];
}

void set_print(Set *set) {
  int i;

  if (!set) {
    return;
  }

  printf("Set contains %d IDs:\n", set->n_ids);
  for (i = 0; i < set->n_ids; i++) {
    printf("%ld ", set->ids[i]); /*  Suponiendo que Id es un tipo numérico */
  }
  printf("\n");
}
