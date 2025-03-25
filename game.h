/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG, Rubén, Ana
 * @version 1
 * @date 11-02-2025
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

Id game_get_connection(Game *game, Id current_location, Direction direction);
Bool game_connection_is_open(Game *game, Id current_location, Direction direction);
Status game_add_link(Game *game, Id id, Id origin, Id destination, Direction dir, Bool open);

/*Create & destroy*/
/**
 * @brief It creates a new game a "restarts" everything
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return OK if everything goes well
 */
Status game_create(Game *game);

/**
 * @brief It frees the memory the game was ocuppying
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return OK if everything goes well
 */
Status game_destroy(Game *game);

/**
 * @brief It initializes the game
 * @author Rubén
 *
 * @param none
 * @return a pointer to the game
 */
Game *game_init();

/*Manejo de spaces*/
/**
 * @brief It gets an array of all the game's spaces
 * @author RUbén
 *
 * @param game a pointer to the game
 * @return an array of pointers to spaces
 */
Space **game_get_space_pointer(Game *game);

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
 * @brief It gets the name of the object located in the n position of the array of objects in the space and copies it to "name"
 * @author Ana
 *
 * @param game a pointer to the game
 * @param space_id the id of the space
 * @param n the desired position of the array
 * @param name where the name of the object will be copied to
 * @return Ok if everything went well, ERROR otherwise
 */
Status space_get_object_name(Game *game, Id space_id, int n, char *name);

/**
 * @brief It gets the id of the space in a certain position
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param positition the position of
 * @return the id of the space in a certain position
 */
Id game_get_space_id_at(Game *game, int position);

/*Manejo de player*/
Player **game_get_players(Game *game);

/**
 * @brief It creates a pointer to a certain space using its id
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param id the id of a certain space
 * @return a pointer to such space
 */
Player *game_get_player(Game *game);

/**
 * @brief It creates a pointer to a certain player using its index
 * @author Ana
 *
 * @param game a pointer to the game
 * @param n the index of the desired player
 * @return a pointer to such player
 */
Player *game_get_n_player(Game *game, int n);

/**
 * @brief It gets the player's location
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return the player's location
 */
Id game_get_player_location(Game *game);

/**
 * @brief It gets a certain player's location
 * @author Ana
 *
 * @param game a pointer to the game
 * @param n the index of the desired player
 * @return the player's location
 */
Id game_get_n_player_location(Game *game, int n);

/**
 * @brief It sets the player's locations
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param id the id of the space the player will go
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_player_location(Game *game, Id id);

/*Manejo de objects*/
/**
 * @brief It creates an array of pointers to the objects of the game
 * @author RUbén
 *
 * @param game a pointer to the game
 * @return an array of pointers to objects
 */
Object **game_get_object_pointer(Game *game);

Object *game_get_n_object(Game *game, int n);

/**
 * @brief It gets the location a certain object
 * @author Rubén
 *
 * @param game a pointer to the game
 * @param object_id the id of the objects
 * @return the id of the space where the object is
 */
Id game_get_object_location(Game *game, Id object_id);

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
 * @brief It gets a pointer to an object from its id
 * @author Ana
 *
 * @param game a pointer to the game
 * @return a pointer to the object
 */
Object *game_get_object_from_id(Game *game, Id object_id);

/**
 * @brief It gets a pointer to the object in a certain position of the game's array aof objects
 * @author Ana
 *
 * @param game a pointer to the game
 * @return a poiner to the object
 */
Object *game_get_object_from_position(Game *game, int n);

/**
 * @brief It gets an object's id from its name
 * @author Ana
 *
 * @param game a pointer to the game
 * @return the object's id
 */
Id game_get_object_id_from_name(Game *game, char *object_name);

Status game_get_string_of_objects_in_space(Game *game, Id space_id, char *objs);

/*Manejo de characters*/
/**
 * @brief It gets an array of pointers to the game's characters
 * @author Rubén
 *
 * @param game a pointer to the game
 * @return an array of pointer to characters
 */
Character **game_get_characters(Game *game);

/**
 * @brief It gets a pointer to a characters from its id
 * @author Rubén
 *
 * @param game a pointer to the game
 * @return a poibter to the character
 */
Character *game_get_character(Game *game, Id character_id);

/**
 * @brief It gets the location a certain object
 * @author Ana
 *
 * @param game a pointer to the game
 * @return the id of the space where the object is
 */
Id game_get_character_location(Game *game, Id character_id);

/**
 * @brief It sets the object's location
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param id the id of the space the object will go
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_set_character_location(Game *game, Id location, Id character_id);

/**
 * @brief It gets the character's id from its name
 * @author Ana
 *
 * @param game a pointer to the game
 * @return the character's id
 */
Id game_get_character_id_from_name(Game *game, char *name);

/**
 * @brief It gets the number of characters in the game
 * @author Ana
 *
 * @param game a pointer to the game
 * @return the number of characters
 */
int game_get_num_characters(Game *game);

/**
 * @brief It gets a pointer to the character in the n position of the game's array of characters
 * @author Ana
 *
 * @param game a pointer to the game
 * @return a pointer to the characters
 */
