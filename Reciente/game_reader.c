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
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  Id object_id = NO_ID, object_location = NO_ID;
  Object *object = NULL;
  Character *character = NULL;
  Id character_id = NO_ID, character_location = NO_ID;
  Status status = OK;
  char gdesc[5][10];
  char character_desc[7], character_message[MAX_MESSAGE], character_friendliness[6];
  int i = 0;

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
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
      for (i = 0; i < 5; i++) {
        printf("Entering loop\n");
        toks = strtok(NULL, "|");
        printf("About to do strcpy\n");
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
        printf("Processing descriptions %d\n", i);
      }

      printf("Creating space with ID: %ld\n", id);
      space = space_create(id);
      if (space) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        for (i = 0; i < 5; i++) {
          space_set_description(space, gdesc);
        }
        if (game_add_space(game, space) == ERROR) {
          printf("Error adding space: %ld\n", id);
          space_destroy(space);
          status = ERROR;
          break;
        }
        printf("Space added successfully: %ld\n", id);
      } else {
        printf("Error creating space: %ld\n", id);
      }
    } else if (strncmp("#o:", line, 3) == 0) {
      printf("Processing object\n");
      toks = strtok(line + 3, "|");
      object_id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(object_name, toks);
      toks = strtok(NULL, "|");
      object_location = atol(toks);

      printf("Creating object with ID: %ld\n", object_id);
      object = object_create(object_id, object_location);
      if (object) {
        object_set_name(object, object_name); /*  Set the object name here */
        if (game_add_object(game, object) == ERROR) {
          printf("Error adding object: %ld\n", object_id);
          object_destroy(object);
          status = ERROR;
          break;
        }
        printf("Object added successfully: %ld\n", object_id);
        /*  Add object to the corresponding space */
        space = game_get_space(game, object_location);
        if (space) {
          space_set_object(space, object_id);
        }
      } else {
        printf("Error creating object: %ld\n", object_id);
      }
    } else if (strncmp("#c:", line, 3) == 0) {
      printf("Processing character\n");
      toks = strtok(line + 3, "|");
      character_id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(character_name, toks);
      toks = strtok(NULL, "|");
      character_location = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(character_desc, toks);
      toks = strtok(NULL, "|");
      strcpy(character_message, toks);
      toks = strtok(NULL, "|");
      strcpy(character_friendliness, toks);

      printf("Creating character with ID: %ld\n", character_id);
      character = character_create(character_id);
      if (character) {
        character_set_name(character, character_name); /*  Set the character name here */
        character_set_description(character, character_desc);
        character_set_message(character, character_message);
        if (strcmp(character_friendliness, "TRUE") == 0) {
          character_set_friendly(character, TRUE);
        } else if (strcmp(character_friendliness, "FALSE") == 0) {
          character_set_friendly(character, FALSE);
        }
        if (game_add_character(game, character) == ERROR) {
          printf("Error adding character: %ld\n", character_id);
          character_destroy(character);
          status = ERROR;
          break;
        }
        printf("Character added successfully: %ld\n", character_id);
        /*  Add character to the corresponding space */
        space = game_get_space(game, character_location);
        if (space) {
          space_set_character(space, character_id);
        }
      } else {
        printf("Error creating character: %ld\n", object_id);
      }
    }
  }

  if (ferror(file)) {
    printf("Error reading file: %s\n", filename);
    status = ERROR;
  }

  fclose(file);
  printf("File closed: %s\n", filename);
  return status;
}