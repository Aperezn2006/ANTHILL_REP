/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Profesores PPROG, Bea, Arturo, Rubén, Ana
 * @version 2
 * @date 12-03-2025
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2
#define N_CMD 17
#define N_CON 3

typedef enum { CMDS, CMDL } CommandType;

typedef enum { NO_CMD = -1, UNKNOWN, EXIT, MOVE, TAKE, DROP, ATTACK, CHAT, INSPECT, INVENTORY, USE, OPEN, LOAD, SAVE } CommandCode;

typedef enum { NO_DEST = -1, OVER, WITH } Connector;
typedef struct _Command Command;

/**
 * @brief It allocates memory for a new command and initializes its members
 * @author Profesores PPROG
 *
 * @param none
 * @return a pointer to the new command, or NULL if it goes wrong
 */
Command *command_create();

/**
 * @brief It frees the memory of a certain command
 * @author Profesores PPROG
 *
 * @param command a pointer to the command
 * @return OK if everything went well, ERROR otherwise
 */
Status command_destroy(Command *command);

/**
 * @brief It sets a certain command
 * @author Profesores PPROG
 *
 * @param command a pointer to the desired command
 * @param code a struct of a command
 * @return OK if everything goes well
 */
Status command_set_code(Command *command, CommandCode code);

/**
 * @brief It gets the code inside a command
 * @author Profesores PPROG
 *
 * @param command a pointer to the desired command
 * @return the code of the command
 */
CommandCode command_get_code(Command *command);

/**
 * @brief It sets the string that came after the command
 *
 * @param c a pointer to the desired command
 * @param word a pointer to the string
 * @return OK if everything goes well, ERROR otherwise
 */
Status command_set_word(Command *c, const char *word);

/**
 * @brief It gets the wordect associated with a command
 * @author Profesores PPROG
 *
 * @param command a pointer to the command
 * @return the word associated with the command
 */
char *command_get_word(Command *c);

Status command_set_connector(Command *command, Connector connector);
Connector command_get_connector(Command *command);
Status command_set_destiny(Command *c, const char *destiny);
char *command_get_destiny(Command *c);

/**
 * @brief It gets the user inputs and sets its command and word
 * @author Profesores PPROG
 *
 * @param command a pointer to the command
 * @return a new command with the inputed one set
 */
Status command_get_user_input(Command *command);

/**
 * @brief It sets wheter the command was succesful or not
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param command a pointer to the command
 * @param result the feedback that will be assigned to a certain command
 * @return OK if everything went well, ERROR otherwise
 */
Status command_set_result(Command *command, Status result);

/**
 * @brief It gets whether the command was successful or not
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param command a pointer to the command
 * @return OK if everything went well, ERROR otherwise
 */
Status command_get_result(Command *command);

/**
 * @brief It transforms a code into a string
 * @author Rubén
 *
 * @param code the desired code
 * @return the string that belongs to a certain command
 */
const char *command_to_str(CommandCode code);

#endif
