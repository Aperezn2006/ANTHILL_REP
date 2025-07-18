/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG, Bea, Arturo, Rubén, Ana
 * @version 2
 * @date 10-03-2025
 */

#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/**
 Private structure
*/
struct _Game {
  Command *last_cmd[MAX_PLAYERS];           /*!< Last command of the game */
  Space *spaces[MAX_SPACES];                /*!< Spaces in the game */
  Player *players[MAX_PLAYERS];             /*!< Players in the game */
  Object *objects[MAX_OBJECTS];             /*!< Objects in the game */
  Character *characters[MAX_CHARACTERS];    /*!< Characters in the game */
  Link *links[MAX_LINK];                    /*!< Links in the game */
  Set *teams[MAX_TEAMS];                    /*!< Equipos en el juego, cada uno es un conjunto de IDs de jugadores */
  int n_spaces;                             /*!< Number of spaces in the game */
  int n_players;                            /*!< Number of players in the game */
  int n_objects;                            /*!< Number of objects in the game */
  int n_characters;                         /*!< Number of characters in the game */
  int n_links;                              /*!< Number of links in the game */
  int n_teams;                              /*!< Number of teams in the game*/
  int turn;                                 /*!< Current game's turn */
  char message[MAX_PLAYERS][WORD_SIZE];     /*!< Highlighted message in the game */
  char object_desc[MAX_PLAYERS][WORD_SIZE]; /*!< Highlighted object description in the game */
  Bool finished;                            /*!< Whether the game is finished or not */
  Bool inventory_vis;                       /*!< Whether the inventory is being visualized*/
  Bool zoom_vis;                            /*!< Whether a space is being visualized in zoom mode*/
  Bool SDL;                                 /*!< Whether the game was launched using SDL2*/
  Bool won;                                 /*!< Whether the players won the game*/
  Ray *ray;
};

/*Create & destroy*/
/**
 * @brief It creates a new game a "restarts" everything
 */
Status game_init(Game *game) {
  int i;
  /*CdE*/
  if (game == NULL) {
    return ERROR;
  }
  /*Initialization*/
  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    game->players[i] = NULL;
    game->last_cmd[i] = NULL;
    strcpy(game->message[i], "");
    strcpy(game->object_desc[i], "");
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    game->objects[i] = NULL;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    game->characters[i] = NULL;
  }

  for (i = 0; i < MAX_LINK; i++) {
    game->links[i] = NULL;
  }
  for (i = 0; i < MAX_TEAMS; i++) {
    game->teams[i] = NULL;
  }

  game->n_spaces = 0;
  game->n_players = 0;
  game->n_objects = 0;
  game->n_characters = 0;
  game->n_links = 0;
  game->n_teams = 0;
  game->finished = FALSE;
  game->turn = 1;
  game->inventory_vis = FALSE;
  game->zoom_vis = FALSE;
  game->won = FALSE;

  player_set_location(game->players[game_get_player_index_from_turn(game)], NO_ID);

  return OK;
}

/**
 * @brief It frees the memory the game was occupying
 */
Status game_destroy(Game *game, Bool full_destruction) {
  int i;
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
    game->spaces[i] = NULL;
  }

  for (i = 0; i < game->n_players; i++) {
    player_destroy(game->players[i]);
    game->players[i] = NULL;

    command_destroy(game->last_cmd[i]);
    game->last_cmd[i] = NULL;
  }

  for (i = 0; i < game->n_objects; i++) {
    object_destroy(game->objects[i]);
    game->objects[i] = NULL;
  }

  for (i = 0; i < game->n_characters; i++) {
    character_destroy(game->characters[i]);
    game->characters[i] = NULL;
  }

  for (i = 0; i < game->n_links; i++) {
    link_destroy(game->links[i]);
    game->links[i] = NULL;
  }
  for (i = 0; i < game->n_teams; i++) {
    set_destroy(game->teams[i]); /* <- liberar los sets */
    game->teams[i] = NULL;
  }

  if (full_destruction == TRUE) {
    free(game);
    game = NULL;
  }

  return OK;
}

/**
 * @brief It allocates memory for the game
 */
Game *game_alloc() {
  Game *game = NULL;

  game = (Game *)calloc(1, sizeof(Game));
  if (!game) {
    return NULL;
  }

  return game;
}

/*Management of last_cmd*/
/**
 * @brief It sets the game's last command
 */
Status game_set_last_command(Game *game, Command *command) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  printf("Setting command in %i index\n", game_get_player_index_from_turn(game));
  game->last_cmd[game_get_player_index_from_turn(game)] = command;

  return OK;
}

/**
 * @brief It gets the game's last command
 */
Command *game_get_last_command(Game *game) {
  /*CdE*/
  if (!game) {
    return NULL;
  }

  return game->last_cmd[game_get_player_index_from_turn(game)];
}

/*Management of spaces*/
/**
 * @brief It adds spaces to the game
 */
Status game_add_space(Game *game, Space *space) {
  /*CdE*/
  if (!game || !space || game_get_num_spaces(game) >= MAX_SPACES) {
    return ERROR;
  }

  game->spaces[game_get_num_spaces(game)] = space;
  game_increment_num_spaces(game);

  return OK;
}

