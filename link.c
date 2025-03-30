#include "link.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Link {
  Id id_link;
  char name[WORD_SIZE + 1];
  Id origin;
  Id destination;
  Bool open;
  Direction direction;
};

Link *link_create(Id id, Direction dir) {
  Link *newlink = NULL;

  if (id == NO_ID) {
    return NULL;
  }

  newlink = (Link *)malloc(sizeof(Link));
  if (!newlink) {
    return NULL;
  }

  newlink->id_link = id;
  newlink->origin = NO_ID;
  newlink->destination = NO_ID;
  newlink->open = FALSE;
  newlink->direction = dir;
  newlink->name[0] = '\0';

  return newlink;
}

void link_destroy(Link *link) {
  if (!link) {
    return;
  }
  free(link);
}

Id link_get_id(Link *link) {
  if (!link) {
    return ERROR;
  }
  return link->id_link;
}

Status link_set_name(Link *link, const char *name) {
  if (!link || !name) {
    return ERROR;
  }
  strncpy(link->name, name, WORD_SIZE);
  link->name[WORD_SIZE] = '\0';
  return OK;
}

const char *link_get_name(Link *link) {
  if (!link) {
    return NULL;
  }
  return link->name;
}

Status link_set_open(Link *link, Bool open) {
  if (!link) {
    return ERROR;
  }
  link->open = open;
  return OK;
}

Bool link_get_open(Link *link) {
  if (!link) {
    return FALSE;
  }

  return link->open;
}

Status link_set_direction(Link *link, Direction dir) {
  if (!link) {
    return ERROR;
  }
  link->direction = dir;
  return OK;
}

Direction link_get_direction(Link *link) {
  if (!link) {
    return N;
  }
  return link->direction;
}

Status link_set_start(Link *link, Id origin) {
  if (!link) {
    return ERROR;
  }

  link->origin = origin;

  return OK;
}

Id link_get_start(Link *link) {
  if (!link) {
    return NO_ID;
  }
  return link->origin;
}

Status link_set_end(Link *link, Id destination) {
  if (!link) {
    return ERROR;
  }

  link->destination = destination;

  return OK;
}

Id link_get_end(Link *link) {
  if (!link) {
    return NO_ID;
  }
  return link->destination;
}

Status link_print(Link *link) {
  if (!link) {
    return ERROR;
  }

  printf("Link ID: %ld, Name: %s, Origin: %ld, Destination: %ld, Direction: %d, Open: %s\n", link->id_link, link->name, link->origin,
         link->destination, link->direction, link->open ? "TRUE" : "FALSE");

  return OK;
}
