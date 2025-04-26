#ifndef PLATFORM_H
#define PLATFORM_H
#include "types.h"

typedef struct _Obstacle Obstacle;

/* Creation and destruction */
Obstacle *obstacle_create(Id id, int x, int y, int width, int height);
void obstacle_destroy(Obstacle *p);

/* Accessors */
int obstacle_get_x(Obstacle *p);
int obstacle_get_y(Obstacle *p);
int obstacle_get_width(Obstacle *p);
int obstacle_get_height(Obstacle *p);
const char *obstacle_get_image(const Obstacle *obstacle);
Status obstacle_set_image(Obstacle *obstacle, const char *image);

/* Collision check */

#endif
