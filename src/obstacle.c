#include "obstacle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

struct _Obstacle {
  Id id;
  int x, y;
  int width, height;
  char image[200];
};

Obstacle *obstacle_create(Id id, int x, int y, int width, int height) {
  Obstacle *p = (Obstacle *)malloc(sizeof(Obstacle));
  if (!p) return NULL;

  p->id = id;
  p->x = x;
  p->y = y;
  p->width = width;
  p->height = height;

  return p;
}

void obstacle_destroy(Obstacle *p) {
  if (p) free(p);
}

int obstacle_get_x(Obstacle *p) { return p ? p->x : 0; }
int obstacle_get_y(Obstacle *p) { return p ? p->y : 0; }
int obstacle_get_width(Obstacle *p) { return p ? p->width : 0; }
int obstacle_get_height(Obstacle *p) { return p ? p->height : 0; }

/* Set obstacle image */
Status obstacle_set_image(Obstacle *obstacle, const char *image) {
  if (!obstacle || !image) return ERROR;
  printf("\nImage now is %s\n\n", image);
  strncpy(obstacle->image, image, 200 - 1);
  obstacle->image[200 - 1] = '\0';
  return OK;
}

/* Get obstacle image */
const char *obstacle_get_image(const Obstacle *obstacle) {
  if (!obstacle) return NULL;
  printf(" \nObstacle image is %s\n\n", obstacle->image);
  return obstacle->image;
}
