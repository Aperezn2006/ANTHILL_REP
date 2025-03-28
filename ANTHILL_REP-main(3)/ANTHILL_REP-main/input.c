#include "input.h"
#include "game_actions.h"



Game_Input game_input = {0};  // Initialize input state

/* Function to update the key state */
static void update_key_state(Uint8 current_state, Key_State *key_state) {
    if (current_state) {
        if (*key_state > 0)
            *key_state = KS_HELD;
        else
            *key_state = KS_PRESSED;
    } else {
        *key_state = KS_UNPRESSED;
    }
}

/* Reads input from SDL and updates game_input */
#include <stdio.h>  // Include for debugging

void input_update() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                update_key_state(1, &game_input.escape);
                break;
            case SDL_KEYDOWN:
                if (event.key.repeat == 0) {
                    switch (event.key.keysym.sym) {
                        case SDLK_w: 
                            update_key_state(1, &game_input.up); 
                            printf("W Pressed\n");
                            break;
                        case SDLK_s: 
                            update_key_state(1, &game_input.down); 
                            printf("S Pressed\n");
                            break;
                        case SDLK_a: 
                            update_key_state(1, &game_input.left); 
                            printf("A Pressed\n");
                            break;
                        case SDLK_d: 
                            update_key_state(1, &game_input.right); 
                            printf("D Pressed\n");
                            break;
                        case SDLK_ESCAPE: 
                            update_key_state(1, &game_input.escape); 
                            printf("Escape Pressed\n");
                            break;
                    }
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_w: update_key_state(0, &game_input.up); break;
                    case SDLK_s: update_key_state(0, &game_input.down); break;
                    case SDLK_a: update_key_state(0, &game_input.left); break;
                    case SDLK_d: update_key_state(0, &game_input.right); break;
                    case SDLK_ESCAPE: update_key_state(0, &game_input.escape); break;
                }
                break;
        }
    }
}
