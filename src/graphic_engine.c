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
#include <unistd.h>

#include "command.h"
#include "game.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"

#define WIDTH_MAP 76
#define WIDTH_DES 30
#define WIDTH_TEA 30
#define WIDTH_BAN 30
#define HEIGHT_MAP 29
#define HEIGHT_BAN 1
#define HEIGHT_HLP 3
#define HEIGHT_FDB 3

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback, *player_info, *full_screen;
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

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + WIDTH_TEA + 4);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL) {
    return NULL;
  }

  graphic_engine_init_game_areas(ge);
  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) {
    return;
  }

  if (ge->map) {
    screen_area_destroy(ge->map);
  }
  if (ge->descript) {
    screen_area_destroy(ge->descript);
  }
  if (ge->banner) {
    screen_area_destroy(ge->banner);
  }
  if (ge->help) {
    screen_area_destroy(ge->help);
  }
  if (ge->feedback) {
    screen_area_destroy(ge->feedback);
  }
  if (ge->player_info) {
    screen_area_destroy(ge->player_info);
  }
  if (ge->full_screen) {
    screen_area_destroy(ge->full_screen);
  }

  screen_destroy();
  free(ge);
}

void graphic_engine_toggle_fullscreen(Graphic_engine *ge) {
  if (ge->map && ge->descript && ge->player_info && ge->banner && ge->help && ge->feedback) {
    screen_area_clear(ge->map);
    screen_area_destroy(ge->map);
    ge->map = NULL;
    screen_area_clear(ge->descript);
    screen_area_destroy(ge->descript);
    ge->descript = NULL;
    screen_area_clear(ge->banner);
    screen_area_destroy(ge->banner);
    ge->banner = NULL;
    screen_area_clear(ge->help);
    screen_area_destroy(ge->help);
    ge->help = NULL;
    screen_area_clear(ge->feedback);
    screen_area_destroy(ge->feedback);
    ge->feedback = NULL;
    screen_area_clear(ge->player_info);
    screen_area_destroy(ge->player_info);
    ge->player_info = NULL;

    screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + WIDTH_TEA + 4);

    ge->full_screen = screen_area_init(1, 1, WIDTH_MAP + WIDTH_DES + WIDTH_TEA + 2, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_FDB + HEIGHT_HLP + 2);

  } else if (ge->full_screen) {
    screen_area_clear(ge->full_screen);
    screen_area_destroy(ge->full_screen);
    ge->full_screen = NULL;

    screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + WIDTH_TEA + 4);

    graphic_engine_init_game_areas(ge);
  }
}

