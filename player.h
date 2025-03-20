/**
 * @brief It defines the player module interface
 *
 * @file player.h
 * @author Ana
 * @version 1
 * @date 05/02/2025
 * @copyright GNU Public License
 */

/*TAD vinculado al jugador de la aventura y que describe la
información relacionada con el estado del protagonista (ubicación, objetos que
tiene, puntos de vida, etc.).*/

#ifndef PLAYER_H_
#define PLAYER_H_

#include "types.h"

typedef struct _Player Player;

/*Create & destroy*/
/**
 * @brief It creates a new player, allocating memory and initializing its
 * members
 * @author Ana
 *
 * @param id the identification number for the new player
 * @return a new player, initialized
 */
Player *player_create(Id id);

/**
 * @brief It destroys a player, freeing the allocated memory
 * @author Ana
 *
 * @param player a pointer to the player that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_destroy(Player *player);

/*Manejo de id*/
/**
 * @brief It gets the id of a player
 * @author Ana
 *
 * @param player a pointer to the player
 * @return the id of player
 */
Id player_get_id(Player *player);

/**
 * @brief It sets the id of a player
 * @author Ana
 *
 * @param object a pointer to the player
 * @param id the id the player will have
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_id(Player *player, Id id);

/*Manejo de player_location*/
/**
 * @brief It gets the player's location
 * @author
 *
 * @param player a pointer to the player
 * @return the player's location
 */
Id player_get_location(Player *player);

/**
 * @brief It sets the player's location
 * @author
 *
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_location(Player *player, Id player_location);

/*Manejo de name*/
/**
 * @brief It gets the name of a player
 * @author Ana
 *
 * @param player a pointer to the player
 * @return  a string with the name of the player
 */
const char *player_get_name(Player *player);

/**
 * @brief It sets the name of a player
 * @author Ana
 *
 * @param player a pointer to the player
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_name(Player *player, char *name);

/*Manejo de objects*/
/**
 * @brief It gets the object in the n position of the array
 * @author
 *
 * @param space a pointer to the space
 * @param n number of the array position where the desired object is
 * @return the object's id
 */
Id player_get_n_object(Player *player, int n);

/**
 * @brief It gets the number of objects the player is carrying
 * @author Ana
 *
 * @param space a pointer to the space
 * @return the number of objects in the inventory
 */
int player_get_num_objects(Player *player);

/**
 * @brief It removes an object from the inventory
 * @author Ana
 *
 * @param space a pointer to the space
 * @return OK if everything went well, ERROR otherwise
 */
Status player_remove_object(Player *player, Id object_id);

/**
 * @brief It gets whether the player has any objects or not
 * @author Ana
 *
 * @param space a pointer to the space
 * @return TRUE if the inventory isn't empty, FALSE otherwise
 */
Bool player_has_object(Player *player, Id object_id);

/**
 * @brief It adds an object to the player's inventory
 * @author Ana
 *
 * @param space a pointer to the space
 * @return OK if everything went well, ERROR otherwise
 */
Status player_add_object(Player *player, Id object_id);

/*Manejo de health*/
/**
 * @brief It gets whether the player has an object or not
 * @author Ana
 *
 * @param player a pointer to the player
 * @return the health of the player
 */
long player_get_health(Player *player);

/**
 * @brief It sets the player's health
 * @author Ana
 *
 * @param player a pointer to the player
 * @param health the health the player will now ahve
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_health(Player *player, long health);

/**
 * @brief It decreases the player's health
 * @author Rubén
 *
 * @param player a pointer to the player
 * @param damage the amount of health that will be decreased
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_decrease_health(Player *player, long damage);

/*Print*/
/**
 * @brief It prints the player information
 * @author Ana
 *
 * This fucntion shows the id and name of the player, the players that surrounds
 * it and wheter it has an object or not.
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_print(Player *player);

#endif