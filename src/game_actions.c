/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Profesores PPROG, Beatriz, Arturo, Rubén, Ana
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

#define DIRECTION_MAP_SIZE 12

typedef struct {
  const char *name;
  Direction dir;
} DirectionMap;

DirectionMap direction_map[] = {{"north", N}, {"n", N}, {"south", S}, {"s", S},
                                {"east", E},  {"e", E}, {"west", W},  {"w", W},
                                {"up", U},    {"u", U}, {"down", D},  {"d", D}};

/**
   Private functions
*/
Direction direction_from_string(const char *str) {
  int i;
  if (!str) return -1;
  for (i = 0; i < DIRECTION_MAP_SIZE; i++) {
    if (strcasecmp(str, direction_map[i].name) == 0) {
      return direction_map[i].dir;
    }
  }
  return -1; /* Invalid direction */
}

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
 * @brief It allows the user to exit the game
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
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_take(Game *game);

/**
 * @brief It allows a player to drop an object if they have it
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_drop(Game *game);

/**
 * @brief It allows the player to attack a character
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_attack(Game *game, int Seed);

/**
 * @brief It allows the player to chat with a character
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_chat(Game *game);

/**
 * @brief It allows the player to inspect an object
 * @author Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_inspect(Game *game);

/**
 * @brief It allows the player to toggle the visualization of the inventory
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game
 * @return  OK if everything goes well, ERROR otherwise
 */
Status game_actions_inventory(Game *game);