/**
 * @brief It gives a pointer to the space located in a certain position of the array of spaces in the game
 */
Space *game_get_space_from_index(Game *game, int index) {
  /*CdE*/
  if (!game) {
    return NULL;
  }
  return game->spaces[index];
}

/**
 * @brief It creates a pointer to a certain space using its id
 */
Space *game_get_space(Game *game, Id id) {
  int i;
  /*CdE*/
  if (!game || id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

/**
 * @brief It gets the name of the object located in a certain position of the array of objects in the space and copies it to "name"
 */
Status space_get_object_name_from_index(Game *game, Id space_id, int index, char *name) {
  /*CdE*/
  if (!game || space_id == NO_ID) {
    return NO_ID;
  }

  strcpy(name, object_get_name(game_get_object_from_id(game, space_get_object_from_index(game_get_space(game, space_id), index))));
  if (!name) {
    return ERROR;
  }

  return OK;
}

/**
 * @brief It gets the id of the space in a certain position of the array of objects in the game
 */
Id game_get_space_id_from_index(Game *game, int index) {
  /*CdE*/
  if (!game || index < 0 || index >= game_get_num_spaces(game)) {
    return NO_ID;
  }

  return space_get_id(game->spaces[index]);
}

/*Management of player*/
/**
 * @brief It adds a player to the game
 */
Status game_add_player(Game *game, Player *player) {
  /*CdE*/
  if (!game || !player || game_get_num_players(game) >= MAX_PLAYERS) {
    return ERROR;
  }

  game->last_cmd[game_get_num_players(game)] = command_create();
  game->players[game_get_num_players(game)] = player;
  game_increment_num_players(game);

  return OK;
}

/**
 * @brief It creates a pointer to the current player
 */
Player *game_get_current_player(Game *game) {
  /*CdE*/
  if (!game) {
    return NULL;
  }

  return game->players[game_get_player_index_from_turn(game)];
}

/**
 * @brief It creates a pointer to a player using its id
 */
Player *game_get_player(Game *game, Id id) {
  int i;
  /*CdE*/
  if (!game || id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_players; i++) {
    if (id == player_get_id(game->players[i])) {
      return game->players[i];
    }
  }

  return NULL;
}

/**
 * @brief It creates a pointer to the player located in a certain position of the array of players in the game
 */
Player *game_get_player_from_index(Game *game, int index) {
  /*CdE*/
  if (!game || (index == -1)) {
    return NULL;
  }

  return game->players[index];
}

/**
 * @brief It sets the player's location
 */
Status game_set_player_location(Game *game, Id id) {
  /*CdE*/
  if (!game || !game->players[game_get_player_index_from_turn(game)] || id == NO_ID) {
    return ERROR;
  }

  return player_set_location(game->players[game_get_player_index_from_turn(game)], id);
}

/**
 * @brief It sets the player's location from an id
 */
Status game_set_player_location_from_id(Game *game, Id space_id, Id player_id) {
  int i;

  if (!game || space_id == NO_ID || player_id == NO_ID) {
    return ERROR;
  }

  for (i = 0; i < game_get_num_players(game); i++) {
    if (player_get_id(game->players[i]) == player_id) {
      return player_set_location(game->players[i], space_id);
    }
  }

  return ERROR;
}

/**
 * @brief It gets the current player's location
 */
Id game_get_player_location(Game *game) {
  /*CdE*/
  if (!game || !game->players[game_get_player_index_from_turn(game)]) {
    return NO_ID;
  }

  return player_get_location(game->players[game_get_player_index_from_turn(game)]);
}

/**
 * @brief It gets the location of the player located in a certain position of the array of players in the game
 */
Id game_get_player_location_from_index(Game *game, int index) {
  /*CdE*/
  if (!game || !game->players[game_get_player_index_from_turn(game)]) {
    return NO_ID;
  }

  return player_get_location(game->players[index]);
}

/**
 * @brief It gets the id of a player by name
 */
Id game_get_player_id_from_name(Game *game, char *name) {
  int i;
  Player *p = NULL;
  Id found_id = NO_ID;

  if (!game || !name) {
    return NO_ID;
  }

  for (i = 0; i < game->n_players; i++) {
    p = game_get_player_from_index(game, i);
    if (p) {
      const char *player_name = player_get_name(p);

      if (strcasecmp(player_name, name) == 0) {
        found_id = player_get_id(p);
        return found_id;
      }
    }
  }

  return NO_ID;
}

/**
 * @brief It gets the player's max amount of consecutive turns
 */
int game_get_player_max_turns(Game *game, Id player_id) {
  int i = 0, total_turns = 0;
  Object *object = NULL;
  /*CdE*/
  if (!game || (player_id == NO_ID)) {
    return -1;
  }

  total_turns = player_get_max_turns(game_get_player(game, player_id));

  for (i = 0; i < game_get_num_objects(game); i++) {
    object = game_get_object_from_index(game, i);
    if (player_has_object(game_get_player(game, player_id), object_get_id(object)) == TRUE) {
      total_turns = total_turns + object_get_turn_amplifier(object);
    }
  }

  return total_turns;
}

/**
 * @brief It allows for characters to chase a player inside a space (for SDL)
 */
Status game_character_chase_player(Game *game, Character *character) {
  Id leader_id;
  int new_x = 0, new_y = 0;
  /*CdE*/
  if (!character) {
    return ERROR;
  }
  if (rand() % 2 == 0) {
    return OK;
  }

  /*leader_id = character_get_following(character);*/
  leader_id = player_get_id(game_get_current_player(game));
  if (leader_id == NO_ID || leader_id != player_get_id(game_get_current_player(game))) {
    return OK;
  } else {
    if (character_get_y(character) > (player_get_y(game_get_player(game, leader_id)) + 5)) {
      new_y = character_get_y(character) - 1;
      character_toggle_curr_image_mode(character);
      character_set_image(character, (char *)character_get_north_image(character, 0), (char *)character_get_north_image(character, 1),
                          (char *)character_get_north_image(character, 2));
    } else if (character_get_y(character) < (player_get_y(game_get_player(game, leader_id)) - 5)) {
      new_y = character_get_y(character) + 1;
      character_toggle_curr_image_mode(character);
      character_set_image(character, (char *)character_get_south_image(character, 0), (char *)character_get_south_image(character, 1),
                          (char *)character_get_south_image(character, 2));
    } else {
      new_y = character_get_y(character);
    }

    if (character_get_x(character) > (player_get_x(game_get_player(game, leader_id)) + 5)) {
      new_x = character_get_x(character) - 1;
      character_toggle_curr_image_mode(character);
      character_set_image(character, (char *)character_get_west_image(character, 0), (char *)character_get_west_image(character, 1),
                          (char *)character_get_west_image(character, 2));
    } else if (character_get_x(character) < (player_get_x(game_get_player(game, leader_id)) - 5)) {
      new_x = character_get_x(character) + 1;
      character_toggle_curr_image_mode(character);
      character_set_image(character, (char *)character_get_east_image(character, 0), (char *)character_get_east_image(character, 1),
                          (char *)character_get_east_image(character, 2));
    } else {
      new_x = character_get_x(character);
    }

    character_set_position(character, new_x, new_y);
  }

  return OK;
}

/**
 * @brief Ir returns the index of the player whose turn it is
 */
int game_get_player_index_from_turn(Game *game) {
  int i = 0, j = 0, guessed_turn = 0;
  Player *last_player = NULL;
  /*CdE*/
  if (!game) {
    return -1;
  }

  if (game->turn == 1) {
    return 0;
  }

  for (i = 0; i < game_get_num_players(game); i++) {
    last_player = game_get_player_from_index(game, i);

    for (j = 0; j < game_get_player_max_turns(game, player_get_id(last_player)); j++) {
      guessed_turn++;
      if (guessed_turn == game->turn) {
        return i;
      }
    }
  }

  return -1;
}

/**
 * @brief It updates the players health
 */
Status game_update_player_health(Game *game, Id object_id) {
  int turn;
  int health = 0;
  Object *object = NULL;

  if (!game || object_id == NO_ID) {
    return ERROR;
  }

  object = game_get_object_from_id(game, object_id);
  if (!object) {
    return ERROR;
  }

  turn = game_get_player_index_from_turn(game);
  health = player_get_health(game->players[turn]) + object_get_health(object);
  if (player_set_health(game->players[turn], health) == OK) {
    return OK;
  }

  return ERROR;
}

/*Management of objects*/
/**
 * @brief It adds objects to the game
 */
Status game_add_object(Game *game, Object *object) {
  /*CdE*/
  if (!game || !object || game_get_num_objects(game) >= MAX_OBJECTS) {
    return ERROR;
  }

  game->objects[game_get_num_objects(game)] = object;
  game_increment_num_objects(game);

  return OK;
}

/**
 * @brief It creates a pointer to the object located in a certain position of the array of objects in the game
 */
Object *game_get_object_from_index(Game *game, int index) {
  /*CdE*/
  if (!game) {
    return NULL;
  }

  return game->objects[index];
}

/**
 * @brief It gets a pointer to an object from its id
 */
Object *game_get_object_from_id(Game *game, Id object_id) {
  int i;
  /*CdE*/
  if (!game) {
    return NULL;
  }

  for (i = 0; i < game->n_objects; i++) {
    if (game->objects[i] && object_get_id(game->objects[i]) == object_id) {
      return game->objects[i];
    }
  }

  return NULL;
}

/**
 * @brief It sets the object's location
 */
Status game_set_object_location(Game *game, Id next_location, Id object_id) {
  Id current_location;
  /*CdE*/
  if (!game || next_location == NO_ID || object_id == NO_ID) {
    return ERROR;
  }

  current_location = game_get_object_location(game, object_id);

  /*The object can be in a player's inventory or in a space*/
  if (game_get_id_type(game, next_location) == SPACE) {
    if (space_add_object(game_get_space(game, next_location), object_id) == ERROR) {
      return ERROR;
    }
  } else if (game_get_id_type(game, next_location) == PLAYER) {
    if (inventory_get_max_objects(player_get_inventory(game_get_player(game, next_location))) >
        inventory_get_num_objects(player_get_inventory(game_get_player(game, next_location)))) {
      if (player_add_object(game_get_player(game, next_location), object_id) == ERROR) {
        return ERROR;
      }
    } else {
      return OK;
    }
  }

  if (game_get_id_type(game, current_location) == SPACE) {
    if (space_remove_object(game_get_space(game, current_location), object_id) == ERROR) {
      return ERROR;
    }
  } else if (game_get_id_type(game, current_location) == PLAYER) {
    if (player_remove_object(game_get_current_player(game), object_id) == ERROR) {
      return ERROR;
    }
  }

  return OK;
}

/**
 * @brief It gets the location a certain object
 */
Id game_get_object_location(Game *game, Id object_id) {
  int i = 0;
  /*CdE*/
  if (!game) {
    return NO_ID;
  }

  for (i = 0; i < game_get_num_players(game); i++) {
    if (player_has_object(game_get_player_from_index(game, i), object_id) == TRUE) {
      return player_get_id(game->players[i]);
    }
  }

  for (i = 0; i < game_get_num_spaces(game); i++) {
    if (space_has_object(game->spaces[i], object_id) == TRUE) {
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;
}

/**
 * @brief It gets an object's id from its name
 */
Id game_get_object_id_from_name(Game *game, const char *object_name) {
  int i;
  /*CdE*/
  if (!game || !object_name) {
    return NO_ID;
  }

  for (i = 0; i < game_get_num_objects(game); i++) {
    if (strcasecmp(object_get_name(game->objects[i]), object_name) == 0) {
      return object_get_id(game->objects[i]);
    }
  }

  return NO_ID;
}

/**
 * @brief It makes a string with the names of all the objects in the space
 */
Status game_get_string_of_objects_in_space(Game *game, Id space_id, char *objs) {
  char temp_obj[BOX_WIDTH + 1];
  int i = 0;
  int n_objects_printed = 0;
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  for (i = 0; i < space_get_num_objects(game_get_space(game, space_id)); i++) {
    space_get_object_name_from_index(game, space_id, i, temp_obj);
    if (strlen(objs) >= BOX_WIDTH + 1 - 3) {
      /*No hace nada*/
    } else if (strlen(objs) + strlen(temp_obj) > BOX_WIDTH + 1 - 3) {
      strcat(objs, "...");
    } else {
      strcat(objs, temp_obj);
      n_objects_printed++;
      if (n_objects_printed != space_get_num_objects(game_get_space(game, space_id))) {
        strcat(objs, ", ");
      }
    }
  }

  while (strlen(objs) < BOX_WIDTH - 1) {
    strcat(objs, " ");
  }

  return OK;
}

/**
 * @brief It checks if an objects needs another object
 */
Bool game_check_object_dependency(Game *game, Id object_id) {
  /* TRUE means object can be used, i.e., either it doesn't have a dependency or player has that object */
  Object *object = NULL;
  Id object_dependency = NO_ID;

  if (game == NULL || object_id == NO_ID) {
    return WRONG;
  }

  object = game_get_object_from_id(game, object_id);
  if (object == NULL) {
    return WRONG;
  }

  object_dependency = object_get_dependency(object);

  if (object_dependency == NO_ID) {
    return TRUE;
  }

  if (player_has_object(game->players[game_get_player_index_from_turn(game)], object_dependency) == TRUE) {
    return TRUE;
  }

  return FALSE;
}

/**
 * @brief It moves an object in a direction
 */
Status game_move_object(Game *game, const char *object_name, Id current_location, Direction direction) {
  Id next_space_id = NO_ID;
  Id object_id = NO_ID;
  Space *current_space = NULL;
  Space *next_space = NULL;

  if (!game || !object_name || !current_location || !direction) {
    return ERROR;
  }

  if (game_connection_is_open(game, current_location, direction) == FALSE) {
    return ERROR;
  }

  object_id = game_get_object_id_from_name(game, object_name);
  next_space_id = game_get_neighbour(game, current_location, direction);
  current_space = game_get_space(game, current_location);
  next_space = game_get_space(game, next_space_id);
  if (space_remove_object(current_space, object_id) == ERROR) {
    return ERROR;
  }

  return space_add_object(next_space, object_id);
}

/**
 * @brief It tells if an object can be moved or not
 */
Bool game_is_object_movable(Game *game, Id object_id) {
  Object *object = NULL;
  if (!game || !object_id) {
    return WRONG;
  }

  object = game_get_object_from_id(game, object_id);

  return object_is_movable(object);
}

/*Management of characters*/
/**
 * @brief It adds a character to the game
 */
Status game_add_character(Game *game, Character *character) {
  if (!game || !character || game_get_num_characters(game) >= MAX_CHARACTERS) {
    return ERROR;
  }

  game->characters[game_get_num_characters(game)] = character;
  game_increment_num_characters(game);

  return OK;
}

/**
 * @brief It gets a pointer to a character from its id
 */
Character *game_get_character(Game *game, Id character_id) {
  int i;
  if (!game || character_id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (game->characters[i] && character_get_id(game->characters[i]) == character_id) {
      return game->characters[i];
    }
  }

  return NULL;
}

/**
 * @brief It gets a pointer to the character located in a certain position of the game's array of characters
 */
Character *game_get_character_from_index(Game *game, int n) {
  if (!game) {
    return NULL;
  }

  return game->characters[n];
}

/**
 * @brief It gets the location of a certain character
 */
Id game_get_character_location(Game *game, Id character_id) {
  int i;
  if (!game || character_id == NO_ID) {
    return NO_ID;
  }

  for (i = 0; i < game_get_num_spaces(game); i++) {
    if (space_has_character(game->spaces[i], character_id) == TRUE) {
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;
}

/**
 * @brief It sets a character's location to a space
 */
Status game_set_character_location(Game *game, Id space_id, Id character_id) {
  if (!game || space_id == NO_ID || character_id == NO_ID) {
    return ERROR;
  }
  space_remove_character(game_get_space(game, game_get_character_location(game, character_id)), character_id);
  return space_add_character(game_get_space(game, space_id), character_id);
}

/**
 * @brief It gets a character's id from its name
 */
Id game_get_character_id_from_name(Game *game, char *name) {
  int i;
  if (!game || !name) {
    return NO_ID;
  }

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (game->characters[i] && strcasecmp(character_get_name(game->characters[i]), name) == 0) {
      return character_get_id(game->characters[i]);
    }
  }

  return NO_ID;
}

/**
 * @brief It gets the description of the character located in a certain space
 */
char *game_get_character_desc_at_space(Game *game, Id space_id) {
  Space *sp;
  Id char_id;

  if (!game || space_id == NO_ID) {
    return NULL;
  }

  sp = game_get_space(game, space_id);
  if (!sp || space_get_num_characters(sp) == 0) {
    return NULL;
  }

  char_id = space_get_character_from_index(sp, 0);
  return character_get_description(game_get_character(game, char_id));
}

/**
 * @brief It removes a character from a space
 */
Status game_remove_character_from_space(Game *game, Id space_id, Id character_id) {
  if (!game || space_id == NO_ID || character_id == NO_ID) {
    return ERROR;
  }

  return space_remove_character(game_get_space(game, space_id), character_id);
}

/**
 * @brief It updates the character health
 */
Status game_update_character_health(Game *game, Character *character, Id object_id) {
  int health = 0;
  Object *object = NULL;

  if (!game || !character || object_id == NO_ID) {
    return ERROR;
  }

  object = game_get_object_from_id(game, object_id);
  if (!object) {
    return ERROR;
  }

  health = character_get_health(character) + object_get_health(object);

  printf("%s will now have %i health\n", character_get_name(character), health);
  if (character_set_health(character, health) == OK) {
    return OK;
  }

  return ERROR;
}

/*Management of links*/
/**
 * @brief It adds a link to the game
 */
Status game_add_link(Game *game, Link *link) {
  /*CdE*/
  if (!game || !link || game_get_num_links(game) >= MAX_LINK) {
    return ERROR;
  }

  game->links[game_get_num_links(game)] = link;
  game_increment_num_links(game);

  return OK;
}
/**
 * @brief It gives a pointer to the link located in a certain position of the array of links in the game
 */
Link *game_get_link_from_index(Game *game, int index) {
  /*CdE*/
  if (!game) {
    return NULL;
  }

  return game->links[index];
}

/**
 * @brief It gives the id of a link from a name
 */
Id game_get_link_id_from_name(Game *game, char *name) {
  int i;
  /*CdE*/
  if (!game || !name) {
    return NO_ID;
  }

  for (i = 0; i < game->n_links; i++) {
    if (game->links[i] && strcasecmp(link_get_name(game->links[i]), name) == 0) {
      return link_get_id(game->links[i]);
    }
  }

  return NO_ID;
}

/**
 * @brief It gets the id of the space located north of the current_location
 */
Id game_get_north(Game *game, Id current_location) {
  /*CdE*/
  if (!game || !current_location) {
    return ERROR;
  }

  return game_get_neighbour(game, current_location, N);
}

/**
 * @brief It gets the id of the space located south of the current_location
 */
Id game_get_south(Game *game, Id current_location) {
  /*CdE*/
  if (!game || !current_location) {
    return ERROR;
  }

  return game_get_neighbour(game, current_location, S);
}

/**
 * @brief It gets the id of the space located east of the current_location
 */
Id game_get_east(Game *game, Id current_location) {
  /*CdE*/
  if (!game || !current_location) {
    return ERROR;
  }

  return game_get_neighbour(game, current_location, E);
}

/**
 * @brief It gets the id of the space located west of the current_location
 */
Id game_get_west(Game *game, Id current_location) {
  /*CdE*/
  if (!game || !current_location) {
    return ERROR;
  }

  return game_get_neighbour(game, current_location, W);
}

/**
 * @brief It gets the id of the space located on top of the current_location
 */
Id game_get_up(Game *game, Id current_location) {
  /*CdE*/
  if (!game || !current_location) {
    return ERROR;
  }

  return game_get_neighbour(game, current_location, U);
}

/**
 * @brief It gets the id of the space located below the current_location
 */
Id game_get_down(Game *game, Id current_location) {
  /*CdE*/
  if (!game || !current_location) {
    return ERROR;
  }

  return game_get_neighbour(game, current_location, D);
}
/**
 * @brief It gets a space's neighboring location in a specified direction
 */
Id game_get_neighbour(Game *game, Id current_location, Direction direction) {
  int i;
  /*CdE*/
  if (!game || current_location == NO_ID) {
    return NO_ID;
  }

  for (i = 0; i < game->n_links; i++) {
    if ((link_get_start(game->links[i]) == current_location) && (link_get_direction(game->links[i]) == direction)) {
      return link_get_end(game->links[i]);
    }
  }

  return NO_ID;
}

/**
 * @brief It gets a space's link in a specified direction
 */
Link *game_get_link_at_direction(Game *game, Id current_location, Direction d) {
  int i = 0;
  if (!game || current_location == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_links; i++) {
    if (link_get_start(game->links[i]) == current_location && link_get_direction(game->links[i]) == d) {
      printf("\nLink at direction found\n");
      return game->links[i];
    }
  }

  return NULL;
}

/**
 * @brief It gets whether the connection of a space in a certain direction is open
 */
Bool game_connection_is_open(Game *game, Id current_location, Direction direction) {
  int i;
  /*CdE*/
  if (!game || current_location == NO_ID) {
    return WRONG;
  }

  for (i = 0; i < game->n_links; i++) {
    if (link_get_start(game->links[i]) == current_location && link_get_direction(game->links[i]) == direction) {
      return link_get_open(game->links[i]);
    }
  }

  return FALSE;
}

/**
 * @brief It gets the id of the space neighbouring a certain space in a specific direction
 */
Id game_get_connection(Game *game, Id current_location, Direction direction) {
  int i;
  if (!game || current_location == NO_ID) {
    return NO_ID;
  }

  for (i = 0; i < game->n_links; i++) {
    if (link_get_start(game->links[i]) == current_location && link_get_direction(game->links[i]) == direction) {
      return link_get_end(game->links[i]);
    }
  }

  return NO_ID;
}

/**
 * @brief It gets a pointer to a link using its id
 */
Link *game_get_link_by_id(Game *game, Id link_id) {
  int i;
  /*CdE*/
  if (!game) {
    return NULL;
  }

  for (i = 0; i < game->n_links; i++) {
    if (game->links[i] && link_get_id(game->links[i]) == link_id) {
      return game->links[i];
    }
  }

  return NULL;
}

/**
 * @brief It sets a link to open
 */
Status game_set_link_open(Game *game, Id current_location, Direction direction) {
  int i;
  /*CdE*/
  if (!game || current_location == NO_ID) {
    return ERROR;
  }

  for (i = 0; i < game->n_links; i++) {
    if (link_get_start(game->links[i]) == current_location && link_get_direction(game->links[i]) == direction) {
      return link_set_open(game->links[i], TRUE);
      break;
    }
  }

  return ERROR;
}

/*Management of teams*/
/**
 * @brief It gets the team of a player
 */
Set *game_get_team(const Game *game, Id player_id) {
  int i;

  if (!game || player_id == NO_ID) return NULL;

  for (i = 0; i < game->n_teams; i++) {
    if (set_has_id(game->teams[i], player_id)) {
      return game->teams[i];
    }
  }

  return NULL;
}

/*Management of n_spaces*/
/**
 * @brief It gets the number of spaces in the game
 */
int game_get_num_spaces(Game *game) {
  /*CdE*/
  if (!game) {
    return -1;
  }
  return game->n_spaces;
}

/**
 * @brief It increments the number of spaces in the game
 */
Status game_increment_num_spaces(Game *game) {
  /*CdE*/
  if (game) {
    game->n_spaces++;
    return OK;
  }

  return ERROR;
}

/*Management of n_players*/
/**
 * @brief It gets the number of players in the game
 */
int game_get_num_players(Game *game) {
  /*CdE*/
  if (!game) {
    return -1;
  }

  return game->n_players;
}

/**
 * @brief It increments the number of players in the game
 */
Status game_increment_num_players(Game *game) {
  /*CdE*/
  if (game) {
    game->n_players++;
    return OK;
  }

  return ERROR;
}

/*Management of n_objects*/
/**
 * @brief It gets the number of objects in the game
 */
int game_get_num_objects(Game *game) {
  /*CdE*/
  if (!game) {
    return -1;
  }

  return game->n_objects;
}

/**
 * @brief It increments the number of objects in the game
 */
Status game_increment_num_objects(Game *game) {
  /*CdE*/
  if (game) {
    game->n_objects++;
    return OK;
  }

  return ERROR;
}

/*Management of n_characters*/
/**
 * @brief It gets the number of characters in the game
 */
int game_get_num_characters(Game *game) {
  /*CdE*/
  if (!game) {
    return -1;
  }

  return game->n_characters;
}

/**
 * @brief It increments the number of characters in the game
 */
Status game_increment_num_characters(Game *game) {
  /*CdE*/
  if (game) {
    game->n_characters++;
    return OK;
  }

  return ERROR;
}

/*Management of n_links*/
/**
 * @brief It gets the number of links in the game
 */
int game_get_num_links(Game *game) {
  /*CdE*/
  if (!game) {
    return -1;
  }

  return game->n_links;
}

/**
 * @brief It increments the number of links in the game
 */
Status game_increment_num_links(Game *game) {
  /*CdE*/
  if (game) {
    game->n_links++;
    return OK;
  }

  return ERROR;
}

/*Management of turn*/
/**
 * @brief It sets the game's current turn
 */
Status game_set_turn(Game *game, int turn) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  game->turn = turn;

  return OK;
}

/**
 * @brief It gets the game's current turn
 */
int game_get_turn(Game *game) {
  /*CdE*/
  if (!game) {
    return -1;
  }

  return game->turn;
}

/**
 * @brief It increments the turn (if it exceeds the current number of players it goes back to 0)
 */
Status game_increment_turn(Game *game) {
  int max_turns = 0, i = 0;
  Player *player = NULL;
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  game->turn++;

  for (i = 0; i < game_get_num_players(game); i++) {
    player = game_get_player_from_index(game, i);
    max_turns = max_turns + game_get_player_max_turns(game, player_get_id(player));
  }

  if (game->turn > max_turns) {
    game->turn = 1;
  }

  return OK;
}

/*Management of message*/
/**
 * @brief It sets the game's last message
 */
Status game_set_message(Game *game, char *message) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  strcpy(game->message[game_get_player_index_from_turn(game)], message);

  return OK;
}

/**
 * @brief It sets a certain player's last message
 */
Status game_set_message_from_index(Game *game, char *message, int index) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  strcpy(game->message[index], message);

  return OK;
}

/**
 * @brief It gets the las message of a certain player
 */
char *game_get_message_from_index(Game *game, int index) {
  /*CdE*/
  if (!game) {
    return NULL;
  }

  return game->message[index];
}

/**
 * @brief It gets the las message of the current player
 */
char *game_get_message(Game *game) {
  /*CdE*/
  if (!game) {
    return NULL;
  }

  return game->message[game_get_player_index_from_turn(game)];
}

/*Management of object_desc*/
/**
 * @brief It gets the description of a certain player's last inspected object
 */
char *game_get_object_desc_from_index(Game *game, int index) {
  /*CdE*/
  if (!game) {
    return NULL;
  }

  return game->object_desc[index];
}

/**
 * @brief It gets the description of the current player's last inspected object
 */
char *game_get_object_desc(Game *game) {
  /*CdE*/
  if (!game) {
    return NULL;
  }

  return game->object_desc[game_get_player_index_from_turn(game)];
}

/**
 * @brief It sets the description of the last inspected object
 */
Status game_set_object_desc(Game *game, char *object_desc) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  strcpy(game->object_desc[game_get_player_index_from_turn(game)], object_desc);

  return OK;
}

/**
 * @brief It sets the description of a certain player's last inspected object
 */
Status game_set_object_desc_from_index(Game *game, char *object_desc, int index) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  strcpy(game->object_desc[index], object_desc);

  return OK;
}

