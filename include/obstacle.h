#ifndef PLATFORM_H
#define PLATFORM_H
#include "types.h"

typedef struct _Obstacle Obstacle;

/* Creation and destruction */
/**
 * @brief It creates an obstacle
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param id the obstacle's id
 * @param x the x coordinate of the obstacle's position
 * @param y the x coordinate of the obstacle's position
 * @param width the obstacle's width
 * @param height the obstacle's height
 * @return a pointer to the obstacle
 */
Obstacle *obstacle_create(Id id, int x, int y, int width, int height);

/**
 * @brief It destroys an obstacle
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param p pointer to the obstacle
 */
void obstacle_destroy(Obstacle *p);

/* Accessors */
/**
 * @brief It get the x coordinate of the obstacle's position
 * @author Rubén, Arturo, Bea, Ana
 *
 * @param p a pointer to the link
 * @return the x coordinate
 */
int obstacle_get_x(Obstacle *p);

/**
 * @brief It get the y coordinate of the obstacle's position
 * @author Rubén, Arturo, Bea, Ana
 *
 * @param p a pointer to the link
 * @return the y coordinate
 */
int obstacle_get_y(Obstacle *p);

/**
 * @brief It get an obstacle's width
 * @author Rubén, Arturo, Bea, Ana
 *
 * @param p a pointer to the link
 * @return the width
 */
int obstacle_get_width(Obstacle *p);

/**
 * @brief It get an obstacle's height
 * @author Rubén, Arturo, Bea, Ana
 *
 * @param p a pointer to the link
 * @return the height
 */
int obstacle_get_height(Obstacle *p);

/**
 * @brief  It gets the obstacle's image
 * @author Rubén, Arturo, Bea, Ana
 *
 * @param obstacle a pointer to the obstacle
 * @return its image's path
 */
const char *obstacle_get_image(const Obstacle *obstacle);

/**
 * @brief It sets the obstacle's image
 * @author Rubén, Arturo, Bea, Ana
 *
 * @param obstacle a pointer to the obstacle
 * @param image its image's path
 * @return OK if everything went well, ERROR otherwise
 */
Status obstacle_set_image(Obstacle *obstacle, const char *image);

/* Collision check */

#endif
