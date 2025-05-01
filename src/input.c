#include "input.h"

#include <stdio.h>

#include "game_actions.h"
#include "ray.h"

Game_Input game_input = {0};

void update_key_state(Uint8 current_state, Key_State *key_state) {
  if (current_state) {
    if (*key_state > 0)
      *key_state = KS_HELD;
    else
      *key_state = KS_PRESSED;
  } else {
    *key_state = KS_UNPRESSED;
  }
}

/* Para teclas que deben considerarse siempre como "presionadas de nuevo" */
void update_action_key_state(Uint8 current_state, Key_State *key_state) {
  if (current_state) {
    *key_state = KS_PRESSED;
  } else {
    *key_state = KS_UNPRESSED;
  }
}

void input_reset_movement_keys(void) {
  game_input.up = KS_UNPRESSED;
  game_input.down = KS_UNPRESSED;
  game_input.left = KS_UNPRESSED;
  game_input.right = KS_UNPRESSED;
}

void input_update(Game *game) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        update_key_state(1, &game_input.escape);
        break;

      case SDL_KEYDOWN:
        if (event.key.repeat == 0) {
          if (event.key.keysym.sym == SDLK_TAB) {
            game_toggle_inventory_vis(game);

            if (!game_get_inventory_vis(game)) {
              input_reset_movement_keys();
            }

          } else {
            if (game_get_inventory_vis(game)) {
              switch (event.key.keysym.sym) {
                case SDLK_w:
                case SDLK_UP:
                  update_key_state(1, &game_input.inventory_up);
                  break;
                case SDLK_s:
                case SDLK_DOWN:
                  update_key_state(1, &game_input.inventory_down);
                  break;
                case SDLK_g:
                  update_action_key_state(1, &game_input.drop);
                  break;
                case SDLK_q:
                  update_action_key_state(1, &game_input.inspect);
                  break;
                case SDLK_RETURN:
                  update_key_state(1, &game_input.inventory_confirm);
                  break;
                case SDLK_ESCAPE:
                  update_key_state(1, &game_input.inventory_cancel);
                  break;
                case SDLK_r:
                  update_action_key_state(1, &game_input.use);
                  printf("Presionada la tecla r (inventario activo)\n");
                  break;
                case SDLK_o:
                  update_action_key_state(1, &game_input.open);
                  break;
              }
            } else {
              switch (event.key.keysym.sym) {
                case SDLK_w:
                  update_key_state(1, &game_input.up);
                  break;
                case SDLK_s:
                  update_key_state(1, &game_input.down);
                  break;
                case SDLK_a:
                  update_key_state(1, &game_input.left);
                  break;
                case SDLK_d:
                  update_key_state(1, &game_input.right);
                  break;
                case SDLK_ESCAPE:
                  update_key_state(1, &game_input.escape);
                  break;
                case SDLK_e:
                  update_key_state(1, &game_input.attack);
                  break;
                case SDLK_c:
                  update_key_state(1, &game_input.chat);
                  break;
                case SDLK_SPACE:
                  update_key_state(1, &game_input.jump);
                  break;
                case SDLK_f:
                  update_key_state(1, &game_input.take);
                  break;
                case SDLK_g:
                case SDLK_q:
                  update_action_key_state(1, &game_input.inspect);
                  break;
                case SDLK_r:
                  update_action_key_state(1, &game_input.use);
                  printf("Presionada la tecla r\n");
                  break;
                case SDLK_o:
                  update_action_key_state(1, &game_input.open);
                  break;
              }
            }
          }
        }
        break;

      case SDL_KEYUP:
        if (game_get_inventory_vis(game)) {
          switch (event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_UP:
              update_key_state(0, &game_input.inventory_up);
              break;
            case SDLK_s:
            case SDLK_DOWN:
              update_key_state(0, &game_input.inventory_down);
              break;
            case SDLK_g:
              update_action_key_state(0, &game_input.drop);
              break;
            case SDLK_q:
              update_action_key_state(0, &game_input.inspect);
              break;
            case SDLK_RETURN:
              update_key_state(0, &game_input.inventory_confirm);
              break;
            case SDLK_ESCAPE:
              update_key_state(0, &game_input.inventory_cancel);
              break;
            case SDLK_r:
              update_action_key_state(0, &game_input.use);
              break;
            case SDLK_o:
              update_action_key_state(0, &game_input.open);
              break;
          }
        } else {
          switch (event.key.keysym.sym) {
            case SDLK_w:
              update_key_state(0, &game_input.up);
              break;
            case SDLK_s:
              update_key_state(0, &game_input.down);
              break;
            case SDLK_a:
              update_key_state(0, &game_input.left);
              break;
            case SDLK_d:
              update_key_state(0, &game_input.right);
              break;
            case SDLK_ESCAPE:
              update_key_state(0, &game_input.escape);
              break;
            case SDLK_e:
              update_key_state(0, &game_input.attack);
              break;
            case SDLK_c:
              update_key_state(0, &game_input.chat);
              break;
            case SDLK_SPACE:
              update_key_state(0, &game_input.jump);
              break;
            case SDLK_f:
              update_key_state(0, &game_input.take);
              break;
            case SDLK_g:
            case SDLK_q:
              update_action_key_state(0, &game_input.inspect);
              break;
            case SDLK_r:
              update_action_key_state(0, &game_input.use);
              break;
            case SDLK_o:
              update_action_key_state(0, &game_input.open);
              break;
          }
        }
        break;
    }
  }
}