/*Management of finished*/
/**
 * @brief It gets whether the game is finished or not
 */
Bool game_get_finished(Game *game) {
  /*CdE*/
  if (!game) {
    return WRONG;
  }

  return game->finished;
}

/**
 * @brief It sets whether the game is finished or not
 */
Status game_set_finished(Game *game, Bool finished) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  game->finished = finished;

  return OK;
}

/*Management of inventory_vis*/
/**
 * @brief It toggles the inventory's visualization
 */
Status game_toggle_inventory_vis(Game *game) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  if (game->inventory_vis == TRUE) {
    game->inventory_vis = FALSE;
  } else {
    game->inventory_vis = TRUE;
  }

  return OK;
}

/**
 * @brief It gets whether the inventory is beinf visualized or not
 */
Bool game_get_inventory_vis(Game *game) {
  /*CdE*/
  if (!game) {
    return FALSE;
  }

  return game->inventory_vis;
}

/*Management of zoom_vis*/
/**
 * @brief It toggles the zoom's visualization
 */
Status game_toggle_zoom_vis(Game *game) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  if (game->zoom_vis == TRUE) {
    game->zoom_vis = FALSE;
  } else {
    game->zoom_vis = TRUE;
  }

  return OK;
}

/**
 * @brief It gets whether the zoom view is being visualized or not
 */
