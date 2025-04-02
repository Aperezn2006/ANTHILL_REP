/**
 * @brief It defines the set module interface
 *
 * @file set.h
 * @version 1.0
 * @date 11-02-2025
 */

#ifndef SET_H_
#define SET_H_

#include "types.h"

typedef struct _Set Set;

/**
 * @brief It creates a set
 * @author Rubén
 *
 * @return a new set, initialized
 */
Set *set_create();

/**
 * @brief It destroys a set
 * @author Rubén
 *
 * @param set a pointer to the set that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_destroy(Set *set);

/**
 * @brief It adds an element to the set
 * @author Rubén
 *
 * @param set a pointer to the set
 * @param id the id of the element to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_add(Set *set, Id id);

/**
 * @brief It deletes an element from the set
 * @author Rubén
 *
 * @param set a pointer to the set
 * @param id the id of the element to be deleted
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_del(Set *set, Id id);

/**
 * @brief It checks if the set contains an element
 * @author Rubén
 *
 * @param set a pointer to the set
 * @param id the id of the element to check
 * @return TRUE if the set contains the element, FALSE otherwise
 */
Bool set_has(Set *set, Id id);

/**
 * @brief It gets the size of the set
 * @author Rubén
 *
 * @param set a pointer to the set
 * @return the size of the set
 */
int set_get_size(Set *set);

/**
 * @brief It gets the element at a given position in the set
 * @author Rubén
 *
 * @param set a pointer to the set
 * @param n the position of the element to get
 * @return the id of the element at the given position
 */
Id set_get_n(Set *set, int n);

/**
 * @brief It prints the set
 * @author Rubén
 *
 * @param set a pointer to the set
 */
void set_print(Set *set);

#endif /* SET_H_ */