/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @version 1
 * @date 11-02-2025
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
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param str a pointer to a string
 * @return nothing
 */
void eraseLeftSpaces(char *str1);

/**
 * @brief It puts the strings 1-9 on the screen
 * @author Rubén, Arturo, Bea, Ana,
 *
 * @param ge a pointer to the graphic engine
 * @param str(i) a string where a section of the screen is defined
 * @return nothing
 */
void someScreenPuts(Graphic_engine *ge, char *str1, char *str2, char *str3, char *str4, char *str5, char *str6, char *str7, char *str8, char *str9);

/**
 * @brief It gets the necessary information to print a certain space
 *
 * @param ge a pointer to the graphic engine
 * @param str(i) a string where a section of the screen is defined
 * @return nothing
 */
void initDescStuff(Game *game, Id space_id, char *objects, char *character_desc, char *space_desc1, char *space_desc2, char *space_desc3,
                   char *space_desc4, char *space_desc5);

/**
 * @brief It prints a certain space and the spaces east and west of it
 *
 * @param ge a pointer to the graphic engine
 * @param str(i) a string where a section of the screen is defined
 * @return nothing
 */
void printHorizontalSection(Graphic_engine *ge, Game *game, Id space_id, char *player_desc);

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
  Object *obj = NULL;
  Character *character = NULL;
  CommandCode last_cmd = UNKNOWN;
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID;
  char str1[1024];
  Id obj_id, obj_loc;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  char result[10];

  screen_area_clear(ge->map);

  id_act = game_get_player_location(game);
  if (id_act != NO_ID) {
    id_back = Game_get_north(game, id_act);
    id_next = Game_get_south(game, id_act);
  }

  /*  ESPACIOS */
  printHorizontalSection(ge, game, id_back, "   ");
  if (id_back != NO_ID) {
    screen_area_puts(ge->map, "                                 /\\");
  }
  printHorizontalSection(ge, game, id_act, player_get_description(game_get_player(game)));
  if (id_next != NO_ID) {
    screen_area_puts(ge->map, "                                 \\/");
  }
  printHorizontalSection(ge, game, id_next, "   ");

  /*  DESCRIPCION  */
  screen_area_clear(ge->descript);

  /*Info sobre el turno*/
  screen_area_puts(ge->descript, " ");
  sprintf(str1, " [ %s's turn ]", player_get_name(game_get_player(game))); /*  Banner */
  screen_area_puts(ge->descript, str1);

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

  /*Brújula*/
  screen_area_puts(ge->descript, " ");
  screen_area_puts(ge->descript, " ");

  screen_area_puts(ge->descript, "          .-----.");
  screen_area_puts(ge->descript, "         |   N   |");
  screen_area_puts(ge->descript, "         | E + W |");
  screen_area_puts(ge->descript, "         |   S   |");
  screen_area_puts(ge->descript, "          '-----'");

  /*  BANNER r */
  screen_area_puts(ge->banner, "    The anthill game ");

  /*  HELP */
  screen_area_clear(ge->help);
  sprintf(str1, " The commands you can use are:");
  screen_area_puts(ge->help, str1);
  sprintf(str1, "    next or n, back or b, t or take, d or drop, r or right, l or left, a or attack, c or chat,        exit or e");
  screen_area_puts(ge->help, str1);

  /*  FEEDBACK */
  last_cmd = command_get_code(game_get_last_command(game));

  if (command_get_result(game_get_last_command(game)) == OK) {
    strcpy(result, "OK");
  } else if (command_get_result(game_get_last_command(game)) == ERROR) {
    strcpy(result, "ERROR");
  }

  sprintf(str1, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], result);
  screen_area_puts(ge->feedback, str1);

  /*  Renderizar en la terminal */
  screen_paint(game_get_turn(game) % 7);
  printf("prompt:> ");
}

