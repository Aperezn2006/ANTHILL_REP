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

DirectionMap direction_map[] = {{"north", N}, {"n", N}, {"south", S}, {"s", S}, {"east", E}, {"e", E},
                                {"west", W},  {"w", W}, {"up", U},    {"u", U}, {"down", D}, {"d", D}};

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

/**
 * @brief It allows the player to use an object
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game
 * @return  OK if everything goes well, ERROR otherwise
 */
Status game_actions_use(Game *game);
/**
 * @brief It allows the player to open links
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game
 * @return  OK if everything goes well, ERROR otherwise
 */
Status game_actions_open(Game *game);

/**
 * @brief It allows the player to save its current game
 * @author Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_load(Game *game);

/**
 * @brief It allows the player to load a saved game
 * @author Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_save(Game *game);

/**
 * @brief It allows the player to recruit a friendly character
 * @author Arturo
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_recruit(Game *game);

/**
 * @brief It allows the player to abandon a friendly character
 * @author Arturo
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_abandon(Game *game);

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
    case OPEN:
      command_set_result(command, game_actions_open(game));
      break;

    case LOAD:
      game_actions_load(game);
      break;

    case SAVE:
      command_set_result(command, game_actions_save(game));
      break;

    case RECRUIT:
      command_set_result(command, game_actions_recruit(game));
      break;

    case ABANDON:
      command_set_result(command, game_actions_abandon(game));
      break;

    default:
      break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

Status game_actions_unknown(Game *game) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  return OK;
}

Status game_actions_exit(Game *game) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  return OK;
}

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
  if (current_space_id == NO_ID) {
    return ERROR;
  }

  c = game_get_last_command(game);
  if (!c) {
    return ERROR;
  }

  word = command_get_word(c);
  connector = command_get_connector(c);
  destiny = command_get_destiny(c);

  direction = direction_from_string(word);

  /* ----- Player move (e.g. "m n" or "move north") ----- */
  if (direction != -1 && (connector == NO_DEST && destiny[0] == '\0')) {
    next_space_id = game_get_neighbour(game, current_space_id, direction);
    if (next_space_id == NO_ID) {
      return ERROR;
    }

    if (!game_connection_is_open(game, current_space_id, direction)) {
      printf("The connection isn't open\n"); /* Debug */
      return ERROR;
    }

    game_set_player_location(game, next_space_id);
    return game_increment_turn(game);
  } else {
    direction = direction_from_string(destiny);
    if (direction == -1) {
      return ERROR;
    }

    game_move_object(game, word, current_space_id, direction);

    return game_increment_turn(game);
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

  if (space_has_object(space, object_id) == TRUE && game_is_object_movable(game, object_id) == TRUE) {
    printf("[DEBUG] Space has object %ld ('%s')\n", object_id, object_name);
    game_set_object_location(game, player_get_id(game_get_current_player(game)), object_id);
    printf("[DEBUG] Object '%s' taken successfully\n", object_name);
    return game_increment_turn(game);
  } else {
    printf("[DEBUG] Object '%s' (ID %ld) not found in current space %ld\n", object_name, object_id, player_location);
    return ERROR;
  }

  return game_increment_turn(game);
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

  if (player_has_object(game_get_current_player(game), object_id) == TRUE) {
    game_set_object_location(game, location, object_id);
    printf("Object %s dropped\n", object_name); /*DEBUG*/
    return game_increment_turn(game);
  } else {
    printf("Player does not have object %s\n", object_name); /*DEBUG*/
    return ERROR;
  }

  return game_increment_turn(game);
}

