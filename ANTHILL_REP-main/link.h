#ifndef LINK_H_
#define LINK_H_

#include "types.h"

#define MAX_LINKS 100

typedef struct _Link Link;

/* Funciones de creación y destrucción */
Link *link_create(Id id, Id origin, Id destination, Direction dir, Bool open);
void link_destroy(Link *link);

/* Funciones de obtención y configuración */
Id link_get_id(Link *link);
Status link_set_name(Link *link, const char *name);
const char *link_get_name(Link *link);
Status link_set_open(Link *link, Bool open);
Bool link_get_open(Link *link);
Status link_set_direction(Link *link, Direction dir);
Direction link_get_direction(Link *link);


/* Obtener inicio y destino del enlace */
Id link_get_start(Link *link);
Id link_get_end(Link *link);

/* Imprimir enlace */
Status link_print(Link *link);

#endif
