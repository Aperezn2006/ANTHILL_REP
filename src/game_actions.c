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
 * @brief It moves the player in the desired direction (north, south, west or
 * east)
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
Status game_actions_attack(Game *game);

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
 * @brief It allows the player to follow another player
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game
 * @return  OK if everything goes well, ERROR otherwise
 */
Status game_actions_follow(Game *game);

/**
 * @brief It allows the player to toggle the visualization of the space
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game
 * @return  OK if everything goes well, ERROR otherwise
 */
Status game_actions_zoom(Game *game);

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

    case INVENTORY:
      command_set_result(command, game_actions_inventory(game));
      break;

    case USE:
      command_set_result(command, game_actions_use(game));
      break;
    case OPEN:
      command_set_result(command, game_actions_open(game));
      break;
    case FOLLOW:
      command_set_result(command, game_actions_follow(game));
      break;
    case ZOOM:
      command_set_result(command, game_actions_zoom(game));
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
  Id current_player_id = NO_ID;
  Set *team = NULL;
  int i, num_players;
  Id pid = NO_ID;

  if (!game) {
    return ERROR;
  }

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

  /* --- Player move (e.g. "move north") --- */
  if (direction != -1 && (connector == NO_DEST && destiny[0] == '\0')) {
    next_space_id = game_get_neighbour(game, current_space_id, direction);
    if (next_space_id == NO_ID) {
      return ERROR;
    }

    if (!game_connection_is_open(game, current_space_id, direction)) {
      printf("The connection isn't open\n");
      return ERROR;
    }

    current_player_id = player_get_id(game_get_player(game, game_get_player_index_from_turn(game)));
    team = game_get_team(game, current_player_id);

    if (team != NULL) {
      num_players = set_get_num_ids(team);
      for (i = 0; i < num_players; i++) {
        pid = set_get_id_from_index(team, i);
        if (pid != NO_ID) {
          game_set_player_location_from_id(game, next_space_id, pid);
        }
      }
    } else {
      game_set_player_location(game, next_space_id);
    }

    /* --- Character follow --- */
    for (i = 0; i < game_get_num_characters(game); i++) {
      if (player_get_id(game_get_player(game, game_get_player_index_from_turn(game))) ==
          character_get_following(game_get_character_from_index(game, i))) {
        printf("[[DEBUG]] MOVED %s %li %li\n", character_get_name(game_get_character_from_index(game, i)),
               player_get_id(game_get_player(game, game_get_player_index_from_turn(game))),
               character_get_following(game_get_character_from_index(game, i)));
        game_set_character_location(game, game_get_player_location(game), character_get_id(game_get_character_from_index(game, i)));
      }
    }

    return game_increment_turn(game);
  }
  /* --- Object move (e.g. "use connector destiny") --- */
  else {
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
    printf("[DEBUG] game_actions_take: Error, el juego no es válido.\n");
    return ERROR;
  }

  c = game_get_last_command(game);
  if (!c) {
    printf("[DEBUG] game_actions_take: Error, comando no disponible.\n");
    return ERROR;
  }

  strcpy(object_name, command_get_word(c));
  printf("[DEBUG] game_actions_take: Objeto recibido: '%s'\n", object_name);

  if (strcmp(object_name, "") == 0) {
    printf("[DEBUG] game_actions_take: Nombre de objeto vacío.\n");
    return ERROR;
  }

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {
    printf("[DEBUG] game_actions_take: La ubicación del jugador es inválida (NO_ID).\n");
    return ERROR;
  }

  printf("[DEBUG] game_actions_take: Ubicación del jugador: %ld\n", player_location);

  object_id = game_get_object_id_from_name(game, object_name);
  if (object_id == NO_ID) {
    printf("[DEBUG] game_actions_take: Objeto no encontrado: '%s'\n", object_name);
    return ERROR;
  } else {
    printf("[DEBUG] game_actions_take: Objeto encontrado, ID: %ld\n", object_id);
  }

  space = game_get_space(game, player_location);
  if (!space) {
    printf("[DEBUG] game_actions_take: Error, espacio no válido.\n");
    return ERROR;
  }

  printf("[DEBUG] game_actions_take: Espacio donde el jugador está ubicado: %ld\n", player_location);

  if (space_has_object(space, object_id) == TRUE) {
    printf("[DEBUG] game_actions_take: El espacio tiene el objeto con ID %ld.\n", object_id);
  } else {
    printf("[DEBUG] game_actions_take: El objeto no está en el espacio del jugador.\n");
  }

  if (game_is_object_movable(game, object_id) == TRUE) {
    printf("[DEBUG] game_actions_take: El objeto es movible.\n");
  } else {
    printf("[DEBUG] game_actions_take: El objeto no es movible.\n");
  }

  if (space_has_object(space, object_id) == TRUE && game_is_object_movable(game, object_id) == TRUE) {
    game_set_object_location(game, player_get_id(game_get_current_player(game)), object_id);
    printf("[DEBUG] game_actions_take: Objeto '%s' tomado con éxito.\n", object_name);
    return game_increment_turn(game);
  } else {
    printf("[DEBUG] game_actions_take: No se pudo tomar el objeto '%s'.\n", object_name);
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
  strcpy(object_name, command_get_word(c)); /*Corrección: Podemos ahorrarnos la variable
                                               object_name si llamamos a get_obj*/

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

Status game_actions_attack(Game *game) {
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
    roll = rand() % 10;
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
            printf(
                "You missed! %s counterattacks. Your recruited %s loses 1 "
                "health point.\n",
                character_name, character_get_name(game_get_character_from_index(game, j)));
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

  return OK;
}

Status game_actions_zoom(Game *game) { /*No pierdes turno al abrir el inventario*/
  if (!game) {
    return ERROR;
  }

  game_toggle_zoom_vis(game);

  return OK;
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
  Object *object = NULL;
  int uses;

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

    object = game_get_object_from_id(game, object_id);
    if (!object) {
      return ERROR;
    }

    uses = object_get_uses(object);
    if (uses <= 1) {
      player_remove_object(game_get_current_player(game), object_id);
    } else {
      object_set_uses(object, uses - 1);
    }

  } else {
    return ERROR;
  }

  /*return game_increment_turn(game);*/
  return OK;
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
    player_remove_object(game_get_current_player(game), object_id);
  }

  return ERROR;
}

