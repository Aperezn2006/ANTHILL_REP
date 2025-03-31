/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Profesores PPROG, Beatriz, Arturo, Rubén, Ana
 * @version 1
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "types.h"

#define CMD_LENGHT 40

/* Comandos dentro del juego */
char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"m", "Move"},   {"t", "Take"},
                                   {"d", "Drop"},      {"a", "Attack"}, {"c", "Chat"}, {"i", "Inspect"}};

/**
 * @brief Command
 *
 * Esta estructura almacena toda la información relacionada con un comando.
 */
struct _Command {
  CommandCode code; /*!< Código del comando */
  char *obj;        /*!< Identificador del objeto */
  Status result;
};

/**
 * @brief Crea un nuevo comando
 *
 * Reserva memoria e inicializa la estructura Command.
 */
Command *command_create() {
  Command *newCommand = (Command *)malloc(sizeof(Command));
  if (!newCommand) {
    return NULL;
  }

  newCommand->code = NO_CMD;
  newCommand->obj = NULL; /*  Inicializamos obj */
  newCommand->result = OK;

  return newCommand;
}

/**
 * @brief Libera la memoria ocupada por un comando
 */
Status command_destroy(Command *command) {
  if (!command) {
    return ERROR;
  }

  if (command->obj) {
    free(command->obj);
  }

  free(command);
  return OK;
}

/**
 * @brief Establece el nombre del objeto en el comando
 */
Status command_set_obj(Command *c, const char *obj) {
  if (!c || !obj) {
    return ERROR;
  }

  if (c->obj) {
    free(c->obj);
  }

  c->obj = (char *)malloc(strlen(obj) + 1); /* Asignar memoria */
  if (!c->obj) {
    return ERROR;
  }

  strcpy(c->obj, obj); /* Copiar el nombre del objeto */

  return OK;
}

/**
 * @brief Obtiene el identificador del objeto del comando
 */
char *command_get_obj(Command *c) { return c ? c->obj : NULL; }

/**
 * @brief Establece el código del comando
 */
Status command_set_code(Command *command, CommandCode code) {
  if (!command) {
    return ERROR;
  }
  command->code = code;
  return OK;
}

/**
 * @brief Obtiene el código del comando
 */
CommandCode command_get_code(Command *command) { return command ? command->code : NO_CMD; }

/**
 * @brief Obtiene la entrada del usuario y asigna el código y el objeto
 * correspondiente
 */
Status command_get_user_input(Command *command) {
  char input[CMD_LENGHT] = "", *token = NULL, *objToken = NULL;
  int i;
  CommandCode cmd = UNKNOWN;

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

    objToken = strtok(NULL, " \n");
    command_set_obj(command, objToken ? objToken : "");

    return OK;
  }

  command_set_code(command, EXIT);
  return OK;
}

/*Manejo del result*/
Status command_get_result(Command *command) {
  if (!command) {
    return ERROR;
  }

  return command->result;
}

Status command_set_result(Command *command, Status result) {
  if (!command) {
    return ERROR;
  }

  command->result = result;

  return OK;
}
const char *command_to_str(CommandCode code) {
  if (code >= NO_CMD && code < N_CMD) {
    return cmd_to_str[code+1][CMDL]; 
  }
  return "UNKNOWN";
}