Status game_actions_use(Game *game);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command, int Seed) {
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
      command_set_result(command, game_actions_attack(game, Seed));
      break;

    case CHAT:
      command_set_result(command, game_actions_chat(game));
      break;

    case INSPECT:
      command_set_result(command, game_actions_inspect(game));
      break;

    case INVENTORY:
      command_set_result(command, game_actions_inventory(game));
      break;

    case USE:
      command_set_result(command, game_actions_use(game));
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

Status game_actions_move(Game *game) {
  Id current_space_id = NO_ID;
  Id next_space_id = NO_ID;
  Command *c = NULL;
  const char *word = NULL;
  Connector connector = NO_DEST;
  const char *destiny = NULL;
  Direction direction;

  if (!game) return ERROR;

  current_space_id = game_get_player_location(game);
  if (current_space_id == NO_ID) return ERROR;

  c = game_get_last_command(game);
  if (!c) return ERROR;

  word = command_get_word(c);
  connector = command_get_connector(c);
  destiny = command_get_destiny(c);

  direction = direction_from_string(word);

  /* ----- Player move (e.g. "m n" or "move north") ----- */
  if (direction != -1 && (connector == NO_DEST && destiny[0] == '\0')) {
    next_space_id = game_get_neighbour(game, current_space_id, direction);
    if (next_space_id == NO_ID) return ERROR;

    if (!game_connection_is_open(game, current_space_id, direction)) {
      printf("The connection isn't open\n"); /* Debug */
      return ERROR;
    }

    game_set_player_location(game, next_space_id);
    return OK;
  }
  else{
    direction = direction_from_string(destiny);
    if (direction == -1) return ERROR;
    return game_move_object(game, word, current_space_id, direction);
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
    printf("[DEBUG] Game is NULL\n");
    return ERROR;
  }

  c = game_get_last_command(game);
  if (!c) {
    printf("[DEBUG] Last command is NULL\n");
    return ERROR;
  }

  strcpy(object_name, command_get_word(c));
  printf("[DEBUG] Command word (object name): '%s'\n", object_name);

  if (strcmp(object_name, "") == 0) {
    printf("[DEBUG] Object name is empty\n");
    return ERROR;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {
    printf("[DEBUG] Invalid player location (NO_ID)\n");
    return ERROR;
  } else {
    printf("[DEBUG] Player location: %ld\n", player_location);
  }

  object_id = game_get_object_id_from_name(game, object_name);
  if (object_id == NO_ID) {
    printf("[DEBUG] No object found with name '%s'\n", object_name);
    return ERROR;
  } else {
    printf("[DEBUG] Object ID found: %ld for name '%s'\n", object_id, object_name);
  }

  space = game_get_space(game, player_location);
  if (!space) {
    printf("[DEBUG] Could not get space for location %ld\n", player_location);
    return ERROR;
  } else {
    printf("[DEBUG] Space found for location %ld\n", player_location);
  }

  if (space_has_object(space, object_id) == TRUE) {
    printf("[DEBUG] Space has object %ld ('%s')\n", object_id, object_name);
    game_set_object_location(game, player_get_id(game_get_player(game)), object_id);
    printf("[DEBUG] Object '%s' taken successfully\n", object_name);
    return OK;
  } else {
    printf("[DEBUG] Object '%s' (ID %ld) not found in current space %ld\n", object_name, object_id, player_location);
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
  strcpy(object_name, command_get_word(c)); /*Corrección: Podemos ahorrarnos la variable object_name si llamamos a get_obj*/

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

Status game_actions_attack(Game *game, int Seed) {
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
  }

  strcpy(character_name, character_get_name(
    game_get_character(game, space_get_character(game_get_space(game, player_location)))
  ));
  
  if (character_name[0] == '\0') {
    return ERROR;
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
  }

  character = game_get_character(game, character_id);
  if (!character) {
    return ERROR;
  }

  player = game_get_player(game);
  if (!player) {
    return ERROR;
  }

  if (character_get_friendly(character)) {
    printf("You cannot attack %s, they are friendly.\n", character_name);
    return ERROR;
  }

  /* Deterministic or random roll */
  if (Seed) {
    roll = 7; /* Always a successful hit in deterministic mode */
  } else {
    roll = rand() % 10; /* Random number between 0 and 9 */
  }

  if (roll >= 0 && roll <= 4) {
    player_decrease_health(player, 1);
    printf("You missed! %s counterattacks. You lose 1 health point.\n", character_name);
  } else {
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

  strcpy(object_name, command_get_word(c));
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

  object_set_inspected(game_get_object_from_id(game, object_id), TRUE);

  fprintf(stdout, "[DEBUG] game_actions_inspect completed successfully\n");
  return OK;
}

Status game_actions_inventory(Game *game) {
  if (!game) {
    return ERROR;
  }

  game_toggle_inventory_vis(game);

  return OK;
}

Status game_actions_use(Game *game) {
  Id object_id;
  Id location;
  Command *c = NULL;
  char object_name[WORD_SIZE] = "";
  Connector connector = NO_DEST;
  char destiny[WORD_SIZE] = "";

  if (!game) {
    printf("[DEBUG] Game is NULL\n");
    return ERROR;
  }

  c = game_get_last_command(game);
  if (!c) {
    printf("[DEBUG] Command is NULL\n");
    return ERROR;
  }

  strcpy(object_name, command_get_word(c));
  printf("[DEBUG] Command word (object): '%s'\n", object_name);

  if (strcmp(object_name, "") == 0) {
    printf("[DEBUG] Object name is empty\n");
    return ERROR;
  }

  object_id = game_get_object_id_from_name(game, object_name);
  printf("[DEBUG] Retrieved object ID: %ld\n", object_id);

  if (object_id == NO_ID) {
    printf("[DEBUG] Object '%s' not found in game\n", object_name);
    return ERROR;
  }

  location = game_get_player_location(game);
  printf("[DEBUG] Player's location is %ld\n", location);

  connector = command_get_connector(c);
  printf("[DEBUG] Connector = %d\n", connector);

  if (connector == NO_DEST) {
    printf("[DEBUG] Connector is NO_DEST\n");
    return ERROR;
  }

  strcpy(destiny, command_get_destiny(c));
  printf("[DEBUG] Destiny = '%s'\n", destiny);

  if (strcmp(destiny, "") == 0) {
    printf("[DEBUG] Destiny string is empty\n");
    return ERROR;
  }

  if (player_has_object(game_get_player(game), object_id) == TRUE && game_check_object_dependency(game, object_id)==TRUE) {
    printf("[DEBUG] Player has object %s\n", object_name);
    if (strcmp(destiny, "player") == 0) {
      printf("[DEBUG] Applying object to player\n");
      if (game_update_player_health(game, object_id) == ERROR) {
        printf("Failed to apply health changes\n");
        return ERROR;
      }
    } else {
      printf("[DEBUG] Unhandled destiny: '%s'\n", destiny);
    }
  } else {
    printf("Player does not have object %s\n", object_name);
    return ERROR;
  }

  return OK;
}