Status game_actions_attack(Game *game, int Seed) {
  Id player_location;
  Character *character = NULL;
  Player *player = NULL;
  int roll;
  int i, j, num_chars, count = 0;
  Id char_id;
  Space *space;
  char character_name[WORD_SIZE] = "";

  if (!game) {
    return ERROR;
  }

  player = game_get_current_player(game);
  if (!player) {
    return ERROR;
  }

  player_location = game_get_player_location(game);
  space = game_get_space(game, player_location);
  if (!space) {
    return ERROR;
  }

  num_chars = space_get_num_characters(space);
  for (i = 0; i < num_chars; i++) {
    char_id = space_get_character_from_index(space, i);
    character = game_get_character(game, char_id);
    if (!character) {
      continue;
    }

    if (character_get_friendly(character)) {
      continue; /* Skip friendly characters */
    }

    strcpy(character_name, character_get_name(character));
    if (Seed) {
      roll = 7; /* Deterministic */
    } else {
      roll = rand() % 10;
    }
    printf("ROLL = %i", roll);
    if (roll >= 0 && roll <= 4) {
      for (j = 0; j < game_get_num_characters(game); j++) {
        if (player_get_id(game_get_player(game, game_get_player_index_from_turn(game))) ==
            character_get_following(game_get_character_from_index(game, j))) {
          count++;
        }
      }
      if (count > 0) {
        roll = rand() % (game_get_num_characters(game) + 2);
        for (j = roll; j; j++) {
          if (j > game_get_num_characters(game) - 1) {
            j = 0;
          }
          if (player_get_id(game_get_player(game, game_get_player_index_from_turn(game))) ==
              character_get_following(game_get_character_from_index(game, j))) {
            character_decrease_health(game_get_character_from_index(game, j), 1);
            printf("You missed! %s counterattacks. Your recruited %s loses 1 health point.\n", character_name,
                   character_get_name(game_get_character_from_index(game, j)));
            break;
          }
        }
      } else {
        player_decrease_health(player, 1);
        printf("You missed! %s counterattacks. You lose 1 health point.\n", character_name);
      }

    } else {
      for (j = 0; j < game_get_num_characters(game); j++) {
        if (player_get_id(game_get_player(game, game_get_player_index_from_turn(game))) ==
            character_get_following(game_get_character_from_index(game, j))) {
          count++;
        }
      }
      character_decrease_health(character, 1 + count);
      printf("You hit %s! They lose %i health points.\n", character_name, 1 + count);
    }

    if (character_get_health(character) <= 0) {
      space_remove_character(space, char_id);
      printf("%s has been defeated.\n", character_name);
    }

    if ((player_get_health(player) == 0) || (character_get_health(character) == 0)) {
      return game_increment_turn(game);
    }

    return OK; /* Only attack one hostile character */
  }

  printf("There are no hostile characters to attack here.\n");
  return ERROR;
}

Status game_actions_chat(Game *game) {
  Id player_location;
  Character *character = NULL;
  Player *player = NULL;
  int i, num_chars;
  Id char_id;
  Space *space;
  char character_name[WORD_SIZE] = "";

  if (!game) {
    return ERROR;
  }

  player = game_get_current_player(game);
  if (!player) {
    return ERROR;
  }

  player_location = game_get_player_location(game);
  space = game_get_space(game, player_location);
  if (!space) {
    return ERROR;
  }

  num_chars = space_get_num_characters(space);
  for (i = 0; i < num_chars; i++) {
    char_id = space_get_character_from_index(space, i);
    character = game_get_character(game, char_id);
    if (!character) {
      continue;
    }

    if (!character_get_friendly(character)) {
      continue; /* Only talk to friendly characters */
    }

    strcpy(character_name, character_get_name(character));
    game_set_message(game, character_get_message(character));
    printf("You talk to %s.\n", character_name);
    return game_increment_turn(game);
  }

  printf("There are no friendly characters here to talk to.\n");
  return ERROR;
}

Status game_actions_inspect(Game *game) {
  Id player_location, object_id;
  Command *c = NULL;
  char object_name[WORD_SIZE] = "";
  char object_description[WORD_SIZE];

  if (!game) {
    return ERROR;
  }

  player_location = game_get_player_location(game);

  c = game_get_last_command(game);
  if (!c) {
    return ERROR;
  }

  strcpy(object_name, command_get_word(c));

  if (strcmp(object_name, "") == 0) {
    return ERROR;
  }

  object_id = game_get_object_id_from_name(game, object_name);

  if (space_has_object(game_get_space(game, player_location), object_id) == TRUE ||
      player_has_object(game_get_current_player(game), object_id) == TRUE) {
    strcpy(object_description, object_get_desc(game_get_object_from_id(game, object_id)));

    game_set_object_desc(game, object_description);
  } else {
    return ERROR;
  }

  object_set_inspected(game_get_object_from_id(game, object_id), TRUE);

  return game_increment_turn(game);
}

Status game_actions_inventory(Game *game) { /*No pierdes turno al abrir el inventario*/
  if (!game) {
    return ERROR;
  }

  game_toggle_inventory_vis(game);

  return game_increment_turn(game);
}

Status game_actions_use(Game *game) {
  Id object_id;
  Command *c = NULL;
  char object_name[WORD_SIZE] = "";
  Connector connector = NO_DEST;
  char destiny[WORD_SIZE] = "";
  Character *character = NULL;
  Player *player = NULL;
  Id character_id;

  if (!game) {
    return ERROR;
  }

  c = game_get_last_command(game);
  if (!c) {
    return ERROR;
  }

  strcpy(object_name, command_get_word(c));

  if (strcmp(object_name, "") == 0) {
    return ERROR;
  }

  object_id = game_get_object_id_from_name(game, object_name);

  if (object_id == NO_ID) {
    return ERROR;
  }

  connector = command_get_connector(c);

  if (connector == NO_DEST) {
    return ERROR;
  }

  strcpy(destiny, command_get_destiny(c));

  if (strcmp(destiny, "") == 0) {
    return ERROR;
  }

  if (player_has_object(game_get_current_player(game), object_id) == TRUE && game_check_object_dependency(game, object_id) == TRUE) {
    if (strcmp(destiny, "player") == 0) {
      if (game_update_player_health(game, object_id) == ERROR) {
        return ERROR;
      }
    } else {
      character_id = game_get_character_id_from_name(game, destiny);
      character = game_get_character(game, character_id);
      player = game_get_current_player(game);

      if (character != NULL && character_get_following(character) == player_get_id(player)) {
        if (game_update_character_health(game, character, object_id) == ERROR) {
          return ERROR;
        }
      } else {
        return ERROR;
      }
    }
  } else {
    return ERROR;
  }

  return game_increment_turn(game);
}

