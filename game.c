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
  Space *spaces[MAX_SPACES];             /*!< Spaces in the game */
  Player *players[MAX_PLAYERS];          /*!< Players in the game */
  Object *objects[MAX_OBJECTS];          /*!< Objects in the game */
  Character *characters[MAX_CHARACTERS]; /*!< Characters in the game */
  Link *links[MAX_LINK];                 /*!< Links in the game */
  int n_spaces;                          /*!< Number of spaces in the game */
  int n_players;                         /*!< Number of players in the game */
  int n_objects;                         /*!< Number of objects in the game */
  int n_characters;                      /*!< Number of characters in the game */
  int n_links;                           /*!< Number of links in the game */
  Command *last_cmd;                     /*!< Last command of the game */
  char message[WORD_SIZE];               /*!< Highlighted message in the game */
  char object_desc[WORD_SIZE];           /*!< Highlighted object description in the game */
  Bool finished;                         /*!< Whether the game is finished or not */
  int turn;                              /*!< Current game's turn */
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

  game->n_spaces = 0;
  game->n_players = 0;
  game->n_objects = 0;
  game->n_characters = 0;
  game->n_links = 0;

  game->last_cmd = command_create();
  if (game->last_cmd == NULL) {
    player_destroy(game->players[game_get_turn(game)]);
    free(game);
    return ERROR;
  }

  strcpy(game->message, "");
  strcpy(game->object_desc, "");

  game->finished = FALSE;
  game->turn = 0;

  player_set_location(game->players[game_get_turn(game)], NO_ID);

  return OK;
}

/**
 * @brief It frees the memory the game was occupying
 */
Status game_destroy(Game *game) {
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

  if (game->last_cmd) {
    command_destroy(game->last_cmd);
    game->last_cmd = NULL;
  }

  free(game);
  game = NULL;

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

  game->players[game_get_num_players(game)] = player;
  game_increment_num_players(game);

  return OK;
}

/**
 * @brief It creates a pointer to the current player
 */
Player *game_get_player(Game *game) {
  /*CdE*/
  if (!game) {
    return NULL;
  }

  return game->players[game_get_turn(game)];
}

/**
 * @brief It creates a pointer to the player located in a certain position of the array of players in the game
 */
Player *game_get_player_from_index(Game *game, int index) {
  /*CdE*/
  if (!game) {
    return NULL;
  }

  return game->players[index];
}

/**
 * @brief It sets the player's location
 */
Status game_set_player_location(Game *game, Id id) {
  /*CdE*/
  if (!game || !game->players[game_get_turn(game)] || id == NO_ID) {
    return ERROR;
  }

  return player_set_location(game->players[game_get_turn(game)], id);
}

/**
 * @brief It gets the current player's location
 */
Id game_get_player_location(Game *game) {
  /*CdE*/
  if (!game || !game->players[game_get_turn(game)]) {
    return NO_ID;
  }

  return player_get_location(game->players[game_get_turn(game)]);
}

/**
 * @brief It gets the location of the player located in a certain position of the array of players in the game
 */
