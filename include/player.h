/**
 * @brief It defines the player module interface
 *
 * @file player.h
 * @author Beatriz, Arturo, Rubén, Ana
 * @version 1
 * @date 05/02/2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "gun.h"
#include "inventory.h"
#include "set.h"
#include "types.h"

typedef struct _Player Player;

/*Cosas de SDL2*/
Gun *player_get_gun(const Player *player);
void player_set_gun(Player *player, Gun *gun);
void player_set_direction(Player *player, Direction direction);
Direction player_get_direction(Player *player);

/*Create & destroy*/
/**
 * @brief It creates a new player, allocating memory and initializing its members
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param id the identification number for the new player
 * @return a new player, initialized
 */
Player *player_create(Id id);

/**
 * @brief It destroys a player, freeing the allocated memory
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_destroy(Player *player);

/*Manejo de id*/
/**
 * @brief It gets the id of a player
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @return the id of player
 */
Id player_get_id(Player *player);

/**
 * @brief It sets the id of a player
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @param id the id the player will have
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_id(Player *player, Id id);

/*Manejo de player_location*/
/**
 * @brief It gets the player's location
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @return the player's location
 */
Id player_get_location(Player *player);

/**
 * @brief It sets the player's location
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @param player_location the location the player will have
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_location(Player *player, Id player_location);

/*Manejo de name*/
/**
 * @brief It gets the name of a player
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @return a string with the name of the player
 */
const char *player_get_name(Player *player);

/**
 * @brief It sets the name of a player
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_name(Player *player, char *name);

/*Manejo de objects*/
/**
 * @brief It gets the object in the n position of the array
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @param n number of the array position where the desired object is
 * @return the object's id
 */
Id player_get_object_from_index(Player *player, int n);

/**
 * @brief It gets the number of objects the player is carrying
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @return the number of objects in the inventory
 */
int player_get_num_objects(Player *player);

/**
 * @brief It removes an object from the inventory
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @param object_id the id of the object to be removed
 * @return OK if everything went well, ERROR otherwise
 */
Status player_remove_object(Player *player, Id object_id);

/**
 * @brief It gets whether the player has an object or not
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @param object_id the id of the object to check
 * @return TRUE if the inventory has the object, FALSE otherwise
 */
Bool player_has_object(Player *player, Id object_id);

/**
 * @brief It adds an object to the player's inventory
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @param object_id the id of the object to be added
 * @return OK if everything went well, ERROR otherwise
 */
Status player_add_object(Player *player, Id object_id);

/*Manejo de health*/
/**
 * @brief It gets the health of the player
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @return the health of the player
 */
long player_get_health(Player *player);

/**
 * @brief It sets the player's health
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @param health the health the player will now have
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

/*Manejo de gdesc*/
/**
 * @brief It sets the graphical description of the player
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @param gdesc a string containing the graphical description
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_description(Player *player, char *gdesc);

/**
 * @brief It gets the graphical description of the player
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @return a string containing the graphical description of the player
 */
char *player_get_description(Player *player);

/*Manejo de inventory*/
/**
 * @brief It sets the maximum number of objects a player can carry
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @param max the new maximum number of objects
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_max_objs(Player *player, int max);

/**
 * @brief It gets a pointer to the player's inventory
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @return a pointer to a inventory
 */
Inventory *player_get_inventory(Player *player);

void player_set_inventory_cursor(Player *player, int cursor);
int player_get_inventory_cursor(Player *player);

/*Management of max_turns*/
/**
 * @brief It sets the max number of turns the player has
 * @author Ana
 *
 * @param player a pointer to the player
 * @param max_turns default number of turns the player has
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_max_turns(Player *player, int max_turns);

/**
 * @brief It gets the max number of turns the player has
 * @author Ana
 *
 * @param player a pointer to the player
 * @return the default number of turns the player has in a row
 */
int player_get_max_turns(Player *player);

/*Management of image*/
/**
 * @brief It sets the player's current image_path
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @param image the path to the player's image
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_image(Player *player, char *image);

/**
 * @brief It gets the player's current image_path
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @return the path to the player's image
 */
char *player_get_image(Player *player);

Status player_set_North_image(Player *player, const char *North_image);
const char *player_get_North_image(const Player *player);

Status player_set_East_image(Player *player, const char *East_image);
const char *player_get_East_image(const Player *player);

Status player_set_South_image(Player *player, const char *South_image);
const char *player_get_South_image(const Player *player);

Status player_set_West_image(Player *player, const char *West_image);
const char *player_get_West_image(const Player *player);

/*Management of position*/
/**
 * @brief It sets the player's position
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @param x the x coordinate of the player's position
 * @param y the y coordinate of the player's position
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_position(Player *player, int x, int y);

/**
 * @brief It gets the player's position
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param player a pointer to the player
 * @param x the x coordinate of the player's position
 * @param y the y coordinate of the player's position
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_get_position(Player *player, int *x, int *y);

/*Print*/
/**
 * @brief It prints the player information
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * This function shows the id and name of the player, the players that surrounds
 * it and whether it has an object or not.
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_print(Player *player);

#endif