Bool game_get_zoom_vis(Game *game) {
  /*CdE*/
  if (!game) {
    return FALSE;
  }

  return game->zoom_vis;
}

/*Management of SDL*/
/**
 * @brief It gets whether the game is being run in the SDL version or not
 */
Bool game_get_SDL(Game *game) {
  if (!game) {
    return FALSE;
  }

  return game->SDL;
}

/*Management of won*/
/**
 * @brief It sets whether the player's won the game
 */
Status game_set_won(Game *game, Bool won) {
  if (!game) {
    return ERROR;
  }

  game->won = won;

  return OK;
}

/**
 * @brief It gets whether the player's won the game
 */
Bool game_get_won(Game *game) {
  if (!game) {
    return FALSE;
  }

  return game->won;
}

/*Misc*/
/**
 * @brief It figures out which game's category a certain id belongs to
 */
Id_Type game_get_id_type(Game *game, Id id) {
  int i = 0;
  /*CdE*/
  if (!game) {
    return UNSIGNED;
  }

  for (i = 0; i < game_get_num_spaces(game); i++) {
    if (id == space_get_id(game_get_space_from_index(game, i))) {
      return SPACE;
    }
  }

  for (i = 0; i < game_get_num_players(game); i++) {
    if (id == player_get_id(game_get_player_from_index(game, i))) {
      return PLAYER;
    }
  }

  for (i = 0; i < game_get_num_objects(game); i++) {
    if (id == object_get_id(game_get_object_from_index(game, i))) {
      return OBJECT;
    }
  }

  for (i = 0; i < game_get_num_characters(game); i++) {
    if (id == character_get_id(game_get_character_from_index(game, i))) {
      return CHARACTER;
    }
  }

  for (i = 0; i < game_get_num_links(game); i++) {
    if (id == link_get_id(game_get_link_from_index(game, i))) {
      return LINK;
    }
  }

  return UNSIGNED;
}