Id game_get_player_location_from_index(Game *game, int index) {
  /*CdE*/
  if (!game || !game->players[game_get_turn(game)]) {
    return NO_ID;
  }

  return player_get_location(game->players[index]);
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
Status game_set_object_location(Game *game, Id location, Id object_id) {
  Id current_location;
  /*CdE*/
  if (!game || location == NO_ID || object_id == NO_ID) {
    return ERROR;
  }

  current_location = game_get_object_location(game, object_id);

  /*Current location may be the player or a space, since the object can't be transfered directly between spaces or players it will always go from a
   * space to a player's inventory and viceversa*/

  if (current_location == player_get_id(game_get_player(game))) {
    /* Player -> space: If player has the object we remove it from the inventory and add it to the space*/
    if (player_remove_object(game_get_player(game), object_id) == ERROR) {
      return ERROR;
    }

    if (space_set_object(game_get_space(game, game_get_player_location(game)), object_id) == ERROR) {
      return ERROR;
    }

    return OK;
  } else {
    /* Space -> player: If space has the object we add it to the player's inventory (new location) and remove it from the space*/
    if (player_add_object(game_get_player(game), object_id) == ERROR) {
      return ERROR;
    }

    if (space_remove_object(game_get_space(game, current_location), object_id) == ERROR) {
      return ERROR;
    }

    return OK;
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

  /*It could be in a player's inventory or in a space, for now, if a player takes an object the rest of the players will no longer now where it is*/
  if (player_has_object(game_get_player(game), object_id) == TRUE) {
    return player_get_id(game->players[game_get_turn(game)]);
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
Id game_get_object_id_from_name(Game *game, char *object_name) {
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
    if (strlen(objs) + strlen(temp_obj) > BOX_WIDTH + 1 - 3) {
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

/*Management of characters*/
/**
 * @brief It adds a character to the game
 */
Status game_add_character(Game *game, Character *character) {
  /*CdE*/
  if (!game || !character || game_get_num_characters(game) >= MAX_CHARACTERS) {
    return ERROR;
  }

  game->characters[game_get_num_characters(game)] = character;
  game_increment_num_characters(game);

  return OK;
}

/**
 * @brief It gets a pointer to a characters from its id
 */
Character *game_get_character(Game *game, Id character_id) {
  int i;
  /*CdE*/
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
  /*CdE*/
  if (!game) {
    return NULL;
  }

  return game->characters[n];
}

/**
 * @brief It gets the location of a certain character
 */
Id game_get_character_location(Game *game, Id character_id) {
  int i = 0;
  /*CdE*/
  if (!game) {
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
 * @brief It gets a character's id from its name
 */
Id game_get_character_id_from_name(Game *game, char *name) {
  int i;
  /*CdE*/
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
  /*CdE*/
  if (!game || space_id == NO_ID) {
    return NULL;
  }

  return character_get_description(game_get_character(game, space_get_character(game_get_space(game, space_id))));
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
 * @brief It gets a space's neighboring location in a specified direction
 */
Id game_get_neighbour(Game *game, Id current_location, Direction direction) {
  int i;
  /*CdE*/
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
 * @brief It gets whether the connection of a space in a certain direction is open
 */
Bool game_connection_is_open(Game *game, Id current_location, Direction direction) {
  int i;
  /*CdE*/
  if (!game || current_location == NO_ID) {
    return FALSE;
  }

  for (i = 0; i < game->n_links; i++) {
    if (link_get_start(game->links[i]) == current_location && link_get_direction(game->links[i]) == direction) {
      return link_get_open(game->links[i]);
    }
  }

  return FALSE;
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

/*Management of last_cmd*/
/**
 * @brief It sets the game's last command
 */
Status game_set_last_command(Game *game, Command *command) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  game->last_cmd = command;

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

  return game->last_cmd;
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

  strcpy(game->message, message);

  return OK;
}

/**
 * @brief It gets the game's last message
 */
char *game_get_message(Game *game) {
  /*CdE*/
  if (!game) {
    return NULL;
  }

  return game->message;
}

/*Management of object_desc*/
/**
 * @brief It gets the description of the last inspected object
 */
char *game_get_object_desc(Game *game) {
  /*CdE*/
  if (!game) {
    return NULL;
  }

  return game->object_desc;
}

/**
 * @brief It sets the description of the last inspected object
 */
Status game_set_object_desc(Game *game, char *object_desc) {
  /*CdE*/
  if (!game) {
    return ERROR;
  }

  strcpy(game->object_desc, object_desc);

  return OK;
}

/*Management of finished*/
/**
 * @brief It gets whether the game is finished or not
 */
Bool game_get_finished(Game *game) {
  /*CdE*/
  if (!game) {
    return FALSE;
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