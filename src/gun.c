#include "gun.h"

#include <stdlib.h>

struct _Gun {
  GunType type;
  int damage;
  int speed;
};

Gun *gun_create(GunType type) {
  Gun *gun = (Gun *)malloc(sizeof(Gun));
  if (!gun) return NULL;

  gun->type = type;
  switch (type) {
    case GUN_TYPE_SINGLE:
      gun->damage = 10;
      gun->speed = 5;
      break;
    case GUN_TYPE_SPREAD:
      gun->damage = 7;
      gun->speed = 4;
      break;
    case GUN_TYPE_EXPLOSIVE:
      gun->damage = 15;
      gun->speed = 3;
      break;
  }
  return gun;
}

void gun_destroy(Gun *gun) { free(gun); }

int gun_get_damage(const Gun *gun) { return gun ? gun->damage : 0; }

int gun_get_speed(const Gun *gun) { return gun ? gun->speed : 0; }

GunType gun_get_type(const Gun *gun) { return gun ? gun->type : GUN_TYPE_SINGLE; }
