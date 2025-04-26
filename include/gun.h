#ifndef GUN_H
#define GUN_H

typedef struct _Gun Gun;  // Opaque type

typedef enum {
  GUN_TYPE_SINGLE,  
  GUN_TYPE_SPREAD,  
  GUN_TYPE_EXPLOSIVE
} GunType;

Gun *gun_create(GunType type);
void gun_destroy(Gun *gun);

int gun_get_damage(const Gun *gun);
int gun_get_speed(const Gun *gun);
GunType gun_get_type(const Gun *gun);

#endif
