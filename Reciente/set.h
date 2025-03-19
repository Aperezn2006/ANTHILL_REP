#ifndef SET_H_
#define SET_H_

#include "types.h"

typedef struct _Set Set;

/**
 * @brief It creates a set
 * @author RUbén
 *
 * @param id the identification number for the new set
 * @return a new set, initialized
 */
Set *set_create();

/**
 * @brief It destroys a set
 * @author RUbén
 *
 * @param set a pointer to the set that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_destroy(Set *set);

/**
 * @brief
 * @author RUbén
 *
 * @param set a pointer to the set that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_add(Set *set, Id id);

/**
 * @brief
 * @author Rubén
 *
 * @param set a pointer to the set that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_del(Set *set, Id id);

/**
 * @brief
 * @author RUbén
 *
 * @param set a pointer to the set that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Bool set_has(Set *set, Id id);

/**
 * @brief
 * @author Rubén
 *
 * @param set a pointer to the set that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
int set_get_size(Set *set);

/**
 * @brief
 * @author RUbén
 *
 * @param set a pointer to the set that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Id set_get_n(Set *set, int n);

/**
 * @brief
 * @author RUbén
 *
 * @param set a pointer to the set that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
void set_print(Set *set);
#endif