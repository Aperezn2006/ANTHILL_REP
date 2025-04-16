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

  if (game_management_load(game, filename, NULL, TRUE) == ERROR) {
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

/**
 * @brief It saves the current game's info in a specified file
 */
Status game_management_save(Game *game, char *file_name) {
  int i = 0;
  FILE *pf = NULL;
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

  fprintf(pf, "Spaces:\n");
  for (i = 0; i < game_get_num_spaces(game); i++) {
    space = game_get_space_from_index(game, i);
    /*id|name|discovered|gdesc*/
    fprintf(pf, "#s:%li|%s|%i|%s|%s|%s|%s|%s|\n", space_get_id(space), space_get_name(space), space_get_discovered(space),
            space_get_i_static_description(space, 0), space_get_i_static_description(space, 1), space_get_i_static_description(space, 2),
            space_get_i_static_description(space, 3), space_get_i_static_description(space, 4));
  }

  fprintf(pf, "\nPlayers:\n");
  for (i = 0; i < game_get_num_players(game); i++) {
    player = game_get_player_from_index(game, i);
    /*id|name|gdesc|location|health|inventory_size|message|object_desc*/
    fprintf(pf, "#p:%li|%s|%s|%li|%li|%i|%s|%s|\n", player_get_id(player), player_get_name(player), player_get_description(player),
            player_get_location(player), player_get_health(player), inventory_get_max_objects(player_get_inventory(player)),
            ((game_get_message_from_index(game, i)[0] == '\0') ? "." : game_get_message_from_index(game, i)),
            ((game_get_object_desc_from_index(game, i)[0] == '\0') ? "." : game_get_object_desc_from_index(game, i)));
  }

  fprintf(pf, "\nLinks:\n");
  for (i = 0; i < game_get_num_links(game); i++) {
    link = game_get_link_from_index(game, i);
    /*id|name|origin|destination|direction|open*/
    fprintf(pf, "#l:%li|%s|%li|%li|%i|%i|\n", link_get_id(link), link_get_name(link), link_get_start(link), link_get_end(link),
            link_get_direction(link), link_get_open(link));
  }

  fprintf(pf, "\nCharacters:\n");
  for (i = 0; i < game_get_num_characters(game); i++) {
    character = game_get_character_from_index(game, i);
    /*id|name|location|health|gdesc|message|friendliness*/
    fprintf(pf, "#c:%li|%s|%li|%li|%s|%s|%i|\n", character_get_id(character), character_get_name(character),
            game_get_character_location(game, character_get_id(character)), character_get_health(character), character_get_description(character),
            character_get_message(character), character_get_friendly(character));
  }

  fprintf(pf, "\nObjects:\n");
  for (i = 0; i < game_get_num_objects(game); i++) {
    object = game_get_object_from_index(game, i);
    /*id|name|location|health|movable|dependency|open_door|inspected|desc|*/
    fprintf(pf, "#o:%li|%s|%li|%i|%i|%li|%li|%i|%s|\n", object_get_id(object), object_get_name(object),
            game_get_object_location(game, object_get_id(object)), object_get_health(object), object_is_movable(object),
            object_get_dependency(object), object_get_open(object), object_get_inspected(object), object_get_desc(object));
  }

  fclose(pf);

  return OK;
}

/**
 * @brief It loads a player's game from a certain file
 */
Status game_management_load(Game *game, char *file_name, Graphic_engine *gengine, Bool new) {
  /*PLAYER*/
  Player *player = NULL;
  int player_max_obj = 0;
  char player_desc[7];
  Id location = NO_ID;

  /*CHARACTER*/
  Character *character = NULL;
  char character_desc[7];
  char character_message[MAX_MESSAGE];
  Bool character_friendliness;

  /*OBJECT*/
  Object *object = NULL;
  char object_desc[WORD_SIZE];
  Bool movable;
  Bool inspected = FALSE; /*PREVIOUS*/
  Id dependency;
  Id open_door;

  /*SPACE*/
  Space *space = NULL;
  char space_desc[5][10];
  Bool discovered = FALSE; /*PREVIOUS*/

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
  char save_path[WORD_SIZE]; /*PREVIOUS*/
  char message[WORD_SIZE];   /*PREVIOUS*/
  int i = 0;
  int health = 0;
  Id id = NO_ID;
  Status status = OK;

  /*CdE*/
  if (!game || !file_name) {
    return ERROR;
  }

  if (new == FALSE) {
    game_destroy(game);  /*PREVIOUS*/
    game = game_alloc(); /*PREVIOUS*/
    if (!game) {
      return ERROR;
    }
    game_init(game); /*PREVIOUS*/

    strcpy(save_path, "saves/");  /*PREVIOUS*/
    strcat(save_path, file_name); /*PREVIOUS*/

    file = fopen(save_path, "r"); /*PREVIOUS*/
  } else {
    file = fopen(file_name, "r");
  }

  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    printf("Reading line: %s", line);

    /*SPACES*/
    if (strncmp("#s:", line, 3) == 0) {
      /*id|name|discovered|gdesc*/
      printf("Processing space\n");
      toks = strtok(line + 3, "|");
      id = atol(toks);

      toks = strtok(NULL, "|");
      strcpy(name, toks);

      if (new == FALSE) {
        toks = strtok(NULL, "|"); /*PREVIOUS*/
        discovered = atol(toks);  /*PREVIOUS*/
      }

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
        if (new == FALSE) {
          space_set_discovered(space, discovered); /*PREVIOUS*/
        }
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
      /*id|name|location|health|movable|dependency|open_door|inspected|desc|*/
      printf("Processing object\n");
      toks = strtok(line + 3, "|");
      id = atol(toks);

      toks = strtok(NULL, "|");
      strcpy(name, toks);

      toks = strtok(NULL, "|");
      location = atol(toks);

      toks = strtok(NULL, "|");
      health = atoi(toks);

      toks = strtok(NULL, "|");
      movable = (atoi(toks) != 0) ? TRUE : FALSE;

      toks = strtok(NULL, "|");
      dependency = atol(toks);

      toks = strtok(NULL, "|");
      open_door = atol(toks);

      if (new == FALSE) {
        toks = strtok(NULL, "|"); /*PREVIOUS*/
        inspected = atol(toks);   /*PREVIOUS*/
      }

      toks = strtok(NULL, "|");
      strcpy(object_desc, toks);

      object = object_create(id, location);
      if (object) {
        object_set_name(object, name);
        object_set_desc(object, object_desc);
        object_set_health(object, health);
        object_set_movable(object, movable);
        object_set_dependency(object, dependency);
        object_set_open(object, open_door);
        if (new == FALSE) {
          object_set_inspected(object, inspected); /*PREVIOUS*/
        }

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
      /*id|name|location|health|gdesc|message|friendliness*/
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
      character_friendliness = atoi(toks);

      character = character_create(id);
      if (character) {
        character_set_name(character, name);
        character_set_health(character, health);
        character_set_description(character, character_desc);
        character_set_message(character, character_message);
        character_set_friendly(character, character_friendliness);

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
      /*id|name|origin|destination|direction|open*/
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
      open = atoi(toks);

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
      /*id|name|gdesc|location|health|inventory_size|message|object_desc*/
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
      player_max_obj = atoi(toks);

      if (new == FALSE) {
        toks = strtok(NULL, "|"); /*REVIOUS*/
        strcpy(message, toks);    /*REVIOUS*/

        toks = strtok(NULL, "|");  /*REVIOUS*/
        strcpy(object_desc, toks); /*REVIOUS*/
      }

      player = player_create(id);
      if (player) {
        player_set_name(player, name);
        player_set_health(player, health);
        player_set_description(player, player_desc);
        player_set_max_objs(player, player_max_obj);
        player_set_location(player, location);
        if (new == FALSE) {
          if (strcmp(message, ".") != 0) { /*REVIOUS*/
            game_set_message_from_index(game, message, game_get_num_players(game));
          }
          if (strcmp(object_desc, ".") != 0) { /*REVIOUS*/
            game_set_object_desc_from_index(game, object_desc, game_get_num_players(game));
          }
        }

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
    status = ERROR;
  }

  fclose(file);
  return status;
}
