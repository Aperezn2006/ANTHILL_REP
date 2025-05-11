/**
 * @brief It defines the object module interface
 *
 * @file object.h
 * @author Beatriz, Arturo, Rubén, Ana
 * @version 2
 * @date 23-03-2024
 * @copyright GNU Public License
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "types.h"

typedef struct _Object Object;

/*Create & destroy*/
/**
 * @brief It creates a new object, allocating memory and initializing its members
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param id the identification number for the new object
 * @return a new object, initialized
 */
Object *object_create(Id id, Id location);

/**
 * @brief It destroys a object, freeing the allocated memory
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param object a pointer to the object that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_destroy(Object *object);

/*Management of id*/
/**
 * @brief It sets the id of a object
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param object a pointer to the object
 * @param id the id the object will have
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_id(Object *object, Id id);

/**
 * @brief It gets the id of a object
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param object a pointer to the object
 * @return the id of object
 */
Id object_get_id(Object *object);

/*Management of name*/
/**
 * @brief It sets the name of a object
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param object a pointer to the object
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_name(Object *object, char *name);

/**
 * @brief It gets the name of a object
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param object a pointer to the object
 * @return  a string with the name of the object
 */
const char *object_get_name(Object *object);

/*Management of desc*/
/**
 * @brief It sets the description of a object
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param object a pointer to the object
 * @param desc a string with the description to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_desc(Object *object, char *desc);

/**
 * @brief It gets the description of a object
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param object a pointer to the object
 * @return a string with the description of the object
 */
const char *object_get_desc(Object *object);

/*Management of inspected*/
/**
 * @brief It sets whether the object has been inspected or not
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param object a pointer to the object
 * @param inspected whether the object has been inspected or not
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_inspected(Object *object, Bool inspected);

/**
 * @brief It gets whether the object has been inspected or not
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param object a pointer to the object
 * @return TRUE if it has, FALSE otherwise
 */
Bool object_get_inspected(Object *object);
Status object_set_health(Object *object, int health);
int object_get_health(const Object *object);
Status object_set_movable(Object *object, Bool movable);
Bool object_is_movable(const Object *object);
Status object_set_dependency(Object *object, Id dependency);
Id object_get_dependency(const Object *object);
Status object_set_open(Object *object, Id link_id);
Id object_get_open(const Object *object);

/*Management of turn_amplifier*/
/**
 * @brief It sets the amount of turns the object increases
 * @author Ana
 *
 * @param object a pointer to the object
 * @param turn_amplifier the amount of turns the object increases
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_turn_amplifier(Object *object, int turn_amplifier);

/**
 * @brief It gets the amount of turns the object increases
 * @author Ana
 *
 * @param object a pointer to the object
 * @return the amount of turns the object increases
 */
int object_get_turn_amplifier(Object *object);
/**
 * @brief It set the uses an object has
 * @author Ana
 *
 * @param object a pointer to the object
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_uses(Object *object, int uses);
/**
 * @brief It gets the amount of uses the object has
 * @author Ana
 *
 * @param object a pointer to the object
 * @return the amount of uses the object has
 */
int object_get_uses(const Object *object);

/*Management of image*/
/**
 * @brief It sets the object's image_path
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param object a pointer to the object
 * @param image the path to the object's image
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_image(Object *object, char *image);

/**
 * @brief It gets the object's image_path
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param object a pointer to the object
 * @return the path to the object's image
 */
char *object_get_image(Object *object);

/*Management of position*/
/**
 * @brief It sets the object's position
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param object a pointer to the object
 * @param x the x coordinate of the object's position
 * @param y the y coordinate of the object's position
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_position(Object *object, int x, int y);

/**
 * @brief It gets the object's position
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param object a pointer to the object
 * @param x the x coordinate of the object's position
 * @param y the y coordinate of the object's position
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_get_position(Object *object, int *x, int *y);

int object_get_x(Object *object);
int object_get_y(Object *object);

/*Print*/
/**
 * @brief It prints the object information
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * This function shows the id and name of the object, the objects that surrounds it and whether it has an object or not.
 * @param object a pointer to the object
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_print(Object *object);

#endif
