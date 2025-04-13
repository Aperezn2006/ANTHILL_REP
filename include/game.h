/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG, Bea, Arturo, Rubén, Ana
 * @version 2
 * @date 10-03-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "command.h"
#include "link.h"
#include "object.h"
#include "player.h"
#include "space.h"
#include "types.h"

typedef struct _Game Game;

/*Create & destroy*/
/**
 * @brief It creates a new game a "restarts" everything
 * @author Profesores PPROG, Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_init(Game *game);

/**
 * @brief It frees the memory the game was occupying
 * @author Profesores PPROG, Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_destroy(Game *game);

/**
 * @brief It allocates memory for the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param none
 * @return a pointer to the game
 */
Game *game_alloc();

/*Management of spaces*/
/**
 * @brief It adds spaces to the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param space a pointer to a space
 * @return OK if everything goes well
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief It gives a pointer to the space located in a certain position of the array of spaces in the game
 * @author Ana
 *
 * @param game a pointer to the game
 * @param index the desired space's position in the array
 * @return a pointer to the desired space
 */
Space *game_get_space_from_index(Game *game, int index);

/**
 * @brief It creates a pointer to a certain space using its id
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param id the id of a certain space
 * @return a pointer to such space
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief It gets the name of the object located in a certain position of the array of objects in the space and copies it to "name"
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @param space_id the id of the space
 * @param index the desired position of the array
 * @param name where the name of the object will be copied to
 * @return Ok if everything went well, ERROR otherwise
 */
Status space_get_object_name_from_index(Game *game, Id space_id, int index, char *name);

/**
 * @brief It gets the id of the space in a certain position of the array of objects in the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param position the position of the space in the array
 * @return the id of the space in a certain position
 */
Id game_get_space_id_from_index(Game *game, int index);

/*Management of player*/
/**
 * @brief It adds a player to the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @param space a pointer to a player
 * @return OK if everything goes well
 */
Status game_add_player(Game *game, Player *player);

/**
 * @brief It creates a pointer to the current player
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param id the id of a certain space
 * @return a pointer to such space
 */
Player *game_get_player(Game *game);

/**
 * @brief It creates a pointer to the player located in a certain position of the array of players in the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @param n the index of the desired player
 * @return a pointer to such player
 */
Player *game_get_player_from_index(Game *game, int n);

/**
 * @brief It sets the player's location
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param id the id of the space the player will go
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief It gets the current player's location
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return the player's location
 */
Id game_get_player_location(Game *game);

/**
 * @brief It gets the location of the player located in a certain position of the array of players in the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @param index the index of the desired player
 * @return the player's location
 */
Id game_get_player_location_from_index(Game *game, int index);

/*Management of objects*/
/**
 * @brief It adds objects to the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @param space a pointer to a object
 * @return OK if everything goes well
 */
Status game_add_object(Game *game, Object *object);

/**
 * @brief It creates a pointer to the object located in a certain position of the array of objects in the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @param index the index of the desired object
 * @return a pointer to such object
 */
Object *game_get_object_from_index(Game *game, int index);

/**
 * @brief It gets a pointer to an object from its id
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return a pointer to the object
 */
Object *game_get_object_from_id(Game *game, Id object_id);

/**
 * @brief It sets the object's location
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param id the id of the space the object will go
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_object_location(Game *game, Id location, Id object_id);

/**
 * @brief It gets the location a certain object
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @param object_id the id of the objects
 * @return the id of the space where the object is
 */
Id game_get_object_location(Game *game, Id object_id);

/**
 * @brief It gets an object's id from its name
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return the object's id
 */
Id game_get_object_id_from_name(Game *game, char *object_name);

/**
 * @brief It makes a string with the names of all the objects in the space
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @param space_id the id of the desired space
 * @param objs the string where the names will be put into
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_get_string_of_objects_in_space(Game *game, Id space_id, char *objs);

/*Management of characters*/
/**
 * @brief It adds a character to the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_add_character(Game *game, Character *character);

/**
 * @brief It gets a pointer to a characters from its id
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return a pointer to the character
 */
Character *game_get_character(Game *game, Id character_id);

/**
 * @brief It gets a pointer to the character located in a certain position of the game's array of characters
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return a pointer to the characters
 */
Character *game_get_character_from_index(Game *game, int n);

/**
 * @brief It gets the location of a certain character
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return the id of the space where the object is
 */
Id game_get_character_location(Game *game, Id character_id);

/**
 * @brief It gets a character's id from its name
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return the character's id
 */
Id game_get_character_id_from_name(Game *game, char *name);

/**
 * @brief It gets the description of the character located in a certain space
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return the graphical description of the character
 */
char *game_get_character_desc_at_space(Game *game, Id space_id);

/*Management of links*/

/**
 * @brief It adds a link to the game
 * @author Rubén
 *
 * @param game a pointer to the game
 * @param link a pointer to the link
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_add_link(Game *game, Link *link);

/**
 * @brief It gives a pointer to the link located in a certain position of the array of links in the game
 * @author Ana
 *
 * @param game a pointer to the game
 * @param index the desired link's position in the array
 * @return a pointer to the desired link
 */
Link *game_get_link_from_index(Game *game, int index);

/**
 * @brief It gets the id of the space located north of the current_location
 * @author Arturo
 *
 * @param game a pointer to the game
 * @param current_location id of actual location
 * @return the id
 */
Id game_get_north(Game *game, Id current_location);

/**
 * @brief It gets the id of the space located south of the current_location
 * @author Arturo
 *
 * @param game a pointer to the game
 * @param current_location id of actual location
 * @return the id
 */
Id game_get_south(Game *game, Id current_location);

