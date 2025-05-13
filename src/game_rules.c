#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "game.h"

/**
 * @brief
 * @author Rubén
 *
 * @param location
 * @return
 */
Bool alcantarillado(Id location);

/**
 * @brief It closes all the links surrounding a space
 * @author Rubén
 *
 * @param game a pointer to the game
 * @param space a pointer to the space
 */
void close_links_in_space(Game *game, Space *space);

/**
 * @brief It opens all the links surrounding a space
 * @author Rubén
 *
 * @param game a pointer to the game
 * @param space a pointer to the space
 */
void open_links_in_space(Game *game, Space *space);

/**
 * @brief It checks whether an object can be used to dig
 * @author Rubén
 *
 * @param obj a pointer to the object
 * @return TRUE if it is a digging tool, FALSE otherwise
 */
Bool object_is_digging_tool(Object *obj);

/**
 * @brief It checks whether a space is in the tunnel
 * @author Rubén
 *
 * @param space_id the id os the space
 * @return TRUE if it is a tunnel, FALSE otherwise
 */
Bool space_is_tunnel(Id space_id);

/**
 * @brief It gets the id of the space where a player can access the tunnel
 * @author Ana
 *
 * @param game a pointer to the game
 * @param current_location th current player's location
 * @return The id of the access
 */
Id game_rules_get_tunnel_access(Game *game, Id current_location);

/**
 * @brief It allows the player to dig
 * @author Rubén
 *
 * @param game a pointer to the game
 * @param cmd a pointer to the last command
 * @return OK if everything went well, ERROR otherwise
 */
Status game_rules_process_digging(Game *game, Command *cmd);

Status create_parachute(Game *game);

Status game_rules_process_use_parachute(Game *game, Id object_id);

/**
 * @brief It moves the guards (characters) and allows them to catch players in tunnels
 * @author Rubén
 *
 * @param game a pointer to the game
 */
void move_guards(Game *game);

Status update_game(Game *game, Command *cmd) {
  Character *character = game_get_character(game, 31);
  Id open_link = 123;
  Link *link = game_get_link_by_id(game, 106);
  Player *player = game_get_current_player(game);
  Id player_location = player_get_location(player);
  Link *link2 = game_get_link_by_id(game, 107);

  printf(":::::::::::::PLAYER IS IN %li\n", player_location);
  if (player_location == 204) {
    game_set_won(game, TRUE);
    game_set_finished(game, TRUE);
    return OK;
  }

  if (player_location == 6 && link_get_open(link) == FALSE) {
    if (game_get_current_player(game) == player) {
      game_increment_turn(game);
    }
  }

  if (link_get_open(link) == TRUE) {
    link_set_open(link2, TRUE);
  }

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
    const char *word = command_get_word(cmd);
    Id obj = game_get_object_id_from_name(game, word); /* Suponiendo que tienes esto */
    Object *object = game_get_object_from_id(game, obj);
    if (obj == 41) {
      game_rules_process_use_parachute(game, object_get_id(object));
    } else {
      game_rules_process_digging(game, cmd); /* Tu lógica anterior */
    }
  }
  if (create_parachute(game) == ERROR) {
    printf("[DEBUG] Error al crear el paracaídas.\n");
  }

  if (link_get_open(link) == TRUE) {
    link_set_open(link2, TRUE);
  }

  return OK;
}
Status game_rules_process_use_parachute(Game *game, Id object_id) {
  Player *player = game_get_current_player(game);
  Id current_space = player_get_location(player);
  int r;
  if (current_space != 141) {
    printf("[DEBUG] El jugador no está en la sala 141. No se puede usar el paracaídas aquí.\n");
    return ERROR;
  }

  if (!player_has_object(player, object_id)) {
    printf("[DEBUG] El jugador no tiene el paracaídas para usar.\n");
    return ERROR;
  }

  /* Eliminar el paracaídas del inventario */
  player_remove_object(player, object_id);
  printf("[DEBUG] Paracaídas usado. Determinando el resultado...\n");

  /* Probabilidad: 70% éxito */
  r = rand() % 100;
  if (r < 70) {
    printf("[DEBUG] ¡El jugador ha escapado con éxito usando el paracaídas!\n");
    /* Aquí puedes marcar el juego como ganado, ejemplo: */
    game_set_won(game, TRUE);
    game_set_finished(game, TRUE); /* Si tienes una función así */
    return OK;
  } else {
    printf("[DEBUG] El paracaídas se ha roto... ¡el jugador ha perdido!\n");
    game_set_finished(game, TRUE); /* Si tienes una función así */
    return ERROR;
  }
}

