#include "game_management.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status game_init_from_file(Game *game, char *filename) {
  Id first_space_id;

  if (!game || !filename) {
    printf("Error: Invalid game or filename\n");
    return ERROR;
  }

  if (game_init(game) == ERROR) {
    printf("Error: Could not create game\n");
    return ERROR;
  }

  if (game_load_everything(game, filename) == ERROR) {
    printf("Error: Could not load spaces and objects from file\n");
    return ERROR;
  }

  first_space_id = game_get_space_id_from_index(game, 0);
  if (first_space_id == NO_ID) {
    printf("Error: Could not get first space ID\n");
    return ERROR;
  }

  game_set_player_location(game, first_space_id);
  printf("Game created from file successfully\n");

  return OK;
}

Status game_load_everything(Game *game, char *filename) {
  /*PLAYER*/
  Player *player = NULL;
  int player_max_obj = 0;
  char player_desc[7];
  Id location = NO_ID;
  int health = 0;

  /*CHARACTER*/
  Character *character = NULL;
  char character_desc[7];
  char character_message[MAX_MESSAGE];
  char character_friendliness[6];

  /*OBJECT*/
  Object *object = NULL;
  char object_desc[WORD_SIZE];

  /*SPACE*/
  Space *space = NULL;
  char space_desc[5][10];

  /*LINK*/
  Link *link = NULL;
  Id link_origin = NO_ID;
  Id link_destination = NO_ID;
  Direction dir = NO_DIR;
  Bool open = FALSE;

  /*GENERAL*/
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char *toks = NULL;
  char name[WORD_SIZE] = "";
  int i = 0;
  Id id = NO_ID;
  Status status = OK;

  if (!game || !filename) {
    printf("Invalid game or filename\n");
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file: %s\n", filename);
    return ERROR;
  }

  printf("File opened successfully: %s\n", filename);

  while (fgets(line, WORD_SIZE, file)) {
    printf("Reading line: %s", line);

    /*SPACES*/
    if (strncmp("#s:", line, 3) == 0) {
      printf("Processing space\n");
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      for (i = 0; i < 5; i++) {
        toks = strtok(NULL, "|");
        if (!toks) {
          strcpy(space_desc[0], "         ");
          strcpy(space_desc[1], "         ");
          strcpy(space_desc[2], "         ");
          strcpy(space_desc[3], "         ");
          strcpy(space_desc[4], "         ");
          break;
        } else {
          strcpy(space_desc[i], toks);
        }
      }

      space = space_create(id);
      if (space) {
        space_set_name(space, name);
        for (i = 0; i < 5; i++) {
          space_set_description(space, space_desc);
        }
        if (game_add_space(game, space) == ERROR) {
          space_destroy(space);
          status = ERROR;
          break;
        }
      }

      /*OBJECTS*/
    } else if (strncmp("#o:", line, 3) == 0) {
      printf("Processing object\n");
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(object_desc, toks);

      object = object_create(id, location);
      if (object) {
        object_set_name(object, name);
        object_set_desc(object, object_desc);
        if (game_add_object(game, object) == ERROR) {
          object_destroy(object);
          status = ERROR;
          break;
        }
        space = game_get_space(game, location);
        if (space) {
          space_add_object(space, id);
        }
      }

      /*CHARACTERS*/
    } else if (strncmp("#c:", line, 3) == 0) {
      printf("Processing character\n");
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      strcpy(character_desc, toks);
      toks = strtok(NULL, "|");
      strcpy(character_message, toks);
      toks = strtok(NULL, "|");
      strcpy(character_friendliness, toks);

      character = character_create(id);
      if (character) {
        character_set_name(character, name);
        character_set_health(character, health);
        character_set_description(character, character_desc);
        character_set_message(character, character_message);
        character_set_friendly(character, strcmp(character_friendliness, "TRUE") == 0);
        if (game_add_character(game, character) == ERROR) {
          character_destroy(character);
          status = ERROR;
          break;
        }
        space = game_get_space(game, location);
        if (space) {
          space_set_character(space, id);
        }
      }

      /*LINKS*/
    } else if (strncmp("#l:", line, 3) == 0) {
      printf("Processing link\n");
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      link_origin = atol(toks);
      toks = strtok(NULL, "|");
      link_destination = atol(toks);
      toks = strtok(NULL, "|");
      dir = (Direction)atoi(toks);
      toks = strtok(NULL, "|");
      open = (atoi(toks) == 1) ? TRUE : FALSE;

      link = link_create(id);
      if (link) {
        link_set_name(link, name);
        link_set_start(link, link_origin);
        link_set_end(link, link_destination);
        link_set_direction(link, dir);
        link_set_open(link, open);
        if (game_add_link(game, link) == ERROR) {
          link_destroy(link);
          status = ERROR;
          break;
        }
      }

    } else if (strncmp("#p:", line, 3) == 0) {
      printf("Processing player\n");
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strcpy(player_desc, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      health = atol(toks);
      toks = strtok(NULL, "|");
      player_max_obj = atol(toks);

      player = player_create(id);
      if (player) {
        player_set_name(player, name);
        player_set_health(player, health);
        player_set_description(player, player_desc);
        player_set_max_objs(player, player_max_obj);
        player_set_location(player, location);
        if (game_add_player(game, player) == ERROR) {
          printf("Error adding player: %ld\n", id);
          player_destroy(player);
          status = ERROR;
          break;
        }
      }
    }
  }
  if (ferror(file)) {
    printf("Error reading file: %s\n", filename);
    status = ERROR;
  }

  fclose(file);
  return status;
}

/**
 * @brief It saves the current game's info in a specified file
 */
Status game_management_save(Game *game, char *file_name) {
  int i;
  FILE *pf;
  char save_path[WORD_SIZE];
  Object *object = NULL;
  Space *space = NULL;
  Link *link = NULL;
  Character *character = NULL;
  Player *player = NULL;
  /*CdE*/
  if (!game || !file_name) {
    return ERROR;
  }

  strcpy(save_path, "saves/");
  strcat(save_path, file_name);

  pf = fopen(save_path, "w");

  fprintf(pf, "Finished: 0\n");
  fprintf(pf, "Inventory_vis: 0\n");

  fprintf(pf, "Nums: %i|%i|%i|%i|%i|\n", game_get_num_spaces(game), game_get_num_players(game), game_get_num_objects(game),
          game_get_num_characters(game), game_get_num_links(game));

  fprintf(pf, "\nObjects:\n");
  for (i = 0; i < game_get_num_objects(game); i++) {
    object = game_get_object_from_index(game, i);
    /*id|name|desc|inspected|location*/
    fprintf(pf, "%li|%s|%s|%i|%li|\n", object_get_id(object), object_get_name(object), object_get_desc(object), object_get_inspected(object),
            game_get_object_location(game, object_get_id(object)));
  }

  fprintf(pf, "\nSpaces:\n");
  for (i = 0; i < game_get_num_spaces(game); i++) {
    space = game_get_space_from_index(game, i);
    /*id|name|gdesc|discovered*/
    fprintf(pf, "%li|%s|%s|%s|%s|%s|%s|%i|\n", space_get_id(space), space_get_name(space), space_get_i_static_description(space, 0),
            space_get_i_static_description(space, 1), space_get_i_static_description(space, 2), space_get_i_static_description(space, 3),
            space_get_i_static_description(space, 4), space_get_discovered(space));
  }

  fprintf(pf, "\nLinks:\n");
  for (i = 0; i < game_get_num_links(game); i++) {
    link = game_get_link_from_index(game, i);
    /*id | name | origin | destination | open | direction*/
    fprintf(pf, "%li|%s|%li|%li|%i|%i|\n", link_get_id(link), link_get_name(link), link_get_start(link), link_get_end(link), link_get_open(link),
            link_get_direction(link));
  }

  fprintf(pf, "\nCharacters:\n");
  for (i = 0; i < game_get_num_characters(game); i++) {
    character = game_get_character_from_index(game, i);
    /*id|name|gdesc|health|friendly|message|location*/
    fprintf(pf, "%li|%s|%s|%li|%i|%s|\n", character_get_id(character), character_get_name(character), character_get_description(character),
            character_get_health(character), character_get_friendly(character), character_get_message(character));
  }

  fprintf(pf, "\nPlayers:\n");
  for (i = 0; i < game_get_num_players(game); i++) {
    player = game_get_player_from_index(game, i);
    /*id|name|health|gdesc|location|message|object_desc*/
    fprintf(pf, "%li|%s|%li|%s|%li|%s|%s|\n", player_get_id(player), player_get_name(player), player_get_health(player),
            player_get_description(player), player_get_location(player), game_get_message_from_index(game, i),
            game_get_object_desc_from_index(game, i));
  }

  fclose(pf);

  return OK;
}

/**
 * @brief It loads a player's game from a certain file
 */
Status game_management_load(Game *game, char *file_name) {
  /*CdE*/
  if (!game || !file_name) {
    return ERROR;
  }
  return OK;
}