Status game_actions_open(Game *game) {
  Id object_id = NO_ID;
  Id current_space_id = NO_ID;
  Id link_id = NO_ID;
  Command *c = NULL;
  const char *link_name = NULL;
  Connector connector = NO_DEST;
  const char *object_name = NULL;
  Direction direction = NO_DIR;
  Link *link = NULL;
  int i;

  if (!game) return ERROR;

  current_space_id = game_get_player_location(game);
  if (current_space_id == NO_ID) return ERROR;

  c = game_get_last_command(game);
  if (!c) return ERROR;

  link_name = command_get_word(c);
  connector = command_get_connector(c);
  object_name = command_get_destiny(c);

  if (!link_name || !object_name) return ERROR;

  if (connector == NO_DEST) {
    return ERROR;
  }

  link_id = game_get_link_id_from_name(game, (char *)link_name);
  if (link_id == NO_ID) {
    return ERROR;
  }

  object_id = game_get_object_id_from_name(game, object_name);
  if (object_id == NO_ID) {
    return ERROR;
  } else {
  }

  /* Find the link object and its direction */
  for (i = 0; i < game_get_num_links(game); i++) {
    link = game_get_link_from_index(game, i);
    if (link && link_get_id(link) == link_id && link_get_start(link) == current_space_id) {
      direction = link_get_direction(link);
      break;
    }
  }

  if (!link || direction == NO_DIR) {
    return ERROR;
  }

  if (player_has_object(game_get_current_player(game), object_id) == TRUE && game_check_object_dependency(game, object_id) == TRUE) {
    if (game_set_link_open(game, current_space_id, direction) == OK) {
      return game_increment_turn(game);
    } else {
      return ERROR;
    }
  }

  return ERROR;
}

/**
 * @brief It allows the player to save its current game
 */
Status game_actions_load(Game *game) {
  Command *c = NULL;
  char file_name[WORD_SIZE] = "";

  /*CdE*/
  if (!game) {
    return ERROR;
  }

  c = game_get_last_command(game);
  if (!c) {
    return ERROR;
  }

  strcpy(file_name, command_get_word(c));
  strcat(file_name, ".txt");

  if (strcmp(file_name, "") == 0) {
    return ERROR;
  }

  if (game_management_load(game, file_name, FALSE) == OK) {
    return game_increment_turn(game);
  }

  return ERROR;
}

/**
 * @brief It allows the player to load a saved game
 */
Status game_actions_save(Game *game) {
  Command *c = NULL;
  char file_name[WORD_SIZE] = "";

  /*CdE*/
  if (!game) {
    return ERROR;
  }

  c = game_get_last_command(game);
  if (!c) {
    return ERROR;
  }

  strcpy(file_name, command_get_word(c));
  strcat(file_name, ".txt");

  if (strcmp(file_name, "") == 0) {
    return ERROR;
  }

  if (game_management_save(game, file_name) == OK) {
    return game_increment_turn(game);
  }

  return ERROR;
}

Status game_actions_recruit(Game *game) {
  Command *c = NULL;
  char *word = NULL;
  Character *character = NULL;
  Player *player = NULL;

  if (!game) {
    return ERROR;
  }

  c = game_get_last_command(game);
  if (!c) return ERROR;

  word = command_get_word(c);
  player = game_get_player(game, game_get_player_index_from_turn(game));
  character = game_get_character(game, game_get_character_id_from_name(game, word));

  if (game_get_player_location(game) != game_get_character_location(game, game_get_character_id_from_name(game, word))) {
    return ERROR;
  }

  if (character_get_friendly(character) == FALSE) {
    return ERROR;
  }

  if (character_set_following(character, player_get_id(player)) == ERROR) {
    return ERROR;
  }

  return game_increment_turn(game);
}

Status game_actions_abandon(Game *game) {
  Command *c = NULL;
  char *word = NULL;
  Character *character = NULL;
  Player *player = NULL;

  if (!game) {
    return ERROR;
  }

  c = game_get_last_command(game);
  if (!c) return ERROR;

  word = command_get_word(c);
  player = game_get_player(game, game_get_player_index_from_turn(game));
  character = game_get_character(game, game_get_character_id_from_name(game, word));

  if (character_get_following(character) != player_get_id(player)) {
    return ERROR;
  }

  character_set_following(character, NO_ID);

  return game_increment_turn(game);
}
