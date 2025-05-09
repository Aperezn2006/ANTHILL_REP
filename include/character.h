/**
 * @brief It defines the character module interface
 *
 * @file character.h
 * @author Beatriz, Arturo, Rubén, Ana
 * @version 0
 * @date 18/02/2025
 * @copyright GNU Public License
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

typedef struct _Character Character;

/*Management of blink_timer*/
/**
 * @brief It gets the blink_timer
 * @author Rubén
 *
 * @param character a pointer to the character
 * @return the blink_timer
 */
int character_get_blink_timer(Character *character);

/**
 * @brief It updates the blink_timer
 * @author Rubén
 *
 * @param character a pointer to the character
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_update_blink_timer(Character *character);

/*  Create y destroy */
/**
 * @brief It creates a new character, allocating memory and initializing its members
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param id the identification number for the new character
 * @return a new character, initialized
 */
Character *character_create(Id id);

/**
 * @brief It destroys a character, freeing the allocated memory
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_destroy(Character *character);

/*  Manejo de id */
/**
 * @brief It gets the id of a character
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @return the id of the character
 */
Id character_get_id(Character *character);

/**
 * @brief It sets the id of a character
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @param id the future id of the character
 * @return OK if everything went well, ERROR otherwise
 */
Status character_set_id(Character *character, Id id);

/*  Manejo de character_location */
/**
 * @brief It gets the id of the space the character is in
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @return The id of the character's location
 */
Id character_get_location(Character *character);

/**
 * @brief It sets the character's location
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @param character_location the id of the space the character will be located
 * @return OK if everything went well, ERROR otherwise
 */
Status character_set_location(Character *character, Id character_location);

/*  Manejo de name */
/**
 * @brief It gets the name of a character
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @return the name of the character
 */
char *character_get_name(Character *character);

/**
 * @brief It sets the name of a character
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @param name the future name of the character
 * @return OK if everything went well, ERROR otherwise
 */
Status character_set_name(Character *character, char *name);

/*  Manejo de gdesc */
/**
 * @brief It gets the description of a character
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @return the description of the character
 */
char *character_get_description(Character *character);

/**
 * @brief It sets the description of a character
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @param description the graphical description that will be asigned to the character
 * @return OK if everything went well, ERROR otherwise
 */
Status character_set_description(Character *character, char *description);

/*  Manejo de health */
/**
 * @brief It gets the health of a character
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @return the health of the character
 */
long character_get_health(Character *character);

/**
 * @brief It sets the health of a character
 * @author Beatriz, Arturo, Rubén, Ana
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
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @return TRUE if it is friendly, FALSE otherwise
 */
Bool character_get_friendly(Character *character);

/**
 * @brief It sets whether the character is friendly or not
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @param friendly whether the character is friendly or nor
 * @return OK if everything went well, ERROR otherwise
 */
Status character_set_friendly(Character *character, Bool friendly);

/*  Manejo de message */
/**
 * @brief It gets the message of a character
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @return the message of the character
 */
char *character_get_message(Character *character);

/**
 * @brief It sets the message of a character
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @param message the message the character will display when prompted
 * @return OK if everything went well, ERROR otherwise
 */
Status character_set_message(Character *character, char *message);

/*  Manejo de following */
/**
 * @brief It gets the id of the character that the current character is following
 * @author Arturo
 *
 * @param character A pointer to the character whose following id is to be retrieved
 * @return The id of the character being followed, or NO_ID if no character is being followed
 */
Id character_get_following(Character *character);

/**
 * @brief It sets the id of the character that the current character will follow
 * @author Arturo
 *
 * @param character A pointer to the character whose following id is to be set
 * @param id The id of the character to be followed
 * @return OK if the operation was successful, or ERROR if there was an issue
 */
Status character_set_following(Character *character, Id id);

/*Management of image*/
/**
 * @brief It cycles the current sprite through the available ones (3)
 * @author Ana
 *
 * @param character a pointer to the character
 * @return OK if the operation was successful, or ERROR if there was an issue
 */
Status character_toggle_curr_image_mode(Character *character);

/**
 * @brief It sets the character's current image_path
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @param image the path to the character's image
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_image(Character *character, char *image1, char *image2, char *image3);

/**
 * @brief It gets the character's current image_path
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @return the path to the character's image
 */
char *character_get_image(Character *character);

/**
 * @brief It sets the character's north image_path
 * @author Ana
 *
 * @param character a pointer to the character
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_north_image(Character *character, const char *north_image, int sprite);

/**
 * @brief It gets the character's north image_path
 * @author Ana
 *
 * @param character a pointer to the character
 * @return the path to the character's image
 */
const char *character_get_north_image(const Character *character, int sprite);

/**
 * @brief It sets the character's east image_path
 * @author Ana
 *
 * @param character a pointer to the character
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_east_image(Character *character, const char *east_image, int sprite);

/**
 * @brief It gets the character's eats image_path
 * @author Ana
 *
 * @param character a pointer to the character
 * @return the path to the character's image
 */
const char *character_get_east_image(const Character *character, int sprite);

/**
 * @brief It sets the character's south image_path
 * @author Ana
 *
 * @param character a pointer to the character
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_south_image(Character *character, const char *south_image, int sprite);

/**
 * @brief It gets the character's south image_path
 * @author Ana
 *
 * @param character a pointer to the character
 * @return the path to the character's image
 */
const char *character_get_south_image(const Character *character, int sprite);

/**
 * @brief It sets the character's west image_path
 * @author Ana
 *
 * @param character a pointer to the character
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_west_image(Character *character, const char *west_image, int sprite);

/**
 * @brief It gets the character's west image_path
 * @author Ana
 *
 * @param character a pointer to the character
 * @return the path to the character's image
 */
const char *character_get_west_image(const Character *character, int sprite);

/*Management of position*/
/**
 * @brief It sets the character's position
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @param x the x coordinate of the character's position
 * @param y the y coordinate of the character's position
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_position(Character *character, int x, int y);

/**
 * @brief It gets the character's position
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @param x the x coordinate of the character's position
 * @param y the y coordinate of the character's position
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_get_position(Character *character, int *x, int *y);

/**
 * @brief It gets the x coordinate of the character's position
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @return the x coordinate
 */
int character_get_x(Character *character);

/**
 * @brief It gets the y coordinate of the character's position
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @return the y coordinate
 */
int character_get_y(Character *character);

/*  Print */
/**
 * @brief It prints the character information
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param character a pointer to the character
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_print(Character *character);

#endif