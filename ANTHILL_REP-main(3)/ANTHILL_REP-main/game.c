/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores
 * @version 1
 * @date 11-02-2025
 */

#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "character.h"
#include "command.h"
#include "game_reader.h"
#include "link.h"
#include "object.h"
#include "player.h"
#include "space.h"
#include "input.h"
#define MOVE_STEP 1      // Adjust for finer movement
#define SCREEN_WIDTH 800 // Set actual screen width
#define SCREEN_HEIGHT 600
#define TILE_SIZE 20 

/**
 Private structure
*/
struct _Game {
  Space *spaces[MAX_SPACES];
  Player *players[MAX_PLAYERS];
  Object *objects[MAX_OBJECTS];
  Character *characters[MAX_CHARACTERS];
  Link *links[MAX_LINK];
  int n_spaces;
  int n_objects;
  int n_characters;
  int n_links;
  int n_players;
  Command *last_cmd;
  char message[WORD_SIZE];
  char object_desc[WORD_SIZE];
  Bool finished;
  int turn;
};

/*Create & destroy*/
Status game_create(Game *game) {
  int i;
  if (game == NULL) {
    return ERROR;
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    game->players[i] = NULL;
  }

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_OBJECTS; i++) {
    game->objects[i] = NULL;
  }

  for (i = 0; i < MAX_LINK; i++) {
    game->links[i] = NULL;
  }

  game->n_spaces = 0;
  game->n_objects = 0;
  game->n_characters = 0;
  game->n_links = 0;
  game->n_players = 0;

  strcpy(game->message, "");
  player_set_location(game->players[game_get_turn(game)], NO_ID);

  game->last_cmd = command_create();
  if (game->last_cmd == NULL) {
    player_destroy(game->players[game_get_turn(game)]);
    free(game);
    return ERROR;
  }

  game->finished = FALSE;
  game->turn = 0;

  return OK;
}

Status game_destroy(Game *game) {
  int i;
  if (!game) {
    return ERROR;
  }

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
    game->spaces[i] = NULL;
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

  for (i = 0; i < game->n_players; i++) {
    player_destroy(game->players[i]);
    game->players[i] = NULL;
  }

  if (game->last_cmd) {
    command_destroy(game->last_cmd);
    game->last_cmd = NULL;
  }

  free(game);
  game = NULL;

  return OK;
}
void game_update_player_position(Game *game) {
  if (!game) return;

  Player *player = game_get_player(game);
  if (!player) return;

  int x = player_get_x(player);
  int y = player_get_y(player);

  fprintf(stdout, "Initial Player Position: x=%d, y=%d\n", x, y);

  if (game_input.up == KS_PRESSED || game_input.up == KS_HELD) y -= MOVE_STEP;
  if (game_input.down == KS_PRESSED || game_input.down == KS_HELD) y += MOVE_STEP;
  if (game_input.left == KS_PRESSED || game_input.left == KS_HELD) x -= MOVE_STEP;
  if (game_input.right == KS_PRESSED || game_input.right == KS_HELD) x += MOVE_STEP;

  // Ensure player stays within screen bounds
  if (x < 0) x = 0;
  if (y < 0) y = 0;
  if (x > SCREEN_WIDTH - TILE_SIZE) x = SCREEN_WIDTH - TILE_SIZE;
  if (y > SCREEN_HEIGHT - TILE_SIZE) y = SCREEN_HEIGHT - TILE_SIZE;

  fprintf(stdout, "New Player Position: x=%d, y=%d\n", x, y);
  fflush(stdout); // Ensure immediate output

  player_set_position(player, x, y);
}



Status game_add_link(Game *game, Id id, Id origin, Id destination, Direction dir, Bool open) {
  Link *new_link = link_create(id, origin, destination, dir, open);
  if (!game || id == NO_ID || origin == NO_ID || destination == NO_ID || dir == NO_DIR) {
    return ERROR;
  }

  if (game->n_links >= MAX_LINKS) {
    return ERROR;
  }

  if (!new_link) {
    return ERROR;
  }

  game->links[game->n_links] = new_link;
  game->n_links++;

  return OK;
}