/**
 * @brief It gets the number of teammates a player has
 */
int game_get_team_of_player(const Game *game, Id player_id) {
  int i;

  if (!game || player_id == NO_ID) return -1;

  for (i = 0; i < game->n_teams; i++) {
    if (set_has_id(game->teams[i], player_id)) {
      return i;
    }
  }

  return -1;
}

/**
 * @brief It adds a team to the game
 */
Status game_add_team(Game *game) {
  Set *new_team = set_create();
  if (!game || game->n_teams >= MAX_TEAMS) return ERROR;

  if (!new_team) return ERROR;

  game->teams[game->n_teams++] = new_team;
  return OK;
}

/**
 * @brief It adds a player to a team
 */
Status game_add_player_to_team(Game *game, int team_index, Id player_id) {
  if (!game || team_index < 0 || team_index >= game->n_teams || player_id == NO_ID) {
    return ERROR;
  }

  return set_add_id(game->teams[team_index], player_id);
}

/**
 * @brief It sets teams
 */
Status game_handle_follow(Game *game, Id follower, Id leader) {
  int team_follower, team_leader, new_team_idx;

  if (!game || follower == NO_ID || leader == NO_ID) {
    return ERROR;
  }

  team_follower = game_get_team_of_player(game, follower);
  team_leader = game_get_team_of_player(game, leader);

  /* Case 1: neither is in a team -> create a new team with both */
  if (team_follower == -1 && team_leader == -1) {
    if (game_add_team(game) == ERROR) {
      return ERROR;
    }
    new_team_idx = game->n_teams - 1;

    if (game_add_player_to_team(game, new_team_idx, follower) == ERROR) {
      return ERROR;
    }

    if (game_add_player_to_team(game, new_team_idx, leader) == ERROR) {
      return ERROR;
    }

    return OK;
  }
  /* Case 2: only follower is in a team -> add leader to that team */
  else if (team_follower != -1 && team_leader == -1) {
    return game_add_player_to_team(game, team_follower, leader);
  }
  /* Case 3: only leader is in a team -> add follower to that team */
  else if (team_follower == -1 && team_leader != -1) {
    return game_add_player_to_team(game, team_leader, follower);
  }
  /* Case 4: both are in the same team -> nothing to do */
  else if (team_follower == team_leader) {
    return OK;
  }

  return ERROR;
}

