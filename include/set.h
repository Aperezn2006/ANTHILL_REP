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

/*Cosas de SDL2*/
int set_get_cursor(Set *set);
void set_set_cursor(Set *set, int cursor);

/*Create & destroy*/
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

/*Management of ids*/
/**
 * @brief It adds an element to the set
 * @author Rubén
 *
 * @param set a pointer to the set
 * @param id the id of the element to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_add_id(Set *set, Id id);

/**
 * @brief It deletes an element from the set
 * @author Rubén
 *
 * @param set a pointer to the set
 * @param id the id of the element to be deleted
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_remove_id(Set *set, Id id);

/**
 * @brief It checks if the set contains an element
 * @author Rubén
 *
 * @param set a pointer to the set
 * @param id the id of the element to check
 * @return TRUE if the set contains the element, FALSE if it doesn't, WRONG if any errors were detected
 */
Bool set_has_id(Set *set, Id id);

/**
 * @brief It gets the element at a given position in the set
 * @author Rubén
 *
 * @param set a pointer to the set
 * @param n the position of the element to get
 * @return the id of the element at the given position
 */
Id set_get_id_from_index(Set *set, int n);

/*Management of n_ids*/
/**
 * @brief It gets the size of the set
 * @author Rubén
 *
 * @param set a pointer to the set
 * @return the size of the set
 */
int set_get_num_ids(Set *set);

/*Print*/
/**
 * @brief It prints the set
 * @author Rubén
 *
 * @param set a pointer to the set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_print(Set *set);

#endif /* SET_H_ */