Id game_get_connection(Game *game, Id current_location, Direction direction) {
  int i;
  if (!game || current_location == NO_ID) {
    return NO_ID;
  }

  fprintf(stdout, "Buscando conexión desde la ubicación %ld en la dirección %d.\n", current_location, direction);

  for (i = 0; i < game->n_links; i++) {
    fprintf(stdout, "Comprobando enlace %d: Start = %ld, Direction = %d, End = %ld\n", i, link_get_start(game->links[i]),
            link_get_direction(game->links[i]), link_get_end(game->links[i]));

    if (link_get_start(game->links[i]) == current_location && link_get_direction(game->links[i]) == direction) {
      fprintf(stdout, "Conexión encontrada. End = %ld\n", link_get_end(game->links[i]));
      return link_get_end(game->links[i]);
    }
  }

  fprintf(stdout, "No se encontró una conexión válida en la dirección %d desde la ubicación %ld.\n", direction, current_location);
  return NO_ID;
}

Bool game_connection_is_open(Game *game, Id current_location, Direction direction) {
  int i;
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

Game *game_init() {
  Game *game = (Game *)calloc(1, sizeof(Game));
  if (!game) {
    return NULL;
  }
  return game;
}

/*Manejo de spaces*/
Space **game_get_space_pointer(Game *game) {
  if (!game) {
    return NULL;
  }
  return game->spaces;
}

Space *game_get_space(Game *game, Id id) {
  int i;
  if (!game || id == NO_ID) return NULL;

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }
  return NULL;
}

/**
 * @brief
 * @author
 *
 * @param space a pointer to the space
 * @return
 */
Status space_get_object_name(Game *game, Id space_id, int n, char *name) {
  if (!game || space_id == NO_ID) {
    return NO_ID;
  }

  strcpy(name, object_get_name(game_get_object_from_id(game, space_get_n_object(game_get_space(game, space_id), n))));
  if (!name) {
    return ERROR;
  }

  return OK;
}

Id game_get_space_id_at(Game *game, int position) {
  Space **spaces = game_get_space_pointer(game);

  if (!game || position < 0 || position >= game_get_num_spaces(game)) {
    printf("Error: Invalid game or position\n");
    return NO_ID;
  }

  if (!spaces) {
    printf("Error: Could not get spaces from game\n");
    return NO_ID;
  }

  return space_get_id(spaces[position]);
}

/*Manejo de player*/
Player **game_get_players(Game *game) {
  if (!game) {
    return NULL;
  }
  return game->players;
}

Player *game_get_player(Game *game) {
  if (!game) {
    return NULL;
  }
  return game->players[game_get_turn(game)];
}

Player *game_get_n_player(Game *game, int n) {
  if (!game) {
    return NULL;
  }
  return game->players[n];
}

Id game_get_player_location(Game *game) {
  if (!game || !game->players[game_get_turn(game)]) return NO_ID;
  return player_get_location(game->players[game_get_turn(game)]);
}

Id game_get_n_player_location(Game *game, int n) {
  if (!game || !game->players[game_get_turn(game)]) return NO_ID;
  return player_get_location(game->players[n]);
}

Status game_set_player_location(Game *game, Id id) {
  if (!game || !game->players[game_get_turn(game)] || id == NO_ID) return ERROR;
  return player_set_location(game->players[game_get_turn(game)], id);
}

/*Manejo de objects*/
Object **game_get_object_pointer(Game *game) {
  if (!game) {
    return NULL;
  }
  return game->objects;
}

Object *game_get_n_object(Game *game, int n) {
  if (!game) {
    return NULL;
  }

  return game->objects[n];
}

