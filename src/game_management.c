#include "game_management.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

Status game_init_from_file(Game *game, char *filename, Bool SDL) {
  Id first_space_id;

  if (!game || !filename) {
    printf("Error: Invalid game or filename\n");
    return ERROR;
  }

  if (game_init(game) == ERROR) {
    printf("Error: Could not create game\n");
    return ERROR;
  }

  if (game_management_load(game, filename, TRUE, SDL) == ERROR) {
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
  time_t current_time;
  char *date;

  /*CdE*/
  if (!game || !file_name) {
    return ERROR;
  }

  strcpy(save_path, "saves/");
  strcat(save_path, file_name);

  pf = fopen(save_path, "w");

  current_time = time(NULL);

  if (current_time == ((time_t)-1)) {
    return ERROR;
  }

  date = ctime(&current_time);
  if (!date) {
    return ERROR;
  }

  fprintf(pf, "-------------------------------------------------------------------------\n");
  fprintf(pf, "Info:\n");
  fprintf(pf, "- Last played: %s", date);
  fprintf(pf, "- Players:\n");
  for (i = 0; i < game_get_num_players(game); i++) {
    fprintf(pf, "   - %i. %s\n", i + 1, player_get_name(game_get_player_from_index(game, i)));
  }
  fprintf(pf, "- Current turn: %i (%s's turn)\n", game_get_turn(game),
          player_get_name(game_get_player_from_index(game, game_get_player_index_from_turn(game))));
  fprintf(pf, "-------------------------------------------------------------------------\n");

  fprintf(pf, "\nSpaces:\n");
  for (i = 0; i < game_get_num_spaces(game); i++) {
    space = game_get_space_from_index(game, i);
    /*id|name|discovered|image|gdesc|*/
    fprintf(pf, "#s:%li|%s|%i|%s|%s|%s|%s|%s|%s|\n", space_get_id(space), space_get_name(space), space_get_discovered(space),
            ((space_get_image(space)[0] == '\0') ? "." : space_get_image(space)), space_get_i_static_description(space, 0),
            space_get_i_static_description(space, 1), space_get_i_static_description(space, 2), space_get_i_static_description(space, 3),
            space_get_i_static_description(space, 4));
  }

  fprintf(pf, "\nPlayers:\n");
  for (i = 0; i < game_get_num_players(game); i++) {
    player = game_get_player_from_index(game, i);
    /*id|name|gdesc|location|health|inventory_size|message|object_desc|max_turns|x|y|image|*/
    fprintf(pf, "#p:%li|%s|%s|%li|%li|%i|%s|%s|%i|%i|%i|%s|\n", player_get_id(player), player_get_name(player), player_get_description(player),
            player_get_location(player), player_get_health(player), inventory_get_max_objects(player_get_inventory(player)),
            ((game_get_message_from_index(game, i)[0] == '\0') ? "." : game_get_message_from_index(game, i)),
            ((game_get_object_desc_from_index(game, i)[0] == '\0') ? "." : game_get_object_desc_from_index(game, i)),
            game_get_player_max_turns(game, player_get_id(player)), player_get_x(player), player_get_y(player),
            ((player_get_image(player)[0] == '\0') ? "." : player_get_image(player)));
  }

  fprintf(pf, "\nLinks:\n");
  for (i = 0; i < game_get_num_links(game); i++) {
    link = game_get_link_from_index(game, i);
    /*id|name|origin|destination|direction|open|image|*/
    fprintf(pf, "#l:%li|%s|%li|%li|%i|%i|%s|\n", link_get_id(link), link_get_name(link), link_get_start(link), link_get_end(link),
            link_get_direction(link), link_get_open(link), ((link_get_image(link)[0] == '\0') ? "." : link_get_image(link)));
  }

  fprintf(pf, "\nCharacters:\n");
  for (i = 0; i < game_get_num_characters(game); i++) {
    character = game_get_character_from_index(game, i);
    /*id|name|location|health|gdesc|message|friendliness|x|y|image|*/
    fprintf(pf, "#c:%li|%s|%li|%li|%s|%s|%i|%i|%i|%s|\n", character_get_id(character), character_get_name(character),
            game_get_character_location(game, character_get_id(character)), character_get_health(character), character_get_description(character),
            character_get_message(character), character_get_friendly(character), character_get_x(character), character_get_y(character),
            ((character_get_image(character)[0] == '\0') ? "." : character_get_image(character)));
  }

  fprintf(pf, "\nObjects:\n");
  for (i = 0; i < game_get_num_objects(game); i++) {
    object = game_get_object_from_index(game, i);
    printf("%s is at %li [%s]\n", object_get_name(object), game_get_object_location(game, object_get_id(object)),
           (game_get_id_type(game, game_get_object_location(game, object_get_id(object))) == PLAYER) ? (char *)"player" : (char *)"space");
    /*id|name|location|health|movable|dependency|open_door|inspected|desc|x|y|image|*/
    fprintf(pf, "#o:%li|%s|%li|%i|%i|%li|%li|%i|%s|%i|%i|%s|\n", object_get_id(object), object_get_name(object),
            game_get_object_location(game, object_get_id(object)), object_get_health(object), object_is_movable(object),
            object_get_dependency(object), object_get_open(object), object_get_inspected(object), object_get_desc(object), object_get_x(object),
            object_get_y(object), ((object_get_image(object)[0] == '\0') ? "." : object_get_image(object)));
  }

  fclose(pf);

  return OK;
}

/**
 * @brief It loads a player's game from a certain file
 */
Status game_management_load(Game *game, char *file_name, Bool new, Bool SDL) {
  /*PLAYER*/
  Player *player = NULL;
  int player_max_obj = 0;
  char player_desc[7];
  Id location = NO_ID;
  int max_turns;

  /*CHARACTER*/
  Character *character = NULL;
  char character_desc[7];
  char character_message[MAX_MESSAGE];
  Bool character_friendliness;

  /*OBJECT*/
  Object *object = NULL;
  char object_desc[WORD_SIZE];
  int movable;
  Bool inspected = FALSE; /*PREVIOUS*/
  Id dependency;
  Id open_door;
  int turn_amplifier;
  int uses;

  /*SPACE*/
  Space *space = NULL;
  char space_desc[5][10];
  /*char space_zoom_desc[17][WORD_SIZE];*/
  Bool discovered = FALSE; /*PREVIOUS*/

  /*LINK*/
  Link *link = NULL;
  Id link_origin = NO_ID;
  Id link_destination = NO_ID;
  Direction dir = NO_DIR;
  Bool open = FALSE;
  char open_image[MAX_MESSAGE], closed_image[MAX_MESSAGE];

  /*OBSTACLE (SDL2)*/
  Obstacle *obstacle = NULL;
  int width, height;

  /*GENERAL*/
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char *toks = NULL;
  char name[WORD_SIZE] = "";
  char save_path[WORD_SIZE]; /*PREVIOUS*/
  char message[WORD_SIZE];   /*PREVIOUS*/
  int i = 0;
  int health = 0;
  int current_turn = 0;
  Id id = NO_ID;
  Status status = OK;
  char image[WORD_SIZE] = ""; /*SDL2*/
  int x, y;
  char north_image_1[MAX_MESSAGE], east_image_1[MAX_MESSAGE], south_image_1[MAX_MESSAGE], west_image_1[MAX_MESSAGE]; /*SDL2*/
  char north_image_2[MAX_MESSAGE], east_image_2[MAX_MESSAGE], south_image_2[MAX_MESSAGE], west_image_2[MAX_MESSAGE]; /*SDL2*/
  char north_image_3[MAX_MESSAGE], east_image_3[MAX_MESSAGE], south_image_3[MAX_MESSAGE], west_image_3[MAX_MESSAGE]; /*SDL2*/

  /*CdE*/
  if (!game || !file_name) {
    return ERROR;
  }

  if (new == FALSE) {
    game_destroy(game, FALSE); /*PREVIOUS*/
    game_init(game);           /*PREVIOUS*/

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
      /*id|name|discovered|image|zoom|gdesc|*/
      printf("Processing space\n");
      toks = strtok(line + 3, "|");
      id = atol(toks);

      toks = strtok(NULL, "|");
      strcpy(name, toks);

      if (new == FALSE) {
        toks = strtok(NULL, "|"); /*PREVIOUS*/
        discovered = atol(toks);  /*PREVIOUS*/
      }

      /*for (i = 0; i < 17; i++) {
        toks = strtok(NULL, "|");
        strcpy(space_zoom_desc[i], toks);
      }*/

      toks = strtok(NULL, "|");
      if (toks) {
        strcpy(image, toks);
        printf("----------Image path is [%s]\n", image);
      }

      for (i = 0; i < 5; i++) {
        toks = strtok(NULL, "|");
        if (!toks || (strcmp(toks, ".") == 0)) {
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
        if (SDL == TRUE) {
          space_set_image(space, image);
        }

        if (new == FALSE) {
          space_set_discovered(space, discovered); /*PREVIOUS*/
        }

        /*space_set_zoom_description(space, space_zoom_desc);*/
        space_set_description(space, space_desc);

        if (game_add_space(game, space) == ERROR) {
          space_destroy(space);
          status = ERROR;
          break;
        }
      }

      /*OBJECTS*/
    } else if (strncmp("#o:", line, 3) == 0) {
      /*id|name|location|health|movable|dependency|open_door|inspected|desc|turn_amplifier|x|y|image|*/
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
      movable = atoi(toks);

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

      toks = strtok(NULL, "|");
      turn_amplifier = atoi(toks);

      toks = strtok(NULL, "|");
      uses = atoi(toks);

      if (SDL == TRUE) {
        toks = strtok(NULL, "|");
        x = atoi(toks);

        toks = strtok(NULL, "|");
        y = atoi(toks);

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(image, toks);
          printf("----------Image path is [%s]\n", image);
        }
      }

      object = object_create(id, location);
      if (object) {
        object_set_name(object, name);
        if (object_desc[0] != '.') {
          object_set_desc(object, object_desc);
        }
        object_set_health(object, health);
        object_set_movable(object, movable);
        object_set_dependency(object, dependency);
        object_set_open(object, open_door);
        object_set_turn_amplifier(object, turn_amplifier);
        object_set_uses(object, uses);

        if (SDL == TRUE) {
          printf("Setting object image [%s]\n", image);
          object_set_image(object, image);
          object_set_position(object, x, y);
        }

        if (new == FALSE) {
          object_set_inspected(object, inspected); /*PREVIOUS*/
        }

        if (game_add_object(game, object) == ERROR) {
          object_destroy(object);
          status = ERROR;
          break;
        }

        if (game_set_object_location(game, location, id) == ERROR) {
          status = ERROR;
        }
        printf("Object %s is at %li with %d uses\n", object_get_name(object), game_get_object_location(game, id), object_get_uses(object));
      }

      /*CHARACTERS*/
    } else if (strncmp("#c:", line, 3) == 0) {
      /*id|name|location|health|gdesc|message|friendliness|x|y|image|*/
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
      if (strcmp(toks, "FALSE") == 0) {
        character_friendliness = FALSE;
      } else {
        character_friendliness = TRUE;
      }

      if (SDL == TRUE) {
        toks = strtok(NULL, "|");
        x = atoi(toks);

        toks = strtok(NULL, "|");
        y = atoi(toks);

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(north_image_1, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(north_image_2, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(north_image_3, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(east_image_1, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(east_image_2, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(east_image_3, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(south_image_1, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(south_image_2, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(south_image_3, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(west_image_1, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(west_image_2, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(west_image_3, toks);
        }
      }

      character = character_create(id);
      if (character) {
        character_set_name(character, name);
        character_set_health(character, health);
        character_set_description(character, character_desc);
        character_set_message(character, character_message);
        character_set_friendly(character, character_friendliness);

        if (SDL == TRUE) {
          character_set_position(character, x, y);
          character_set_image(character, north_image_1, north_image_2, north_image_3);
          character_set_north_image(character, north_image_1, 0);
          character_set_north_image(character, north_image_2, 1);
          character_set_north_image(character, north_image_3, 2);
          character_set_east_image(character, east_image_1, 0);
          character_set_east_image(character, east_image_2, 1);
          character_set_east_image(character, east_image_3, 2);
          character_set_south_image(character, south_image_1, 0);
          character_set_south_image(character, south_image_2, 1);
          character_set_south_image(character, south_image_3, 2);
          character_set_west_image(character, west_image_1, 0);
          character_set_west_image(character, west_image_2, 1);
          character_set_west_image(character, west_image_3, 2);
        }

        if (game_add_character(game, character) == ERROR) {
          character_destroy(character);
          status = ERROR;
          break;
        }

        space = game_get_space(game, location);
        if (space) {
          space_add_character(space, id);
        }
      }

      /*LINKS*/
    } else if (strncmp("#l:", line, 3) == 0) {
      /*id|name|origin|destination|direction|open|closed_image|open_image|*/
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

      if (SDL == TRUE) {
        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(closed_image, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(open_image, toks);
        }
      }

      link = link_create(id);
      if (link) {
        link_set_name(link, name);
        link_set_start(link, link_origin);
        link_set_end(link, link_destination);
        link_set_direction(link, dir);
        link_set_open(link, open);

        if (SDL == TRUE) {
          link_set_image(link, closed_image, 0);
          link_set_image(link, open_image, 1);
        }

        if (game_add_link(game, link) == ERROR) {
          link_destroy(link);
          status = ERROR;
          break;
        }
      }

    } else if (strncmp("#p:", line, 3) == 0) {
      /*id|name|gdesc|location|health|inventory_size|message|object_desc|max_turns|x|y|n1|n2|n3|e1|e2|e3|s1|s2|s3|w1|w2|w3*/
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

      toks = strtok(NULL, "|");
      max_turns = atoi(toks);

      if (SDL == TRUE) {
        toks = strtok(NULL, "|");
        x = atoi(toks);

        toks = strtok(NULL, "|");
        y = atoi(toks);

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(north_image_1, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(north_image_2, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(north_image_3, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(east_image_1, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(east_image_2, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(east_image_3, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(south_image_1, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(south_image_2, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(south_image_3, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(west_image_1, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(west_image_2, toks);
        }

        toks = strtok(NULL, "|");
        if (toks) {
          strcpy(west_image_3, toks);
        }
      }

      player = player_create(id);
      if (player) {
        player_set_name(player, name);
        player_set_health(player, health);
        player_set_description(player, player_desc);
        player_set_max_objs(player, player_max_obj);
        player_set_location(player, location);
        player_set_max_turns(player, max_turns);

        if (SDL == TRUE) {
          player_set_position(player, x, y);
          player_set_image(player, north_image_1, north_image_2, north_image_3);
          player_set_north_image(player, north_image_1, 0);
          player_set_north_image(player, north_image_2, 1);
          player_set_north_image(player, north_image_3, 2);
          player_set_east_image(player, east_image_1, 0);
          player_set_east_image(player, east_image_2, 1);
          player_set_east_image(player, east_image_3, 2);
          player_set_south_image(player, south_image_1, 0);
          player_set_south_image(player, south_image_2, 1);
          player_set_south_image(player, south_image_3, 2);
          player_set_west_image(player, west_image_1, 0);
          player_set_west_image(player, west_image_2, 1);
          player_set_west_image(player, west_image_3, 2);
        }

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
    } else if ((strncmp("#g:", line, 3) == 0) && (SDL == TRUE)) {
      printf("Processing obstacle\n");
      toks = strtok(line + 3, "|");
      id = atol(toks);

      toks = strtok(NULL, "|");
      strcpy(name, toks);

      toks = strtok(NULL, "|");
      x = atoi(toks);

      toks = strtok(NULL, "|");
      y = atoi(toks);

      toks = strtok(NULL, "|");
      width = atoi(toks);

      toks = strtok(NULL, "|");
      height = atoi(toks);

      toks = strtok(NULL, "|");
      location = atol(toks);

      toks = strtok(NULL, "|");
      strcpy(image, toks);
      printf("----------Image path is [%s]\n", image);

      obstacle = obstacle_create(id, x, y, width, height);
      if (obstacle) {
        space = game_get_space(game, location);
        if (space) {
          space_add_obstacle(space, obstacle);
        }
        obstacle_set_image(obstacle, image);
      }

    } else if (strncmp("- Current turn: ", line, 16) == 0) {
      printf("Processing turn\n");
      toks = strtok(line + 16, "|");
      current_turn = atoi(toks);

      game_set_turn(game, current_turn);
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);
  return status;
}
