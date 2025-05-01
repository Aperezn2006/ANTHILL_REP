/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @version 1
 * @date 11-02-2025
 */

#ifndef SPACE_H
#define SPACE_H

#include "object.h"
#include "obstacle.h"
#include "set.h"
#include "types.h"

typedef struct _Space Space;

/*Create & destroy*/
/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space *space_create(Id id);

/*Cosas de SDL2*/
Status space_add_obstacle(Space *space, Obstacle *p);

int space_get_num_obstacles(Space *space);

Obstacle *space_get_obstacle(Space *space, int index);

Status space_set_image(Space *space, const char *image);

const char *space_get_image(const Space *space);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space *space);

/*Manejo de id*/
/**
 * @brief It gets the id of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space *space);

/**
 * @brief It set the id of a space
 * @author Ruben, Ana, Arturo, Bea
 *
 * @param space a pointer to the space, Id of the space
 * @return Status, Ok if everything went well, ERROR if something happens
 */
Status space_set_id(Space *space, Id id);

/*Manejo de name*/
/**
 * @brief It gets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return a string with the name of the space
 */
const char *space_get_name(Space *space);

/**
 * @brief It sets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space *space, char *name);

/*Manejo de objects*/
/**
 * @brief It gets the object in the n position of the array
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param space a pointer to the space
 * @param n number of the array position where the desired object is
 * @return the object's id
 */
Id space_get_object_from_index(Space *space, int n);

/**
 * @brief It gets the number of objects in the space
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param space a pointer to the space
 * @return the number of objects
 */
int space_get_num_objects(Space *space);

/**
 * @brief It removes an object from the space
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param space a pointer to the space
 * @param object_id the id of the object to be removed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_remove_object(Space *space, Id object_id);

/**
 * @brief It checks whether the space has a specific object
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param space a pointer to the space
 * @param object_id the id of the object to check
 * @return TRUE if it has the object, FALSE otherwise, WRONG if error
 */
Bool space_has_object(Space *space, Id object_id);

/**
 * @brief It adds an object to the space
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param space a pointer to the space
 * @param object_id the id of the object to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_add_object(Space *space, Id object_id);

/**
 * @brief Adds a character to the space
 * @author Beatriz, Arturo, Rubén, Ana
 * @param space a pointer to the space
 * @param character_id the id of the character to add
 * @return OK if successful, ERROR otherwise
 */
Status space_add_character(Space *space, Id character_id);

/**
 * @brief Removes a character from the space
 * @author Beatriz, Arturo, Rubén, Ana
 * @param space a pointer to the space
 * @param character_id the id of the character to remove
 * @return OK if successful, ERROR otherwise
 */
Status space_remove_character(Space *space, Id character_id);

/**
 * @brief Checks whether the space has a specific character
 * @author Beatriz, Arturo, Rubén, Ana
 * @param space a pointer to the space
 * @param character_id the id of the character to check
 * @return TRUE if it has the character, FALSE otherwise
 */
Bool space_has_character(Space *space, Id character_id);

/**
 * @brief Gets the number of characters in the space
 * @author Beatriz, Arturo, Rubén, Ana
 * @param space a pointer to the space
 * @return the number of characters in the space, or -1 if error
 */
int space_get_num_characters(Space *space);

/**
 * @brief Gets a character id from the space by index
 * @author Beatriz, Arturo, Rubén, Ana
 * @param space a pointer to the space
 * @param index index of the character to retrieve
 * @return the id of the character at that index, or NO_ID on error
 */
Id space_get_character_from_index(Space *space, int index);

/*Manejo de gdesc*/
/**
 * @brief It gets the description of a space
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param space a pointer to the space
 * @return the graphical description, it is a char bidimensional
 */
char **space_get_description(Space *space);

/**
 * @brief It gets the graphical description of the space located in the n
 * position of the array, whether its hidden or not
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param space a pointer to the space
 * @param n the position of the graphical description to get
 * @return the n line of the graphical description, it is char one-dimension
 */
char *space_get_i_static_description(Space *space, int n);

/**
 * @brief It gets the graphical description of the space located in the n
 * position of the array, it its hidden it hids it
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param space a pointer to the space
 * @param n the position of the graphical description to get
 * @return the n line of the graphical description, it is char one-dimension
 */
char *space_get_i_dynamic_description(Space *space, int n);

/**
 * @brief It sets the graphical description of a space
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param space a pointer to the space
 * @param description the graphical description to set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_description(Space *space, char description[5][10]);

/*Manejo de zoom_description*/
/**
 * @brief It gets the graphical description of the space located in the n
 * position of the array, it its hidden it hids it
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param space a pointer to the space
 * @param n the position of the graphical description to get
 * @return the n line of the graphical zoom description, it is char one-dimension
 */
char *space_get_zoom_description_from_index(Space *space, int n);

/**
 * @brief It sets the graphical zoom description of a space
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param space a pointer to the space
 * @param description the graphical zoom description to set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_zoom_description(Space *space, char description[17][WORD_SIZE]);

/*Manejo de discovered*/
/**
 * @brief It gets whether the space is discovered or not
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param space a pointer to the space
 * @return TRUE if it's discovered, FALSE otherwise, WRONG if error
 */
Bool space_get_discovered(Space *space);

/**
 * @brief It sets whether the space is discovered or not
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param space a pointer to the space
 * @param discovered TRUE if it's discovered, FALSE otherwise
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_discovered(Space *space, Bool discovered);

/*Print*/
/**
 * @brief It prints the space information
 * @author Profesores PPROG
 *
 * 1. Print the id and the name of the space
 * 2. Print if there is an object in the space or not
 * 3. Print its descrption
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space *space);

#endif /* SPACE_H */
