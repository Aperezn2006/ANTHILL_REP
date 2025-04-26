/**
 * @brief
 * @author Bea It defines the inventory interface
 *
 * @file inventory.h
 * @author Beatriz
 * @version 4.5
 * @date 11-02-2024
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "set.h"
#include "types.h"

typedef struct _Inventory Inventory;

/*Cosas de SDL2*/
int inventory_get_cursor(Inventory *inv);
void inventory_set_cursor(Inventory *inv, int cursor);

/*Create & destroy*/
/**
 * @brief It creates a new player, allocating memory and initializing its members
 * @author Bea
 *
 * @param max_objects the maximun number of objects the inventory can hold
 * @return a pointer to the inventory
 */
Inventory *inventory_create(int max_objects);

/**
 * @brief It destroys an inventory, freeing the allocated memory
 * @author Bea
 *
 * @param inventory a pointer to the inventory
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_destroy(Inventory *inventory);

/*Management of objects*/
/**
 * @brief It adds an object to the inventory
 * @author Bea
 *
 * @param inventory a pointer to the inventory
 * @param object_id the id of the object to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_add_object(Inventory *inventory, Id object_id);

/**
 * @brief It gets a pointer to the set of objects of a certain inventory
 * @author Bea
 *
 * @param inventory a pointer to the inventory
 * @return A pointer ot the set of objects
 */
Set *inventory_get_objects(Inventory *inventory);

/**
 * @brief It removes an object from the inventory
 * @author Bea
 *
 * @param inventory a pointer to the inventory
 * @param object_id the id of the object to be removed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_remove_object(Inventory *inventory, Id object_id);

/**
 * @brief It checks whether the inventory has a certain object
 * @author Bea
 *
 * @param inventory a pointer to the inventory
 * @param object_id
 * @return TRUE if the inventory does have it, FALSE if it doesn't, WRONG if any errors were detected
 */
Bool inventory_has_object(Inventory *inventory, Id object_id);

/**
 * @brief It gets the number of objects that the inventory has
 * @author Bea
 *
 * @param inventory a pointer to the inventory
 * @return the number of objects in the inventory
 */
int inventory_get_num_objects(Inventory *inventory);

/**
 * @brief It gets a certain object using its index in the array of objects in the object set
 * @author Bea
 *
 * @param inventory a pointer to the inventory
 * @param index
 * @return the id of the desired object
 */
Id inventory_get_object_by_index(Inventory *inventory, int index);

/**
 * @brief It gets the index of a certain object in the array of objects in the object set
 * @author Bea Get the obj act possition object
 *
 * @param inventory a pointer to the inventory
 * @param object_id
 * @return the index of the object in the set's array
 */
int inventory_get_object_index(Inventory *inventory, Id object_id); /*terminar*/

/*Management of max_objects*/
/**
 * @brief It sets the maximun amount of objects the inventory can hold
 * @author Bea
 *
 * @param inventory a pointer to the inventory
 * @param max
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_set_max_objects(Inventory *inventory, int max);

/**
 * @brief It gets the maximun amount of objects the inventory can hold
 * @author Bea
 *
 * @param inventory a pointer to the inventory
 * @return the inventory's capacity
 */
int inventory_get_max_objects(Inventory *inventory);

/*Print*/
/**
 * @brief It prints the inventory's information
 * @author Bea
 *
 * @param inventory a pointer to the inventory
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_print(Inventory *inventory);

#endif