Status game_actions_follow(Game *game) {
  Command *c = NULL;
  const char *follower_name = NULL;
  Id follower_id = NO_ID;
  Id leader_id = NO_ID;
  Player *leader_player = NULL;
  Player *follower_player = NULL;
  Id leader_location = NO_ID;
  Id follower_location = NO_ID;

  if (!game) {
    printf("[DEBUG] game is NULL\n");
    return ERROR;
  }

  /* Get leader (current player) ID */
  leader_player = game_get_current_player(game);
  if (!leader_player) {
    printf("[DEBUG] leader_player is NULL\n");
    return ERROR;
  }
  leader_id = player_get_id(leader_player);
  printf("[DEBUG] Leader ID: %ld\n", leader_id);

  /* Get follower name from command */
  c = game_get_last_command(game);
  if (!c) {
    printf("[DEBUG] Last command is NULL\n");
    return ERROR;
  }

  follower_name = command_get_word(c); /* e.g. "p2" from 'follow p2' */
  if (!follower_name) {
    printf("[DEBUG] follower_name is NULL\n");
    return ERROR;
  }
  printf("[DEBUG] Follower name from command: %s\n", follower_name);

  /* Get follower player by name and ID */
  follower_id = game_get_player_id_from_name(game, (char *)follower_name);
  if (follower_id == NO_ID) {
    printf("[DEBUG] No player found with name: %s\n", follower_name);
    return ERROR;
  }
  follower_player = game_get_player(game, follower_id);
  if (!follower_player) {
    printf("[DEBUG] follower_player with ID %ld is NULL\n", follower_id);
    return ERROR;
  }
  printf("[DEBUG] Follower ID: %ld\n", follower_id);

  /* Avoid self-following */
  if (leader_id == follower_id) {
    printf("[DEBUG] Leader and follower are the same player (ID %ld)\n", leader_id);
    return ERROR;
  }

  /* Ensure both are in the same space */
  leader_location = player_get_location(leader_player);
  follower_location = player_get_location(follower_player);
  if (leader_location == NO_ID || follower_location == NO_ID) {
    printf("[DEBUG] One or both players have NO_ID location\n");
    return ERROR;
  }
  printf("[DEBUG] Leader location: %ld, Follower location: %ld\n", leader_location, follower_location);

  if (leader_location != follower_location) {
    printf("[DEBUG] Players are not in the same space\n");
    return ERROR;
  }

  printf(
      "[DEBUG] Players are in the same space, attempting to handle follow "
      "logic...\n");
  return game_handle_follow(game, follower_id, leader_id);
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

  if (game_management_load(game, file_name, FALSE, FALSE) == OK) {
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
    printf("[DEBUG] game is NULL\n");
    return ERROR;
  }

  c = game_get_last_command(game);
  if (!c) {
    printf("[DEBUG] Last command is NULL\n");
    return ERROR;
  }

  word = command_get_word(c);
  if (!word) {
    printf("[DEBUG] Command word is NULL\n");
    return ERROR;
  }
  printf("[DEBUG] Command word: %s\n", word);

  player = game_get_player(game, game_get_player_index_from_turn(game));
  if (!player) {
    printf("[DEBUG] Current player is NULL\n");
    return ERROR;
  }
  printf("[DEBUG] Player ID: %ld\n", player_get_id(player));

  character = game_get_character(game, game_get_character_id_from_name(game, word));
  if (!character) {
    printf("[DEBUG] Character with name '%s' not found\n", word);
    return ERROR;
  }
  printf("[DEBUG] Character ID: %ld\n", character_get_id(character));

  if (game_get_player_location(game) != game_get_character_location(game, game_get_character_id_from_name(game, word))) {
    printf("[DEBUG] Player and character are not in the same location\n");
    return ERROR;
  }

  if (character_get_friendly(character) == FALSE) {
    printf("[DEBUG] Character '%s' is not friendly\n", word);
    return ERROR;
  }

  if (character_set_following(character, player_get_id(player)) == ERROR) {
    printf("[DEBUG] Failed to set character '%s' as following the player\n", word);
    return ERROR;
  }

  printf("[DEBUG] Character '%s' successfully recruited\n", word);
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
