/**
 * @brief It defines the link interface
 *
 * @file link.h
 * @author Rubén
 * @version 1.0
 * @date 11-02-2025
 */

#ifndef LINK_H_
#define LINK_H_

#include "types.h"

/**
 * @brief
 *
 */
typedef struct _Link Link;

/*Cosas de SDL2*/
Status link_set_image(Link *link, const char *image, int sprite);
const char *link_get_image(const Link *link);
int link_get_x(Link *link);
int link_get_y(Link *link);

/* Funciones de creación y destrucción */
/**
 * @brief It creates a new link
 *
 * @param id the id of the link
 * @param origin the origin id of the link
 * @param destination the destination id of the link
 * @param dir the direction of the link
 * @param open the status of the link (open or closed)
 * @return a pointer to the new link
 */
Link *link_create(Id id);

/**
 * @brief It destroys a link
 *
 * @param link a pointer to the link
 */
void link_destroy(Link *link);

/* Funciones de obtención y configuración */
/**
 * @brief It gets the id of a link
 *
 * @param link a pointer to the link
 * @return the id of the link
 */
Id link_get_id(Link *link);

Status link_set_id(Link *link, Id id);

/**
 * @brief It sets the name of a link
 *
 * @param link a pointer to the link
 * @param name the name to be set
 * @return OK if everything goes well, ERROR otherwise
 */
Status link_set_name(Link *link, const char *name);

/**
 * @brief It gets the name of a link
 *
 * @param link a pointer to the link
 * @return the name of the link
 */
const char *link_get_name(Link *link);

/**
 * @brief It sets the status of a link (open or closed)
 *
 * @param link a pointer to the link
 * @param open the status to be set
 * @return OK if everything goes well, ERROR otherwise
 */
Status link_set_open(Link *link, Bool open);

/**
 * @brief It gets the status of a link (open or closed)
 *
 * @param link a pointer to the link
 * @return the status of the link
 */
Bool link_get_open(Link *link);

/**
 * @brief It sets the direction of a link
 *
 * @param link a pointer to the link
 * @param dir the direction to be set
 * @return OK if everything goes well, ERROR otherwise
 */
Status link_set_direction(Link *link, Direction dir);

/**
 * @brief It gets the direction of a link
 *
 * @param link a pointer to the link
 * @return the direction of the link
 */
Direction link_get_direction(Link *link);

/* Obtener inicio y destino del enlace */
/**
 * @brief
 *
 * @param link a pointer to the link
 * @return
 */
Status link_set_start(Link *link, Id origin);

/**
 * @brief It gets the origin id of a link
 *
 * @param link a pointer to the link
 * @return the origin id of the link
 */
Id link_get_start(Link *link);

/**
 * @brief It gets the destination id of a link
 *
 * @param link a pointer to the link
 * @return the destination id of the link
 */
Id link_get_end(Link *link);

/**
 * @brief
 *
 * @param link
 * @param destination
 * @return Status
 */
Status link_set_end(Link *link, Id destination);

/* Imprimir enlace */
/**
 * @brief It prints the information of a link
 *
 * @param link a pointer to the link
 * @return OK if everything goes well, ERROR otherwise
 */
Status link_print(Link *link);

#endif
