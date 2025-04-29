/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Profesores PPROG, Beatriz, Arturo, Rubén, Ana
 * @version 1
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#include "game_actions_sdl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#include "input.h"
#include "physics.h"

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
Status game_actions_unknown_sdl(Game *game);

/**
 * @brief It allows the user to exit the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the game
 * @return OK always
 */
Status game_actions_exit_sdl(Game *game);

/**
 * @brief It moves the player in the desired direction (north, south, west or east)
 * @author Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_move_sdl(Game *game);

/**
 * @brief It allows a player to pick up an object if they're in the same room
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_take_sdl(Game *game);

/**
 * @brief It allows a player to drop an object if they have it
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_drop_sdl(Game *game);

/**
 * @brief It allows the player to attack a character
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_attack_sdl(Game *game, int seed);

/**
 * @brief It allows the player to chat with a character
 * @author Beatriz, Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_chat_sdl(Game *game);

/**
 * @brief It allows the player to inspect an object
 * @author Arturo, Rubén, Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_inspect_sdl(Game *game);

/**
 * @brief It allows the player to toggle the visualization of the inventory
 * @author Bea, Arturo, Rubén, Ana
 *
 * @param game
 * @return  OK if everything goes well, ERROR otherwise
 */
Status game_actions_inventory_sdl(Game *game);

Status game_actions_use_sdl(Game *game);
Status game_actions_open_sdl(Game *game);

/**
 * @brief It allows the player to save its current game
 * @author Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_load_sdl(Game *game);

/**
 * @brief It allows the player to load a saved game
 * @author Ana
 *
 * @param game a pointer to the game
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_actions_save_sdl(Game *game);

/**
   Game actions implementation
*/

void game_actions_update_sdl(Game *game, int seed) {
  Player *player = game_get_current_player(game);
  if (!player) return;

  /* INVENTARIO - Si está activo, solo procesamos las teclas del menú */
  if (game_get_inventory_vis(game)) {
    if (game_input.inventory_up == KS_PRESSED) {
      game_move_inventory_cursor(game, -1); /* Mover el cursor hacia arriba */
    } else if (game_input.inventory_down == KS_PRESSED) {
      game_move_inventory_cursor(game, 1); /* Mover el cursor hacia abajo */
    } else if (game_input.inventory_confirm == KS_PRESSED) {
      game_select_inventory_object(game); /* Seleccionar o usar el objeto */
    } else if (game_input.inventory_cancel == KS_PRESSED) {
      game_toggle_inventory_vis(game); /* Cerrar el inventario */
    } else if (game_input.drop == KS_PRESSED) {
      game_actions_drop_sdl(game); /* Botón de drop */
    } else if (game_input.use == KS_PRESSED) {
      game_actions_use_sdl(game); /* Usar objeto */
    }else if (game_input.open == KS_PRESSED) {
      game_actions_open_sdl(game);
    }

    return; /* Si el inventario está abierto, ignoramos el resto de acciones */
  }

  /* Si el inventario no está abierto, se procesan las acciones del juego */

  /* Movimiento */
  if (game_input.up == KS_PRESSED) {
    player_set_position(player, player_get_x(player), player_get_y(player) - 1);
    player_toggle_curr_image_mode(player);
    player_set_image(player, (char *)player_get_North_image(player, 0), (char *)player_get_North_image(player, 1));
  }

  if (game_input.down == KS_PRESSED) {
    player_set_position(player, player_get_x(player), player_get_y(player) + 1);
    player_toggle_curr_image_mode(player);
    player_set_image(player, (char *)player_get_South_image(player, 0), (char *)player_get_South_image(player, 1));
  }

  if (game_input.left == KS_PRESSED) {
    player_set_position(player, player_get_x(player) - 1, player_get_y(player));
    player_toggle_curr_image_mode(player);
    player_set_image(player, (char *)player_get_West_image(player, 0), (char *)player_get_West_image(player, 1));
  }

  if (game_input.right == KS_PRESSED) {
    player_set_position(player, player_get_x(player) + 1, player_get_y(player));
    player_toggle_curr_image_mode(player);
    player_set_image(player, (char *)player_get_East_image(player, 0), (char *)player_get_East_image(player, 1));
  }

  /* ABRIR INVENTARIO */
  if (game_input.inventory_toggle == KS_PRESSED) {
    game_toggle_inventory_vis(game); /* Alternar visibilidad del inventario */
  }

  /* ATAQUE */
  if (game_input.attack == KS_PRESSED) {
    game_actions_attack_sdl(game, seed);
  }

  /* TOMAR OBJETO */
  if (game_input.take == KS_PRESSED) {
    game_actions_take_sdl(game);
  }

  /* INSPECCIONAR */
  if (game_input.inspect == KS_PRESSED) {
    game_actions_inspect_sdl(game);
  }

  /* USAR OBJETO */
  

  /* ABRIR PUERTA O CONTENEDOR */
  
}


