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
#include "ray.h"
#include "space.h"
#include "types.h"

typedef struct _Game Game;

/*Cosas de SDL2*/
Bool game_get_SDL(Game *game);

Id game_get_connection(Game *game, Id current_location, Direction direction);

Bool game_connection_is_open(Game *game, Id current_location, Direction direction);

Status game_add_link(Game *game, Link *link);

Link *game_get_link_by_id(Game *game, Id link_id);

Ray *game_get_ray(Game *game);

void game_set_ray(Game *game, Ray *ray);

void game_move_inventory_cursor(Game *game, int direction);

Status game_select_inventory_object(Game *game);

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
Status game_destroy(Game *game, Bool full_destruction);

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
 * @return a pointer to such player
 */
Player *game_get_current_player(Game *game);

/**
 * @brief It creates a pointer to a player using its id
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param id the id of a certain player
 * @return a pointer to such player
 */
Player *game_get_player(Game *game, Id id);

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
 * @brief It sets the player's location from an id
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param id the id of the space the player will go, and id of the player
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_player_location_from_id(Game *game, Id space_id, Id player_id);

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

/**
 * @brief It gets the id of a player by name
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @param name name of the player
 * @return the player's id
 */
Id game_get_player_id_from_name(Game *game, char *name);

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
Id game_get_object_id_from_name(Game *game, const char *object_name);

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
 * @brief Adds a character to the game and places them in the appropriate space
 * @author Bea, Arturo, Rubén, Ana
 * @param game Pointer to the game
 * @param character Pointer to the character to be added
 * @return OK if successful, ERROR otherwise
 */
Status game_add_character(Game *game, Character *character);

/**
 * @brief Retrieves a pointer to a character by ID
 * @author Bea, Arturo, Rubén, Ana
 * @param game Pointer to the game
 * @param character_id ID of the character
 * @return Pointer to the character, or NULL if not found
 */
Character *game_get_character(Game *game, Id character_id);

/**
 * @brief Gets a pointer to the character at the given index in the game's character array
 * @author Bea, Arturo, Rubén, Ana
 * @param game Pointer to the game
 * @param n Index of the character in the array
 * @return Pointer to the character, or NULL if index is invalid
 */
Character *game_get_character_from_index(Game *game, int n);

/**
 * @brief Retrieves the space ID where the character is currently located
 * @author Bea, Arturo, Rubén, Ana
 * @param game Pointer to the game
 * @param character_id ID of the character
 * @return ID of the space, or NO_ID if invalid
 */
Id game_get_character_location(Game *game, Id character_id);
/**
 * @brief Sets the location of a character in the game.

 *
 * @param game Pointer to the Game structure.
 * @param space_id The ID of the space where the character will be placed.
 * @param character_id The ID of the character whose location is being set.
 * @return Returns OK , or ERROR otherwise
 */

Status game_set_character_location(Game *game, Id space_id, Id character_id);

/**
 * @brief Retrieves the ID of a character given its name
 * @author Bea, Arturo, Rubén, Ana
 * @param game Pointer to the game
 * @param name Name of the character
 * @return Character ID, or NO_ID if not found
 */
Id game_get_character_id_from_name(Game *game, char *name);

/**
 * @brief Gets the description of the first character at a space (used for rendering or brief display)
 * @author Bea, Arturo, Rubén, Ana
 * @param game Pointer to the game
 * @param space_id ID of the space
 * @return Graphical description string, or NULL if none
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
 * @brief It gives the id of a link from a name
 * @author Ana
 *
 * @param game a pointer to the game
 * @param name the name of the link
 * @return the id of the link
 */
Id game_get_link_id_from_name(Game *game, char *name);

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
 * @brief It sets the current player's last message
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything went well, ERROR otherwise
 */
Status game_set_message(Game *game, char *message);

/**
 * @brief It sets a certain player's last message
 * @author Ana
 *
 * @param game a pointer to the game
 * @return OK if everything went well, ERROR otherwise
 */
Status game_set_message_from_index(Game *game, char *message, int index);

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
 * @brief It sets the description of the current player's last inspected object
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a poinnter to the game
 * @param object_desc the description of the object
 * @return OK if everything went well
 */
Status game_set_object_desc(Game *game, char *object_desc);

/**
 * @brief It sets the description of a certain player's last inspected object
 * @author Ana
 *
 * @param game a pointer to the game
 * @param object_desc the description of the object
 * @return OK if everything went well
 */
Status game_set_object_desc_from_index(Game *game, char *object_desc, int index);

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

/**
 * @brief Ir returns the index of the player whose turn it is
 * @author Ana
 *
 * @param game a pointer to the game
 * @return the index of the current player
 */
int game_get_player_index_from_turn(Game *game);

/**
 * @brief It increments the turn (if it exceeds the current number of players it goes back to 0)
 * @author Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_increment_turn(Game *game);

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

/**
 * @brief It toggles the zoom's visualization
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_toggle_zoom_vis(Game *game);

/**
 * @brief It gets whether the zoom is beinf visualized or not
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return whether the zoom is beinf visualized or not
 */
Bool game_get_zoom_vis(Game *game);

/**
 * @brief It updates the players health
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game, Object_id
 * @return OK if everything went well
 */
Status game_update_player_health(Game *game, Id object_id);

/**
 * @brief It updates the character health
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game, Object_id
 * @return OK if everything went well
 */
Status game_update_character_health(Game *game, Character *character, Id object_id);
/**
 * @brief It checks if an objects needs another object
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game, an object_id
 * @return TRUE if object can be used, FALSE if cant, WRONG if error
 */
Bool game_check_object_dependency(Game *game, Id object_id);
/**
 * @brief It moves an object in a direction
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game, an object_id, Id of current space, direction
 * @return Ok if everything went well
 */
Status game_move_object(Game *game, const char *object_name, Id current_location, Direction direction);

/*Misc*/
/**
 * @brief It figures out which game's category a certain id belongs to
 * @author Ana
 *
 * @param game a pointer to the game
 * @param id the desired id
 * @return the category in the Id_Type format
 */
Id_Type game_get_id_type(Game *game, Id id);
/**
 * @brief It tells if an object can be moved or not
 * @author Ana
 *
 * @param game a pointer to the game, id of an object
 * @param id
 * @return TRUE if can be moved
 */
Bool game_is_object_movable(Game *game, Id object_id);

/**
 * @brief It sets a link to open
 * @author Ana
 *
 * @param game a pointer to the game,
 * @param id of current space and a direction
 * @return Ok if everything went well
 */
Status game_set_link_open(Game *game, Id current_location, Direction direction);

/**
 * @brief It sets teams
 * @author Ana
 *
 * @param game a pointer to the game,
 * @param id of two players
 * @return Ok if everything went well
 */
Status game_handle_follow(Game *game, Id follower, Id leader);

/**
 * @brief It gets the team of a player
 * @author Ana
 *
 * @param game a pointer to the game,
 * @param id of a player
 * @return Ok if everything went well
 */
Set *game_get_team(const Game *game, Id player_id);
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
