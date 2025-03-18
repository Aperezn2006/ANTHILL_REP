/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 * @version 1
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "object.h"
#include "set.h"
#include "types.h"

typedef struct _Space Space;

/*Create & destroy*/
/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space *space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space *space);

/*Manejo de id*/
/**
 * @brief It gets the id of a space
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space *space);

/*Manejo de name*/
/**
 * @brief It gets the name of a space
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param space a pointer to the space
 * @return  a string with the name of the space
 */
const char *space_get_name(Space *space);

/**
 * @brief It sets the name of a space
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space *space, char *name);

/*Manejo de north*/
/**
 * @brief It gets the id of the space located at the north
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the north
 */
Id space_get_north(Space *space);

/**
 * @brief It sets the id of the space located at the north
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the north
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_north(Space *space, Id id);

/*Manejo de south*/
/**
 * @brief It gets the id of the space located at the south
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the south
 */
Id space_get_south(Space *space);

/**
 * @brief It sets the id of the space located at the south
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the south
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_south(Space *space, Id id);

/*Manejo de east*/
/**
 * @brief It gets the id of the space located at the east
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the east
 */
Id space_get_east(Space *space);

/**
 * @brief It sets the id of the space located at the east
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the east
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_east(Space *space, Id id);

/*Manejo de west*/
/**
 * @brief It gets the id of the space located at the west
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the west
 */
Id space_get_west(Space *space);

/**
 * @brief It sets the id of the space located at the west
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the west
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_west(Space *space, Id id);

/*Manejo de objects*/
/**
 * @brief It gets whether the space has an object or not
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param space a pointer to the space
 * @return a boolean, specifying if in the space there is an object (TRUE) or
 * not (FALSE)
 */
Id space_get_i_object(Space *space, int n);

/**
 * @brief It gets the number of objects in the game
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param space a pointer to the space
 * @return the number of objects
 */
int space_get_num_objects(Space *space);

/**
 * @brief It sets whether the space has an object or not
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * @param space a pointer to the space
 * @param value a boolean, specifying if in the space there is an object (TRUE)
 * or not (FALSE)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_object(Space *space, Id object_id);

/**
 * @brief It adds an object to the space
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_add_object(Space *space, Id object_id);

/**
 * @brief It removes an object from the space
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_remove_object(Space *space, Id object_id);

/**
 * @brief It checks whether the space has any objects
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param space a pointer to the space
 * @return TRUE if it has any, FALSE otherwise
 */
Bool space_has_object(Space *space, Id object_id);

/**
 * @brief It adds an object to the space
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_add_object(Space *space, Id object_id);

/*Manejo de character_id*/
/**
 * @brief It gets the character in the space
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param space a pointer to the space
 * @return the id of the character
 */
Id space_get_character(Space *space);

/**
 * @brief It sets the character in the space
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_character(Space *space, Id character_id);

/**
 * @brief It gets whether the player is in the space
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param space a pointer to the space
 * @return TRUE if it is, ERROR otherwise
 */
Bool space_has_character(Space *space, Id character_id);

/**
 * @brief It removes the character from the space
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_remove_character(Space *space);

/*Manejo de gdesc*/
/**
 * @brief It gets the description of a space
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param space a pointer to the space
 * @return the graphical description
 */
char **space_get_description(Space *space);

/**
 * @brief It gets the grpahical description of the space located in the n postion of the array
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param space a pointer to the space
 * @return the n line of the graphical description
 */
char *space_get_i_description(Space *space, int n);

/**
 * @brief It sets the characters descrptions
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_description(Space *space, char description[5][10]);

/*Manejo de discovered*/
/**
 * @brief It gets whether the space is discovered or not
 * @author
 *
 * @param space a pointer to the space
 * @return TRUE if it's discovered, FALSE otherwise
 */
Bool space_get_discovered(Space *space);

/**
 * @brief It gets whether the space is discovered or not
 * @author
 *
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_discovered(Space *space, Bool discovered);

/*Print*/
/**
 * @brief It prints the space information
 * @author Rubén, Arturo, Bea, Ana, Profesores PPROG
 *
 * This fucntion shows the id and name of the space, the spaces that surrounds
 * it and wheter it has an object or not.
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space *space);

#endif