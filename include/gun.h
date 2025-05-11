#ifndef GUN_H
#define GUN_H

typedef struct _Gun Gun;

typedef enum { GUN_TYPE_SINGLE, GUN_TYPE_SPREAD, GUN_TYPE_EXPLOSIVE } GunType;

/**
 * @brief It creates a gun
 * @author Rubén
 *
 * @param type the type of gun desired
 * @return a pointer to the gun
 */
Gun *gun_create(GunType type);

/**
 * @brief It destroys a fun
 * @author Rubén
 *
 * @param gun a pointer to the gun
 */
void gun_destroy(Gun *gun);

/**
 * @brief It gets the gun's damage
 * @author Rubén
 *
 * @param gun a pointer to the gun
 * @return the damage
 */
int gun_get_damage(const Gun *gun);

/**
 * @brief It gets the gun's speed
 * @author Rubén
 *
 * @param gun a pointer to the gun
 * @return the speed
 */
int gun_get_speed(const Gun *gun);

/**
 * @brief It gets the gun's type
 * @author Rubén
 *
 * @param gun a pointer to the gun
 * @return the type
 */
GunType gun_get_type(const Gun *gun);

#endif
