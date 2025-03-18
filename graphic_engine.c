/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @version 2
 * @date 14-03-2025
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "game.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"

#define WIDTH_MAP 68
#define WIDTH_DES 29
#define WIDTH_BAN 23
#define HEIGHT_MAP 29
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
};

/**
 * @brief It makes sure there are no empty spaces at the beginning of a string
 * @author Rubén
 *
 * @param str a pointer to a string
 * @return nothing
 */
void graphic_engine_erase_left_spaces(char *str1);

/**
 * @brief It puts the strings 1-9 on the screen
 * @author Ana
 *
 * @param ge a pointer to the graphic engine
 * @param str(i) a string where a section of the screen is defined
 * @return nothing
 */
void graphic_engine_some_screen_puts(Graphic_engine *ge, char *str1, char *str2, char *str3, char *str4, char *str5, char *str6, char *str7,
                                     char *str8, char *str9);

Graphic_engine *graphic_engine_create() {
  static Graphic_engine *ge = NULL;

  if (ge) {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL) {
    return NULL;
  }

  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) {
    return;
  }

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  int i = 0, n_inventory = 0;
  Space *space_act = NULL;
  Object *obj = NULL;
  Character *character = NULL;
  CommandCode last_cmd = UNKNOWN;
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, id_east = NO_ID, id_west = NO_ID;
  Id obj_id, obj_loc;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  char str1[1024], str2[1024], str3[1024], str4[1024], str5[1024], str6[1024], str7[1024], str8[1024], str9[1024], str10[1024], temp[1204];
  char objects[BOX_WIDTH + 1], result[10], character_desc[7];

  screen_area_clear(ge->map);

  id_act = game_get_player_location(game);
  if (id_act != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    id_east = space_get_east(space_act);
    id_west = space_get_west(space_act);
  }

  /*  Espacio BACK */
  if (id_back != NO_ID) {
    strcpy(objects, "");
    game_get_string_of_objects_in_space(game, id_back, objects);
    if (game_get_character_desc_at_space(game, id_back) == NULL) {
      strcpy(character_desc, "      ");
    } else {
      strcpy(character_desc, game_get_character_desc_at_space(game, id_back));
    }

    sprintf(str1, "                        +------------------+");
    if (id_back >= 100) {
      sprintf(str2, "                        |        %s %2d|", character_desc, (int)id_back);
    } else {
      sprintf(str2, "                        |         %s %2d|", character_desc, (int)id_back);
    }
    sprintf(str3, "                        |%s         |", space_get_n_description(game_get_space(game, id_back), 0));
    sprintf(str4, "                        |%s         |", space_get_n_description(game_get_space(game, id_back), 1));
    sprintf(str5, "                        |%s         |", space_get_n_description(game_get_space(game, id_back), 2));
    sprintf(str6, "                        |%s         |", space_get_n_description(game_get_space(game, id_back), 3));
    sprintf(str7, "                        |%s         |", space_get_n_description(game_get_space(game, id_back), 4));
    sprintf(str8, "                        |%s|", objects);
    sprintf(str9, "                        +------------------+");
    sprintf(str10, "                                 /\\");

    graphic_engine_some_screen_puts(ge, str1, str2, str3, str4, str5, str6, str7, str8, str9);
    screen_area_puts(ge->map, str10);
  } else if (id_back == NO_ID) {
    /*  Esto es para que la casilla del jugador siempre esté centrada */
    sprintf(str1, "                              ");
    sprintf(str2, "                              ");
    sprintf(str3, "                              ");
    sprintf(str4, "                              ");
    sprintf(str5, "                              ");
    sprintf(str6, "                              ");
    sprintf(str7, "                              ");
    sprintf(str8, "                              ");
    sprintf(str9, "                              ");
    sprintf(str10, "                              ");

    graphic_engine_some_screen_puts(ge, str1, str2, str3, str4, str5, str6, str7, str8, str9);
    screen_area_puts(ge->map, str10);
  }

  /*  Espacio ACTUAL */
  if (id_act != NO_ID) {
    strcpy(objects, "");
    game_get_string_of_objects_in_space(game, id_act, objects);
    if (game_get_character_desc_at_space(game, id_act) == NULL) {
      strcpy(character_desc, "      ");
    } else {
      strcpy(character_desc, game_get_character_desc_at_space(game, id_act));
    }
    sprintf(str1, "                        +------------------+");
    if (id_act >= 100) {
      sprintf(str2, "                        | m0^    %s %2d|", character_desc, (int)id_act);
    } else {
      sprintf(str2, "                        | m0^     %s %2d|", character_desc, (int)id_act);
    }
    sprintf(str3, "                        |%s         |", space_get_n_description(game_get_space(game, id_act), 0));
    sprintf(str4, "                        |%s         |", space_get_n_description(game_get_space(game, id_act), 1));
    sprintf(str5, "                        |%s         |", space_get_n_description(game_get_space(game, id_act), 2));
    sprintf(str6, "                        |%s         |", space_get_n_description(game_get_space(game, id_act), 3));
    sprintf(str7, "                        |%s         |", space_get_n_description(game_get_space(game, id_act), 4));
    sprintf(str8, "                        |%s|", objects);
    sprintf(str9, "                        +------------------+");
    sprintf(str10, "                                    ");

    /*  Si hay espacio a la derecha (id_east), concatenar */
    if (id_east != NO_ID) {
      strcpy(objects, "");
      game_get_string_of_objects_in_space(game, id_east, objects);
      if (game_get_character_desc_at_space(game, id_east) == NULL) {
        strcpy(character_desc, "      ");
      } else {
        strcpy(character_desc, game_get_character_desc_at_space(game, id_east));
      }
      strcat(str1, "   +------------------+");
      if (id_east >= 100) {
        sprintf(temp, "   |        %s %2d|", character_desc, (int)id_east);
      } else {
        sprintf(temp, "   |         %s %2d|", character_desc, (int)id_east);
      }
      strcat(str2, temp);
      sprintf(temp, "   |%s         |", space_get_n_description(game_get_space(game, id_east), 0));
      strcat(str3, temp);
      sprintf(temp, "   |%s         |", space_get_n_description(game_get_space(game, id_east), 1));
      strcat(str4, temp);
      sprintf(temp, " > |%s         |", space_get_n_description(game_get_space(game, id_east), 2));
      strcat(str5, temp);
      sprintf(temp, "   |%s         |", space_get_n_description(game_get_space(game, id_east), 3));
      strcat(str6, temp);
      sprintf(temp, "   |%s         |", space_get_n_description(game_get_space(game, id_east), 4));
      strcat(str7, temp);
      sprintf(temp, "   |%s|", objects);
      strcat(str8, temp);
      sprintf(temp, "   +------------------+");
      strcat(str9, temp);
      sprintf(temp, "                       ");
      strcat(str10, temp);
    }

    /*  Si hay espacio a la izquierda (id_west), no agregamos espacio adicional
    antes de str2 */
    if (id_west != NO_ID) {
      strcpy(objects, "");
      game_get_string_of_objects_in_space(game, id_west, objects);
      if (game_get_character_desc_at_space(game, id_west) == NULL) {
        strcpy(character_desc, "      ");
      } else {
        strcpy(character_desc, game_get_character_desc_at_space(game, id_west));
      }
      graphic_engine_erase_left_spaces(str1);
      graphic_engine_erase_left_spaces(str2);
      graphic_engine_erase_left_spaces(str3);
      graphic_engine_erase_left_spaces(str4);
      graphic_engine_erase_left_spaces(str5);
      graphic_engine_erase_left_spaces(str6);
      graphic_engine_erase_left_spaces(str7);
      graphic_engine_erase_left_spaces(str8);
      graphic_engine_erase_left_spaces(str9);
      graphic_engine_erase_left_spaces(str10);
      sprintf(temp, " +------------------+   %s", str1);
      strcpy(str1, temp);
      if (id_west >= 100) {
        sprintf(temp, " |        %s %2d|   %s", character_desc, (int)id_west, str2);
      } else {
        sprintf(temp, " |         %s %2d|   %s", character_desc, (int)id_west, str2);
      }
      strcpy(str2, temp);
      sprintf(temp, " |%s         |   %s", space_get_n_description(game_get_space(game, id_west), 0), str3);
      strcpy(str3, temp);
      sprintf(temp, " |%s         |   %s", space_get_n_description(game_get_space(game, id_west), 1), str4);
      strcpy(str4, temp);
      sprintf(temp, " |%s         | < %s", space_get_n_description(game_get_space(game, id_west), 2), str5);
      strcpy(str5, temp);
      sprintf(temp, " |%s         |   %s", space_get_n_description(game_get_space(game, id_west), 3), str6);
      strcpy(str6, temp);
      sprintf(temp, " |%s         |   %s", space_get_n_description(game_get_space(game, id_west), 4), str7);
      strcpy(str7, temp);
      sprintf(temp, " |%s|   %s", objects, str8);
      strcpy(str8, temp);
      sprintf(temp, " +------------------+   %s", str9);
      strcpy(str9, temp);
      sprintf(temp, "                        %s", str10);
      strcpy(str10, temp);
    }

    graphic_engine_some_screen_puts(ge, str1, str2, str3, str4, str5, str6, str7, str8, str9);
  }

  /*  Espacio NEXT */
  if (id_next != NO_ID) {
    strcpy(objects, "");
    game_get_string_of_objects_in_space(game, id_next, objects);
    if (game_get_character_desc_at_space(game, id_next) == NULL) {
      strcpy(character_desc, "      ");
    } else {
      strcpy(character_desc, game_get_character_desc_at_space(game, id_next));
    }
    sprintf(str1, "                                 \\/");
    sprintf(str2, "                        +------------------+");
    if (id_next >= 100) {
      sprintf(str3, "                        |        %s %2d|", character_desc, (int)id_next);
    } else {
      sprintf(str3, "                        |         %s %2d|", character_desc, (int)id_next);
    }
    sprintf(str4, "                        |%s         |", space_get_n_description(game_get_space(game, id_next), 0));
    sprintf(str5, "                        |%s         |", space_get_n_description(game_get_space(game, id_next), 1));
    sprintf(str6, "                        |%s         |", space_get_n_description(game_get_space(game, id_next), 2));
    sprintf(str7, "                        |%s         |", space_get_n_description(game_get_space(game, id_next), 3));
    sprintf(str8, "                        |%s         |", space_get_n_description(game_get_space(game, id_next), 4));
    sprintf(str9, "                        |%s|", objects);
    sprintf(str10, "                        +------------------+");

    graphic_engine_some_screen_puts(ge, str1, str2, str3, str4, str5, str6, str7, str8, str9);
    screen_area_puts(ge->map, str10);
  }

  /*  Pintar descripción */
  screen_area_clear(ge->descript);

  /*  Bucle para los objetos fuera del inventario */

  screen_area_puts(ge->descript, " ");

  sprintf(str1, " Objects:"); /*  Banner */
  screen_area_puts(ge->descript, str1);

  for (i = 0; i < game_get_num_objects(game); i++) {
    Object *obj = game_get_n_object(game, i);
    if (obj == NULL) {
      printf("Object %d is NULL\n", i); /*  Debug statement */
      continue;
    }

    obj_id = object_get_id(obj);
    obj_loc = game_get_object_location(game, obj_id);

    if (obj_loc != NO_ID) {
      if (obj_loc == player_get_id(game_get_player(game))) {
        sprintf(str1, "  %s: Player", object_get_name(obj));
      } else {
        sprintf(str1, "  %s: %d", object_get_name(obj), (int)obj_loc);
        screen_area_puts(ge->descript, str1);
      }
    }
  }

  /* Characters */
  if (game_get_num_characters(game) > 0) {
    sprintf(str1, " "); /*  Hueco para que quede mono */
    screen_area_puts(ge->descript, str1);
    sprintf(str1, " Characters:");
    screen_area_puts(ge->descript, str1);
    for (i = 0; i < game_get_num_characters(game); i++) {
      character = game_get_n_character(game, i);

      if (game_get_character_location(game, character_get_id(character)) != NO_ID) {
        sprintf(str1, "  %s : %li (%li)", character_get_description(character), game_get_character_location(game, character_get_id(character)),
                character_get_health(character));
      } else {
        /*character_set_description(character, "/RIP\\_"); Molaba pero era poco intuitivo*/
        sprintf(str1, "  %s : Dead", character_get_description(character));
      }

      screen_area_puts(ge->descript, str1);
    }
  }

  /* Player */
  sprintf(str1, " "); /*  Hueco para que quede mono */
  screen_area_puts(ge->descript, str1);
  sprintf(str1, " Player: %li (%li)", game_get_player_location(game), player_get_health(game_get_player(game)));
  screen_area_puts(ge->descript, str1);

  /*  Bucle para los objetos dentro del inventario */
  sprintf(str1, " "); /*  Hueco para que quede mono */
  screen_area_puts(ge->descript, str1);
  sprintf(str1, " Inventory:"); /*  Banner */
  screen_area_puts(ge->descript, str1);

  for (i = 0; i < game_get_num_objects(game); i++) {
    obj = game_get_n_object(game, i);
    if (obj == NULL) {
      printf("Object %d is NULL\n", i); /*  Debug statement */
      continue;
    }

    obj_id = object_get_id(obj);
    obj_loc = game_get_object_location(game, obj_id);
    printf("Object ID: %ld, Location: %ld\n", obj_id, obj_loc); /*  Debug statement */

    if (obj_loc != NO_ID) {
      if (obj_loc == player_get_id(game_get_player(game))) {
        sprintf(str1, "  %s", object_get_name(obj));
        n_inventory++;
        screen_area_puts(ge->descript, str1);
      } else {
        sprintf(str1, "  %s: %d", object_get_name(obj), (int)obj_loc);
      }
    }
  }

  if (n_inventory == 0) {
    sprintf(str1, "  Player has no objects");
    screen_area_puts(ge->descript, str1);
  }

  /*  Message */
  if (game_get_message(game)[0] != '\0') {
    sprintf(str1, " "); /*  Hueco para que quede mono */
    screen_area_puts(ge->descript, str1);
    sprintf(str1, " Message: %s", game_get_message(game)); /*  Banner */
    screen_area_puts(ge->descript, str1);
  }

  /*  Pintar banner */
  screen_area_puts(ge->banner, "    The anthill game ");

  /*  Pintar ayuda */
  screen_area_clear(ge->help);
  sprintf(str1, " The commands you can use are:");
  screen_area_puts(ge->help, str1);
  sprintf(str1, "    next or n, back or b, t or take, d or drop, r or right, l or left, a or attack, c or chat,        exit or e");
  screen_area_puts(ge->help, str1);

  /*  Pintar feedback */
  last_cmd = command_get_code(game_get_last_command(game));
  if (command_get_result(game_get_last_command(game)) == OK) {
    strcpy(result, "OK");
  } else if (command_get_result(game_get_last_command(game)) == ERROR) {
    strcpy(result, "ERROR");
  }
  sprintf(str1, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], result);
  screen_area_puts(ge->feedback, str1);

  /*  Renderizar en la terminal */
  screen_paint();
  printf("prompt:> ");
}

void graphic_engine_erase_left_spaces(char *str1) {
  int i = 0, j = 0;

  /*  Recorremos la cadena hasta encontrar el primer carácter no espacio */
  while (str1[i] == ' ') {
    i++;
  }

  /*  Movemos el resto de la cadena hacia la izquierda */
  while (str1[i]) {
    str1[j++] = str1[i++];
  }

  /*  Terminamos la cadena sin los espacios iniciales */
  str1[j] = '\0';
}

void graphic_engine_some_screen_puts(Graphic_engine *ge, char *str1, char *str2, char *str3, char *str4, char *str5, char *str6, char *str7,
                                     char *str8, char *str9) {
  screen_area_puts(ge->map, str1);
  screen_area_puts(ge->map, str2);
  screen_area_puts(ge->map, str3);
  screen_area_puts(ge->map, str4);
  screen_area_puts(ge->map, str5);
  screen_area_puts(ge->map, str6);
  screen_area_puts(ge->map, str7);
  screen_area_puts(ge->map, str8);
  screen_area_puts(ge->map, str9);
}