Id game_get_object_location(Game *game, Id object_id) {
  int i = 0;

  if (!game) {
    return NO_ID;
  }

  /*Si no está en los espacios, miramos si lo tiene el jugador*/
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

Status game_set_object_location(Game *game, Id location, Id object_id) {
  Id current_location;

  if (!game || location == NO_ID || object_id == NO_ID) {
    return ERROR;
  }

  current_location = game_get_object_location(game, object_id);
  printf("The desired object's location is %li\n", current_location); /*DEBUG*/

  /*El objeto pasará de estar en current_location a location, hay dos casos, player->space, space->player*/

  if (current_location == player_get_id(game_get_player(game))) {
    /*Caso player->space*/
    /*Le quitamos el objeto al player*/
    if (player_remove_object(game_get_player(game), object_id) == ERROR) {
      return ERROR;
    }

    /*Le damos el objeto al space*/
    if (space_set_object(game_get_space(game, game_get_player_location(game)), object_id) == ERROR) {
      return ERROR;
    }

    return OK;
  } else {
    /*Caso space->player*/
    /*Le quitamos el objeto al space*/

    /*Le damos el objeto al player*/
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

Object *game_get_object_from_id(Game *game, Id object_id) {
  int i;

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

Object *game_get_object_from_position(Game *game, int n) {
  if (!game) {
    return NULL;
  }

  return game->objects[n];
}

Id game_get_object_id_from_name(Game *game, char *object_name) {
  int i;

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

Status game_get_string_of_objects_in_space(Game *game, Id space_id, char *objs) {
  char temp_obj[BOX_WIDTH + 1];
  int i = 0;
  int n_objects_printed = 0;

  if (!game) {
    return ERROR;
  }

  for (i = 0; i < space_get_num_objects(game_get_space(game, space_id)); i++) {
    space_get_object_name(game, space_id, i, temp_obj);
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

/*Manejo de characters*/
Character **game_get_characters(Game *game) {
  if (!game) {
    return NULL;
  }
  return game->characters;
}

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

Id game_get_character_location(Game *game, Id character_id) {
  int i = 0;

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

Status game_set_character_location(Game *game, Id location, Id character_id) {
  Id current_location;

  if (!game || location == NO_ID || character_id == NO_ID) {
    return ERROR;
  }

  current_location = game_get_character_location(game, character_id);
  printf("The desired character's location is %li\n", current_location); /*DEBUG*/

  /*Le damos el objeto al space*/
  if (space_set_character(game_get_space(game, game_get_player_location(game)), character_id) == ERROR) {
    return ERROR;
  }

  /*if (space_remove_character(game_get_space(game, current_location), character_id) == ERROR) {
    return ERROR;
  }*/

  return OK;
}

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

Character *game_get_n_character(Game *game, int n) {
  if (!game) {
    return NULL;
  }

  return game->characters[n];
}

char *game_get_character_desc_at_space(Game *game, Id space_id) {
  if (!game || space_id == NO_ID) {
    return NULL;
  }

  return character_get_description(game_get_character(game, space_get_character(game_get_space(game, space_id))));
}

/*Manejo de n_objects*/
int game_get_num_objects(Game *game) {
  if (!game) {
    return -1;
  }
  return game->n_objects;
}

void game_increment_num_objects(Game *game) {
  if (game) {
    game->n_objects++;
  }
}

/*Manejo de n_spaces*/
int game_get_num_spaces(Game *game) {
  if (!game) {
    return -1;
  }
  return game->n_spaces;
}

void game_increment_num_spaces(Game *game) {
  if (game) {
    game->n_spaces++;
  }
}

/*Manejo de n_characters*/
int game_get_num_characters(Game *game) {
  if (!game) {
    return -1;
  }
  return game->n_characters;
}

void game_increment_num_characters(Game *game) {
  if (game) {
    game->n_characters++;
  }
}

/*Manejo de n_players*/
int game_get_num_players(Game *game) {
  if (!game) {
    return -1;
  }
  return game->n_players;
}

void game_increment_num_players(Game *game) {
  if (game) {
    game->n_players++;
  }
}

/*Manejo de last_cmd*/
Command *game_get_last_command(Game *game) {
  if (!game) return NULL;
  return game->last_cmd;
}

Status game_set_last_command(Game *game, Command *command) {
  if (!game) return ERROR;
  game->last_cmd = command;
  return OK;
}

/*Manejo de message*/
char *game_get_message(Game *game) {
  if (!game) {
    return NULL;
  }

  return game->message;
}

Status game_set_message(Game *game, char *message) {
  if (!game) {
    return ERROR;
  }

  strcpy(game->message, message);

  return OK;
}

/*Manejo de object_desc*/
char *game_get_object_desc(Game *game) {
  if (!game) {
    return NULL;
  }

  return game->object_desc;
}

Status game_set_object_desc(Game *game, char *object_desc) {
  if (!game) {
    return ERROR;
  }

  strcpy(game->object_desc, object_desc);

  return OK;
}

/*Manejo de finished*/
Bool game_get_finished(Game *game) {
  if (!game) return FALSE;
  return game->finished;
}

Status game_set_finished(Game *game, Bool finished) {
  if (!game) {
    return ERROR;
  }
  game->finished = finished;
  return OK;
}

/*Manejo de turn*/
Status game_set_turn(Game *game, int turn) {
  if (!game) {
    return ERROR;
  }

  game->turn = turn;

  return OK;
}

int game_get_turn(Game *game) {
  if (!game) {
    return -1;
  }

  return game->turn;
}

/*Print*/
void game_print(Game *game) {
  int i;
  if (!game) return;

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

/*Adds*/
Status game_add_space(Game *game, Space *space) {
  Space **spaces = game_get_space_pointer(game);

  if (!game || !space || game_get_num_spaces(game) >= MAX_SPACES) {
    printf("Error: Invalid game or space, or maximum spaces reached\n");
    return ERROR;
  }

  if (!spaces) {
    printf("Error: Could not get spaces from game\n");
    return ERROR;
  }

  spaces[game_get_num_spaces(game)] = space;
  game_increment_num_spaces(game);
  printf("Space added successfully\n");

  return OK;
}

Status game_add_object(Game *game, Object *object) {
  Object **objects = game_get_object_pointer(game);

  if (!game || !object || game_get_num_objects(game) >= MAX_OBJECTS) {
    printf("Error: Invalid game or object, or maximum objects reached\n");
    return ERROR;
  }

  if (!objects) {
    printf("Error: Could not get objects from game\n");
    return ERROR;
  }

  objects[game_get_num_objects(game)] = object;
  game_increment_num_objects(game);
  printf("Object added successfully\n");

  return OK;
}

Status game_add_character(Game *game, Character *character) {
  Character **characters = game_get_characters(game);

  if (!game || !character || game_get_num_characters(game) >= MAX_CHARACTERS) {
    printf("Error: Invalid game or character, or maximum characters reached\n");
    return ERROR;
  }

  if (!characters) {
    printf("Error: Could not get characters from game\n");
    return ERROR;
  }

  characters[game_get_num_characters(game)] = character;
  game_increment_num_characters(game);
  printf("Chracter added successfully\n");

  return OK;
}

Status game_add_player(Game *game, Player *player) {
  Player **players = game_get_players(game);

  if (!game || !player || game_get_num_players(game) >= MAX_PLAYERS) {
    printf("Error: Invalid game or player, or maximum players reached\n");
    return ERROR;
  }

  if (!players) {
    printf("Error: Could not get players from game\n");
    return ERROR;
  }

  players[game_get_num_players(game)] = player;
  game_increment_num_players(game);
  printf("Player added successfully\n");

  return OK;
}

Id Game_get_north(Game *game, Id current_location) {
  if (!game || !current_location) {
    return ERROR;
  }
  printf("Northern neighbour: %li --> %li\n", current_location, Game_get_neighbour(game, current_location, N));
  return Game_get_neighbour(game, current_location, N);
}

Id Game_get_south(Game *game, Id current_location) {
  if (!game || !current_location) {
    return ERROR;
  }
  printf("Southern neighbour: %li --> %li\n", current_location, Game_get_neighbour(game, current_location, S));
  return Game_get_neighbour(game, current_location, S);
}
Id Game_get_east(Game *game, Id current_location) {
  if (!game || !current_location) {
    return ERROR;
  }
  printf("Eastern neighbour: %li --> %li\n", current_location, Game_get_neighbour(game, current_location, E));
  return Game_get_neighbour(game, current_location, E);
}

Id Game_get_west(Game *game, Id current_location) {
  if (!game || !current_location) {
    return ERROR;
  }
  printf("Western neighbour: %li --> %li\n", current_location, Game_get_neighbour(game, current_location, W));
  return Game_get_neighbour(game, current_location, W);
}

Id Game_get_neighbour(Game *game, Id current_location, Direction d) {
  int i;
  if (!game || current_location == NO_ID || ((d != 0) && (d != 1) && (d != 2) && (d != 3))) {
    return NO_ID;
  }

  for (i = 0; i < game->n_links; i++) {
    if (link_get_start(game->links[i]) == current_location) {
      if (d == link_get_direction(game->links[i])) {
        printf("CONNECTION FOUND BETWEEN %li and %li!\n", current_location, link_get_end(game->links[i])); /*Debug*/
        return link_get_end(game->links[i]);
      }
    }
  }

  return NO_ID;
}
