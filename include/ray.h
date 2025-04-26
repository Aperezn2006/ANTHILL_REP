#ifndef RAY_H
#define RAY_H
#include "types.h"

typedef struct Ray Ray;

Ray* ray_create(int x, int y, Direction direction);
void ray_update(Ray* ray);
void ray_destroy(Ray* ray);
int ray_get_x(const Ray* ray);
int ray_get_y(const Ray* ray);
const char* ray_get_image(const Ray* ray);
int ray_is_active(const Ray *ray);

#endif