void eraseLeftSpaces(char *str1) {
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

void someScreenPuts(Graphic_engine *ge, char *str1, char *str2, char *str3, char *str4, char *str5, char *str6, char *str7, char *str8, char *str9) {
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

void initDescStuff(Game *game, Id space_id, char *objects, char *character_desc, char *space_desc1, char *space_desc2, char *space_desc3,
                   char *space_desc4, char *space_desc5) {
  strcpy(objects, "");
  if (space_get_discovered(game_get_space(game, space_id)) == TRUE) {
    game_get_string_of_objects_in_space(game, space_id, objects);
  } else {
    strcpy(objects, "                  ");
  }
  if (game_get_character_desc_at_space(game, space_id) == NULL) {
    strcpy(character_desc, "      ");
  } else {
    strcpy(character_desc, game_get_character_desc_at_space(game, space_id));
  }

  strcpy(space_desc1, space_get_n_description(game_get_space(game, space_id), 0));
  strcpy(space_desc2, space_get_n_description(game_get_space(game, space_id), 1));
  strcpy(space_desc3, space_get_n_description(game_get_space(game, space_id), 2));
  strcpy(space_desc4, space_get_n_description(game_get_space(game, space_id), 3));
  strcpy(space_desc5, space_get_n_description(game_get_space(game, space_id), 4));
}

void printHorizontalSection(Graphic_engine *ge, Game *game, Id space_id, char *player_desc) {
  Id id_east = NO_ID, id_west = NO_ID;
  char str1[1024], str2[1024], str3[1024], str4[1024], str5[1024], str6[1024], str7[1024], str8[1024], str9[1024], temp[1204];
  char objects[BOX_WIDTH + 1], character_desc[7];
  char space_desc1[10], space_desc2[10], space_desc3[10], space_desc4[10], space_desc5[10];

  id_east = Game_get_east(game, space_id);
  id_west = Game_get_west(game, space_id);

  /*  Espacio ACTUAL */
  if (space_id != NO_ID) {
    initDescStuff(game, space_id, objects, character_desc, space_desc1, space_desc2, space_desc3, space_desc4, space_desc5);

    sprintf(str1, "                        +------------------+");
    if (space_get_discovered(game_get_space(game, space_id)) == TRUE) {
      sprintf(str2, "                        | %s    %6s %3d|", player_desc, character_desc, (int)space_id);
    } else {
      sprintf(str2, "                        |               %3d|", (int)space_id);
    }
    sprintf(str3, "                        |     %s    |", space_desc1);
    sprintf(str4, "                        |     %s    |", space_desc2);
    sprintf(str5, "                        |     %s    |", space_desc3);
    sprintf(str6, "                        |     %s    |", space_desc4);
    sprintf(str7, "                        |     %s    |", space_desc5);
    sprintf(str8, "                        |%s|", objects);
    sprintf(str9, "                        +------------------+");

    /*  Si hay espacio a la derecha (id_east), concatenar */
    if (id_east != NO_ID) {
      initDescStuff(game, id_east, objects, character_desc, space_desc1, space_desc2, space_desc3, space_desc4, space_desc5);

      strcat(str1, "   +------------------+");
      if (space_get_discovered(game_get_space(game, id_east)) == TRUE) {
        sprintf(temp, "   |        %6s %3d|", character_desc, (int)id_east);
      } else {
        sprintf(temp, "   |               %3d|", (int)id_east);
      }
      strcat(str2, temp);
      sprintf(temp, "   |     %s    |", space_desc1);
      strcat(str3, temp);
      sprintf(temp, "   |     %s    |", space_desc2);
      strcat(str4, temp);
      if (space_id == game_get_player_location(game)) {
        sprintf(temp, " > |     %s    |", space_desc3);
      } else {
        sprintf(temp, "   |     %s    |", space_desc3);
      }
      strcat(str5, temp);
      sprintf(temp, "   |     %s    |", space_desc4);
      strcat(str6, temp);
      sprintf(temp, "   |     %s    |", space_desc5);
      strcat(str7, temp);
      sprintf(temp, "   |%s|", objects);
      strcat(str8, temp);
      sprintf(temp, "   +------------------+");
      strcat(str9, temp);
    }

    /*  Si hay espacio a la izquierda (id_west), no agregamos espacio adicional
    antes de str2 */
    if (id_west != NO_ID) {
      initDescStuff(game, id_west, objects, character_desc, space_desc1, space_desc2, space_desc3, space_desc4, space_desc5);

      eraseLeftSpaces(str1);
      eraseLeftSpaces(str2);
      eraseLeftSpaces(str3);
      eraseLeftSpaces(str4);
      eraseLeftSpaces(str5);
      eraseLeftSpaces(str6);
      eraseLeftSpaces(str7);
      eraseLeftSpaces(str8);
      eraseLeftSpaces(str9);

      sprintf(temp, " +------------------+   %s", str1);
      strcpy(str1, temp);
      if (space_get_discovered(game_get_space(game, id_west)) == TRUE) {
        sprintf(temp, " |        %6s %3d|   %s", character_desc, (int)id_west, str2);
      } else {
        sprintf(temp, " |               %3d|   %s", (int)id_west, str2);
      }
      strcpy(str2, temp);
      sprintf(temp, " |     %s    |   %s", space_desc1, str3);
      strcpy(str3, temp);
      sprintf(temp, " |     %s    |   %s", space_desc2, str4);
      strcpy(str4, temp);
      if (space_id == game_get_player_location(game)) {
        sprintf(temp, " |     %s    | < %s", space_desc3, str5);
      } else {
        sprintf(temp, " |     %s    |   %s", space_desc3, str5);
      }
      strcpy(str5, temp);
      sprintf(temp, " |     %s    |   %s", space_desc4, str6);
      strcpy(str6, temp);
      sprintf(temp, " |     %s    |   %s", space_desc5, str7);
      strcpy(str7, temp);
      sprintf(temp, " |%s|   %s", objects, str8);
      strcpy(str8, temp);
      sprintf(temp, " +------------------+   %s", str9);
      strcpy(str9, temp);
    }

    someScreenPuts(ge, str1, str2, str3, str4, str5, str6, str7, str8, str9);
  } else if (space_id == NO_ID) {
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

    someScreenPuts(ge, str1, str2, str3, str4, str5, str6, str7, str8, str9);
  }
}