/*Cosas de SDL2*/
/**
 * @brief It allows for the player to move the cursor inside its inventory
 */
void game_move_inventory_cursor(Game *game, int direction) {
  Player *player = NULL;
  Inventory *inventory = NULL;
  int num_objects, cursor;

  player = game_get_current_player(game);
  if (!player) {
    return;
  }

  inventory = player_get_inventory(player);
  if (!inventory) {
    return;
  }

  num_objects = inventory_get_max_objects(inventory);
  if (num_objects == 0) {
    return;
  }

  cursor = player_get_inventory_cursor(player);

  cursor += direction;

  if (cursor < 0) {
    cursor = 0;
  } else if (cursor >= num_objects) {
    cursor = num_objects;
  }

  player_set_inventory_cursor(player, cursor);
}

/*Management of ray*/
/**
 * @brief It gets a pointer to the game's ray
 */
Ray *game_get_ray(Game *game) {
  if (!game) return NULL;
  return game->ray;
}

/**
 * @brief It sets the ray inside the game
 */
void game_set_ray(Game *game, Ray *ray) {
  if (!game) return;
  game->ray = ray;
}

/*Print*/
/**
 * @brief It prints the game
 */
void game_print(Game *game) {
  int i;
  /*CdE*/
  if (!game) {
    return;
  }

  printf("\n\n-------------\n\n");
  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    if (object_get_id(game->objects[i]) != NO_ID) {
      printf("=> %s location: %d\n", object_get_name(game->objects[i]), (int)game_get_object_location(game, object_get_id(game->objects[i])));
    }
  }

  printf("=> Player location: %d\n", (int)game_get_player_location(game));
}