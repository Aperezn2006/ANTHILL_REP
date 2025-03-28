/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Profesores PPROG, Rubén, Ana
 * @version 1
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

/**
   Private functions
*/

/**
 * @brief It waits for a known action
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return OK always
 */
Status game_actions_unknown(Game *game);

/**
 * @brief It allows for the user to exit the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return OK always
 */
Status game_actions_exit(Game *game);

/**
 * @brief It moves the player in the desired direction (north, south, west or east)
 * @author Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_move(Game *game);

/**
 * @brief It allows a player to pick up an object if they're in the same room
 * @author Rubén
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_take(Game *game);

/**
 * @brief It allows a player to drop an object if they have it
 * @author Rubén
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_drop(Game *game);

/**
 * @brief
 * @author Rubén
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_attack(Game *game);

/**
 * @brief It allows the player to chat with a character
 * @author Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_chat(Game *game);

/**
 * @brief It allows the player to inspect an object
 * @author
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_inspect(Game *game);

/**
   Game actions implementation
*/

#include "game_actions.h"
#include "input.h"  // Include the new input system

Status game_actions_update(Game *game, Command *command) {
    CommandCode cmd;

    game_set_last_command(game, command);
    cmd = command_get_code(command);

    switch (cmd) {
        case UNKNOWN:
            command_set_result(command, game_actions_unknown(game));
            break;

        case EXIT:
            command_set_result(command, game_actions_exit(game));
            break;

        case MOVE:
            command_set_result(command, game_actions_move(game));
            break;

        case TAKE:
            command_set_result(command, game_actions_take(game));
            break;

        case DROP:
            command_set_result(command, game_actions_drop(game));
            break;

        case ATTACK:
            command_set_result(command, game_actions_attack(game));
            break;

        case CHAT:
            command_set_result(command, game_actions_chat(game));
            break;

        case INSPECT:
            command_set_result(command, game_actions_inspect(game));
            break;

        default:
            break;
    }

    return OK;
}

/* 🟢 Handle movement based on input state */
Status game_actions_move(Game *game) {
    Id current_space_id, next_space_id;
    Direction direction = NO_DIR;

    current_space_id = game_get_player_location(game);
    if (current_space_id == NO_ID) {
        return ERROR;
    }

    // 🔹 Map keyboard input to movement direction
    if (game_input.up == KS_PRESSED) {
        direction = N;
    } else if (game_input.down == KS_PRESSED) {
        direction = S;
    } else if (game_input.right == KS_PRESSED) {
        direction = E;
    } else if (game_input.left == KS_PRESSED) {
        direction = W;
    } else {
        return ERROR;  // No valid direction pressed
    }

    next_space_id = game_get_connection(game, current_space_id, direction);
    if (next_space_id != NO_ID) {
        if (game_connection_is_open(game, current_space_id, direction)) {
            game_set_player_location(game, next_space_id);
            return OK;
        } else {
            printf("The connection isn't open\n");
            return ERROR;
        }
    }

    return ERROR;
}

/**
   Calls implementation for each action
*/

Status game_actions_unknown(Game *game) { return OK; }

Status game_actions_exit(Game *game) { return OK; }



