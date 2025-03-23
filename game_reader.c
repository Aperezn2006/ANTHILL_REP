#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "space.h"
#include "types.h"

Status game_create_from_file(Game *game, char *filename) {
  Id first_space_id;

  if (!game || !filename) {
    printf("Error: Invalid game or filename\n");
    return ERROR;
  }

  if (game_create(game) == ERROR) {
    printf("Error: Could not create game\n");
    return ERROR;
  }

  if (game_load_everything(game, filename) == ERROR) {
    printf("Error: Could not load spaces and objects from file\n");
    return ERROR;
  }

  first_space_id = game_get_space_id_at(game, 0);
  if (first_space_id == NO_ID) {
    printf("Error: Could not get first space ID\n");
    return ERROR;
  }

  game_set_player_location(game, first_space_id);
  printf("Game created from file successfully\n");

  return OK;
}

Status game_load_everything(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char object_name[WORD_SIZE] = "";
  char character_name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID;
  long player_health = 0, player_max_obj = 0;
  Id player_location = NO_ID;
  char player_desc[7];
  char player_name[WORD_SIZE];
  Space *space = NULL;
  Player *player = NULL;
  Id player_id = NO_ID;
  Id object_id = NO_ID, object_location = NO_ID;
  Object *object = NULL;
  Character *character = NULL;
  Id character_id = NO_ID, character_location = NO_ID;
  Id link_id = NO_ID, origin = NO_ID, destination = NO_ID;
  Direction dir = NO_DIR;
  Bool open = FALSE;
  Status status = OK;
  char gdesc[5][10];
  char character_desc[7], character_message[MAX_MESSAGE], character_friendliness[6];
  int i = 0, character_health = 0;

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

    if (strncmp("#s:", line, 3) == 0) {
      printf("Processing space\n");
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      for (i = 0; i < 5; i++) {
        toks = strtok(NULL, "|");
        if (!toks) {
          strcpy(gdesc[0], "         ");
          strcpy(gdesc[1], "         ");
          strcpy(gdesc[2], "         ");
          strcpy(gdesc[3], "         ");
          strcpy(gdesc[4], "         ");
          break;
        } else {
          strcpy(gdesc[i], toks);
        }
      }

      space = space_create(id);
      if (space) {
        space_set_name(space, name);
        for (i = 0; i < 5; i++) {
          space_set_description(space, gdesc);
        }
        if (game_add_space(game, space) == ERROR) {
          space_destroy(space);
          status = ERROR;
          break;
        }
      }
    } else if (strncmp("#o:", line, 3) == 0) {
      printf("Processing object\n");
      toks = strtok(line + 3, "|");
      object_id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(object_name, toks);
      toks = strtok(NULL, "|");
      object_location = atol(toks);

      object = object_create(object_id, object_location);
      if (object) {
        object_set_name(object, object_name);
        if (game_add_object(game, object) == ERROR) {
          object_destroy(object);
          status = ERROR;
          break;
        }
        space = game_get_space(game, object_location);
        if (space) {
          space_set_object(space, object_id);
        }
      }
    } else if (strncmp("#c:", line, 3) == 0) {
      printf("Processing character\n");
      toks = strtok(line + 3, "|");
      character_id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(character_name, toks);
      toks = strtok(NULL, "|");
      character_health = atol(toks);
      toks = strtok(NULL, "|");
      character_location = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(character_desc, toks);
      toks = strtok(NULL, "|");
      strcpy(character_message, toks);
      toks = strtok(NULL, "|");
      strcpy(character_friendliness, toks);

      character = character_create(character_id);
      if (character) {
        character_set_name(character, character_name);
        character_set_health(character, character_health);
        character_set_description(character, character_desc);
        character_set_message(character, character_message);
        character_set_friendly(character, strcmp(character_friendliness, "TRUE") == 0);
        if (game_add_character(game, character) == ERROR) {
          character_destroy(character);
          status = ERROR;
          break;
        }
        space = game_get_space(game, character_location);
        if (space) {
          space_set_character(space, character_id);
        }
      }
    } else if (strncmp("#l:", line, 3) == 0) {
      printf("Processing link\n");
      toks = strtok(line + 3, "|");
      link_id = atol(toks);
      toks = strtok(NULL, "|");
      toks = strtok(NULL, "|");
      origin = atol(toks);
      toks = strtok(NULL, "|");
      destination = atol(toks);
      toks = strtok(NULL, "|");
      dir = (Direction)atoi(toks);
      toks = strtok(NULL, "|");
      open = (atoi(toks) == 1) ? TRUE : FALSE;

      if (game_add_link(game, link_id, origin, destination, dir, open) == ERROR) {
        printf("Error adding link: %ld\n", link_id);
        status = ERROR;
        break;
      }
    } else if (strncmp("#p:", line, 3) == 0) {
      printf("Processing player\n");
      toks = strtok(line + 3, "|");
      player_id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(player_name, toks);
      toks = strtok(NULL, "|");
      strcpy(player_desc, toks);
      toks = strtok(NULL, "|");
      player_location = atol(toks);
      toks = strtok(NULL, "|");
      player_health = atol(toks);
      toks = strtok(NULL, "|");
      player_max_obj = atol(toks);

      player = player_create(player_id);
      if (player) {
        player_set_name(player, player_name);
        player_set_health(player, player_health);
        player_set_description(player, player_desc);
        player_set_max_objs(player, player_max_obj);
        player_set_location(player, player_location);
        if (game_add_player(game, player) == ERROR) {
          printf("Error adding player: %ld\n", player_id);
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