void graphic_engine_init_game_areas(Graphic_engine *ge) {
  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->player_info = screen_area_init(WIDTH_MAP + 3 + WIDTH_DES, 1, WIDTH_TEA, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + WIDTH_TEA + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + WIDTH_TEA + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + WIDTH_TEA + 1, HEIGHT_FDB);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  int i = 0, n_inventory = 0;
  Object *obj = NULL;
  Character *character = NULL;
  Player *player;
  CommandCode last_cmd = UNKNOWN;
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID;
  char str1[1024];
  Id object_id, object_loc;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  char result[10];

  screen_area_clear(ge->map);

  id_act = game_get_player_location(game);
  if (id_act != NO_ID) {
    id_back = game_get_north(game, id_act);
    id_next = game_get_south(game, id_act);
  }

  /*  ESPACIOS */
  printHorizontalSection(ge, game, id_back, "   ");
  if ((id_back != NO_ID) && (game_connection_is_open(game, id_act, N) == TRUE)) {
    screen_area_puts(ge->map, "                                  [ ]");
  } else if ((id_back != NO_ID) && game_connection_is_open(game, id_act, S) == FALSE) {
    screen_area_puts(ge->map, "                                  [x]");
  } else {
    screen_area_puts(ge->map, " ");
  }
  printHorizontalSection(ge, game, id_act, player_get_description(game_get_current_player(game)));
  if ((id_next != NO_ID) && (game_connection_is_open(game, id_act, S) == TRUE)) {
    screen_area_puts(ge->map, "                                  [ ]");
  } else if ((id_next != NO_ID) && game_connection_is_open(game, id_act, S) == FALSE) {
    screen_area_puts(ge->map, "                                  [x]");
  } else {
    screen_area_puts(ge->map, " ");
  }
  printHorizontalSection(ge, game, id_next, "   ");

  /*  DESCRIPCION  */
  screen_area_clear(ge->descript);
  screen_area_clear(ge->player_info);

  /*Info sobre el turno*/
  screen_area_puts(ge->descript, " ");
  sprintf(str1, " [ %s's turn ]", player_get_name(game_get_current_player(game))); /*  Banner */
  screen_area_puts(ge->descript, str1);

  /*  Bucle para los objetos fuera del inventario */
  screen_area_puts(ge->descript, " ");
  sprintf(str1, " Objects:"); /*  Banner */
  screen_area_puts(ge->descript, str1);

  for (i = 0; i < game_get_num_objects(game); i++) {
    Object *obj = game_get_object_from_index(game, i);
    if (obj == NULL) {
      printf("Object %d is NULL\n", i); /*  Debug statement */
      continue;
    }

    object_id = object_get_id(obj);
    object_loc = game_get_object_location(game, object_id);

    if (object_loc != NO_ID) {
      if (object_loc == player_get_id(game_get_current_player(game))) {
        sprintf(str1, "  %s: Player", object_get_name(obj));
      } else {
        sprintf(str1, "  %s: %d", object_get_name(obj), (int)object_loc);
        screen_area_puts(ge->descript, str1);
      }
    }
  }

  /* Characters */
  if (game_get_num_characters(game) > 0) {
    sprintf(str1, " "); /*  Hueco para que quede mono */
    screen_area_puts(ge->player_info, str1);
    sprintf(str1, " Characters:");
    screen_area_puts(ge->player_info, str1);

    for (i = 0; i < game_get_num_characters(game); i++) {
      character = game_get_character_from_index(game, i);
      printf("Studying %s...\n", character_get_name(character));
      if (game_get_character_location(game, character_get_id(character)) != NO_ID) {
        sprintf(str1, "  %s : %li (%li) [%s]", character_get_description(character), game_get_character_location(game, character_get_id(character)),
                character_get_health(character), character_get_name(character));
      } else if (character_get_health(character) <= 0) {
        /*character_set_description(character, "/RIP\\_"); Molaba pero era poco intuitivo*/
        sprintf(str1, "  %s : Dead", character_get_description(character));
      } else {
        sprintf(str1, "  ERROR");
      }

      if (character_get_following(character) != player_get_id(game_get_current_player(game))) {
        screen_area_puts(ge->player_info, str1);
      }
    }
  }

  /* Player */
  sprintf(str1, " "); /*  Hueco para que quede mono */
  screen_area_puts(ge->descript, str1);
  sprintf(str1, " Players:"); /* Banner */
  screen_area_puts(ge->descript, str1);
  for (i = 0; i < game_get_num_players(game); i++) {
    player = game_get_player_from_index(game, i);
    sprintf(str1, "  %s : %li (%li)", player_get_name(player), game_get_player_location_from_index(game, i), player_get_health(player));
    screen_area_puts(ge->descript, str1);
  }

  /*Brújula*/
  screen_area_puts(ge->player_info, " ");

  screen_area_puts(ge->player_info, "        .-----.");
  screen_area_puts(ge->player_info, "       |   N   |");
  screen_area_puts(ge->player_info, "       | W + E |");
  screen_area_puts(ge->player_info, "       |   S   |");
  screen_area_puts(ge->player_info, "        '-----'");

  /*  Bucle para los objetos dentro del inventario */
  sprintf(str1, " "); /*  Hueco para que quede mono */
  screen_area_puts(ge->player_info, str1);
  sprintf(str1, " Inventory: (%i/%i)", inventory_get_num_objects(player_get_inventory(game_get_current_player(game))),
          inventory_get_max_objects(player_get_inventory(game_get_current_player(game)))); /*  Banner */
  screen_area_puts(ge->player_info, str1);

  for (i = 0; i < game_get_num_objects(game); i++) {
    obj = game_get_object_from_index(game, i);
    if (obj == NULL) {
      printf("Object %d is NULL\n", i); /*  Debug statement */
      continue;
    }

    object_id = object_get_id(obj);
    object_loc = game_get_object_location(game, object_id);
    printf("Object ID: %ld, Location: %ld\n", object_id, object_loc); /*  Debug statement */

    if (object_loc != NO_ID) {
      if (player_has_object(game_get_current_player(game), object_id) == TRUE) {
        sprintf(str1, "  %s", object_get_name(obj));
        n_inventory++;
        screen_area_puts(ge->player_info, str1);
      }
    }
  }

  if (n_inventory == 0) {
    sprintf(str1, "  Player has no objects");
    screen_area_puts(ge->player_info, str1);
  }

  /*  Message */
  if (game_get_message(game)[0] != '\0') {
    sprintf(str1, " "); /*  Hueco para que quede mono */
    screen_area_puts(ge->player_info, str1);
    sprintf(str1, " Message: %s", game_get_message(game)); /*  Banner */
    screen_area_puts(ge->player_info, str1);
  }

  /*  Object_desc */
  if (game_get_object_desc(game)[0] != '\0') {
    sprintf(str1, " "); /*  Hueco para que quede mono */
    screen_area_puts(ge->descript, str1);
    sprintf(str1, " Object description: %s", game_get_object_desc(game)); /*  Banner */
    screen_area_puts(ge->descript, str1);
  }

  /*  BANNER r */
  screen_area_puts(ge->banner, "       The anthill game ");

  /*  HELP */
  screen_area_clear(ge->help);
  sprintf(str1, " The commands you can use are:");
  screen_area_puts(ge->help, str1);
  sprintf(str1,
          "    m or move, t or take, d or drop, a or attack, c or chat, n or inventory, u or use, o or open, f or follow, z or zoom, l or load");
  screen_area_puts(ge->help, str1);
  sprintf(str1, "    s or save, r or recruit, ab or abandon, exit or e");
  screen_area_puts(ge->help, str1);

  /*  FEEDBACK */
  screen_area_clear(ge->feedback);
  last_cmd = command_get_code(game_get_last_command(game));

  screen_area_puts(ge->feedback, " ");

  if (command_get_result(game_get_last_command(game)) == OK) {
    strcpy(result, "OK");
  } else if (command_get_result(game_get_last_command(game)) == ERROR) {
    strcpy(result, "ERROR");
  }

  sprintf(str1, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], result);
  screen_area_puts(ge->feedback, str1);

  /*TEAM*/
  screen_area_puts(ge->player_info, " ");
  screen_area_puts(ge->player_info, " My team:");
  screen_area_puts(ge->player_info, " ");
  for (i = 0; i < game_get_num_characters(game); i++) {
    character = game_get_character_from_index(game, i);
    if (character_get_following(character) == player_get_id(game_get_current_player(game))) {
      sprintf(str1, " %s (%li)", character_get_description(character), character_get_health(character));
      screen_area_puts(ge->player_info, str1);
    }
  }

  /*  Renderizar en la terminal */
  screen_paint(game_get_player_index_from_turn(game) % 7);
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

  strcpy(space_desc1, space_get_i_dynamic_description(game_get_space(game, space_id), 0));
  strcpy(space_desc2, space_get_i_dynamic_description(game_get_space(game, space_id), 1));
  strcpy(space_desc3, space_get_i_dynamic_description(game_get_space(game, space_id), 2));
  strcpy(space_desc4, space_get_i_dynamic_description(game_get_space(game, space_id), 3));
  strcpy(space_desc5, space_get_i_dynamic_description(game_get_space(game, space_id), 4));
}

