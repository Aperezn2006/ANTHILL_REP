#include "ray.h"

#include <stdlib.h>
#include <string.h>

#include "types.h"

struct Ray {
  int x, y;
  int speed;
  char image[WORD_SIZE];  // Stores the path to the image
  Direction direction;
  int is_active;
};

Ray* ray_create(int x, int y, Direction direction) {
  Ray* ray = malloc(sizeof(Ray));
  if (!ray) return NULL;

  ray->x = x;
  ray->y = y;
  ray->speed = 5;
  ray->direction = direction;
  ray->is_active = 1;

  // Set the image path manually
  strncpy(ray->image, "resources/ray.jpeg", WORD_SIZE - 1);
  ray->image[WORD_SIZE - 1] = '\0';  // Ensure null-termination

  return ray;
}

void ray_update(Ray* ray) {
  if (!ray || !ray->is_active) return;

  // Update ray position based on its direction
  switch (ray->direction) {
    case N:
      ray->y -= ray->speed;
      break;
    case S:
      ray->y += ray->speed;
      break;
    case E:
      ray->x += ray->speed;
      break;
    case W:
      ray->x -= ray->speed;
      break;
    default:
      ray->is_active = 0; // Deactivate ray with invalid direction
      return;
  }

  // Check if the ray is out of bounds
  if (ray->x < 0 || ray->x > 800 || ray->y < 0 || ray->y > 600) {
    ray->is_active = 0;
  }
}


void ray_destroy(Ray* ray) { free(ray); }

int ray_get_x(const Ray* ray) { return ray ? ray->x : 0; }

int ray_get_y(const Ray* ray) { return ray ? ray->y : 0; }

const char* ray_get_image(const Ray* ray) { return ray ? ray->image : NULL; }

int ray_is_active(const Ray* ray) {
  return ray && ray->is_active;  // Returns true if the ray is not NULL and is active
}