Status create_parachute(Game *game) {
  Id required_ids[] = {37, 38, 39, 40}; /* Tela, Cuerda, Varillas, CintaAdhesiva */
  const int required_count = 4;
  Bool has_all = TRUE;
  Player *player = game_get_current_player(game);
  int i;
  Id parachute_id = 41; /* Asegúrate de que esté definido en tu .dat */
  int player_object_count = player_get_num_objects(player);

  printf("[DEBUG] Comprobando si el jugador tiene todos los objetos necesarios para crear el paracaídas\n");

  /* Mostrar todos los objetos actuales del jugador */
  printf("[DEBUG] Objetos actuales del jugador (%d):\n", player_object_count);
  for (i = 0; i < player_object_count; i++) {
    Id obj_id = player_get_object_from_index(player, i);
    printf("  [DEBUG] - Objeto %d: ID = %ld\n", i, obj_id);
  }

  /* Comprobar si tiene todos los objetos requeridos */
  for (i = 0; i < required_count; i++) {
    if (!player_has_object(player, required_ids[i])) {
      printf("[DEBUG] FALTA el objeto requerido con ID = %ld\n", required_ids[i]);
      has_all = FALSE;
    } else {
      printf("[DEBUG] Objeto requerido con ID = %ld encontrado\n", required_ids[i]);
    }
  }

  if (has_all == TRUE) {
    printf("[DEBUG] Todos los objetos requeridos están presentes. Procediendo a eliminarlos...\n");
    for (i = 0; i < required_count; i++) {
      if (player_remove_object(player, required_ids[i]) == OK) {
        printf("[DEBUG] Objeto con ID = %ld eliminado del inventario del jugador\n", required_ids[i]);
      } else {
        printf("[DEBUG] ERROR al eliminar el objeto con ID = %ld\n", required_ids[i]);
      }
    }

    if (player_add_object(player, parachute_id) == OK) {
      printf("[DEBUG] Paracaídas (ID = %ld) añadido al inventario del jugador\n", parachute_id);
      return OK;
    } else {
      printf("[DEBUG] ERROR al añadir el paracaídas (ID = %ld) al inventario del jugador\n", parachute_id);
      return ERROR;
    }
  }

  printf("[DEBUG] No se han cumplido los requisitos para crear el paracaídas\n");
  return ERROR;
}

Id game_rules_get_tunnel_access(Game *game, Id current_location);

Bool alcantarillado(Id location) {
  int i;
  Id tunnel_spaces[22] = {7, 10, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139};
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
  Id tunnel_spaces[] = {11, 200, 201, 202, 203};
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
  int i, num_chars, guardias_presentes;
  Character *character = NULL;
  Id player_loc, new_location;
  Space *space = NULL;
  const Id possible_locations[] = {120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139};
  const int num_possible_locations = 20;

  if (!game) {
    return;
  }

  player_loc = game_get_player_location(game);

  space = game_get_space(game, player_loc);
  if (!space) {
    return;
  }

  /* Si estamos en una sala del alcantarillado */
  if (alcantarillado(space_get_id(space))) {
    num_chars = space_get_num_characters(space);

    guardias_presentes = 0;

    /* Ver si hay guardias vivos */
    for (i = 0; i < num_chars; i++) {
      Id char_id = space_get_character_from_index(space, i);
      character = game_get_character(game, char_id);

      if (!character) {
        continue;
      }

      /* IDs de guardias = 62, 63, 64 */
      if ((char_id == 62 || char_id == 63 || char_id == 64) && character_get_health(character) > 0) {
        guardias_presentes = 1;
        close_links_in_space(game, space);
        break;
      }
    }

    /* Si no hay guardias vivos, abrir enlaces y mover personajes */
    if (!guardias_presentes) {
      open_links_in_space(game, space);

      /* Mover personajes (excepto guardias) */
      for (i = 0; i < num_chars; i++) {
        Id char_id = space_get_character_from_index(space, i);
        character = game_get_character(game, char_id);

        if (!character || char_id == 62 || char_id == 63 || char_id == 64) {
          continue;
        }

        if (character_get_health(character) <= 0) {
          continue;
        }

        new_location = possible_locations[rand() % num_possible_locations];

        space_remove_character(space, char_id);
        space_add_character(game_get_space(game, new_location), char_id);
      }
    }
  }
}
