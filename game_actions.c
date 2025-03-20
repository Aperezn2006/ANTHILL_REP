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
 * @brief It moves the player south
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_next(Game *game);

/**
 * @brief It moves the player north
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_back(Game *game);

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
 * @brief It moves the player east
 * @author Rubén
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_east(Game *game);

/**
 * @brief It moves the player west
 * @author Rubén
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_west(Game *game);

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
   Game actions implementation
*/

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

    case NEXT:
      command_set_result(command, game_actions_next(game));
      break;

    case BACK:
      command_set_result(command, game_actions_back(game));
      break;

    case TAKE:
      command_set_result(command, game_actions_take(game));
      break;

    case DROP:
      command_set_result(command, game_actions_drop(game));
      break;

    case RIGHT:
      command_set_result(command, game_actions_east(game));
      break;

    case LEFT:
      command_set_result(command, game_actions_west(game));
      break;

    case ATTACK:
      command_set_result(command, game_actions_attack(game));
      break;

    case CHAT:
      command_set_result(command, game_actions_chat(game));
      break;

    default:
      break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

Status game_actions_unknown(Game *game) { return OK; }

Status game_actions_exit(Game *game) { return OK; }

Status game_actions_next(Game *game) {
  Id space_id = NO_ID;   
  Id next_id = NO_ID;

  space_id = game_get_player_location(game);
  fprintf(stdout, "Ubicación actual del jugador (space_id): %ld\n", space_id);
  
  if (space_id == NO_ID) {
    fprintf(stdout, "Error: La ubicación del jugador no es válida.\n");
    return ERROR;
  }

  next_id = game_get_connection(game, space_id, S);
  fprintf(stdout, "Próxima conexión (next_id): %ld\n", next_id);


  if (next_id != NO_ID) {
    game_set_player_location(game, next_id);
    fprintf(stdout, "Ubicación del jugador actualizada a: %ld\n", next_id);
  } else {
    fprintf(stdout, "No hay conexión válida para el jugador desde la ubicación %ld.\n", space_id);
  }

  return OK;
}


Status game_actions_back(Game *game) {
  Id space_id = game_get_player_location(game);
  Id next_id = game_get_connection(game, space_id, N);
  if (space_id == NO_ID) {
      return ERROR;
  }

  if (!game_connection_is_open(game, space_id, N)) {
      return ERROR;
  }

  if (next_id != NO_ID) {
      game_set_player_location(game, next_id);
      return OK;
  }

  return ERROR;
}

Status game_actions_east(Game *game) {
  Id space_id = game_get_player_location(game);
  Id next_id = game_get_connection(game, space_id, E);
  if (space_id == NO_ID) {
      return ERROR;
  }

  if (!game_connection_is_open(game, space_id, E)) {
      return ERROR;
  }

  if (next_id != NO_ID) {
      game_set_player_location(game, next_id);
      return OK;
  }

  return ERROR;
}

Status game_actions_west(Game *game) {
  Id space_id = game_get_player_location(game);
  Id next_id = game_get_connection(game, space_id, W);
  if (space_id == NO_ID) {
      return ERROR;
  }

  if (!game_connection_is_open(game, space_id, W)) {
      return ERROR;
  }

  if (next_id != NO_ID) {
      game_set_player_location(game, next_id);
      return OK;
  }

  return ERROR;
}


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