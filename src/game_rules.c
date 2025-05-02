#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

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
      printf("[DEBUG] object_is_digging_tool: herramienta de excavación reconocida (ID %ld)\n", digging_tools[i]);
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
    printf("[DEBUG] El objeto no es válido o no es una herramienta de excavación\n");
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

void update_game(Game *game, Command *cmd) {
  Character *character = game_get_character(game, 31);
  Id open_link = 123;

  printf("[DEBUG] update_game: actualizando juego\n");

  if (cmd) {
    printf("[DEBUG] Comando recibido: código=%d, palabra='%s', conector=%d, destino='%s'\n", command_get_code(cmd), command_get_word(cmd),
           command_get_connector(cmd), command_get_destiny(cmd));
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