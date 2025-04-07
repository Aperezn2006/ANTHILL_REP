/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Profesores PPROG, Beatriz, Arturo, Rubén, Ana
 * @version 2
 * @date 12-03-2025
 * @copyright GNU Public License
 */

#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define CMD_LENGHT 40

/* Commands inside the game */
char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"m", "Move"},    {"t", "Take"},
                                   {"d", "Drop"},      {"a", "Attack"}, {"c", "Chat"}, {"i", "Inspect"}, {"n", "Inventory"}};

/**
 * @brief Command
 *
 * This structure contains all of the information related to a command
 */
struct _Command {
  CommandCode code;     /*!< Command's code */
  char word[WORD_SIZE]; /*!< String input after code */
  Status result;        /*!< Command's result*/
};

/* Create & destroy */
/**
 * @brief It allocates memory for a new command and initializes its members
 */
Command *command_create() {
  Command *newCommand = (Command *)malloc(1 * sizeof(Command));
  /*CdE*/
  if (!newCommand) {
    return NULL;
  }

  /*Initialization*/
  newCommand->code = NO_CMD;
  newCommand->word[0] = '\0';
  newCommand->result = OK;

  return newCommand;
}

/**
 * @brief It frees the memory of a certain command
 */
Status command_destroy(Command *command) {
  /*CdE*/
  if (!command) {
    return ERROR;
  }

  free(command);

  return OK;
}

/* Management of code */
/**
 * @brief It sets a certain command
 */
Status command_set_code(Command *command, CommandCode code) {
  /*CdE*/
  if (!command) {
    return ERROR;
  }

  command->code = code;

  return OK;
}

/**
 * @brief It gets the code inside a command
 */
CommandCode command_get_code(Command *command) {
  /*CdE & get*/
  return command ? command->code : NO_CMD;
}

/* Management of word */
/**
 * @brief It sets the string that came after the command
 */
Status command_set_word(Command *c, const char *word) {
  /*CdE*/
  if (!c || !word) {
    return ERROR;
  }

  strcpy(c->word, word);

  return OK;
}

/**
 * @brief It gets the wordect associated with a command
 */
char *command_get_word(Command *c) {
  /*CdE & get*/
  return c ? c->word : NULL;
}

/* Management of result */
/**
 * @brief It sets wheter the command was succesful or not
 */
Status command_set_result(Command *command, Status result) {
  /*CdE*/
  if (!command) {
    return ERROR;
  }

  command->result = result;

  return OK;
}

/**
 * @brief It gets whether the command was successful or not
 */
Status command_get_result(Command *command) {
  /*CdE*/
  if (!command) {
    return ERROR;
  }

  return command->result;
}

/* Misc */
/**
 * @brief It gets the user inputs and sets its command and word
 */
Status command_get_user_input(Command *command) {
  char input[CMD_LENGHT] = "", *token = NULL, *wordToken = NULL;
  int i;
  CommandCode cmd = UNKNOWN;
  /*CdE*/
  if (!command) {
    return ERROR;
  }

  if (fgets(input, CMD_LENGHT, stdin)) {
    token = strtok(input, " \n");
    if (!token) {
      command_set_code(command, UNKNOWN);
      return OK;
    }

    cmd = UNKNOWN;

    for (i = 0; i < N_CMD; i++) {
      if (cmd_to_str[i][CMDS] && cmd_to_str[i][CMDL]) {
        if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL])) {
          cmd = i + NO_CMD;
          break;
        }
      }
    }

    command_set_code(command, cmd);

    wordToken = strtok(NULL, " \n");
    command_set_word(command, wordToken ? wordToken : "");

    return OK;
  }

  command_set_code(command, EXIT);
  return OK;
}

/**
 * @brief It transforms a code into a string
 */
const char *command_to_str(CommandCode code) {
  /*CdE*/
  if (code >= NO_CMD && code < N_CMD) {
    return cmd_to_str[code + 1][CMDL];
  }

  return "UNKNOWN";
}