/**
 * @brief It gets the id of the space located east of the current_location
 * @author Arturo
 *
 * @param game a pointer to the game
 * @param current_location id of actual location
 * @return the id
 */
Id game_get_east(Game *game, Id current_location);

/**
 * @brief It gets the id of the space located west of the current_location
 * @author Arturo
 *
 * @param game a pointer to the game
 * @param current_location id of actual location
 * @return the id
 */
Id game_get_west(Game *game, Id current_location);

/**
 * @brief It gets the id of the space located on top of the current_location
 * @author Ana
 *
 * @param game a pointer to the game
 * @param current_location id of actual location
 * @return the id
 */
Id game_get_up(Game *game, Id current_location);

/**
 * @brief It gets the id of the space located below the current_location
 * @author Ana
 *
 * @param game a pointer to the game
 * @param current_location id of actual location
 * @return the id
 */
Id game_get_down(Game *game, Id current_location);

/**
 * @brief It gets a space's neighboring location in a specified direction
 * @author Arturo
 *
 * @param game A pointer to the Game structure
 * @param current_location The ID of the current location
 * @param direction The direction in which to look for the neighbor
 * @return The ID of the neighboring location if found, otherwise NO_ID
 */
Id game_get_neighbour(Game *game, Id current_location, Direction direction);

/**
 * @brief It gets whether the connection of a space in a certain direction is open
 *
 * @param game a pointer ti the game
 * @param current_location The ID of the current location
 * @param direction The direction in which to look for the neighbor
 * @return TRUE if the connection is open, FALSE if it isn't, WRONG if any errors were detected
 */
Bool game_connection_is_open(Game *game, Id current_location, Direction direction);

/*Management of n_objects*/
/**
 * @brief It gets the number of objects in the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return the number of objects
 */
int game_get_num_objects(Game *game);

/**
 * @brief It increments the number of objects in the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything went well
 */
Status game_increment_num_objects(Game *game);

/*Management of n_spaces*/
/**
 * @brief It gets the number of spaces in the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return the number of spaces
 */
int game_get_num_spaces(Game *game);

/**
 * @brief It increments the number of spaces in the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything went well
 */
Status game_increment_num_spaces(Game *game);

/*Management of n_characters*/
/**
 * @brief It gets the number of characters in the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return the number of characters
 */
int game_get_num_characters(Game *game);

/**
 * @brief It increments the number of characters in the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything went well
 */
Status game_increment_num_characters(Game *game);

/*Management of n_players*/
/**
 * @brief It gets the number of players in the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return the number of players in the game
 */
int game_get_num_players(Game *game);

/**
 * @brief It increments the number of players in the game
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything went well
 */
Status game_increment_num_players(Game *game);

/*Management of n_links*/
/**
 * @brief It gets the number of links in the game
 * @author Rubén
 *
 * @param game a pointer to the game
 * @return the number of links in the game
 */
int game_get_num_links(Game *game);

/**
 * @brief It increments the number of links in the game
 * @author Rubén
 *
 * @param game a pointer to the game
 * @return OK if everything went well
 */
Status game_increment_num_links(Game *game);

/*Management of last_cmd*/
/**
 * @brief It sets the game's last command for a certain turn/player
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param command a pointer to a command
 * @return OK if everything goes well
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief It gets the game's last command
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return a pointer to the last command
 */
Command *game_get_last_command(Game *game);

/*Management of message*/
/**
 * @brief It sets the game's last message
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything went well, ERROR otherwise
 */
Status game_set_message(Game *game, char *message);

/**
 * @brief It gets the las message of a certain player
 * @author Ana
 *
 * @param game a pointer to the game
 * @param index the certain player's index in the array
 * @return the desired player's last message
 */
char *game_get_message_from_index(Game *game, int index);

/**
 * @brief It gets the las message of the current player
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return the current player's last message
 */
char *game_get_message(Game *game);

/*Management of object_desc*/
/**
 * @brief It gets the description of a certain player's last inspected object
 * @author Ana
 *
 * @param game a pointer to the game
 * @param index the certain player's index in the array
 * @return the description of the last inspected object
 */
char *game_get_object_desc_from_index(Game *game, int index);

/**
 * @brief It gets the description of the current player's last inspected object
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return the description of the last inspected object
 */
char *game_get_object_desc(Game *game);

/**
 * @brief It sets the description of the last inspected object
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game
 * @param object_desc
 * @return OK if everything went well
 */
Status game_set_object_desc(Game *game, char *object_desc);

/*Management of finished*/
/**
 * @brief It gets whether the game is finished or not
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return TRUE if it's finished, FALSE if it isn't, WRONG if any errors were detected
 */
Bool game_get_finished(Game *game);

/**
 * @brief It sets whether the game is finished or not
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param finished a variable of type bool which determines if it's finished
 * (TRUE/FALSE)
 * @return OK if everything goes well
 */
Status game_set_finished(Game *game, Bool finished);

/*Management of turn*/
/**
 * @brief It sets the game's current turn
 * @author Ana
 *
 * @param game a pointer to the game
 * @param turn the current turn
 * @return OK if everything goes well
 */
Status game_set_turn(Game *game, int turn);

/**
 * @brief It gets the game's current turn
 * @author Ana
 *
 * @param game a pointer to the game
 * @return the game's current turn
 */
int game_get_turn(Game *game);

/*Management of inventory*/
/**
 * @brief It toggles the inventory's visualization
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_toggle_inventory_vis(Game *game);

/**
 * @brief It gets whether the inventory is beinf visualized or not
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return whether the inventory is beinf visualized or not
 */
Bool game_get_inventory_vis(Game *game);

/*Print*/
/**
 * @brief It prints the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
void game_print(Game *game);

#endif