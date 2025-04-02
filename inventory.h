/**
 * @brief It defines the inventory interface
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

/**
 * @brief
 *
 */
typedef struct _Inventory Inventory;

/**
 * @brief
 *
 * @param max_objs
 * @return Inventory*
 */
Inventory *inventory_create(int max_objs);

/**
 * @brief
 *
 * @param inventory
 * @return Status
 */
Status inventory_destroy(Inventory *inventory);

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
 * @brief It removes an object from the inventory
 * @author Bea
 *
 * @param inventory a pointer to the inventory
 * @param object_id the id of the object to be removed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_remove_object(Inventory *inventory, Id object_id);

/**
 * @brief
 *
 * @param inventory
 * @param object_id
 * @return Bool
 */
Bool inventory_has_obj(Inventory *inventory, Id object_id);

/**
 * @brief
 *
 * @param inventory
 * @return Set*
 */
Set *inventory_get_objs(Inventory *inventory);

/**
 * @brief
 *
 * @param inventory
 * @param max
 * @return Status
 */
Status inventory_set_max_objs(Inventory *inventory, int max);

/**
 * @brief
 *
 * @param inventory
 * @return int
 */
int inventory_get_max_objs(Inventory *inventory);

/**
 * @brief
 *
 * @param inventory
 * @return int
 */
int inventory_get_num_objs(Inventory *inventory);

/**
 * @brief
 *
 * @param inventory
 * @param n
 * @return Id
 */
Id inventory_get_obj_by_iteration(Inventory *inventory, int n);

/**
 * @brief Get the obj act possition object
 *
 * @param inventory
 * @param object_id
 * @return int
 */
int get_obj_act_possition(Inventory *inventory, Id object_id); /*terminar*/

/**
 * @brief It prints the inventory information
 * @author Bea
 *
 * @param inventory a pointer to the inventory
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_print(Inventory *inventory);

/**
 * @brief It frees the memory allocated for the inventory
 * @author Bea
 *
 * @param inventory a pointer to the inventory
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_free(Inventory *inventory);

#endif
