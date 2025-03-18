/**
 * @brief It defines the object module interface
 *
 * @file object.c
 * @author Rubén, Arturo, Bea, Ana
 * @version 1
 * @date 11-02-2024
 * @copyright GNU Public License
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "types.h"

typedef struct _Object Object;

/**
 * @brief It creates a new object, allocating memory and initializing its
 * members
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param id the identification number for the new object
 * @return a new object, initialized
 */
Object *object_create(Id id, Id location);

/**
 * @brief It destroys a object, freeing the allocated memory
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param object a pointer to the object that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_destroy(Object *object);

/*  GET */

/**
 * @brief It gets the id of a object
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param object a pointer to the object
 * @return the id of object
 */
Id object_get_id(Object *object);

/**
 * @brief It gets the name of a object
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param object a pointer to the object
 * @return  a string with the name of the object
 */
const char *object_get_name(Object *object);

/*  SET */

/**
 * @brief It sets the id of a object
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param object a pointer to the object
 * @param id the id the object will have
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_id(Object *object, Id id);

/**
 * @brief It sets the name of a object
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param object a pointer to the object
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_name(Object *object, char *name);

/**
 * @brief It prints the object information
 * @author Rubén, Arturo, Bea, Ana,
 *
 * This fucntion shows the id and name of the object, the objects that surrounds
 * it and wheter it has an object or not.
 * @param object a pointer to the object
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_print(Object *object);

#endif