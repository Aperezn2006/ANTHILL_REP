#include "obstacle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

#define MAX_SEGMENTS 10

typedef struct {
  int x1, y1;
  int x2, y2;
} Segment;

struct _obstacle {
  Id id;
  Segment segments[MAX_SEGMENTS];
  int segment_count;
  char image[200];
};

obstacle *obstacle_create(Id id) {
  obstacle *p = (obstacle *)malloc(sizeof(obstacle));
  if (!p) return NULL;

  p->id = id;
  p->segment_count = 0;
  p->image[0] = '\0';

  return p;
}

void obstacle_destroy(obstacle *p) {
  if (p) free(p);
}

Status obstacle_add_segment(obstacle *p, int x1, int y1, int x2, int y2) {
  if (!p || p->segment_count >= MAX_SEGMENTS) return ERROR;

  p->segments[p->segment_count].x1 = x1;
  p->segments[p->segment_count].y1 = y1;
  p->segments[p->segment_count].x2 = x2;
  p->segments[p->segment_count].y2 = y2;
  p->segment_count++;

  return OK;
}

int obstacle_get_segment_count(const obstacle *p) { return p ? p->segment_count : 0; }

Status obstacle_get_segment(const obstacle *p, int index, int *x1, int *y1, int *x2, int *y2) {
  if (!p || index < 0 || index >= p->segment_count) return ERROR;

  if (x1) *x1 = p->segments[index].x1;
  if (y1) *y1 = p->segments[index].y1;
  if (x2) *x2 = p->segments[index].x2;
  if (y2) *y2 = p->segments[index].y2;

  return OK;
}

/* Set obstacle image */
Status obstacle_set_image(obstacle *obstacle, const char *image) {
  if (!obstacle || !image) return ERROR;
  printf("\nImage now is %s\n\n", image);
  strncpy(obstacle->image, image, 200 - 1);
  obstacle->image[200 - 1] = '\0';
  return OK;
}

/* Get obstacle image */
const char *obstacle_get_image(const obstacle *obstacle) {
  if (!obstacle) return NULL;
  printf(" \nobstacle image is %s\n\n", obstacle->image);
  return obstacle->image;
}
