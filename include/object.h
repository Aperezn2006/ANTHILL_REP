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