Status game_actions_take(Game *game) {
  Id object_id;
  Id player_location;
  Command *c = NULL;
  Space *space = NULL;
  char object_name[WORD_SIZE] = "";

  if (!game) {
    return ERROR;
  }

  c = game_get_last_command(game);
  strcpy(object_name, command_get_obj(c));

  if (strcmp(object_name, "") == 0) {
    return ERROR;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {
    return ERROR;
  }

  object_id = game_get_object_id_from_name(game, object_name);
  if (object_id == NO_ID) {
    return ERROR;
  }

  space = game_get_space(game, player_location);
  if (!space) {
    return ERROR;
  }

  if (space_has_object(space, object_id) == TRUE) {
    game_set_object_location(game, PLAYER_ID, object_id);
    printf("Object %s taken\n", object_name); /*DEBUG*/
    return OK;
  } else {
    printf("Object %s not found in this space\n", object_name); /*DEBUG*/
    return ERROR;
  }

  return OK;
}

Status game_actions_drop(Game *game) {
  Id object_id;
  Id location;
  Command *c = NULL;
  char object_name[WORD_SIZE] = "";

  if (!game) {
    return ERROR;
  }

  c = game_get_last_command(game);
  strcpy(object_name, command_get_obj(c));

  if (strcmp(object_name, "") == 0) {
    return ERROR;
  }

  object_id = game_get_object_id_from_name(game, object_name);
  if (object_id == NO_ID) {
    return ERROR;
  }

  location = game_get_player_location(game);
  printf("Player's location is %li\n", location); /*DEBUG*/

  if (player_has_object(game_get_player(game), object_id) == TRUE) {
    game_set_object_location(game, location, object_id);
    printf("Object %s dropped\n", object_name); /*DEBUG*/
    return OK;
  } else {
    printf("Player does not have object %s\n", object_name); /*DEBUG*/
    return ERROR;
  }

  return OK;
}

Status game_actions_attack(Game *game) {
  Id player_location;
  Id character_location;
  Id character_id;
  Character *character = NULL;
  Player *player = NULL;
  int roll;
  char character_name[WORD_SIZE] = "";

  if (!game) {
    return ERROR;
  }

  player_location = game_get_player_location(game);

  if (space_get_character(game_get_space(game, player_location)) == NO_ID) {
    return ERROR;
  } else {
    strcpy(character_name, character_get_name(game_get_character(game, space_get_character(game_get_space(game, player_location)))));
    if (character_name[0] == '\0') {
      return ERROR;
    }
  }

  character_id = game_get_character_id_from_name(game, character_name);
  if (character_id == NO_ID) {
    printf("Character not found.\n");
    return ERROR;
  }

  character_location = game_get_character_location(game, character_id);

  if (player_location != character_location || player_location == NO_ID) {
    printf("You are not in the same location as %s.\n", character_name);
    return ERROR;
    /*  No hay ataque si no están en la misma ubicación */
  }

  character = game_get_character(game, character_id);
  if (!character) {
    return ERROR;
  }

  player = game_get_player(game);
  if (!player) {
    return ERROR;
  }

  /*  Verificar si el personaje es "friendly" */
  if (character_get_friendly(character)) {
    printf("You cannot attack %s, they are friendly.\n", character_name);
    return ERROR;
  }

  /*  Inicializar la semilla aleatoria (esto solo se hace una vez en main) */
  srand(time(NULL));
  roll = rand() % 10; /*  Número entre 0 y 9 */

  if (roll >= 0 && roll <= 4) {
    /*  El jugador pierde 1 punto de vida */
    player_decrease_health(player, 1);
    printf("You missed! %s counterattacks. You lose 1 health point.\n", character_name);
  } else {
    /*  El personaje pierde 1 punto de vida */
    character_decrease_health(character, 1);
    printf("You hit %s! They lose 1 health point.\n", character_name);
  }

  if (character_get_health(character) == 0) {
    space_remove_character(game_get_space(game, character_location));
  }

  return OK;
}

Status game_actions_chat(Game *game) {
  Id player_location;
  Id character_location;
  Id character_id;
  Character *character = NULL;
  Player *player = NULL;
  char character_name[WORD_SIZE] = "";

  if (!game) {
    return ERROR;
  }

  player_location = game_get_player_location(game);

  if (space_get_character(game_get_space(game, player_location)) == NO_ID) {
    return ERROR;
  } else {
    strcpy(character_name, character_get_name(game_get_character(game, space_get_character(game_get_space(game, player_location)))));
    if (character_name[0] == '\0') {
      return ERROR;
    }
  }

  character_id = game_get_character_id_from_name(game, character_name);
  if (character_id == NO_ID) {
    printf("Character not found.\n");
    return ERROR;
  }
  character_location = game_get_character_location(game, character_id);

  if (player_location != character_location || player_location == NO_ID) {
    printf("%s is in %li, player is in %li\n", character_name, character_location, player_location);
    printf("You are not in the same location as %s.\n", character_name);
    return ERROR; /*  No hay chat si no están en la misma ubicación */
  }

  character = game_get_character(game, character_id);
  if (!character) {
    return ERROR;
  }

  player = game_get_player(game);
  if (!player) {
    return ERROR;
  }

  /*  Verificar si el personaje es "friendly" */
  if (!character_get_friendly(character)) {
    printf("%s does not seem interested in talking to you.\n", character_name);
    return ERROR; /*  No habla si el personaje no es amistoso */
  }

  /*  El personaje lanza su mensaje */
  game_set_message(game, character_get_message(character));

  return OK;
}

Status game_actions_inspect(Game *game) {
  Id player_location, object_id;
  Command *c = NULL;
  char object_name[WORD_SIZE] = "";
  char object_description[WORD_SIZE];

  fprintf(stdout, "[DEBUG] Starting game_actions_inspect\n");

  if (!game) {
    fprintf(stdout, "[DEBUG] Game pointer is NULL\n");
    return ERROR;
  }

  player_location = game_get_player_location(game);
  fprintf(stdout, "[DEBUG] Player location: %ld\n", player_location);

  c = game_get_last_command(game);
  if (!c) {
    fprintf(stdout, "[DEBUG] Last command is NULL\n");
    return ERROR;
  }

  strcpy(object_name, command_get_obj(c));
  fprintf(stdout, "[DEBUG] Object name from command: %s\n", object_name);

  if (strcmp(object_name, "") == 0) {
    fprintf(stdout, "[DEBUG] Object name is empty\n");
    return ERROR;
  }

  object_id = game_get_object_id_from_name(game, object_name);
  fprintf(stdout, "[DEBUG] Object ID: %ld\n", object_id);

  if (space_has_object(game_get_space(game, player_location), object_id) == TRUE || player_has_object(game_get_player(game), object_id) == TRUE) {
    printf("AAAAAAAA\n");
    strcpy(object_description, object_get_desc(game_get_object_from_id(game, object_id)));

    fprintf(stdout, "[DEBUG] Object description: %s\n", object_description);
    game_set_object_desc(game, object_description);
  } else {
    fprintf(stdout, "[DEBUG] Object not found in player's location or inventory\n");
    return ERROR;
  }

  fprintf(stdout, "[DEBUG] game_actions_inspect completed successfully\n");
  return OK;
}