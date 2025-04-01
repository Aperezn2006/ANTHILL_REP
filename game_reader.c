#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "space.h"
#include "types.h"

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
  int i = 0, health = 0, player_max_obj = 0;
  FILE *file = NULL;
  Space *space = NULL;
  Player *player = NULL;
  Object *object = NULL;
  Character *character = NULL;
  Link *link = NULL;
  char line[WORD_SIZE] = "", *toks = NULL;
  char name[WORD_SIZE] = "";
  char player_desc[7], space_desc[5][10], object_desc[WORD_SIZE], character_desc[7];
  char character_message[MAX_MESSAGE], character_friendliness[6];
  Id id = NO_ID, location = NO_ID, link_origin = NO_ID, link_destination = NO_ID;
  Direction dir = NO_DIR;
  Bool open = FALSE;
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
          space_set_object(space, id);
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
      toks = strtok(NULL, "|");
      link_origin = atol(toks);
      toks = strtok(NULL, "|");
      link_destination = atol(toks);
      toks = strtok(NULL, "|");
      dir = (Direction)atoi(toks);
      toks = strtok(NULL, "|");
      open = (atoi(toks) == 1) ? TRUE : FALSE;

      link = link_create(id, dir);
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
