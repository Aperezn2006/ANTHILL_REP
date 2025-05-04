#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "game.h"

Id game_rules_get_tunnel_access(Game *game, Id current_location);

Bool is_in_tunnel(Id location) {
  int i;
  Id tunnel_spaces[21] = {10, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139};
  for (i = 0; i < 21; i++) {
    if (location == tunnel_spaces[i]) {
      return TRUE;
    }
  }
  return FALSE;
}

void close_links_in_space(Game *game, Space *space) {
  int directions[] = {N, S, E, W, U, D};
  int i;

  for (i = 0; i < 6; i++) {
    Link *link = game_get_link_at_direction(game, space_get_id(space), directions[i]);
    if (link) {
      link_set_open(link, FALSE);
    }
  }
}

void open_links_in_space(Game *game, Space *space) {
  int directions[] = {N, S, E, W, U, D};
  int i;

  for (i = 0; i < 6; i++) {
    Link *link = game_get_link_at_direction(game, space_get_id(space), directions[i]);
    if (link) {
      link_set_open(link, TRUE);
    }
  }
}

Bool object_is_digging_tool(Object *obj) {
  int i;
  Id digging_tools[] = {30, 31, 32, 33, 34, 35};
  size_t num_tools = sizeof(digging_tools) / sizeof(digging_tools[0]);
  if (!obj) {
    printf("[DEBUG] object_is_digging_tool: objeto es NULL\n");
    return FALSE;
  }

  printf("[DEBUG] object_is_digging_tool: comprobando objeto con ID %ld\n", object_get_id(obj));

  for (i = 0; i < num_tools; i++) {
    if (object_get_id(obj) == digging_tools[i]) {
      printf(
          "[DEBUG] object_is_digging_tool: herramienta de excavación "
          "reconocida (ID %ld)\n",
          digging_tools[i]);
      return TRUE;
    }
  }
  printf("[DEBUG] object_is_digging_tool: no es herramienta de excavación\n");
  return FALSE;
}

Bool space_is_tunnel(Id space_id) {
  int i;
  Id tunnel_spaces[] = {10, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139};
  size_t num_spaces = sizeof(tunnel_spaces) / sizeof(tunnel_spaces[0]);

  printf("[DEBUG] space_is_tunnel: comprobando espacio ID %ld\n", space_id);

  for (i = 0; i < num_spaces; i++) {
    if (space_id == tunnel_spaces[i]) {
      printf("[DEBUG] space_is_tunnel: espacio %ld es túnel\n", space_id);
      return TRUE;
    }
  }

  printf("[DEBUG] space_is_tunnel: espacio %ld NO es túnel\n", space_id);
  return FALSE;
}