void printHorizontalSection(Graphic_engine *ge, Game *game, Id space_id, char *player_desc) {
  Id id_east = NO_ID, id_west = NO_ID;
  char str1[1024], str2[1024], str3[1024], str4[1024], str5[1024], str6[1024], str7[1024], str8[1024], str9[1024], temp[1204];
  char objects[BOX_WIDTH + 1], character_desc[7];
  char space_desc1[10], space_desc2[10], space_desc3[10], space_desc4[10], space_desc5[10];
  char up_signal[10], down_signal[10];

  id_east = game_get_east(game, space_id);
  id_west = game_get_west(game, space_id);

  up_signal[0] = '\0';
  down_signal[0] = '\0';

  /*  Espacio ACTUAL */
  if (space_id != NO_ID) {
    initDescStuff(game, space_id, objects, character_desc, space_desc1, space_desc2, space_desc3, space_desc4, space_desc5);
    if ((game_get_up(game, space_id) != NO_ID) && (game_connection_is_open(game, space_id, U) == TRUE)) {
      strcpy(up_signal, "[/\\]");
    } else if ((game_get_up(game, space_id) != NO_ID) && (game_connection_is_open(game, space_id, U) == FALSE)) {
      strcpy(up_signal, "[x]");
    } else {
      strcpy(up_signal, "   ");
    }

    if ((game_get_down(game, space_id) != NO_ID) && (game_connection_is_open(game, space_id, D) == TRUE)) {
      strcpy(down_signal, "[\\/]");
    } else if ((game_get_down(game, space_id) != NO_ID) && (game_connection_is_open(game, space_id, D) == FALSE)) {
      strcpy(down_signal, "[x]");
    } else {
      strcpy(down_signal, "   ");
    }

    sprintf(str1, "                          +------------------+");
    if (space_get_discovered(game_get_space(game, space_id)) == TRUE) {
      sprintf(str2, "                          | %s    %6s %3d|", player_desc, character_desc, (int)space_id);
    } else {
      sprintf(str2, "                          |                  |");
    }
    sprintf(str3, "                          |     %s    |", space_desc1);
    sprintf(str4, "                          |     %s    |", space_desc2);
    sprintf(str5, "                          |%4s %s%4s|", up_signal, space_desc3, down_signal);
    sprintf(str6, "                          |     %s    |", space_desc4);
    sprintf(str7, "                          |     %s    |", space_desc5);
    sprintf(str8, "                          |%9s|", objects);

    sprintf(str9, "                          +------------------+");

    /*  Si hay espacio a la derecha (id_east), concatenar */
    if (id_east != NO_ID) {
      initDescStuff(game, id_east, objects, character_desc, space_desc1, space_desc2, space_desc3, space_desc4, space_desc5);

      strcat(str1, "     +------------------+");
      if (space_get_discovered(game_get_space(game, id_east)) == TRUE) {
        sprintf(temp, "     |        %6s %3d|", character_desc, (int)id_east);
      } else {
        sprintf(temp, "     |                  |");
      }
      strcat(str2, temp);
      sprintf(temp, "     |     %s    |", space_desc1);
      strcat(str3, temp);
      sprintf(temp, "     |     %s    |", space_desc2);
      strcat(str4, temp);
      if ((game_connection_is_open(game, space_id, E) == TRUE)) {
        sprintf(temp, " [ ] |     %s    |", space_desc3);
      } else if (game_connection_is_open(game, space_id, E) == FALSE) {
        sprintf(temp, " [x] |     %s    |", space_desc3);
      } else {
        sprintf(temp, "     |     %s    |", space_desc3);
      }
      strcat(str5, temp);
      sprintf(temp, "     |     %s    |", space_desc4);
      strcat(str6, temp);
      sprintf(temp, "     |     %s    |", space_desc5);
      strcat(str7, temp);
      sprintf(temp, "     |%9s|", objects);
      strcat(str8, temp);
      sprintf(temp, "     +------------------+");
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

      sprintf(temp, " +------------------+     %s", str1);
      strcpy(str1, temp);
      if (space_get_discovered(game_get_space(game, id_west)) == TRUE) {
        sprintf(temp, " |        %6s %3d|     %s", character_desc, (int)id_west, str2);
      } else {
        sprintf(temp, " |                  |     %s", str2);
      }
      strcpy(str2, temp);
      sprintf(temp, " |     %s    |     %s", space_desc1, str3);
      strcpy(str3, temp);
      sprintf(temp, " |     %s    |     %s", space_desc2, str4);
      strcpy(str4, temp);
      if ((game_connection_is_open(game, space_id, W) == TRUE)) {
        sprintf(temp, " |     %s    | [ ] %s", space_desc3, str5);
      } else if (game_connection_is_open(game, space_id, W) == FALSE) {
        sprintf(temp, " |     %s    | [x] %s", space_desc3, str5);
      } else {
        sprintf(temp, " |     %s    |     %s", space_desc3, str5);
      }
      strcpy(str5, temp);
      sprintf(temp, " |     %s    |     %s", space_desc4, str6);
      strcpy(str6, temp);
      sprintf(temp, " |     %s    |     %s", space_desc5, str7);
      strcpy(str7, temp);
      sprintf(temp, " |%9s|     %s", objects, str8);
      strcpy(str8, temp);
      sprintf(temp, " +------------------+     %s", str9);
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

void graphic_engine_paint_start(Graphic_engine *ge, Game *game) {
  graphic_engine_toggle_fullscreen(ge);

  screen_area_puts(ge->full_screen, "                                                                                                  ");
  screen_area_puts(ge->full_screen, "                                  ,");
  screen_area_puts(ge->full_screen, "                         _,-'\\   /|   .    .    /`.");
  screen_area_puts(ge->full_screen, "                     _,-'     \\_/_|_  |\\   |`. /   `._,--===--.__");
  screen_area_puts(ge->full_screen, "                    ^       _/\"/  \" \\ : \\__|_ /.   ,'    :.  :. .`-._");
  screen_area_puts(ge->full_screen, "                           // ^   /7 t'\"\"    \"`-._/ ,'\\   :   :  :  .`.");
  screen_area_puts(ge->full_screen, "                           Y      L/ )\\         ]],'   \\  :   :  :   : `.");
  screen_area_puts(ge->full_screen,
                   "                           |        /  `.n_n_n,','\\_    \\ ;   ;  ;   ;  _>                   _    _     _  _  _ ");
  screen_area_puts(ge->full_screen,
                   "                           |__    ,'     |  \\`-'    `-.__\\_______.==---'          __ _ _ __ | |_ | |__ (_)| || |");
  screen_area_puts(ge->full_screen,
                   "                          //  `\"\"\\\\      |   \\            \\                      / _` | '_ \\| __/| '_ \\| || || |");
  screen_area_puts(ge->full_screen,
                   "                          \\|     |/      /    \\            \\                    | (_| | | | | |_ | | | | || || |");
  screen_area_puts(ge->full_screen,
                   "                                        /     |             `.                   \\__,_|_| |_|\\__||_| |_|_||_||_|");
  screen_area_puts(ge->full_screen,
                   "                                       /      |               ^                                        The game");
  screen_area_puts(ge->full_screen, "                                      ^       |                              ");
  screen_area_puts(ge->full_screen, "                                              ^                                ");
  screen_area_puts(ge->full_screen,
                   "                                                                                                                     ");
  screen_area_puts(ge->full_screen,
                   "                                                         _ _ _ _ _ _ _ _ _ _ _                                       ");
  screen_area_puts(ge->full_screen,
                   "                      (\\   (\\   (\\   (\\   (\\   (\\   (\\ '                     '   /)   /)   /)   /)   /)   /)   /)");
  screen_area_puts(ge->full_screen,
                   "                    o - - - - - - - - - - - - - - - - - '  Escape jail to win ' - - - - - - - - - - - - - - - - - o");
  screen_area_puts(ge->full_screen,
                   "                      (/   (/   (/   (/   (/   (/   (/  '_ _ _ _ _ _ _ _ _ _ _'   \\)   \\)   \\)   \\)   \\)   \\)   \\)");
  screen_area_puts(ge->full_screen,
                   "                                                                                                                     ");
  screen_area_puts(ge->full_screen,
                   "                                                                                                                     ");
  screen_area_puts(ge->full_screen, "                                                                           ,");
  screen_area_puts(ge->full_screen, "                                                                  _,-'\\   /|   .    .    /`.");
  screen_area_puts(ge->full_screen, "                                                              _,-'     \\_/_|_  |\\   |`. /   `._,--===--.__");
  screen_area_puts(ge->full_screen,
                   "                                                             ^       _/\"/  \" \\ : \\__|_ /.   ,'    :.  :. .`-._");
  screen_area_puts(ge->full_screen,
                   "                                                                    // ^   /7 t'\"\"    \"`-._/ ,'\\   :   :  :  .`.");
  screen_area_puts(ge->full_screen,
                   "                                  Made by:                          Y      L/ )\\         ]],'   \\  :   :  :   : `.");
  screen_area_puts(ge->full_screen,
                   "                                  Ruben Garcia,                     |        /  `.n_n_n,','\\_    \\ ;   ;  ;   ;  _>");
  screen_area_puts(ge->full_screen,
                   "                                  Arturo Perez,                     |__    ,'     |  \\`-'    `-.__\\_______.==---'");
  screen_area_puts(ge->full_screen, "                                  Beatriz Gallo                    //  `\"\"\\\\      |   \\            \\");
  screen_area_puts(ge->full_screen, "                                  & Ana Olsson                     \\|     |/      /    \\            \\");
  screen_area_puts(ge->full_screen, "                                                                                 /     |             `.");
  screen_area_puts(ge->full_screen, "                                                                                /      |               ^");
  screen_area_puts(ge->full_screen, "                                                                               ^       |");
  screen_area_puts(ge->full_screen, "                                                                                       ^");

  /*  Renderizar en la terminal */
  screen_paint(game_get_player_index_from_turn(game) % 7);
  printf(" ");

  graphic_engine_toggle_fullscreen(ge);
}

void graphic_engine_paint_end(Graphic_engine *ge, Game *game) {
  int i = 0;

  graphic_engine_toggle_fullscreen(ge);
  screen_area_clear(ge->full_screen);

  for (i = 0; i < 18; i++) {
    screen_area_puts(ge->full_screen, " ");
  }
  screen_area_puts(ge->full_screen, "                                               Someone from your party died");
  screen_area_puts(ge->full_screen, "                                                   or exited the game");

  screen_color_paint(game_get_player_index_from_turn(game) % 7, 31, 40);

  sleep(2);

  screen_area_clear(ge->full_screen);

  screen_area_puts(ge->full_screen, "                                                                                                  ");
  screen_area_puts(ge->full_screen, " ");
  screen_area_puts(ge->full_screen, " ");
  screen_area_puts(ge->full_screen, "                                GGGGGGGGGGGGG");
  screen_area_puts(ge->full_screen, "                             GGG::::::::::::G");
  screen_area_puts(ge->full_screen, "                           GG:::::::::::::::G");
  screen_area_puts(ge->full_screen, "                          G:::::GGGGGGGG::::G");
  screen_area_puts(ge->full_screen, "                         G:::::G        GGGGGG  aaaaaaaaaaaaa      mmmmmmm    mmmmmmm       eeeeeeeeeeee");
  screen_area_puts(ge->full_screen, "                         G:::::G                a::::::::::::a   mm:::::::m  m:::::::mm   ee::::::::::::ee");
  screen_area_puts(ge->full_screen, "                         G:::::G                aaaaaaaaa:::::a m::::::::::mm::::::::::m e::::::eeeee:::::ee");
  screen_area_puts(ge->full_screen, "                         G:::::G    GGGGGGGGGG           a::::a m::::::::::::::::::::::me::::::e     e:::::e");
  screen_area_puts(ge->full_screen, "                         G:::::G    G::::::::G    aaaaaaa:::::a m:::::mmm::::::mmm:::::me:::::::eeeee::::::e");
  screen_area_puts(ge->full_screen, "                         G:::::G    GGGGG::::G  aa::::::::::::a m::::m   m::::m   m::::me:::::::::::::::::e");
  screen_area_puts(ge->full_screen, "                         G:::::G        G::::G a::::aaaa::::::a m::::m   m::::m   m::::me::::::eeeeeeeeeee");
  screen_area_puts(ge->full_screen, "                          G:::::G       G::::Ga::::a    a:::::a m::::m   m::::m   m::::me:::::::e");
  screen_area_puts(ge->full_screen, "                           G:::::GGGGGGGG::::Ga::::a    a:::::a m::::m   m::::m   m::::me::::::::e");
  screen_area_puts(ge->full_screen, "                            GG:::::::::::::::Ga:::::aaaa::::::a m::::m   m::::m   m::::m e::::::::eeeeeeee");
  screen_area_puts(ge->full_screen, "                              GGG::::::GGG:::G a::::::::::aa:::am::::m   m::::m   m::::m  ee:::::::::::::e");
  screen_area_puts(ge->full_screen, "                                 GGGGGG   GGGG  aaaaaaaaaa  aaaammmmmm   mmmmmm   mmmmmm    eeeeeeeeeeeeee");
  screen_area_puts(ge->full_screen, " ");
  screen_area_puts(ge->full_screen, " ");
  screen_area_puts(ge->full_screen, " ");
  screen_area_puts(ge->full_screen, "                                 ooooooooooo vvvvvvv           vvvvvvv eeeeeeeeeeee    rrrrr   rrrrrrrrr");
  screen_area_puts(ge->full_screen, "                               oo:::::::::::oov:::::v         v:::::vee::::::::::::ee  r::::rrr:::::::::r");
  screen_area_puts(ge->full_screen, "                              o:::::::::::::::ov:::::v       v:::::ve::::::eeeee:::::eer:::::::::::::::::r");
  screen_area_puts(ge->full_screen, "                              o:::::ooooo:::::o v:::::v     v:::::ve::::::e     e:::::err::::::rrrrr::::::r");
  screen_area_puts(ge->full_screen, "                              o::::o     o::::o  v:::::v   v:::::v e:::::::eeeee::::::e r:::::r     r:::::r");
  screen_area_puts(ge->full_screen, "                              o::::o     o::::o   v:::::v v:::::v  e:::::::::::::::::e  r:::::r     rrrrrrr");
  screen_area_puts(ge->full_screen, "                              o::::o     o::::o    v:::::v:::::v   e::::::eeeeeeeeeee   r:::::r");
  screen_area_puts(ge->full_screen, "                              o::::o     o::::o     v:::::::::v    e:::::::e            r:::::r");
  screen_area_puts(ge->full_screen, "                              o:::::ooooo:::::o      v:::::::v     e::::::::e           r:::::r");
  screen_area_puts(ge->full_screen, "                              o:::::::::::::::o       v:::::v       e::::::::eeeeeeee   r:::::r");
  screen_area_puts(ge->full_screen, "                               oo:::::::::::oo         v:::v         ee:::::::::::::e   r:::::r");
  screen_area_puts(ge->full_screen, "                                 ooooooooooo            vvv            eeeeeeeeeeeeee   rrrrrrr");
  screen_area_puts(ge->full_screen, " ");
  screen_area_puts(ge->full_screen, " ");

  screen_color_paint(game_get_player_index_from_turn(game) % 7, 31, 40);
  printf(" ");
}

void graphic_engine_paint_inventory(Graphic_engine *ge, Game *game) {
  char str1[1024];
  int i = 0;
  Object *object = NULL;

  screen_area_clear(ge->map);
  screen_area_puts(ge->map, " ");

  sprintf(str1, "       Object:      |                   Observations:                       ");
  screen_area_puts(ge->map, str1);
  sprintf(str1, "----------------------------------------------------------------------------");
  screen_area_puts(ge->map, str1);
  for (i = 0; i < MAX_OBJECTS; i++) {
    object = game_get_object_from_index(game, i);
    if (player_has_object(game_get_current_player(game), object_get_id(object)) == TRUE) {
      if (object_get_inspected(object) == TRUE) {
        sprintf(str1, "       %12s |%s", object_get_name(object), object_get_desc(object));
        screen_area_puts(ge->map, str1);
      } else {
        sprintf(str1, "%20s| No info yet", object_get_name(object));
        screen_area_puts(ge->map, str1);
      }
      sprintf(str1, "----------------------------------------------------------------------------");
      screen_area_puts(ge->map, str1);
    }
  }

  screen_paint(game_get_player_index_from_turn(game) % 7);
  printf("prompt:> ");
}

void graphic_engine_paint_zoom(Graphic_engine *ge, Game *game) {
  char str1[1024];
  Space *space = NULL;
  Id player_loc = NO_ID;
  int i = 0;
  int num_objects = 0;
  Id object_id = NO_ID;
  Object *object = NULL;

  printf("[DEBUG] Entrando en graphic_engine_paint_zoom\n");

  if (!ge || !game) {
    printf("[ERROR] Graphic_engine o Game es NULL\n");
    return;
  }

  screen_area_clear(ge->map);
  screen_area_puts(ge->map, " ");

  player_loc = game_get_player_location(game);
  printf("[DEBUG] player_loc: %ld\n", player_loc);

  space = game_get_space(game, player_loc);
  printf("[DEBUG] space: %p\n", (void *)space);

  if (!space) {
    screen_area_puts(ge->map, "No current space.");
    screen_paint(game_get_player_index_from_turn(game) % 7);
    printf("prompt:> ");
    return;
  }

  /* Print space name and description */
  sprintf(str1, "Zoom view of the space:");
  screen_area_puts(ge->map, str1);
  sprintf(str1, "----------------------------------------------------------------------------");
  screen_area_puts(ge->map, str1);

  printf("[DEBUG] Obteniendo nombre del espacio\n");
  if (space_get_name(space) == NULL) {
    printf("[ERROR] space_get_name devolvió NULL\n");
  }
  sprintf(str1, "Name: %s", space_get_name(space));
  screen_area_puts(ge->map, str1);
  /*
  printf("[DEBUG] Obteniendo descripción del espacio\n");
  if (space_get_description(space) == NULL) {
    printf("[ERROR] space_get_description devolvió NULL\n");
  } else {
    sprintf(str1, "Description: %s", *space_get_description(space));
    screen_area_puts(ge->map, str1);
  }
  */
  sprintf(str1, "----------------------------------------------------------------------------");
  screen_area_puts(ge->map, str1);

  /* Print objects in the space */
  num_objects = space_get_num_objects(space);
  printf("[DEBUG] num_objects: %d\n", num_objects);

  if (num_objects > 0) {
    sprintf(str1, "Objects in the space:");
    screen_area_puts(ge->map, str1);

    for (i = 0; i < num_objects; i++) {
      printf("[DEBUG] Iterando objeto %d\n", i);

      object_id = space_get_object_from_index(space, i);
      printf("[DEBUG] object_id: %ld\n", object_id);

      if (object_id != NO_ID) {
        object = game_get_object_from_id(game, object_id);
        printf("[DEBUG] object: %p\n", (void *)object);

        if (object) {
          if (object_get_name(object) == NULL) {
            printf("[ERROR] object_get_name devolvió NULL para el objeto %d\n", i);
          }
          sprintf(str1, "- %s", object_get_name(object));
          screen_area_puts(ge->map, str1);
        } else {
          printf("[WARNING] Objeto con ID %ld no encontrado en el juego\n", object_id);
        }
      }
    }
  } else {
    sprintf(str1, "No objects in this space.");
    screen_area_puts(ge->map, str1);
  }

  sprintf(str1, "----------------------------------------------------------------------------");
  screen_area_puts(ge->map, str1);

  if (space_get_id(space) == 11) {
  } else if (space_get_id(space) == 3) {
    sprintf(str1, "  ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "             ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "             __");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "           /  /|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "          /  / |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "         /  //||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "        /_ // ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "       |  || //");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "       |  ||//|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "       |  | / |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "       |__|/| |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "         |  | |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "         |  | |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "         |  | |__________________________ ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "         |  | |__________                /");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "         |  | |         /               /");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "        /|  | /        /               /");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "       / |__|/        /               /");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "      /______________/               /");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "     /______________________________/ ");
    screen_area_puts(ge->map, str1);

  } else if (space_get_id(space) == 4) {
    sprintf(str1, "                                                       ________________");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                         | / / /|/ / /|     |         |\\ ____________ /|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                         | / / /|/ /_/| __  |         | |            | |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                         | / / /|/|/:/||: | |         | |____________| |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                         | / / /|/|/_/||__| |         |/______________\\| ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                         | / / /|/ / /|     |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                         | / / /|/ / /|     |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                         | / / /|/_/_/|_____|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                         | / / / / / /     /|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                         | / / / / /     /  |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "               /|        | / / / /     /    |         /|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "             /  |        | / / /     /      |       /  |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "            |   |_____ / | / /     /        |   ___|   |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "            |  /     /   | /     /         /  /    |  /|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "            |/_____/_____|_____/         /  /______|/  |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "            |      |          |        /    |      |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "            |      |          |      /      |      |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                   |          |    /        ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                   |          |  /");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                   |__________|/");
    screen_area_puts(ge->map, str1);
  } else if (space_get_id(space) == 8) {
    sprintf(str1, "            |       _____                 /||/ /||/ /||/ /||/ /||/ /||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "            |      /  _  \\                /||/ /||/ /||/ /||/ /||/ /||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "            |      | |_| |                /||/ /||/ /||/ /||/ /||/ /||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "            |      \\_____/                /||/ /||/ /||/ /||/ /||/ /||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "            |                             /||/ /||/ /||/ /||/ /||/ /||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "            |                  _____      /||/ /||/ /||/ /||/ /||/ /||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "            |_______          |     |     /||/ /||/ /||/ /||/ /||/ /||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "          /_______ /|         |_____|     /||/ /||/ /||/ /||/ /||/ /||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "        /_______ /_||________/ /_/ /|_____/||/_/||/_/||/_/||/_/||/__||____");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "      /_______ /            /____/ /      /||/ /||/ /||/ /||/ /|| /");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "    /________/              |____|/       /||/ /||/ /||/ /||/  ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "   ||/     ||                             /||/ /||/ /||/ /|| /");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "   ||      ||                             /||/ /||/ /||/  ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  /                                       /||/ /||/ /|| /");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                          /||/ /||/  ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                          /||/ /|| /");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                          /||/  ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                          /|| /");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                          /||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                          /");
    screen_area_puts(ge->map, str1);

  } else if (space_get_id(space) == 5) {
    sprintf(str1, "                                     ||                                    ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                     ||                                    ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                    (__)                                    ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                _____           _____           _____");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "              /     /|        /     /|        /     /|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "            /     /  |      /     /  |      /     /  | ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "          /     /| / |    /     /| / |    /     /| / |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "        /     /  |  /|  /     /  |  /|  /     /  |  /|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "      /     /| / |/  |/     /| / |/  |/     /| / |/  |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "    /____ /  |  /| //____ /  |  /| //____ /  |  /| / |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "   |     | / |/  | |     | / |/  | |     | / |/  |  /|         ____/|_____");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "   |     |  /| / |/|     |  /| / |/|     |  /| / |/  |       /  __/ |    /|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "___|     |/  |  /| |     |/  |  /| |     |/  |  /| / |_____/  /  | /   /_||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "   |     | / |/  | |     | / |/  | |     | / |/  |  /    /  /____|/  /   ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "   |     |  /| / |/|     |  /| / |/|     |  /| / |/    /___________/     ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "   |     |/  |  /  |     |/  |  /  |     |/  |  /      ||        ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "   |     | / |/    |     | / |/    |     | / |/        ||        ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "   |     |  /      |     |  /      |     |  /          ||        || ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "   |_____|/        |_____|/        |_____|/            ||        ||");
    screen_area_puts(ge->map, str1);
  } else if (space_get_id(space) == 6) {
    sprintf(str1, "   ___________________                   \\______/");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  |___________________|                                      ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  |___________________|                                       ___________");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  |                _  |                                      |   _____   |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  |               | | |                                      |  ||   ||  |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  |               |_| |                    ____              | _||___||_ |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  |                   |                   /____\\             ||_________||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  |                   |                   __||__             |___________|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  |___________________|                  |      |                   |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  |___________________|                  |______|                   |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  |                   |                 /________\\                  |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "__|___________________|________________/          \\_________________|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                     ( )__________( )               |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                      |            |                |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                  ____|____________|_____           |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                 |        _\\||/_         |          |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                 |       |(_)(_)|        |__________|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                 |_______________________|       ");
    screen_area_puts(ge->map, str1);

  } else if (space_get_id(space) == 10) {
    sprintf(str1, "                                     ||                          ___/|\\_ ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                     ||                         /__|__|__\\");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                     ||                         \\_|__|__|_\\");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                    /  \\                         \\_|__|__|/");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                  __|  |__                                 ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                 /________\\                                 ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                 \\___\\/___/                                 ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "           ________");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "          |__|__|__\\");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "         /__|__|__|_\\");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "        |_|__|__|__|_|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "        \\_|__|/");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                                               _______");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                                              /  __  /|");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                                             / ()__|/ |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                                            /______/");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                                            |      |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                                            |      |");
    screen_area_puts(ge->map, str1);

  } else if (space_get_id(space) == 9) {
    sprintf(str1, " ________________________________________________________________________");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ||__|__|__||__|__|__||__|__|__||__|__|__||__|__|__||__|__|__||__|__|__||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ||__|__|__||__|__|__||__|__|__||__|__|__||__|__|__||__|__|__||__|__|__||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ||__|__|__||__|__|__||__|__|__||__|__|__||__|__|__||__|__|__||__|__|__||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||  |  |  ||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ||__|__|__||__|__|__||__|__|__||__|__|__||__|__|__||__|__|__||__|__|__||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                                     __/\\");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                                  __/'   |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                                 |__      \\");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                                    /      \\       /\\");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                                    \\       \\    _/ /");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                                     \\ | \\__ \\__/ _/");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                                     /_| /_______/");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                                    ");
    screen_area_puts(ge->map, str1);

  } else if (space_get_id(space) == 7) {
    sprintf(str1, "     ________");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "    / / || \\ \\");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "   /_/__||__\\_\\");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  __|_|____|_|__");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " |_|__|__|__|__||");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ||__|__|__|__|_|        ___                                        ___");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "    \\ |__|_| /          / /||                                      ||\\ \\");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "_____\\|_|__|/___________\\/_||______________________________________||_\\/__");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "      |__|_|               | |                                    | |");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "      |_|__|               | |                                    | | ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "______|__|_|_______________| |____________________________________| |______ ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "\\/\\/\\/|_|__|\\/\\/\\/\\/\\/\\/\\/\\| |_________________||_________________| |\\/\\/\\/ ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "/\\/\\/\\|__|_|/\\/\\/\\/\\/\\/\\/\\/| |_________________||_________________| |/\\/\\/\\ ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "\\/\\/\\/|_|__|\\/\\/\\/\\/\\/\\/\\/\\| |_________________||_________________| |\\/\\/\\/ ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "/\\/\\/\\|__|_|/\\/\\/\\/\\/\\/\\/\\/| |_________________||_________________| |/\\/\\/\\ ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "\\/\\/\\/|_|__|\\/\\/\\/\\/\\/\\/\\/\\| |_________________||_________________| |\\/\\/\\/ ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "/\\/\\/\\|__|_|/\\/\\/\\/\\/\\/\\/\\/| |_________________||_________________| |/\\/\\/\\ ");
    screen_area_puts(ge->map, str1);
  } else if (space_get_id(space) == 2) {
    sprintf(str1, " ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, " ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                  ____________  ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                                  __ _  _______   ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                              ___';,_____     __  ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "                ____'',;:::clodxxxkkxdoolc:,'''_  ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  ||,;,',;;:ccloddxxxxxxxxkxxkkkkkkkkOOOOOkdo:_  ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  || || || dddxxxxxxxxxkkkkkkkkkOkxdolc:,'_____  ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  ||    || || ddxxkkkkkkkkxxdlc:;,___        ||   ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  ||       || cxkdol:;,'___                 ||   ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "  ||         \\__                           ||  ");
    screen_area_puts(ge->map, str1);
    sprintf(str1, "             ||                                  ");
    screen_area_puts(ge->map, str1);
    printf(str1, "              ||                                  ");
    screen_area_puts(ge->map, str1);
    printf(str1, "              ||                                  ");
    screen_area_puts(ge->map, str1);
  }

  screen_paint(game_get_player_index_from_turn(game) % 7);
  printf("prompt:> ");
}