/**
   Calls implementation for each action
*/

Status game_actions_unknown_sdl(Game *game) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  return OK;
}

Status game_actions_exit_sdl(Game *game) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  return OK;
}

Status game_actions_move_sdl(Game *game) {
  Id current_space_id = NO_ID;
  Id next_space_id = NO_ID;
  Command *c = NULL;
  const char *word = NULL;
  Connector connector = NO_DEST;
  const char *destiny = NULL;
  Direction direction;

  if (!game) {
    return ERROR;
  }

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
      return ERROR;
    }

    game_set_player_location(game, next_space_id);
    return OK;
  } else {
    direction = direction_from_string(destiny);
    if (direction == -1) return ERROR;
    return game_move_object(game, word, current_space_id, direction);
  }
  return ERROR;
}

Status game_actions_take_sdl(Game *game) {
  Player *player = game_get_current_player(game);
  Space *space = NULL;
  Object *obj = NULL;
  Id player_space;
  int i, num_objects;
  Id object_id;
  Bool taken = FALSE;

  if (!game || !player) return ERROR;

  player_space = game_get_player_location(game);
  if (player_space == NO_ID) return ERROR;

  space = game_get_space(game, player_space);
  if (!space) return ERROR;

  num_objects = space_get_num_objects(space);

  for (i = 0; i < num_objects; i++) {
    object_id = space_get_object_from_index(space, i);
    if (object_id == NO_ID) continue;

    obj = game_get_object_from_id(game, object_id);
    if (!obj) continue;

    if (physics_check_object_collision(game, player, obj)) {
      game_set_object_location(game, player_get_id(player), object_id);
      printf("[DEBUG] Picked up object ID %ld\n", object_id);
      taken = TRUE;
      break;
    }
  }

  if (!taken) {
    printf("[DEBUG] No object nearby to pick up.\n");
    return ERROR;
  }

  return OK;
}

Status game_actions_drop_sdl(Game *game) {
  Id object_id;
  Id location;
  int x, y;
  Inventory *inv;
  Set *set;
  Player *player;
  int cursor;

  if (!game) return ERROR;

  player = game_get_current_player(game);
  if (!player) return ERROR;

  /* Solo permitimos soltar si el inventario está abierto */
  if (!game_get_inventory_vis(game)) {
    printf("Inventory is not open. Cannot drop.\n");
    return ERROR;
  }

  inv = player_get_inventory(player);
  if (!inv) return ERROR;

  set = inventory_get_objects(inv);
  if (!set) return ERROR;

  cursor = set_get_cursor(set);
  if (cursor < 0 || cursor >= set_get_num_ids(set)) {
    printf("Cursor out of range. Cannot drop.\n");
    return ERROR;
  }

  object_id = set_get_id_from_index(set, cursor);
  if (object_id == NO_ID) {
    printf("No object selected to drop.\n");
    return ERROR;
  }

  location = game_get_player_location(game);
  player_get_position(player, &x, &y);

  if (player_has_object(player, object_id) == TRUE) {
    game_set_object_location(game, location, object_id);
    object_set_position(game_get_object_from_id(game, object_id), x, y);
    player_remove_object(player, object_id);
    printf("Object %ld dropped at (%d, %d)\n", object_id, x, y);
    return OK;
  }

  printf("Player does not have object %ld\n", object_id);
  return ERROR;
}


Status game_actions_attack_sdl(Game *game, int seed) {
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

  if (space_get_character_from_index(game_get_space(game, player_location), 0) == NO_ID) {
    return ERROR;
  }

  strcpy(character_name, character_get_name(game_get_character(game, space_get_character_from_index(game_get_space(game, player_location), 0))));

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

  player = game_get_current_player(game);
  if (!player) {
    return ERROR;
  }

  if (character_get_friendly(character)) {
    printf("You cannot attack %s, they are friendly.\n", character_name);
    return ERROR;
  }

  /* Deterministic or random roll */
  if (seed) {
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
    space_remove_character(game_get_space(game, character_location), character_get_id(character));
  }

  return OK;
}

