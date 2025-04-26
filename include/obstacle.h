#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "types.h"

typedef struct _obstacle obstacle;

/* Creation and destruction */
obstacle *obstacle_create(Id id);
void obstacle_destroy(obstacle *p);

/* Accessors */
Status obstacle_add_segment(obstacle *p, int x1, int y1, int x2, int y2);
int obstacle_get_segment_count(const obstacle *p);
Status obstacle_get_segment(const obstacle *p, int index, int *x1, int *y1, int *x2, int *y2);

const char *obstacle_get_image(const obstacle *obstacle);
Status obstacle_set_image(obstacle *obstacle, const char *image);

/* Collision check */

#endif