Status game_rules_process_digging(Game *game, Command *cmd) {
  Object *obj = NULL;
  const char *used_obj = NULL;
  Id obj_id;
  Id current_space;
  Link *closed_links[6];
  int directions[] = {N, S, E, W, U, D};
  int num_closed_links = 0;
  int i;

  printf("[DEBUG] game_rules_process_digging: iniciando procesamiento\n");

  if (!cmd) {
    printf("[DEBUG] No hay comando\n");
    return ERROR;
  }

  printf("[DEBUG] Comando recibido: código=%d, resultado=%d\n", command_get_code(cmd), command_get_result(cmd));

  if (command_get_result(cmd) != OK) {
    return ERROR;
  }

  used_obj = command_get_word(cmd);
  if (!used_obj || !strlen(used_obj)) {
    printf("[DEBUG] Palabra del comando inválida o vacía\n");
    return ERROR;
  }

  printf("[DEBUG] Objeto usado en el comando: '%s'\n", used_obj);

  obj_id = game_get_object_id_from_name(game, used_obj);
  obj = game_get_object_from_id(game, obj_id);

  printf("[DEBUG] Objeto ID: %ld, puntero: %p\n", obj_id, (void *)obj);

  if (!obj || !object_is_digging_tool(obj)) {
    printf(
        "[DEBUG] El objeto no es válido o no es una herramienta de "
        "excavación\n");
    return ERROR;
  }

  current_space = game_get_player_location(game);
  printf("[DEBUG] Ubicación actual del jugador: %ld\n", current_space);

  if (!space_is_tunnel(current_space)) {
    printf("No puedes excavar aquí, solo en espacios del túnel.\n");
    return ERROR;
  }

  for (i = 0; i < 6; i++) {
    Link *link = game_get_link_at_direction(game, current_space, directions[i]);
    printf("[DEBUG] Buscando enlace cerrado en dirección %d\n", directions[i]);
    if (link) {
      printf("[DEBUG] Enlace encontrado: ID %ld, abierto=%d\n", link_get_id(link), link_get_open(link));
      if (!link_get_open(link)) {
        closed_links[num_closed_links++] = link;
      }
    } else {
      printf("[DEBUG] No se encontró enlace en dirección %d\n", directions[i]);
    }
  }

  if (num_closed_links > 0) {
    int chosen_index = rand() % num_closed_links;
    printf("[DEBUG] Número de enlaces cerrados: %d, seleccionado índice: %d\n", num_closed_links, chosen_index);
    link_set_open(game_get_link_by_id(game, link_get_id(closed_links[chosen_index])), TRUE);
    printf("Has abierto un enlace en la dirección %d (ID enlace: %ld).\n", directions[chosen_index], link_get_id(closed_links[chosen_index]));
  } else {
    printf("No hay enlaces cerrados que se puedan abrir aquí.\n");
  }

  printf("[DEBUG] game_rules_process_digging: terminado correctamente\n");
  return OK;
}