Status game_actions_chat_sdl(Game *game) {
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

  if (space_get_character_from_index(game_get_space(game, player_location), 0) == NO_ID) {
    return ERROR;
  } else {
    strcpy(character_name, character_get_name(game_get_character(game, space_get_character_from_index(game_get_space(game, player_location), 0))));
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

  player = game_get_current_player(game);
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

Status game_actions_inspect_sdl(Game *game) {
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

  if (space_has_object(game_get_space(game, player_location), object_id) == TRUE ||
      player_has_object(game_get_current_player(game), object_id) == TRUE) {
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

Status game_actions_inventory_sdl(Game *game) {
  if (!game) {
    return ERROR;
  }

  game_toggle_inventory_vis(game);

  return OK;
}

Status game_actions_use_sdl(Game *game) {
  Id object_id;
  Inventory *inv;
  Set *set;
  Player *player;
  int cursor;

  printf("[DEBUG] Entered game_actions_use_sdl\n");

  if (!game) {
    printf("[ERROR] game is NULL\n");
    return ERROR;
  }

  /* Solo permitimos usar objetos si el inventario está abierto */
  if (!game_get_inventory_vis(game)) {
    printf("[ERROR] Inventory is not open. Cannot use.\n");
    return ERROR;
  }

  player = game_get_current_player(game);
  if (!player) {
    printf("[ERROR] Failed to get current player\n");
    return ERROR;
  }

  inv = player_get_inventory(player);
  if (!inv) {
    printf("[ERROR] Failed to get player inventory\n");
    return ERROR;
  }

  set = inventory_get_objects(inv);
  if (!set) {
    printf("[ERROR] Failed to get object set from inventory\n");
    return ERROR;
  }

  cursor = set_get_cursor(set);
  printf("[DEBUG] Inventory cursor at index: %d\n", cursor);

  if (cursor < 0 || cursor >= set_get_num_ids(set)) {
    printf("[ERROR] Cursor out of range. Cannot use.\n");
    return ERROR;
  }

  object_id = set_get_id_from_index(set, cursor);
  if (object_id == NO_ID) {
    printf("[ERROR] No object selected to use.\n");
    return ERROR;
  }

  printf("[DEBUG] Selected object ID: %ld\n", object_id);

  if (!player_has_object(player, object_id)) {
    printf("[ERROR] Player does not have object %ld\n", object_id);
    return ERROR;
  }

  if (!game_check_object_dependency(game, object_id)) {
    printf("[ERROR] Dependency check failed for object %ld\n", object_id);
    return ERROR;
  }

  printf("[DEBUG] Applying object %ld to player\n", object_id);

  if (game_update_player_health(game, object_id) == ERROR) {
    printf("[ERROR] Failed to apply object effect to player.\n");
    return ERROR;
  }
  player_remove_object(player, object_id);

  printf("[DEBUG] Object %ld used successfully. Advancing turn.\n", object_id);
  return game_increment_turn(game);
}




Status game_actions_open_sdl(Game *game) {
  Player *player;
  Inventory *inv;
  Set *set;
  int cursor;
  Id object_id;
  Link *link;
  Id current_space_id;

  printf("[DEBUG] Entered game_actions_open_sdl\n");

  if (!game) {
    printf("[ERROR] game is NULL\n");
    return ERROR;
  }

  if (!game_get_inventory_vis(game)) {
    printf("[ERROR] Inventory is not open. Cannot open link.\n");
    return ERROR;
  }

  player = game_get_current_player(game);
  if (!player) {
    printf("[ERROR] Failed to get current player\n");
    return ERROR;
  }

  inv = player_get_inventory(player);
  if (!inv) {
    printf("[ERROR] Failed to get player inventory\n");
    return ERROR;
  }

  set = inventory_get_objects(inv);
  if (!set) {
    printf("[ERROR] Failed to get object set from inventory\n");
    return ERROR;
  }

  cursor = set_get_cursor(set);
  printf("[DEBUG] Inventory cursor at index: %d\n", cursor);

  if (cursor < 0 || cursor >= set_get_num_ids(set)) {
    printf("[ERROR] Cursor out of range. Cannot open.\n");
    return ERROR;
  }

  object_id = set_get_id_from_index(set, cursor);
  if (object_id == NO_ID) {
    printf("[ERROR] No object selected to open.\n");
    return ERROR;
  }

  if (!player_has_object(player, object_id)) {
    printf("[ERROR] Player does not have object %ld\n", object_id);
    return ERROR;
  }

  if (!game_check_object_dependency(game, object_id)) {
    printf("[ERROR] Dependency check failed for object %ld\n", object_id);
    return ERROR;
  }

  current_space_id = game_get_player_location(game);
  if (current_space_id == NO_ID) {
    printf("[ERROR] Invalid player location\n");
    return ERROR;
  }

  link = physics_get_colliding_link(game, player);
  if (!link) {
    printf("[ERROR] No link collision detected. Cannot open.\n");
    return ERROR;
  }

  if (game_set_link_open(game, current_space_id, link_get_direction(link)) == OK) {
    printf("[DEBUG] Link '%s' opened successfully with object %ld.\n",
           link_get_name(link), object_id);
    player_remove_object(player, object_id);
    return game_increment_turn(game);
  }

  printf("[ERROR] Failed to open link.\n");
  return ERROR;
}



/**
 * @brief It allows the player to save its current game
 */
Status game_actions_load_sdl(Game *game) {
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

  return game_management_load(game, file_name, FALSE, TRUE);
}

/**
 * @brief It allows the player to load a saved game
 */
Status game_actions_save_sdl(Game *game) {
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

  return game_management_save(game, file_name);
}