Character *game_get_n_character(Game *game, int n);

/**
 * @brief It gets the description of the character locate din a certain space
 * @author Ana
 *
 * @param game a pointer to the game
 * @return the graphical description of the character
 */
char *game_get_character_desc_at_space(Game *game, Id space_id);

/**
 * @brief It sets the character's location
 * @author Ana
 *
 * @param game a pointer to the game
 * @return Ok if everything went well, ERROR otherwise
 */
Status game_character_set_location(Game *game, Id character_id, Id character_location);

/*Manejo de n_objects*/
/**
 * @brief It gets the number of objects in the game
 * @author Rubén
 *
 * @param game a pointer to the game
 * @return the number of objects
 */
int game_get_num_objects(Game *game);

/**
 * @brief It increments the number of objects in the game
 * @author Rubén
 *
 * @param game a pointer to the game
 * @return nothing
 */
void game_increment_num_objects(Game *game);

/*Manejo de n_spaces*/
/**
 * @brief It gets the number of spaces in the game
 * @author RUbén
 *
 * @param game a pointer to the game
 * @return the number of spaces
 */
int game_get_num_spaces(Game *game);

/**
 * @brief It increments the number of spaces in the game
 * @author Rubén
 *
 * @param game a pointer to the game
 * @return nothing
 */
void game_increment_num_spaces(Game *game);

/*Manejo de n_characters*/
/**
 * @brief It gets the number of characters in the game
 * @author Rubén
 *
 * @param game a pointer to the game
 * @return the number of characters
 */
int game_get_num_characters(Game *game);

/**
 * @brief It increments the number of characters in the game
 * @author RUbén
 *
 * @param game a pointer to the game
 * @return nothing
 */
void game_increment_num_characters(Game *game);

/*Manejo de n_players*/
/**
 * @brief
 * @author
 *
 * @param
 * @return
 */
int game_get_num_players(Game *game);

/**
 * @brief
 * @author
 *
 * @param
 * @return
 */
void game_increment_num_players(Game *game);

/*Manejo de last_cmd*/
/**
 * @brief It gets the game's last command
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return a pointer to the last command
 */
Command *game_get_last_command(Game *game);

/**
 * @brief It sets the game's last command
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @param command a pointer to a command
 * @return OK if everything goes well
 */
Status game_set_last_command(Game *game, Command *command);

/*Manejo de message*/
/**
 * @brief It gets the game's last message
 * @author Ana
 *
 * @param game a pointer to the game
 * @return the game's last message
 */
char *game_get_message(Game *game);

/**
 * @brief It sets the game's last message
 * @author Ana
 *
 * @param game a pointer to the game
 * @return OK if everything went well, ERROR otherwise
 */
Status game_set_message(Game *game, char *message);

/*Manejo de object_desc*/
char *game_get_object_desc(Game *game);

Status game_set_object_desc(Game *game, char *object_desc);

/*Manejo de finished*/
/**
 * @brief It gets whether the game is finished or not
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return TRUE if it's finished, FALSE otherwise
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

/*Manejo de turn*/
Status game_set_turn(Game *game, int turn);

int game_get_turn(Game *game);

/*Print*/
/**
 * @brief It prints the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
void game_print(Game *game);

/*Adds*/
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
 * @brief It adds players to the game
 * @author Rubén
 *
 * @param game a pointer to the game
 * @param space a pointer to a player
 * @return OK if everything goes well
 */
Status game_add_player(Game *game, Player *player);

/**
 * @brief It adds objects to the game
 * @author Rubén
 *
 * @param game a pointer to the game
 * @param space a pointer to a object
 * @return OK if everything goes well
 */
Status game_add_object(Game *game, Object *object);

/**
 * @brief It adds a character to the game
 * @author Rubén
 *
 * @param game a pointer to the game
 * @return OK if everything goes well
 */
Status game_add_character(Game *game, Character *character);

/**
 * @brief gets north direction
 * @author Arturo
 *
 * @param game a pointer to the game
 * @param current_location id of actual location
 * @return the id
 */
Id Game_get_north(Game *game, Id current_location);

/**
 * @brief gets south direction
 * @author Arturo
 *
 * @param game a pointer to the game
 * @param current_location id of actual location
 * @return the id
 */
Id Game_get_south(Game *game, Id current_location);

/**
 * @brief gets east direction
 * @author Arturo
 *
 * @param game a pointer to the game
 * @param current_location id of actual location
 * @return the id
 */
Id Game_get_east(Game *game, Id current_location);

/**
 * @brief gets west direction
 * @author Arturo
 *
 * @param game a pointer to the game
 * @param current_location id of actual location
 * @return the id
 */
Id Game_get_west(Game *game, Id current_location);

/**
 * @brief Gets the neighboring location in a specified direction
 *
 * @param game A pointer to the Game structure
 * @param current_location The ID of the current location
 * @param d The direction in which to look for the neighbor
 * @return The ID of the neighboring location if found, otherwise NO_ID
 */
Id Game_get_neighbour(Game *game, Id current_location, Direction d);

#endif