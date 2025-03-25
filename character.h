/**
 * @brief It defines the character module interface
 *
 * @file character.h
 * @author
 * @version 0
 * @date 18/02/2025
 * @copyright GNU Public License
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

#define MAX_MESSAGE 100

typedef struct _Character Character;

/*  Create y destroy */
/**
 * @brief It creates a new character, allocating memory and initializing its members
 * @author Ana
 *
 * @param id the identification number for the new character
 * @return a new character, initialized
 */
Character *character_create(Id id);

/**
 * @brief It destroys a character, freeing the allocated memory
 * @author Ana
 *
 * @param character a pointer to the character that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_destroy(Character *character);

/*  Manejo de id */
/**
 * @brief It gets the id of a character
 * @author Ana
 *
 * @param character a pointer to the character
 * @return the id of the character
 */
Id character_get_id(Character *character);

/**
 * @brief It sets the id of a character
 * @author Ana
 *
 * @param character a pointer to the character
 * @param id the future id of the character
 * @return OK if everything went well, ERROR otherwise
 */
Status character_set_id(Character *character, Id id);

/*  Manejo de character_location */
/**
 * @brief It gets the id of the space the character is in
 * @author Ana
 *
 * @param character a pointer to the character
 * @return The id of the character's location
 */
Id character_get_location(Character *character);

/**
 * @brief It sets the character's location
 * @author Ana
 *
 * @param character a pointer to the character
 * @param character_location the id of the space the character will be located
 * @return OK if everything went well, ERROR otherwise
 */
Status character_set_location(Character *character, Id character_location);

/*  Manejo de name */
/**
 * @brief It gets the name of a character
 * @author Ana
 *
 * @param character a pointer to the character
 * @return the name of the character
 */
char *character_get_name(Character *character);

/**
 * @brief It sets the name of a character
 * @author Ana
 *
 * @param character a pointer to the character
 * @param name the future name of the character
 * @return OK if everything went well, ERROR otherwise
 */
Status character_set_name(Character *character, char *name);

/*  Manejo de gdesc */
/**
 * @brief It gets the description of a character
 * @author Ana
 *
 * @param character a pointer to the character
 * @return the description of the character
 */
char *character_get_description(Character *character);

/**
 * @brief It sets the description of a character
 * @author Ana
 *
 * @param character a pointer to the character
 * @param description the graphical description that will be asigned to the character
 * @return OK if everything went well, ERROR otherwise
 */
Status character_set_description(Character *character, char *description);

/*  Manejo de health */
/**
 * @brief It gets the health of a character
 * @author Ana
 *
 * @param character a pointer to the character
 * @return the health of the character
 */
long character_get_health(Character *character);

/**
 * @brief It sets the health of a character
 * @author Ana
 *
 * @param character a pointer to the character
 * @param health the amount of health that will be set
 * @return OK if everything went well, ERROR otherwise
 */
Status character_set_health(Character *character, long health);

/**
 * @brief It descreases the character's health by a certain amount
 * @author Rubén
 *
 * @param character a pointer to the character
 * @param damage the amount of health that will be decreased
 * @return OK if everything went well, ERROR otherwise
 */
Status character_decrease_health(Character *character, long damage);

/*  Manejo de friendly */
/**
 * @brief It gets whether the character is friendly or not
 * @author Ana
 *
 * @param character a pointer to the character
 * @return TRUE if it is friendly, FALSE otherwise
 */
Bool character_get_friendly(Character *character);

/**
 * @brief It sets whether the character is friendly or not
 * @author Ana
 *
 * @param character a pointer to the character
 * @param friendly whether the character is friendly or nor
 * @return OK if everything went well, ERROR otherwise
 */
Status character_set_friendly(Character *character, Bool friendly);

/*  Manejo de message */
/**
 * @brief It gets the message of a character
 * @author Ana
 *
 * @param character a pointer to the character
 * @return the message of the character
 */
char *character_get_message(Character *character);

/**
 * @brief It sets the message of a character
 * @author Ana
 *
 * @param character a pointer to the character
 * @param message the message the character will display when prompted
 * @return OK if everything went well, ERROR otherwise
 */
Status character_set_message(Character *character, char *message);

/*  Print */
/**
 * @brief It prints the character information
 * @author Ana
 *
 * This fucntion shows the id and name of the character, the characters that
 * surrounds it and wheter it has an object or not.
 * @param character a pointer to the character
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_print(Character *character);

#endif