void move_guards(Game *game) {
  Character *guard = NULL;
  Player *player = NULL;
  int player_health = 0;
  int guard_health = 0;
  Id guard_loc, player_loc;
  Space *current_space = NULL;
  Id guard_ids[] = {62, 63, 64};
  Id cell_rooms[] = {124, 125}; /* Celdas de castigo y laboratorio */
  Id guard_paths[][15] = {
      {140, 131, 130, 132, 133, 140, NO_ID}, /* Guardia 1 */
      {134, 126, 120, 134, NO_ID},           /* Guardia 2 */
      {127, 128, 129, 121, 122, 127, NO_ID}  /* Guardia 3 */
  };
  static int path_indices[] = {0, 0, 0}; /* Índices actuales para cada guardia */
  int num_guards = 3;
  int i = 0, j = 0;
  Id tunnel_spaces[17] = {10, 120, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139};
  Id next_room = NO_ID;
  Id north, south, east, west;
  Id possible_moves[4];
  int valid_moves = 0;
  Id valid_destinations[4] = {NO_ID, NO_ID, NO_ID, NO_ID};
  Link *link = NULL;
  Id new_room = NO_ID;
  Space *new_space = NULL;
  Space *next_space = NULL;

  player = game_get_current_player(game);
  player_loc = game_get_player_location(game);

  for (i = 0; i < num_guards; i++) {
    guard = game_get_character(game, guard_ids[i]);
    guard_loc = game_get_character_location(game, guard_ids[i]);
    current_space = game_get_space(game, guard_loc);

    if (!guard || !current_space) continue;

    if ((guard_loc == player_loc) && is_in_tunnel(guard_loc) == FALSE) {
      if ((rand() % 100) < 30) {
        int cell_index = rand() % 2;
        Id cell_id = cell_rooms[cell_index];
        printf("[DEBUG] Guardia %ld encontró al jugador, lo manda a celda %ld\n", guard_ids[i], cell_id);
        game_set_player_location(game, cell_id);
      }
    }

    /* 1. Si el jugador y el guardia están en el mismo espacio del túnel */
    if (guard_loc == player_loc && is_in_tunnel(guard_loc)) {
      char message[256];
      sprintf(message, "[!] A guard has detected you in the tunnel, currently %ld", guard_loc);
      game_set_message(game, message);

      close_links_in_space(game, current_space); /* Ahora sí se ejecuta */
      printf("[DEBUG] Enlace cerrado en el túnel\n");

      player_health = player_get_health(player);
      guard_health = character_get_health(guard);

      if (guard_health <= 0 && player_health > 0) {
        printf("[DEBUG] Guardia %ld muerto\n", guard_ids[i]);
        game_set_message(game, "Guard is dead");
        open_links_in_space(game, current_space);
      } else if (guard_health > 0 && player_health <= 0) {
        game_set_message(game, "Player is dead");
        game_set_finished(game, TRUE);
      }

      continue; /* Después de cerrar/enfrentar */
    }

    /* 2. Movimiento según camino predefinido */
    next_room = guard_paths[i][path_indices[i]];

    for (j = 0; j < 17; j++) {
      if (space_get_id(current_space) == tunnel_spaces[j]) {
        char message[256];
        sprintf(message, "[!] A guard has accessed the tunnel, currently %ld", guard_loc);
        game_set_message(game, message);
        next_room = tunnel_spaces[j++];
      }
    }

    if (next_room != NO_ID && next_room != guard_loc) {
      next_space = game_get_space(game, next_room);
      link = game_get_link_by_id(game, game_get_connection(game, guard_loc, next_room));

      if ((link && link_get_open(link)) || (!link)) {
        if (space_remove_character(current_space, guard_ids[i]) == OK && space_add_character(next_space, guard_ids[i]) == OK) {
          printf("[DEBUG] Guardia %ld movido de %ld a %ld (camino predefinido)\n", guard_ids[i], guard_loc, next_room);

          /* Actualizar ubicación del guardia */
          guard_loc = next_room;
          current_space = next_space;

          path_indices[i]++;
          if (guard_paths[i][path_indices[i]] == NO_ID) {
            path_indices[i] = 0;
          }
          continue;
        }
      } else {
        path_indices[i]++;
        if (guard_paths[i][path_indices[i]] == NO_ID) {
          path_indices[i] = 0;
        }
      }
    }

    /* 3. Movimiento aleatorio */
    north = game_get_north(game, guard_loc);
    possible_moves[0] = north;
    south = game_get_south(game, guard_loc);
    possible_moves[1] = south;
    east = game_get_east(game, guard_loc);
    possible_moves[2] = east;
    west = game_get_west(game, guard_loc);
    possible_moves[3] = west;

    for (j = 0; j < 4; j++) {
      if (possible_moves[j] != NO_ID) {
        link = game_get_link_at_direction(game, guard_loc, possible_moves[j]);
        if ((link && link_get_open(link)) || (!link)) {
          valid_destinations[valid_moves++] = possible_moves[j];
        }
      }
    }

    if (valid_moves > 0) {
      new_room = valid_destinations[rand() % valid_moves];
      new_space = game_get_space(game, new_room);

      if (space_remove_character(current_space, guard_ids[i]) == OK && space_add_character(new_space, guard_ids[i]) == OK) {
        printf("[DEBUG] Guardia %ld movido de %ld a %ld (aleatorio)\n", guard_ids[i], guard_loc, new_room);

        /* Actualizar ubicación del guardia */
        guard_loc = new_room;
        current_space = new_space;
      }
      path_indices[i]--;
    }
  }
}

void update_game(Game *game, Command *cmd) {
  Character *character = game_get_character(game, 31);
  Id open_link = 123;

  printf("[DEBUG] update_game: actualizando juego\n");
  move_guards(game);
  if (cmd) {
    printf(
        "[DEBUG] Comando recibido: código=%d, palabra='%s', conector=%d, "
        "destino='%s'\n",
        command_get_code(cmd), command_get_word(cmd), command_get_connector(cmd), command_get_destiny(cmd));
  } else {
    printf("[DEBUG] No se ha recibido ningún comando válido.\n");
  }

  if (character_get_health(character) == 0) {
    printf("[DEBUG] Personaje 31 muerto, abriendo enlace %ld\n", open_link);
    game_set_link_open(game, open_link, S);
  }

  if (command_get_code(cmd) == USE) {
    if (game_rules_process_digging(game, cmd) == ERROR) {
      printf("[DEBUG] Error al procesar la acción de excavar.\n");
    } else {
      printf("[DEBUG] Acción de excavar procesada correctamente.\n");
    }
  }
}